/* Copyright (c) 2021 Xie Meiyi(xiemeiyi@hust.edu.cn) and OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2021/5/13.
//

#include <limits.h>
#include <string.h>
#include <algorithm>

#include "storage/common/table.h"
#include "storage/common/table_meta.h"
#include "common/log/log.h"
#include "common/lang/string.h"
#include "storage/default/disk_buffer_pool.h"
#include "storage/common/record_manager.h"
#include "storage/common/condition_filter.h"
#include "storage/common/meta_util.h"
#include "storage/common/index.h"
#include "storage/common/bplus_tree_index.h"
#include "storage/trx/trx.h"
#include "storage/common/date.h"
#include <stdio.h>
#include "storage/common/bitmap.h"

Table::Table() : 
    data_buffer_pool_(nullptr),
    file_id_(-1),
    record_handler_(nullptr) {
}

Table::~Table() {
  delete record_handler_;
  record_handler_ = nullptr;

  if (data_buffer_pool_ != nullptr && file_id_ >= 0) {
    data_buffer_pool_->close_file(file_id_);
    data_buffer_pool_ = nullptr;
  }

  LOG_INFO("Table has been closed: %s", name());
}

RC Table::create(const char *path, const char *name, const char *base_dir, int attribute_count, const AttrInfo attributes[]) {

  if (nullptr == name || common::is_blank(name)) {
    LOG_WARN("Name cannot be empty");
    return RC::INVALID_ARGUMENT;
  }
  LOG_INFO("Begin to create table %s:%s", base_dir, name);

  if (attribute_count <= 0 || nullptr == attributes) {
    LOG_WARN("Invalid arguments. table_name=%s, attribute_count=%d, attributes=%p",
        name, attribute_count, attributes);
    return RC::INVALID_ARGUMENT;
  }

  RC rc = RC::SUCCESS;

  // 使用 table_name.table记录一个表的元数据
  // 判断表文件是否已经存在

  int fd = ::open(path, O_WRONLY | O_CREAT | O_EXCL | O_CLOEXEC, 0600);
  if (-1 == fd) {
    if (EEXIST == errno) {
      LOG_ERROR("Failed to create table file, it has been created. %s, EEXIST, %s",
                path, strerror(errno));
      return RC::SCHEMA_TABLE_EXIST;
    }
    LOG_ERROR("Create table file failed. filename=%s, errmsg=%d:%s", 
       path, errno, strerror(errno));
    return RC::IOERR;
  }

  close(fd);

  // 创建文件
  if ((rc = table_meta_.init(name, attribute_count, attributes)) != RC::SUCCESS) {
    LOG_ERROR("Failed to init table meta. name:%s, ret:%d", name, rc);
    return rc; // delete table file
  }

  std::fstream fs;
  fs.open(path, std::ios_base::out | std::ios_base::binary);
  if (!fs.is_open()) {
    LOG_ERROR("Failed to open file for write. file name=%s, errmsg=%s", path, strerror(errno));
    return RC::IOERR;
  }

  // 记录元数据到文件中
  table_meta_.serialize(fs);
  fs.close();

  std::string data_file = std::string(base_dir) + "/" + name + TABLE_DATA_SUFFIX;
  data_buffer_pool_ = theGlobalDiskBufferPool();
  rc = data_buffer_pool_->create_file(data_file.c_str());
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to create disk buffer pool of data file. file name=%s", data_file.c_str());
    return rc;
  }

  rc = init_record_handler(base_dir);

  base_dir_ = base_dir;
  LOG_INFO("Successfully create table %s:%s", base_dir, name);
  return rc;
}

RC Table::drop(const char *path, const char *name, const char *base_dir){
  DiskBufferPool* buffer_pool = theGlobalDiskBufferPool();
  
  //删除table元数据文件
  int ok = ::remove(path);
  if(ok!=0){
    LOG_ERROR("Failed to delete %s when drop %s.",path,name);
    return RC::IOERR;
  }
  //删除数据文件
  std::string data_file = std::string(base_dir) + "/" + name + TABLE_DATA_SUFFIX;
  // int data_file_id = buffer_pool->get_file_id(data_file.c_str());
  // buffer_pool->close_file(data_file_id);
  ok = ::remove(data_file.c_str());
  if(ok!=0){
    LOG_ERROR("Failed to delete %s when drop %s.",path,name);
    return RC::IOERR;
  }
  //删除索引文件
  for(Index* index :this->indexes_){
    const char* indexname = (index->index_meta()).name();
    // int file_id = buffer_pool->get_file_id(indexname);
    // buffer_pool->close_file(file_id);
    std::string indexFile = index_data_file(base_dir,name,indexname);
    ok = ::remove(indexFile.c_str());
    if(ok!=0){
      LOG_ERROR("Failed to delete %s when drop %s.",path,name);
      return RC::IOERR;
    }
  }
  return RC::SUCCESS;
  //删除缓冲池中数据文件TODO
}

RC Table::open(const char *meta_file, const char *base_dir) {
  // 加载元数据文件
  std::fstream fs;
  std::string meta_file_path = std::string(base_dir) + "/" + meta_file;
  fs.open(meta_file_path, std::ios_base::in | std::ios_base::binary);
  if (!fs.is_open()) {
    LOG_ERROR("Failed to open meta file for read. file name=%s, errmsg=%s", meta_file, strerror(errno));
    return RC::IOERR;
  }
  if (table_meta_.deserialize(fs) < 0) {
    LOG_ERROR("Failed to deserialize table meta. file name=%s", meta_file);
    return RC::GENERIC_ERROR;
  }
  fs.close();

  // 加载数据文件
  RC rc = init_record_handler(base_dir);

  base_dir_ = base_dir;

  const int index_num = table_meta_.index_num();
  for (int i = 0; i < index_num; i++) {
    const IndexMeta *index_meta = table_meta_.index(i);
    const FieldMeta *field_meta = table_meta_.field(index_meta->field());
    if (field_meta == nullptr) {
      LOG_PANIC("Found invalid index meta info which has a non-exists field. table=%s, index=%s, field=%s",
                name(), index_meta->name(), index_meta->field());
      return RC::GENERIC_ERROR;
    }

    BplusTreeIndex *index = new BplusTreeIndex();
    std::string index_file = index_data_file(base_dir, name(), index_meta->name());
    rc = index->open(index_file.c_str(), *index_meta, *field_meta);
    if (rc != RC::SUCCESS) {
      delete index;
      LOG_ERROR("Failed to open index. table=%s, index=%s, file=%s, rc=%d:%s",
                name(), index_meta->name(), index_file.c_str(), rc, strrc(rc));
      return rc;
    }
    indexes_.push_back(index);
  }
  return rc;
}

RC Table::commit_insert(Trx *trx, const RID &rid) {
  Record record;
  RC rc = record_handler_->get_record(&rid, &record);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  return trx->commit_insert(this, record);
}

RC Table::rollback_insert(Trx *trx, const RID &rid) {

  Record record;
  RC rc = record_handler_->get_record(&rid, &record);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  // remove all indexes
  rc = delete_entry_of_indexes(record.data, rid, false);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to delete indexes of record(rid=%d.%d) while rollback insert, rc=%d:%s",
              rid.page_num, rid.slot_num, rc, strrc(rc));
  } else {
    rc = record_handler_->delete_record(&rid);
  }
  return rc;
}

RC Table::insert_record(Trx *trx, Record *record) {
  RC rc = RC::SUCCESS;
  if (trx != nullptr) {
    trx->init_trx_info(this, *record);
  }
  rc = record_handler_->insert_record(record->data, table_meta_.record_size(), &record->rid);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Insert record failed. table name=%s, rc=%d:%s", table_meta_.name(), rc, strrc(rc));
    return rc;
  }

  if (trx != nullptr) {
    rc = trx->insert_record(this, record);
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Failed to log operation(insertion) to trx");

      RC rc2 = record_handler_->delete_record(&record->rid);
      if (rc2 != RC::SUCCESS) {
        LOG_PANIC("Failed to rollback record data when insert index entries failed. table name=%s, rc=%d:%s",
                  name(), rc2, strrc(rc2));
      }
      return rc;
    }
  }
  rc = insert_entry_of_indexes(record->data, record->rid);
  if (rc != RC::SUCCESS) {
    RC rc2 = delete_entry_of_indexes(record->data, record->rid, true);
    if (rc2 != RC::SUCCESS) {
      LOG_PANIC("Failed to rollback index data when insert index entries failed. table name=%s, rc=%d:%s",
                name(), rc2, strrc(rc2));
    }
    rc2 = record_handler_->delete_record(&record->rid);
    if (rc2 != RC::SUCCESS) {
      LOG_PANIC("Failed to rollback record data when insert index entries failed. table name=%s, rc=%d:%s",
                name(), rc2, strrc(rc2));
    }
    return rc;
  }
  return rc;
}
RC Table::insert_record(Trx *trx, int value_num, const Value *values) {
  LOG_TRACE("enter");
  if (value_num <= 0 || nullptr == values ) {
    LOG_ERROR("Invalid argument. value num=%d, values=%p", value_num, values);
    return RC::INVALID_ARGUMENT;
  }

  char *record_data;
  RC rc = make_record(value_num, values, record_data);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to create a record. rc=%d:%s", rc, strrc(rc));
    if(trx!= nullptr) {
      trx->rollback();
    }
    return rc;
  }

  Record record;
  record.data = record_data;
  // record.valid = true;
  rc = insert_record(trx, &record);
  if(rc!=RC::SUCCESS && trx != nullptr) {
    trx->rollback();
  }
  delete[] record_data;
  LOG_TRACE("exit");
  return rc;
}

const char *Table::name() const {
  return table_meta_.name();
}

const TableMeta &Table::table_meta() const {
  return table_meta_;
}

RC Table::make_record(int value_num, const Value *values, char * &record_out) {
  LOG_TRACE("in make record");
  // 检查字段类型是否一致 null is not count
  if (value_num + table_meta_.sys_field_num()+1 != table_meta_.field_num()) {
    // printf("%d!=%d\n", value_num + table_meta_.sys_field_num(), table_meta_.field_num());
    return RC::SCHEMA_FIELD_MISSING;
  }

  const int normal_field_start_index = table_meta_.sys_field_num();
  // type check && skip first null
  // because null field at first, so i+1 is the field inserted
  for (int i = 0; i < value_num; i++) {
    const FieldMeta *field = table_meta_.field(i + 1 + normal_field_start_index);
    const Value &value = values[i];
    // TODO may be wrong in compare NULL
    if(value.type == NULLS){
      if(field->nullable()==0){
         LOG_ERROR("Can't be null. field name=%s, type=%d, but given=NULL",
          field->name(), field->type());
        return RC::SCHEMA_FIELD_TYPE_MISMATCH;
      }
    }else{
      if (field->type() != value.type) {
        // if dates or chars
        if(field->type()==DATES&&value.type==CHARS){
          continue;
        }
        if(field->type()==TEXT_PAGE_NUM && value.type==CHARS) {
          continue;
        }
        LOG_ERROR("Invalid value type. field name=%s, type=%d, but given=%d",
          field->name(), field->type(), value.type);
        return RC::SCHEMA_FIELD_TYPE_MISMATCH;
      }
    }
  }
  // 复制所有字段的值
  int record_size = table_meta_.record_size();
  LOG_DEBUG("record size is %d",record_size);
  char *record = new char [record_size];
  memset(record,0,record_size);
  const FieldMeta * null_field = table_meta_.field("null_field");
  int bitmap_offset = null_field->offset();
  int bitmap_len = null_field->len();
  Bitmap &bitmap = Bitmap::get_instance();
  char buf[bitmap_len];
  // printf("set bitmap offset %d\n",bitmap_offset);
  // printf("normal_field_start_index %d\n",normal_field_start_index);
  for (int i = 0; i < value_num; i++) {
    // skip null field
    const FieldMeta *field = table_meta_.field(i + 1 + normal_field_start_index);
    const Value &value = values[i];
    // TODO memory leakage
    if(value.type == NULLS){
      bitmap.set_bit_at_index_null(record+bitmap_offset, i, buf);
    }else{
      bitmap.set_bit_at_index_not_null(record+bitmap_offset, i, buf);
      if(field->type()==DATES){
          Date &date = Date::get_instance();
          int date_int = date.date_to_int((const char*)value.data);
          // if wrong date format
          if(date_int < 0){
            LOG_ERROR("Wrong date format Invalid date type. field name=%s, type=%d, but given=%d",
            field->name(), field->type(), value.type);
            return RC::SCHEMA_FIELD_TYPE_MISMATCH;
          }else{
            memcpy(record + field->offset(), &date_int, field->len());
          }
      } else if(field->type() == TEXT_PAGE_NUM) {
        //分配两个新页面用来保存text数据，把两个page的num存到字段中
        RC ret;
        char text_buf[8];
        for(int i=0;i<2;++i) {
          BPPageHandle page_handle;
          page_handle.open=false;
          int count=0;
          if((ret=data_buffer_pool_->get_page_count(file_id_,&count))!=RC::SUCCESS) {
            LOG_ERROR("can't get file %d for insert text",file_id_);
            return ret;
          }
          LOG_DEBUG("file %d page count is %d",file_id_,count);
          //找一个空闲的text data页面
          for(int p=1;p<count;++p) {
            if ((ret = data_buffer_pool_->get_this_page(file_id_,p, &page_handle)) != RC::SUCCESS) {
              LOG_ERROR("Failed to allocate page when inserting text data. file_it:%d, ret:%d",
                        file_id_, ret);
              return ret;
            }
            auto* page_header_ = (PageHeader*)(page_handle.frame->page.data);
            if(page_header_->record_capacity == 1 && page_header_->record_num == 0) {
              LOG_DEBUG("get a empty text data page[%d] for insert text data",p);
              break;
            }
            LOG_DEBUG("get a page[%d] for insert text data,but it's capacity is %d,num is %d",p,page_header_->record_capacity,page_header_->record_num );
            data_buffer_pool_->unpin_page(&page_handle);

          }
          //如果找不到就分配一个
          if(!page_handle.open) {
            LOG_DEBUG("can't get a empty page, allocate a new page");
            if ((ret = data_buffer_pool_->allocate_page(file_id_, &page_handle)) != RC::SUCCESS) {
              LOG_ERROR("Failed to allocate page when inserting text data. file_it:%d, ret:%d",
                        file_id_, ret);
              return ret;
            }

          }
          //0号页面好像有啥用，不清楚，跳过这一页
          if(page_handle.frame->page.page_num == 0 ){
            LOG_DEBUG("page num is 0, can't use this page");
            data_buffer_pool_->unpin_page(&page_handle);
            if ((ret = data_buffer_pool_->allocate_page(file_id_, &page_handle)) != RC::SUCCESS) {
              LOG_ERROR("Failed to allocate page when inserting text data. file_it:%d, ret:%d",
                        file_id_, ret);
              return ret;
            }
          }

          PageNum current_page_num = page_handle.frame->page.page_num;
          auto* page_header_ = (PageHeader*)(page_handle.frame->page.data);
          LOG_DEBUG("text data is inserted into page:%d",current_page_num);
          page_header_->record_capacity=1;
          page_header_->record_num=1;
          page_header_->record_size=2048;
          page_header_->record_real_size=2048;
          page_header_->first_record_offset=sizeof(PageHeader);
          memcpy(page_handle.frame->page.data+page_header_->first_record_offset, (char*)value.data+i*2048, 2048);
          memcpy(text_buf+i*4,&current_page_num,4);
          data_buffer_pool_->mark_dirty(&page_handle);
          if((ret=data_buffer_pool_->unpin_page(&page_handle))!=RC::SUCCESS) {
            LOG_ERROR("Failed to unpin page when inserting text data. file_it:%d, ret:%d",
                      file_id_, ret);
            return ret;
          }
          //memcpy(&p1,&current_page_num,4);
          //LOG_DEBUG("text data is inserted into page:[%d]",*(int*)(text_buf+4*i));
        }
        LOG_DEBUG("text data is inserted into page:[%d:%d]",*(int*)text_buf,*(int*)(text_buf+4));
        memcpy(record + field->offset(), text_buf, 8);
      }
      else{
        memcpy(record + field->offset(), value.data, field->len());
      }
    }
    memcpy(record+bitmap_offset, buf, bitmap_len);
  }
  record_out = record;
  LOG_TRACE("exit make record");
  return RC::SUCCESS;
}

RC Table::init_record_handler(const char *base_dir) {
  std::string data_file = std::string(base_dir) + "/" + table_meta_.name() + TABLE_DATA_SUFFIX;
  if (nullptr == data_buffer_pool_) {
    data_buffer_pool_ = theGlobalDiskBufferPool();
  }

  int data_buffer_pool_file_id;
  RC rc = data_buffer_pool_->open_file(data_file.c_str(), &data_buffer_pool_file_id);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to open disk buffer pool for file:%s. rc=%d:%s",
              data_file.c_str(), rc, strrc(rc));
    return rc;
  }

  record_handler_ = new RecordFileHandler();
  std::vector<int> text_offset;
  for(int i=0;i<table_meta_.field_num();++i){
    if(table_meta_.field(i)->type()==TEXT_PAGE_NUM) {
      text_offset.push_back(table_meta_.field(i)->offset());
    }
  }
  rc = record_handler_->init(*data_buffer_pool_, data_buffer_pool_file_id,text_offset);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to init record handler. rc=%d:%s", rc, strrc(rc));
    return rc;
  }

  file_id_ = data_buffer_pool_file_id;
  return rc;
}

/**
 * 为了不把Record暴露出去，封装一下
 */
class RecordReaderScanAdapter {
public:
  explicit RecordReaderScanAdapter(void (*record_reader)(const char *data, void *context), void *context)
      : record_reader_(record_reader), context_(context){
  }

  void consume(const Record *record) {
    record_reader_(record->data, context_);
  }
private:
  void (*record_reader_)(const char *, void *);
  void *context_;
};
static RC scan_record_reader_adapter(Record *record, void *context) {
  RecordReaderScanAdapter &adapter = *(RecordReaderScanAdapter *)context;
  adapter.consume(record);
  return RC::SUCCESS;
}

RC Table::scan_record(Trx *trx, ConditionFilter *filter, int limit, void *context, void (*record_reader)(const char *data, void *context)) {
  RecordReaderScanAdapter adapter(record_reader, context);
  return scan_record(trx, filter, limit, (void *)&adapter, scan_record_reader_adapter);
}

RC Table::scan_record(Trx *trx, ConditionFilter *filter, int limit, void *context, RC (*record_reader)(Record *record, void *context)) {
  LOG_TRACE("enter");
  if (nullptr == record_reader) {
    return RC::INVALID_ARGUMENT;
  }

  if (0 == limit) {
    return RC::SUCCESS;
  }

  if (limit < 0) {
    limit = INT_MAX;
  }

  IndexScanner *index_scanner = find_index_for_scan(filter);
  if (index_scanner != nullptr) {
    return scan_record_by_index(trx, index_scanner, filter, limit, context, record_reader);
  }
  RC rc = RC::SUCCESS;
  RecordFileScanner scanner;
  rc = scanner.open_scan(*data_buffer_pool_, file_id_, filter);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("failed to open scanner. file id=%d. rc=%d:%s", file_id_, rc, strrc(rc));
    return rc;
  }
  int record_count = 0;
  Record record;
  rc = scanner.get_first_record(&record);
  for ( ; RC::SUCCESS == rc && record_count < limit; rc = scanner.get_next_record(&record)) {
    if (trx == nullptr || trx->is_visible(this, &record)) {
      rc = record_reader(&record, context);
      if (rc != RC::SUCCESS) {
        break;
      }
      record_count++;
    }
  }

  if (RC::RECORD_EOF == rc) {
    rc = RC::SUCCESS;
  } else {
    LOG_ERROR("failed to scan record. file id=%d, rc=%d:%s", file_id_, rc, strrc(rc));
  }
  scanner.close_scan();
  LOG_TRACE("exit");
  return rc;
}

RC Table::scan_record_by_index(Trx *trx, IndexScanner *scanner, ConditionFilter *filter, int limit, void *context,
                               RC (*record_reader)(Record *, void *)) {
  RC rc = RC::SUCCESS;
  RID rid;
  Record record;
  int record_count = 0;
  while (record_count < limit) {
    rc = scanner->next_entry(&rid);
    if (rc != RC::SUCCESS) {
      if (RC::RECORD_EOF == rc) {
        rc = RC::SUCCESS;
        break;
      }
      LOG_ERROR("Failed to scan table by index. rc=%d:%s", rc, strrc(rc));
      break;
    }

    rc = record_handler_->get_record(&rid, &record);
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Failed to fetch record of rid=%d:%d, rc=%d:%s", rid.page_num, rid.slot_num, rc, strrc(rc));
      break;
    }

    if ((trx == nullptr || trx->is_visible(this, &record)) && (filter == nullptr || filter->filter(record))) {
      rc = record_reader(&record, context);
      if (rc != RC::SUCCESS) {
        LOG_TRACE("Record reader break the table scanning. rc=%d:%s", rc, strrc(rc));
        break;
      }
    }

    record_count++;
  }

  scanner->destroy();
  return rc;
}

class IndexInserter {
public:
  explicit IndexInserter(Index *index, Table* table) : index_(index), table_(table) {
  }

  RC insert_index(const Record *record) {
    return index_->insert_entry(record->data, &record->rid);
  }
  
  bool index_value_is_null(const Record *record){
    const char* field_name = index_->index_meta().field();
    int ind = table_->table_meta().field_index(field_name);
    int null_offset = table_->null_offset();
    Bitmap &bitmap = Bitmap::get_instance();
    return bitmap.get_null_at_index(record->data+null_offset, ind-2);
  }
private:
  Index * index_;
  Table* table_;
};

static RC insert_index_record_reader_adapter(Record *record, void *context) {
  IndexInserter &inserter = *(IndexInserter *)context;
  if(inserter.index_value_is_null(record)){
    return RC::SUCCESS;
  }
  return inserter.insert_index(record);
}

class UniqueIndexInserter{
public:
  explicit UniqueIndexInserter(Index *index) : index_(index) {
  }

  RC insert_index(const Record *record) {
    int field_int_value = *(int*)(record->data+index_->get_field_offset());
    if(set_.count(field_int_value)!=0){
      LOG_ERROR("index create fail have dulpica");
      return RC::ABORT;
    }else{
      LOG_INFO("index insert value:%d", field_int_value);
      set_.insert(field_int_value);
    }
    return index_->insert_entry(record->data, &record->rid);
  }
private:
  Index * index_;
  std::set<int> set_;
};

static RC insert_unique_index_record_reader_adapter(Record *record, void *context) {
  UniqueIndexInserter &inserter = *(UniqueIndexInserter *)context;
  return inserter.insert_index(record);
}

RC Table::create_index(Trx *trx, const char *index_name, const char *attribute_name) {
  return create_index(trx, index_name,attribute_name, false);
}

RC Table::create_index(Trx *trx, const char *index_name, const char *attribute_name, bool is_unique) {
  if (index_name == nullptr || common::is_blank(index_name) ||
      attribute_name == nullptr || common::is_blank(attribute_name)) {
    return RC::INVALID_ARGUMENT;
  }
  if (table_meta_.index(index_name) != nullptr ||
      table_meta_.find_index_by_field((attribute_name))) {
    return RC::SCHEMA_INDEX_EXIST;
  }

  const FieldMeta *field_meta = table_meta_.field(attribute_name);
  if (!field_meta) {
    return RC::SCHEMA_FIELD_MISSING;
  }

  IndexMeta new_index_meta;
  RC rc = new_index_meta.init(index_name, *field_meta, is_unique);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  // 创建索引相关数据
  BplusTreeIndex *index = new BplusTreeIndex();
  std::string index_file = index_data_file(base_dir_.c_str(), name(), index_name);
  rc = index->create(index_file.c_str(), new_index_meta, *field_meta);
  if (rc != RC::SUCCESS) {
    delete index;
    LOG_ERROR("Failed to create bplus tree index. file name=%s, rc=%d:%s", index_file.c_str(), rc, strrc(rc));
    return rc;
  }

  // 遍历当前的所有数据，插入这个索引
  if(is_unique){
    LOG_INFO("in unique create index");
    UniqueIndexInserter index_inserter(index);
    rc = scan_record(trx, nullptr, -1, &index_inserter, insert_unique_index_record_reader_adapter);
  }else{
    LOG_INFO("in not unique create index");
    IndexInserter index_inserter(index, this);
    rc = scan_record(trx, nullptr, -1, &index_inserter, insert_index_record_reader_adapter);
  } 
  if (rc != RC::SUCCESS) {
    // rollback
    delete index;
    remove(index_file.c_str());
    LOG_ERROR("Failed to insert index to all records. table=%s, rc=%d:%s", name(), rc, strrc(rc));
    return rc;
  }
  LOG_INFO("index create success");
  indexes_.push_back(index);

  TableMeta new_table_meta(table_meta_);
  rc = new_table_meta.add_index(new_index_meta);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to add index (%s) on table (%s). error=%d:%s", index_name, name(), rc, strrc(rc));
    return rc;
  }
  // 创建元数据临时文件
  std::string tmp_file = table_meta_file(base_dir_.c_str(), name()) + ".tmp";
  std::fstream fs;
  fs.open(tmp_file, std::ios_base::out | std::ios_base::binary | std::ios_base::trunc);
  if (!fs.is_open()) {
    LOG_ERROR("Failed to open file for write. file name=%s, errmsg=%s", tmp_file.c_str(), strerror(errno));
    return RC::IOERR; // 创建索引中途出错，要做还原操作
  }
  if (new_table_meta.serialize(fs) < 0) {
    LOG_ERROR("Failed to dump new table meta to file: %s. sys err=%d:%s", tmp_file.c_str(), errno, strerror(errno));
    return RC::IOERR;
  }
  fs.close();

  // 覆盖原始元数据文件
  std::string meta_file = table_meta_file(base_dir_.c_str(), name());
  int ret = rename(tmp_file.c_str(), meta_file.c_str());
  if (ret != 0) {
    LOG_ERROR("Failed to rename tmp meta file (%s) to normal meta file (%s) while creating index (%s) on table (%s). " \
              "system error=%d:%s", tmp_file.c_str(), meta_file.c_str(), index_name, name(), errno, strerror(errno));
    return RC::IOERR;
  }

  table_meta_.swap(new_table_meta);

  LOG_INFO("add a new index (%s) on the table (%s)", index_name, name());

  return rc;
}

RC Table::create_index_by_list(Trx *trx, const char *index_name, CreateIndexList create_index_list) {
  LOG_TRACE("enter");
  std::vector<std::string> name_vec;
  for (int i=0;i< create_index_list.index_num;i++) {
    auto it = create_index_list.index[i];
      if (it.attribute_name == nullptr || common::is_blank(it.attribute_name)) {
          return RC::INVALID_ARGUMENT;
      }
      name_vec.push_back(it.attribute_name);
  }

  if (index_name == nullptr || common::is_blank(index_name)) {
      return RC::INVALID_ARGUMENT;
  }
  if (table_meta_.index(index_name) != nullptr || table_meta_.find_index_by_list(name_vec)!=nullptr) {
      return RC::SCHEMA_INDEX_EXIST;
  }
  std::vector<const FieldMeta *> field_vec;
  for(auto it : name_vec){
    const FieldMeta *field_meta = table_meta_.field(it.c_str());
    if (!field_meta) {
      return RC::SCHEMA_FIELD_MISSING;
    }
    field_vec.push_back(field_meta);
  }

  IndexMeta new_index_meta;
  RC rc = new_index_meta.init(index_name, name_vec);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  BplusTreeIndex *index = new BplusTreeIndex();
  std::string index_file = index_data_file(base_dir_.c_str(), name(), index_name);
  rc = index->create(index_file.c_str(), new_index_meta, field_vec);
  if (rc != RC::SUCCESS) {
    delete index;
    LOG_ERROR("Failed to create bplus tree index. file name=%s, rc=%d:%s", index_file.c_str(), rc, strrc(rc));
    return rc;
  }

  LOG_INFO("in not unique create index");
  IndexInserter index_inserter(index, this);
  rc = scan_record(trx, nullptr, -1, &index_inserter, insert_index_record_reader_adapter);

  if (rc != RC::SUCCESS) {
    // rollback
    delete index;
    remove(index_file.c_str());
    LOG_ERROR("Failed to insert index to all records. table=%s, rc=%d:%s", name(), rc, strrc(rc));
    return rc;
  }
  LOG_INFO("index create success");
  indexes_.push_back(index);

  TableMeta new_table_meta(table_meta_);
  rc = new_table_meta.add_index(new_index_meta);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to add index (%s) on table (%s). error=%d:%s", index_name, name(), rc, strrc(rc));
    return rc;
  }

  // 创建元数据临时文件
  std::string tmp_file = table_meta_file(base_dir_.c_str(), name()) + ".tmp";
  std::fstream fs;
  fs.open(tmp_file, std::ios_base::out | std::ios_base::binary | std::ios_base::trunc);
  if (!fs.is_open()) {
    LOG_ERROR("Failed to open file for write. file name=%s, errmsg=%s", tmp_file.c_str(), strerror(errno));
    return RC::IOERR; // 创建索引中途出错，要做还原操作
  }
  if (new_table_meta.serialize(fs) < 0) {
    LOG_ERROR("Failed to dump new table meta to file: %s. sys err=%d:%s", tmp_file.c_str(), errno, strerror(errno));
    return RC::IOERR;
  }
  fs.close();

  // 覆盖原始元数据文件
  std::string meta_file = table_meta_file(base_dir_.c_str(), name());
  int ret = rename(tmp_file.c_str(), meta_file.c_str());
  if (ret != 0) {
    LOG_ERROR("Failed to rename tmp meta file (%s) to normal meta file (%s) while creating index (%s) on table (%s). " \
              "system error=%d:%s", tmp_file.c_str(), meta_file.c_str(), index_name, name(), errno, strerror(errno));
    return RC::IOERR;
  }

  table_meta_.swap(new_table_meta);

  LOG_INFO("add a new index (%s) on the table (%s)", index_name, name());
  return rc;
}

class RecordUpdater{
  //仅支持单字段更新
  public:
  RecordUpdater(Table& tab,Trx* trx, const Value* value):table_(tab),trx_(trx),value_(value){
    
  }

  RC set_field(const char* attr_name){
    field_ = table_.table_meta_.field(attr_name);
    if(field_ ==nullptr)
      return RC::SCHEMA_FIELD_NOT_EXIST;
    if(field_->type()!=value_->type){
      // printf("field type:%d, value type:%d\n",(int)field_->type(), (int)value_->type);
      if(value_->type==NULLS){
        if(field_->nullable()==0){
          return RC::SCHEMA_FIELD_TYPE_MISMATCH; 
        }else{
          return RC::SUCCESS;
        }
      }else{
        if(field_->type()==DATES && value_->type){
          return RC::SUCCESS;
        } else if(field_->type() == TEXT_PAGE_NUM && value_->type == CHARS) {
          LOG_DEBUG("field type is text page num, value type is char, field offset is %d",field_->offset());
          return RC::SUCCESS;
        }
        else{
          return RC::SCHEMA_FIELD_TYPE_MISMATCH; 
        }
      }
    }
    return RC::SUCCESS;
  }

  RC update_record(Record* rec){
    LOG_TRACE("enter");
    RC rc = RC::SUCCESS;
    bool need_rollback = false;
    rc = table_.delete_entry_of_indexes(rec->data,rec->rid,true);
    // TODO memory leakage
    char *bak = (char*)malloc(sizeof(char)*field_->len());
    memcpy(&bak, rec->data, field_->len());

    //将value的值复制到对应的偏移量处
    // if dates then save int rather char
    TableMeta table_meta = table_.table_meta_;
    const FieldMeta *null_field = table_meta.field("null_field");
    int bitmap_offset = null_field->offset();
    int bitmap_len = null_field->len();

    Bitmap &bitmap = Bitmap::get_instance();
    char buf[bitmap_len];
    int ind = table_meta.field_index(field_->name());

    if(value_->type==NULLS){
      if(field_->nullable()==1){
        bitmap.set_bit_at_index(rec->data+bitmap_offset,ind-2,1, buf);
      }else{
        LOG_ERROR("can't update null");
          return RC::SCHEMA_FIELD_NOT_EXIST;
      }
    }else{
      bitmap.set_bit_at_index(rec->data+bitmap_offset,ind-2,0, buf);
      if(field_->type()==DATES){
        Date &date = Date::get_instance();
        int date_int = date.date_to_int((const char*)value_->data);
        if(date_int < 0){
          LOG_ERROR("wrong date format");
          return RC::SCHEMA_FIELD_NOT_EXIST;
        }
        memcpy(rec->data + field_->offset(), &date_int, field_->len());
      } else if(field_->type()==TEXT_PAGE_NUM) {
        LOG_DEBUG("update text field");
        RC rc=RC::SUCCESS;
        LOG_DEBUG("get text values");
        int p1 = *(int*)(rec->data + field_->offset());
        int p2 = *(int*)(rec->data + field_->offset() + 4);
        LOG_DEBUG("get page [%d:%d] for update text field", p1,p2);
        BPPageHandle ph1,ph2;
        if((rc=table_.get_buffer_pool()->get_this_page(table_.file_id_,p1,&ph1))!=RC::SUCCESS) {
          LOG_ERROR("failed to get page[%d:%d] for update text data",table_.file_id_,p1);
          return rc;
        }
        if((rc=table_.get_buffer_pool()->get_this_page(table_.file_id_,p2,&ph2))!=RC::SUCCESS) {
          LOG_ERROR("failed to get page[%d:%d] for update text data",table_.file_id_,p2);
          return rc;
        }
        auto* page_header_1 = (PageHeader*)(ph1.frame->page.data);
        auto* page_header_2 = (PageHeader*)(ph2.frame->page.data);
        memset(ph1.frame->page.data+page_header_1->first_record_offset,0,2048);
        memset(ph2.frame->page.data+page_header_2->first_record_offset,0,2048);
        memcpy(ph1.frame->page.data+page_header_1->first_record_offset, (char*)value_->data, 2048);
        memcpy(ph2.frame->page.data+page_header_2->first_record_offset, (char*)value_->data+2048, 2048);
        table_.get_buffer_pool()->mark_dirty(&ph1);
        table_.get_buffer_pool()->mark_dirty(&ph2);
        LOG_DEBUG("update page[%d:%d] data for update text data,their record num is [%d:%d]",p1,p2,page_header_1->record_num,page_header_2->record_num);
        if((rc=table_.get_buffer_pool()->unpin_page(&ph1))!=RC::SUCCESS) {
          LOG_ERROR("failed to unpin page[%d:%d] for update text data",table_.file_id_,p1);
          return rc;
        }
        if((rc=table_.get_buffer_pool()->unpin_page(&ph2))!=RC::SUCCESS) {
          LOG_ERROR("failed to unpin page[%d:%d] for update text data",table_.file_id_,p2);
          return rc;
        }
      }
      else{
        memcpy(rec->data + field_->offset(), value_->data, field_->len());
      }
    }
    memcpy(rec->data + bitmap_offset, buf, bitmap_len);
    
    if(rc!=RC::SUCCESS){
      //update索引
      if(rc!=RC::RECORD_INVALID_KEY){
        need_rollback=false;
        return rc;
      }
    } else {
      need_rollback = true;
      table_.insert_entry_of_indexes(rec->data,rec->rid);
    }
    rc = table_.update_record(trx_,rec);
    if(rc!=RC::SUCCESS){
      if(need_rollback){
        memcpy(bak, rec->data + field_->offset(), field_->len());
        table_.insert_entry_of_indexes(rec->data,rec->rid);
      }
    }else{
      update_count_++;
    }
    LOG_TRACE("exit");
    return rc;
  }
  
  int update_count() const{
    return update_count_;
  }

  private:
    Table& table_;
    Trx* trx_;
    //const char* attr_name_;
    const Value *value_;
    const FieldMeta* field_;
    int update_count_ = 0;
};

static RC record_reader_update_adapter(Record* record,void* context){
  RecordUpdater &updater = *(RecordUpdater*)context;
  return updater.update_record(record);
}

RC Table::update_record(Trx *trx, const char *attribute_name, const Value *value, ConditionFilter *filter, int *update_count) {
  RecordUpdater updater(*this,trx,value);
  RC rc = updater.set_field(attribute_name);
  if(rc!=RC::SUCCESS){
    LOG_DEBUG("mismatch\n");
    return rc;
  }
  rc = scan_record(trx,filter,-1,&updater,record_reader_update_adapter);
  if(update_count!=nullptr){
    *update_count = updater.update_count();
  }

  return rc;
}

RC Table::update_record(Trx* trx, Record* rec){
  //未支持事务
  return this->record_handler_->update_record(rec);
}





class RecordDeleter {
public:
  RecordDeleter(Table &table, Trx *trx) : table_(table), trx_(trx) {
  }

  RC delete_record(Record *record) {
    RC rc = RC::SUCCESS;
    rc = table_.delete_record(trx_, record);
    if (rc == RC::SUCCESS) {
      deleted_count_++;
    }
    return rc;
  }

  int deleted_count() const {
    return deleted_count_;
  }

private:
  Table & table_;
  Trx *trx_;
  int deleted_count_ = 0;
};

static RC record_reader_delete_adapter(Record *record, void *context) {
  RecordDeleter &record_deleter = *(RecordDeleter *)context;
  return record_deleter.delete_record(record);
}

RC Table::delete_record(Trx *trx, ConditionFilter *filter, int *deleted_count) {
  RecordDeleter deleter(*this, trx);
  RC rc = scan_record(trx, filter, -1, &deleter, record_reader_delete_adapter);
  if (deleted_count != nullptr) {
    *deleted_count = deleter.deleted_count();
  }
  return rc;
}

RC Table::delete_record(Trx *trx, Record *record) {
  RC rc = RC::SUCCESS;
  if (trx != nullptr) {
    rc = trx->delete_record(this, record);
  } else {
    rc = delete_entry_of_indexes(record->data, record->rid, false);// 重复代码 refer to commit_delete
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Failed to delete indexes of record (rid=%d.%d). rc=%d:%s",
                record->rid.page_num, record->rid.slot_num, rc, strrc(rc));
    } else {
      rc = record_handler_->delete_record(&record->rid);
    }
  }
  return rc;
}

RC Table::commit_delete(Trx *trx, const RID &rid) {
  RC rc = RC::SUCCESS;
  Record record;
  rc = record_handler_->get_record(&rid, &record);
  if (rc != RC::SUCCESS) {
    return rc;
  }
  rc = delete_entry_of_indexes(record.data, record.rid, false);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to delete indexes of record(rid=%d.%d). rc=%d:%s",
              rid.page_num, rid.slot_num, rc, strrc(rc));// panic?
  }

  rc = record_handler_->delete_record(&rid);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  return rc;
}

RC Table::rollback_delete(Trx *trx, const RID &rid) {
  RC rc = RC::SUCCESS;
  Record record;
  rc = record_handler_->get_record(&rid, &record);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  return trx->rollback_delete(this, record); // update record in place
}

RC Table::insert_entry_of_indexes(const char *record, const RID &rid) {
  LOG_TRACE("enter");
  RC rc = RC::SUCCESS;
  for (Index *index : indexes_) {
    index = (BplusTreeIndex*)index;
    if(index->index_meta().unique()){
      // TODO memory leakage
      char *buf = (char*)malloc(sizeof(char)*(index->get_field_len()));
      memcpy(buf, record+index->get_field_offset(), index->get_field_len());
      IndexScanner* scanner = index->create_scanner(EQUAL_TO, buf);
      RID rid;
      rc=scanner->next_entry(&rid);
      // if success then there is duplica
      if(rc==RC::SUCCESS){
        return RC::RECORD_DUPLICATE_KEY;
      }
    }
  }
  Bitmap &bitmap = Bitmap::get_instance();
  int bitmap_offset = null_offset();
  for (Index *index : indexes_) {
    int ind = table_meta_.field_index(index->index_meta().field());
    if(bitmap.get_null_at_index(record+bitmap_offset, ind-2)==1){
      continue;
    }

    rc = index->insert_entry(record, &rid);
    if (rc != RC::SUCCESS) {
      break;
    }
  }
  return rc;
}

RC Table::delete_entry_of_indexes(const char *record, const RID &rid, bool error_on_not_exists) {
  RC rc = RC::SUCCESS;
  Bitmap &bitmap = Bitmap::get_instance();
  int bitmap_offset = null_offset();
  for (Index *index : indexes_) {
    int ind = table_meta_.field_index(index->index_meta().field());
    if(bitmap.get_null_at_index(record+bitmap_offset, ind-2)==1){
      continue;
    }
    rc = index->delete_entry(record, &rid);
    if (rc != RC::SUCCESS) {
      if (rc != RC::RECORD_INVALID_KEY || !error_on_not_exists) {
        break;
      }
    }
  }
  return rc;
}

Index *Table::find_index(const char *index_name) const {
  for (Index *index: indexes_) {
    if (0 == strcmp(index->index_meta().name(), index_name)) {
      return index;
    }
  }
  return nullptr;
}

Index *Table::find_index_multi_index(std::vector<std::string> filter_attr_list) const {
  for (Index *index: indexes_) {
    if(0==index->index_meta().compare_multi_index(filter_attr_list)){
      return index;
    }
  }
  return nullptr;
}

IndexScanner *Table::find_index_for_scan(const DefaultConditionFilter &filter) {
  const ConDesc *field_cond_desc = nullptr;
  const ConDesc *value_cond_desc = nullptr;
  if (filter.left().is_attr && !filter.right().is_attr) {
    field_cond_desc = &filter.left();
    value_cond_desc = &filter.right();
  } else if (filter.right().is_attr && !filter.left().is_attr) {
    field_cond_desc = &filter.right();
    value_cond_desc = &filter.left();
  }
  if (field_cond_desc == nullptr || value_cond_desc == nullptr) {
    return nullptr;
  }

  const FieldMeta *field_meta = table_meta_.find_field_by_offset(field_cond_desc->attr_offset);
  if (nullptr == field_meta) {
    LOG_PANIC("Cannot find field by offset %d. table=%s",
              field_cond_desc->attr_offset, name());
    return nullptr;
  }

  const IndexMeta *index_meta = table_meta_.find_index_by_field(field_meta->name());
  if (nullptr == index_meta) {
    return nullptr;
  }

  Index *index = find_index(index_meta->name());
  if (nullptr == index) {
    return nullptr;
  }
  return index->create_scanner(filter.comp_op(), (const char *)value_cond_desc->value);
}

IndexScanner *Table::find_index_for_scan(const ConditionFilter *filter) {
  if (nullptr == filter) {
    return nullptr;
  }

  // remove dynamic_cast
  const DefaultConditionFilter *default_condition_filter = dynamic_cast<const DefaultConditionFilter *>(filter);
  if (default_condition_filter != nullptr) {
    if(!default_condition_filter->left().is_attr&&default_condition_filter->left().value==nullptr){
      return nullptr;
    }
    if(!default_condition_filter->right().is_attr&&default_condition_filter->right().value==nullptr){
      return nullptr;
    }
    return find_index_for_scan(*default_condition_filter);
  }

  // TODO scan filter see if 
  const CompositeConditionFilter *composite_condition_filter = dynamic_cast<const CompositeConditionFilter *>(filter);
  std::vector<std::string> filter_attr_list;
  std::vector<std::string> value_list;
  std::vector<CompOp> comop_list;
  if (composite_condition_filter != nullptr) {
    int filter_num = composite_condition_filter->filter_num();
    for (int i = 0; i < filter_num; i++) {
        const DefaultConditionFilter* temp =
            dynamic_cast<const DefaultConditionFilter*>(
                &composite_condition_filter->filter(i));
        comop_list.push_back(temp->comp_op());

        if (temp->left().is_attr) {
            const FieldMeta* field_meta = table_meta_.find_field_by_offset(temp->left().attr_offset);
            if (nullptr == field_meta) {
                LOG_PANIC("Cannot find field by offset %d. table=%s",
                          temp->left().attr_offset, name());
                return nullptr;
            }
            filter_attr_list.push_back(field_meta->name());
            if(temp->right().value==nullptr){
              filter_attr_list.clear();
              value_list.clear();
              comop_list.clear();
              break;
            }
            value_list.push_back((const char *)temp->right().value);
        } else if (temp->right().is_attr) {
          const FieldMeta* field_meta = table_meta_.find_field_by_offset(temp->right().attr_offset);
            if (nullptr == field_meta) {
                LOG_PANIC("Cannot find field by offset %d. table=%s",
                          temp->left().attr_offset, name());
                return nullptr;
            }
            filter_attr_list.push_back(field_meta->name());
            if(temp->left().value==nullptr){
              filter_attr_list.clear();
              value_list.clear();
              comop_list.clear();
              break;
            }
            value_list.push_back((const char *)temp->left().value);
        } else {
            filter_attr_list.clear();
            value_list.clear();
            comop_list.clear();
            break;
        }
    }
  }

  if(comop_list.size()>0){
    IndexScanner *scanner= find_index_for_scan_by_list(filter_attr_list, value_list, comop_list);
    if (scanner != nullptr) {
      return scanner; 
    }
  }
 
  if (composite_condition_filter != nullptr) {
    int filter_num = composite_condition_filter->filter_num();
    for (int i = 0; i < filter_num; i++) {
      IndexScanner *scanner= find_index_for_scan(&composite_condition_filter->filter(i));
      if (scanner != nullptr) {
        return scanner; // 可以找到一个最优的，比如比较符号是=
      }
    }
  }
  return nullptr;
}

IndexScanner *Table::find_index_for_scan_by_list(std::vector<std::string> filter_attr_list, std::vector<std::string> value_list, std::vector<CompOp> comop_list){
  Index* index = find_index_multi_index(filter_attr_list);
  if(nullptr == index){
    return nullptr;
  }
  return index->create_scanner_multi_index(value_list, comop_list);
}

RC Table::sync() {
  RC rc = data_buffer_pool_->flush_all_pages(file_id_);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to flush table's data pages. table=%s, rc=%d:%s", name(), rc, strrc(rc));
    return rc;
  }

  for (Index *index: indexes_) {
    rc = index->sync();
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Failed to flush index's pages. table=%s, index=%s, rc=%d:%s",
                name(), index->index_meta().name(), rc, strrc(rc));
      return rc;
    }
  }
  LOG_INFO("Sync table over. table=%s", name());
  return rc;
}

int Table::null_offset(){
  return table_meta_.field("null_field")->offset();
}