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
// Created by Wangyunlai on 2021/5/14.
//

#include "sql/executor/tuple.h"
#include "storage/common/table.h"
#include "common/log/log.h"
#include "storage/common/date.h"
#include <limits>
#include <string>
#include <regex>
#include "storage/common/bitmap.h"


Tuple::Tuple(const Tuple &other) {
  LOG_PANIC("Copy constructor of tuple is not supported");
  exit(1);
}

Tuple::Tuple(Tuple &&other) noexcept : values_(std::move(other.values_)) {
}

Tuple & Tuple::operator=(Tuple &&other) noexcept {
  if (&other == this) {
    return *this;
  }

  values_.clear();
  values_.swap(other.values_);
  return *this;
}

Tuple::~Tuple() {
}

// add (Value && value)
void Tuple::add(TupleValue *value) {
  values_.emplace_back(value);
}
void Tuple::add(const std::shared_ptr<TupleValue> &other) {
  values_.emplace_back(other);
}
void Tuple::add(int value) {
  add(new IntValue(value));
}

void Tuple::add(float value) {
  add(new FloatValue(value));
}

void Tuple::add(const char *s, int len) {
  add(new StringValue(s, len));
}

void Tuple::add_date(int value) {
  add(new DateValue(value));
}

void Tuple::add(const char*d1,int len1, const char* d2,int len2) {
  add(new TextValue(d1,len1,d2,len2));
}

void Tuple::add_null() {
  add(new NullValue());
}

////////////////////////////////////////////////////////////////////////////////

std::string TupleField::to_string() const {
  return std::string(table_name_) + "." + field_name_ + std::to_string(type_);
}

////////////////////////////////////////////////////////////////////////////////
void TupleSchema::from_table(const Table *table, TupleSchema &schema) {
  const char *table_name = table->name();
  const TableMeta &table_meta = table->table_meta();
  const int field_num = table_meta.field_num();
  for (int i = 0; i < field_num; i++) {
    const FieldMeta *field_meta = table_meta.field(i);
    if (field_meta->visible()) {
      schema.add(field_meta->type(), table_name, field_meta->name());
    }
  }
}

void TupleSchema::add(AttrType type, const char *table_name, const char *field_name) {
  fields_.emplace_back(type, table_name, field_name,ATF_NULL);
}

void TupleSchema::add_agg_field(AttrType type, const char *table_name, const char *field_name,AggregationTypeFlag af){
  fields_.emplace_back(type, table_name, field_name,af);
}


void TupleSchema::add_if_not_exists(AttrType type, const char *table_name, const char *field_name) {
  for (const auto &field: fields_) {
    if (0 == strcmp(field.table_name(), table_name) &&
        0 == strcmp(field.field_name(), field_name)) {
      return;
    }
  }

  add(type, table_name, field_name);
}

void TupleSchema::append(const TupleSchema &other) {
  fields_.reserve(fields_.size() + other.fields_.size());
  for (const auto &field: other.fields_) {
    fields_.emplace_back(field);
  }
}

int TupleSchema::index_of_field(const char *table_name, const char *field_name) const {
  const int size = fields_.size();
  for (int i = 0; i < size; i++) {
    const TupleField &field = fields_[i];
    if (0 == strcmp(field.table_name(), table_name) && 0 == strcmp(field.field_name(), field_name)) {
      return i;
    }
  }
  return -1;
}
void TupleSchema::print_by_order(std::ostream &os, std::vector<std::pair<int, int>> &order) const {
  if (fields_.empty()) {
    os << "No schema";
    return;
  }
  for(int i=0;i<order.size();++i) {
    auto f=fields_[order[i].second];
    os << f.table_name() << "." << f.field_name();
    if(i==order.size()-1) {
      os << std::endl;
    } else {
      os << " | ";
    }
  }
}
void TupleSchema::print(std::ostream &os,bool table_name) const {
  if (fields_.empty()) {
    os << "No schema";
    return;
  }

  // 判断有多张表还是只有一张表
  std::set<std::string> table_names;
  for (const auto &field: fields_) {
    table_names.insert(field.table_name());
  }

  for (std::vector<TupleField>::const_iterator iter = fields_.begin(), end = --fields_.end();
       iter != end; ++iter) {
    if(strcmp("null_field", iter->field_name())== 0){
      continue;
    }
    if (table_name) {
      os << iter->table_name() << ".";
    }
    os << iter->field_name() << " | ";
  }

  if (table_name) {
    os << fields_.back().table_name() << ".";
  }
  os << fields_.back().field_name() << std::endl;
}

void TupleSchema::print_with_agg(std::ostream &os,bool table_name){
  if (fields_.empty()) {
    os << "No schema";
    return;
  }

  // 判断有多张表还是只有一张表
  std::set<std::string> table_names;
  for (const auto &field: fields_) {
    table_names.insert(field.table_name());
  }

  for (std::vector<TupleField>::const_iterator iter = fields_.begin(), end = --fields_.end();
       iter != end; ++iter) {
    if(strcmp("null_field", iter->field_name())== 0){
      continue;
    }
    if(iter->agg_type()!=ATF_NULL){
      switch (iter->agg_type())
      {
      case ATF_COUNT:
        os<<"count(";
        break;
      case ATF_SUM:
        os<<"sum(";
        break;
      case ATF_MAX:
        os<<"max(";
        break;
      case ATF_MIN:
        os<<"min(";
        break;
      case ATF_AVG:
        os<<"avg(";
        break;
      default:
        break;
      }
    }
    if (table_name) {
      os << iter->table_name() << ".";
    }
    os << iter->field_name();
    if(iter->agg_type()!=ATF_NULL){
      os<<")";
    }
    os << " | ";
  }

  if(fields_.back().agg_type()!=ATF_NULL){
      switch (fields_.back().agg_type())
      {
      case ATF_COUNT:
        os<<"count(";
        break;
      case ATF_SUM:
        os<<"sum(";
        break;
      case ATF_MAX:
        os<<"max(";
        break;
      case ATF_MIN:
        os<<"min(";
        break;
      case ATF_AVG:
        os<<"avg(";
        break;
      default:
        break;
      }
    }
  if (table_name) {
    os << fields_.back().table_name() << ".";
  }
  os << fields_.back().field_name();
  if(fields_.back().agg_type()!=ATF_NULL){
    os<<")";
  }
  os << std::endl;
}

/////////////////////////////////////////////////////////////////////////////
TupleSet::TupleSet(TupleSet &&other) : tuples_(std::move(other.tuples_)), schema_(other.schema_){
  other.schema_.clear();
}

TupleSet &TupleSet::operator=(TupleSet &&other) {
  if (this == &other) {
    return *this;
  }

  schema_.clear();
  schema_.append(other.schema_);
  other.schema_.clear();

  tuples_.clear();
  tuples_.swap(other.tuples_);
  return *this;
}

void TupleSet::add(Tuple &&tuple) {
  tuples_.emplace_back(std::move(tuple));
}

void TupleSet::clear() {
  tuples_.clear();
  schema_.clear();
}

void TupleSet::print_by_order(std::ostream &os, std::vector<std::pair<int,int>>& print_order) const {
  if (schema_.fields().empty()) {
    LOG_WARN("Got empty schema");
    return;
  }
  schema_.print_by_order(os,print_order);
  for (const Tuple &item : tuples_) {
    const std::vector<std::shared_ptr<TupleValue>> &values = item.values();
    for(int i=0;i< print_order.size();++i) {
      values[print_order[i].second]->to_string(os);
      if(i==print_order.size()-1) {
        os << std::endl;
      } else {
        os << " | ";
      }
    }
  }
}

void TupleSet::print(std::ostream &os, bool table_name) const {
  if (schema_.fields().empty()) {
    LOG_WARN("Got empty schema");
    return;
  }

  schema_.print(os,table_name);

  for (const Tuple &item : tuples_) {
    const std::vector<std::shared_ptr<TupleValue>> &values = item.values();
    for (std::vector<std::shared_ptr<TupleValue>>::const_iterator iter = values.begin(), end = --values.end();
          iter != end; ++iter) {
      (*iter)->to_string(os);
      os << " | ";
    }
    values.back()->to_string(os);
    //LOG_DEBUG("print endl");
    os << std::endl;
  }
}

void TupleSet::set_schema(const TupleSchema &schema) {
  schema_ = schema;
}

void TupleSet::set_schema(const TupleSchema &&schema) {
  schema_ = schema;
}

const TupleSchema &TupleSet::get_schema() const {
  return schema_;
}

bool TupleSet::is_empty() const {
  return tuples_.empty();
}

int TupleSet::size() const {
  return tuples_.size();
}

const Tuple &TupleSet::get(int index) const {
  return tuples_[index];
}

const std::vector<Tuple> &TupleSet::tuples() const {
  return tuples_;
}

/////////////////////////////////////////////////////////////////////////////
TupleRecordConverter::TupleRecordConverter(Table *table, TupleSet &tuple_set) :
      table_(table), tuple_set_(tuple_set){
}

void TupleRecordConverter::add_record(const char *record) {
  const TupleSchema &schema = tuple_set_.schema();
  Tuple tuple;
  const TableMeta &table_meta = table_->table_meta();
  Bitmap &bitmap = Bitmap::get_instance();
  int bitmap_offset = table_->null_offset();
  for (int i = 0; i < schema.fields().size();i++) {
    const TupleField &field = schema.fields()[i];
    const FieldMeta *field_meta = table_meta.field(field.field_name());
    int ind = table_meta.field_index(field.field_name());
    assert(field_meta != nullptr);
    if(bitmap.get_null_at_index(record+bitmap_offset, ind-2)==1){
      tuple.add_null();
      continue;
    }
    switch (field_meta->type()) {
      case INTS: {
        int value = *(int*)(record + field_meta->offset());
        tuple.add(value);
      }
      break;
      case FLOATS: {
        float value = *(float *)(record + field_meta->offset());
        tuple.add(value);
      }
        break;
      case DATES:{
        int value = *(int*)(record + field_meta->offset());
        tuple.add_date(value);
      }
        break;
      case CHARS: {
        const char *s = record + field_meta->offset();  // 现在当做Cstring来处理
        tuple.add(s, std::min((int)strlen(s),field_meta->len()));
      }
        break;
      case TEXT_PAGE_NUM:{
        LOG_DEBUG("get text values");
        int p1 = *(int*)(record + field_meta->offset());
        int p2 = *(int*)(record + field_meta->offset() + 4);
        BPPageHandle h1,h2;
        if (table_->get_buffer_pool()->get_this_page(table_->get_file_id(),p1,&h1)!=RC::SUCCESS) {
          LOG_ERROR("failed to get page for get text data ");
        }
        if (table_->get_buffer_pool()->get_this_page(table_->get_file_id(),p2,&h2)!=RC::SUCCESS) {
          LOG_ERROR("failed to get page for get text data ");
        }
        PageHeader* ph1=(PageHeader*)h1.frame->page.data;
        PageHeader* ph2=(PageHeader*)h1.frame->page.data;
        LOG_DEBUG("text value page is [%d:%d]",p1,p2);
        tuple.add(h1.frame->page.data+ph1->first_record_offset,2048,h2.frame->page.data+ph2->first_record_offset,2048);
        if(table_->get_buffer_pool()->unpin_page(&h1)!=RC::SUCCESS ||
            table_->get_buffer_pool()->unpin_page(&h2)!=RC::SUCCESS) {
          LOG_ERROR("failed to unpin page after get text data");
        }
      }
      break;
      default: {
        LOG_PANIC("Unsupported field type. type=%d", field_meta->type());
      }
    }
  }

  tuple_set_.add(std::move(tuple));
}

SetRecordConverter::SetRecordConverter(Table* table,std::unordered_set<int>* in_set,const FieldMeta* fm)
            :table_(table),in_set_(in_set),fm_(fm){}

RC SetRecordConverter::add_record(Record* rec){
  void* data = malloc(sizeof(int));
  memcpy(data,(rec->data)+fm_->offset(),fm_->len());
  in_set_->insert(*reinterpret_cast<int*>(data));
  return RC::SUCCESS;
};

RecordAggregater::RecordAggregater(Table& tab) : table_(tab){}

RecordAggregater::~ RecordAggregater(){
    //释放value，先判断类型避免delete void
    // for(int i=0;i!=value_.size();i++){
    //   if(field_[i].second == ATF_COUNT){
    //     continue;
    //   }
    //   else{
    //     switch (field_[i].first->type())
    //     {
    //     case INTS:
    //     case DATES:
    //       delete (int*)value_[i];
    //       break;
    //     case FLOATS:
    //       delete (float*)value_[i];
    //       break;
    //     case CHARS:
    //       delete (char*)value_[i];
    //       break;
    //     default:
    //       break;
    //     }
    //   }
    // }
}

RC RecordAggregater::set_field(const AggregatesField* agg_field,int agg_field_num){
  TupleSchema schema;
  for(int i=agg_field_num-1;i!=-1;i--){
    //解析出来的顺序是反的，所以要反过来加入
    const FieldMeta* fm = table_.table_meta_.field(agg_field[i].attribute_name);
    LOG_INFO("%s ",agg_field[i].attribute_name);
    if(fm==nullptr){
      if(agg_field[i].aggregation_type!=ATF_COUNT)
        return RC::SCHEMA_FIELD_NOT_EXIST;
      else{
        //判断是否是count(*)或者count(num)的情况
        std::string typestr(agg_field[i].attribute_name,strlen(agg_field[i].attribute_name));
          if(!std::regex_match(typestr,std::regex("[*]"))&&!std::regex_match(typestr,std::regex("[0-9]+"))){
            return RC::SCHEMA_FIELD_NOT_EXIST;
        }
      }
    }
    field_.push_back({fm,agg_field[i].aggregation_type});
    if(agg_field[i].aggregation_type == ATF_COUNT){
      value_.push_back(new int(0));
      schema.add(INTS,table_.name(),schema_field_name(agg_field[i].attribute_name,agg_field[i].aggregation_type).c_str());
      continue;
    }
    else if(agg_field[i].aggregation_type == ATF_AVG){
      std::pair<void*, int> *p;
      if(fm->type()==FLOATS){
        p = new std::pair<void*, int>(new float(0) ,0);
      }else{
        p = new std::pair<void*, int>(new int(0) ,0);
      }
      value_.push_back(p);
      schema.add(FLOATS,table_.name(),schema_field_name(agg_field[i].attribute_name,agg_field[i].aggregation_type).c_str());
      continue;
    }
    else{
      schema.add(fm->type(),table_.name(),schema_field_name(agg_field[i].attribute_name,agg_field[i].aggregation_type).c_str());
    }
    switch(fm->type()){
      //对不支持的类型插入一个空指针,目前只支持float,int
      case FLOATS:{
        std::pair<void*, int> *p;
        float* tmp;
        if(agg_field[i].aggregation_type == ATF_MAX)
          tmp = new float(-std::numeric_limits<float>::max());
        else if(agg_field[i].aggregation_type == ATF_MIN)
          tmp = new float(std::numeric_limits<float>::max());
        else{
          tmp = new float(0);
        }
        p = new std::pair<void*, int>(tmp ,0);
        value_.push_back(p);
      }
      break;
      case DATES:
      case INTS:{
        std::pair<void*, int> *p;
        int* tmp;
        if(agg_field[i].aggregation_type == ATF_MAX)
          tmp = new int(INT32_MIN);
        else if(agg_field[i].aggregation_type == ATF_MIN)
          tmp = new int(INT32_MAX);
        else{
          tmp = new int(0);
        }
        p = new std::pair<void*, int>(tmp ,0);
        value_.push_back(p);
      }
      break;
      case CHARS:{
        std::pair<void*, int> *p;
        char* tmp = new char('\0');
        if(agg_field[i].aggregation_type == ATF_AVG || agg_field[i].aggregation_type == ATF_SUM){
          return RC::SCHEMA_FIELD_NOT_EXIST;
        }
        p = new std::pair<void*, int>(tmp ,0);
        value_.push_back(p);
      }
      break;
      default:
        value_.push_back(nullptr);
      break;
    }  
  }
  if(value_.size()!=field_.size()){
    LOG_ERROR("Get %d values and %d field",value_.size(),field_.size());
  }
  tupleset.set_schema(std::move(schema));
  return RC::SUCCESS;
}
void str_set_cmp(void*& target, void*& value, bool is_max){
  if(*(char*)target=='\0'){
    std::swap(target,value);
  }
  else if((strcmp((char*)target,(char*)value)>0)^is_max){
    std::swap(target,value);
  }
  
}
RC RecordAggregater::update_record(Record* rec){
  LOG_TRACE("Enter");
  rec_count++;
  Bitmap &bitmap = Bitmap::get_instance();
  int bitmap_offset = table_.null_offset();
  for(int i=0;i!=field_.size();i++){
    if(value_[i]==nullptr){
      //不支持的类型
      continue;
    }
    // count(*)
    if(field_[i].first == nullptr){
      continue;
    }
    TableMeta &table_meta = table_.table_meta_;
    int ind = table_meta.field_index(field_[i].first->name());
    if (bitmap.get_null_at_index(rec->data + bitmap_offset, ind - 2) == 1){
      continue;
    }
    void* field_data = malloc(sizeof(char)*field_[i].first->len());
    memcpy(field_data,(rec->data)+field_[i].first->offset(),field_[i].first->len());
    switch (field_[i].second)
    {
    //遍历过程对ATF_COUNT不做任何处理
    case ATF_MAX:
      {
        std::pair<void*, int>* p = (std::pair<void*, int> *)value_[i];
        p->second++;
        switch (field_[i].first->type())
        {
        case INTS:
        case DATES:
          *(int*)p->first = std::max(*(int*)p->first, *(int*)field_data);
          break;
        case FLOATS:
          *(float*)p->first = std::max(*(float*)p->first,*(float*)field_data);
          break;
        case CHARS:
          str_set_cmp(p->first,field_data,true);
          break;
        default:
          return RC::SCHEMA_FIELD_TYPE_MISMATCH;
          break;
        }
      }
      break;
    case ATF_MIN:
      {
        std::pair<void*, int>* p = (std::pair<void*, int> *)value_[i];
        p->second++;
        switch (field_[i].first->type())
        {
        case INTS:
        case DATES:
          *(int*)p->first = std::min(*(int*)p->first,*(int*)field_data);
          break;
        case FLOATS:
          *(float*)p->first = std::min(*(float*)p->first,*(float*)field_data);
          break;
        case CHARS:
          str_set_cmp(p->first,field_data,false);
          break;
        default:
          return RC::SCHEMA_FIELD_TYPE_MISMATCH;
          break;
        }
      }
      break;
    case ATF_SUM:
    {
      std::pair<void*, int>* p = (std::pair<void*, int> *)value_[i];
      p->second++;
      switch (field_[i].first->type())
        {
        case INTS:
        case DATES:
          *(int*)p->first += *(int*)field_data;
          break;
        case FLOATS:
          *(float*)p->first += *(float*)field_data;
          break;
        default:
          return RC::SCHEMA_FIELD_TYPE_MISMATCH;
          break;
        }
    }
    break;
    case ATF_AVG:
      {
        std::pair<void*, int>* p = (std::pair<void*, int> *)value_[i];
        p->second++;
        switch (field_[i].first->type())
        {
        case INTS:
        case DATES:
          *(int*)p->first +=*(int*)field_data;
          break;
        case FLOATS:
          if(p->first==nullptr){
          }
          *(float*)p->first +=*(float*)field_data;
          break;
        default:
          return RC::SCHEMA_FIELD_TYPE_MISMATCH;
          break;
        }
      }
      break;
    case ATF_COUNT:
    {
      *(int*)value_[i] = *(int*)value_[i] + 1;
    }
    break;

    default:
      break;
    }
    free(field_data);
  }
  return RC::SUCCESS;
}
RC RecordAggregater::get_condition_value(Value* conditionvalue){
  //设置返回的value类的类型
  if(value_.size()!=1){
    LOG_ERROR("Get %d values!",value_.size());
  }
  switch (field_[0].second)
  {
  case ATF_COUNT:{
    conditionvalue->type = INTS;
    conditionvalue->data = new int(rec_count);
    }
    break;
  case ATF_AVG:{
    std::pair<void*, int>* p = (std::pair<void*, int> *)value_[0];
    int not_null_count = p->second;
    conditionvalue->type = FLOATS;
    conditionvalue->data = new float;
    if(rec_count==0){
      return RC::SCHEMA_FIELD_NOT_EXIST;
    }else{
      if(field_[0].first->type() == INTS)
        *((float*)conditionvalue->data) = (float)*(int*)p->first/(float)not_null_count;
      else if(field_[0].first->type() == FLOATS)
        *((float*)conditionvalue->data) = *(float*)p->first/(float)not_null_count;
      else if(field_[0].first->type() == DATES)
        *((int*)conditionvalue->data) = *(int*)p->first/not_null_count;
      else
        return RC::SCHEMA_FIELD_NOT_EXIST;
    }
  }
    break;
  default:{
    conditionvalue->type = field_[0].first->type();
    std::pair<void*, int>* p = (std::pair<void*, int> *)value_[0];
    switch(field_[0].first->type()){
      case INTS:
      case DATES:
        conditionvalue->data = new int(*(int*)p->first);
      break;
      case FLOATS:
        conditionvalue->data = new float(*(float*)p->first);
      break;
      case CHARS:
        conditionvalue->data = strdup((char*)p->first);
      break;
      default:
        LOG_ERROR("Got unsupported type %d",field_[0].first->type());
      break;
    }
  }
    break;
  }

  return RC::SUCCESS;
}
void RecordAggregater::agg_done(){
  //AVG字段要除，输出是一个float
  //count字段原本是空指针现在需设置为count值，输出是一个int
  Tuple tuple;
  for(int i =0;i!=field_.size();i++){
    switch (field_[i].second)
    {
    case ATF_COUNT:{
        if(field_[i].first==nullptr){
          tuple.add(rec_count);
        }else{
          tuple.add(*(int*)value_[i]);
        }
      }
      break;
    case ATF_AVG:{
      std::pair<void*, int>* p = (std::pair<void*, int> *)value_[i];
      int not_null_count = p->second;
      if(not_null_count==0){
        tuple.add_null();
      }else{
        if(field_[i].first->type() == INTS)
          tuple.add((float)*(int*)p->first/(float)not_null_count);
        else if(field_[i].first->type() == FLOATS)
          tuple.add(*(float*)p->first/(float)not_null_count);
        else if(field_[i].first->type() == DATES)
          tuple.add_date(*(int*)p->first/not_null_count);
        else
          tuple.add_null();
      }
    }
      break;
    default:{
      std::pair<void*, int>* p = (std::pair<void*, int> *)value_[i];
      int not_null_count = p->second;
      if(not_null_count==0){
        tuple.add_null();
        break;
      }
      switch (field_[i].first->type())
      {
      case DATES:
        tuple.add_date(*(int*)p->first);
        break;
      case INTS:
        tuple.add(*(int*)p->first);
        break;
      case FLOATS:
        tuple.add(*(float*)p->first);
        break;
      case CHARS:
        tuple.add((char*)p->first ,std::min((int)strlen((char*)p->first),field_[i].first->len()));
        break;
      default:
        break;
      }
    }
      break;
    }
  }
  tupleset.add(std::move(tuple));
}


std::string RecordAggregater::schema_field_name(const char *attr_name,enum AggregationTypeFlag flag){
  std::string aggtypeWithattr;
  switch (flag)
  {
  case ATF_MAX:
    aggtypeWithattr+="max";
    break;
  case ATF_MIN:
    aggtypeWithattr+="min";
    break;
  case ATF_SUM:
    aggtypeWithattr+="sum";
    break;
  case ATF_COUNT:
    aggtypeWithattr+="count";
    break;
  case ATF_AVG:
    aggtypeWithattr+="avg";
    break;
  }

  aggtypeWithattr+="(";
  aggtypeWithattr+=attr_name;
  aggtypeWithattr+=")";
  return aggtypeWithattr;
}

TupleSet* RecordAggregater::get_tupleset(){
  return &tupleset;
}


GroupTupleSet::GroupTupleSet(TupleSet* input,Selects* select,const std::vector<std::pair<int,int>>& order):input_(input),order_(order){
  for(int i =select->attr_num-1;i!=-1;i--){
    if(select->attributes[i].agg_type!=ATF_NULL)
      agg_index.push_back({select->attr_num-1-i,select->attributes[i].agg_type});
    if(select->attributes[i].relation_name==nullptr){
      if(select->relation_num>1)
        LOG_ERROR("Get no relation name");
      select->attributes[i].relation_name = select->relations[0];
    }
    // if(select->attributes[i].agg_type==ATF_NULL)
    //   by_index.push_back(select->attr_num-1-i);
    // else
    //   agg_index.push_back({select->attr_num-1-i,select->attributes[i].agg_type});
    switch (select->attributes[i].agg_type)
    {
    //count和sum固定类型值
    case ATF_COUNT:
      schema_.add_agg_field(INTS,select->attributes[i].relation_name,select->attributes[i].attribute_name,
      select->attributes[i].agg_type);
      break;
    case ATF_AVG:
      schema_.add_agg_field(FLOATS,select->attributes[i].relation_name,select->attributes[i].attribute_name,
      select->attributes[i].agg_type);
      break;
    default:
      schema_.add_agg_field(input_->get_schema().field(order_[select->attr_num-1-i].second).type(),select->attributes[i].relation_name,
      select->attributes[i].attribute_name,select->attributes[i].agg_type);
      break;
    }
  }
}

GroupTupleSet::~GroupTupleSet(){
  for(auto it = groups.begin();it!=groups.end();it++){
    delete it->second;
  }
}

void GroupTupleSet::print(std::ostream &os,bool table_name){
  if (schema_.fields().empty()) {
    LOG_WARN("Got empty schema");
    return;
  }

  schema_.print_with_agg(os,table_name);

  for(auto it = groups.begin();it!=groups.end();it++){
    const Tuple &item = *it->second;
    const std::vector<std::shared_ptr<TupleValue>> &values = item.values();
    for (std::vector<std::shared_ptr<TupleValue>>::const_iterator iter = values.begin(), end = --values.end();
          iter != end; ++iter) {
      (*iter)->to_string(os);
      os << " | ";
    }
    values.back()->to_string(os);
    //LOG_DEBUG("print endl");
    os << std::endl;
  }
}

RC GroupTupleSet::init_tuple(Tuple* init,const Tuple& ref){
  //用第一个tuple的值初始化聚合结果字段
  //segment fault
  for(int i =0;i!=schema_.size();i++){
    if(i>=order_.size())
      return RC::ABORT;
    if(order_[i].second>=ref.size())
      return RC::ABORT;
    switch (schema_.field(i).type())
    {
    case FLOATS:
      init->add((float)0);
      ((FloatValue&)init->get(i)).plus(ref.get(order_[i].second));
      break;
    case INTS:
      init->add((int)0);
      ((IntValue&)init->get(i)).plus(ref.get(order_[i].second));
      break;
    case CHARS:
      init->add(((const StringValue&)ref.get(order_[i].second)).get_value().c_str(),strlen(((const StringValue&)ref.get(i)).get_value().c_str()));
      break;
    case DATES:
      init->add_date(((const DateValue&)ref.get(order_[i].second)).get_value());
      break;
    default:
      LOG_ERROR("Unsupportted agg type!");
      break;
    }
  }
  if(is_multi)
    return RC::ABORT;
  return RC::SUCCESS;
}

RC GroupTupleSet::aggregates(){
  for(int i =0;i!=input_->size();i++){
    const Tuple& row = input_->get(i);
    std::string key = get_key(row);
    if(!this->groups.count(key)){
      groups[key] = new Tuple;
      count[key] = 1;
      RC rc = init_tuple(groups[key],row);
      if(rc!= RC::SUCCESS)
        return rc;
    }
    else{
      Tuple* target = groups[key]; 
      count[key]++;
      for(int j=0;j!=this->agg_index.size();j++){
        switch (agg_index[j].second)
        {
        case ATF_SUM:
        case ATF_AVG:
          const_cast<TupleValue &>(target->get(agg_index[j].first)).plus(row.get(order_[agg_index[j].first].second));
          break;
        case ATF_MAX:
          const_cast<TupleValue &>(target->get(agg_index[j].first)).compare_and_set(row.get(order_[agg_index[j].first].second),true);
          break;
        case ATF_MIN:
          const_cast<TupleValue &>(target->get(agg_index[j].first)).compare_and_set(row.get(order_[agg_index[j].first].second),false);
          break;
        default:
          //ATF_COUNT
          break;
        }
      }
    }
  }



  for(auto it = groups.begin();it!=groups.end();it++){
    Tuple* grouprow = it->second;
    for(int j=0;j!=this->agg_index.size();j++){
      switch (agg_index[j].second)
        {
        case ATF_COUNT:{
          IntValue& iv = (IntValue&)grouprow->get(agg_index[j].first);
          iv.set_value(count[it->first]);
          break;
        }
        case ATF_AVG:{
          FloatValue& fv = (FloatValue&)grouprow->get(agg_index[j].first);
          if(count[it->first]==0)
            return::ABORT;
          fv.set_value((float)fv.get_value()/count[it->first]);
          break;
        }
        default:
          break;
        }
    }
  }
  return RC::SUCCESS;
}

RC GroupTupleSet::set_by_field(Selects* select,bool is_multitable){
  is_multi = is_multitable;
  const TupleSchema& input_schema = input_->get_schema();
  for(size_t j=0;j!=input_schema.size();j++){
    LOG_TRACE("Get tuplefiled %s.%s",input_schema.field(j).table_name(),input_schema.field(j).field_name());
  }
  if(is_multitable){
    for(size_t i=0;i!=select->group_attr_num;i++){
      for(size_t j=0;j!=input_schema.size();j++){
        //LOG_TRACE("Get tuplefiled %s.%s",input_schema.field(j).table_name(),input_schema.field(j).field_name());
        if(std::strcmp(select->group_attr[i].attribute_name,input_schema.field(j).field_name()) ==0
          && std::strcmp(select->group_attr[i].relation_name,input_schema.field(j).table_name())==0){
            by_index.push_back(j);
            break;
          }
      }
    }
  }
  else{
    for(size_t i=0;i!=select->group_attr_num;i++){
      for(size_t j=0;j!=input_schema.size();j++){
        //LOG_TRACE("Get tuplefiled %s.%s",input_schema.field(j).table_name(),input_schema.field(j).field_name());
        if(std::strcmp(select->group_attr[i].attribute_name,input_schema.field(j).field_name()) ==0){
            by_index.push_back(j);
            break;
          }
      }
    }
  }
  
  if(by_index.size()!=select->group_attr_num){
    LOG_INFO("missing group field");
    return RC::SCHEMA_FIELD_NOT_EXIST;
  }
  return RC::SUCCESS;
}

std::string GroupTupleSet::get_key(const Tuple& row){
  std::ostringstream stream;
  for(int i : this->by_index){
    row.get(i).to_string(stream);
    stream<<"|";
  }
  return stream.str();
}
RC GroupTupleSet::to_value(Value* value){
  if(groups.size()!=1){
    LOG_ERROR("Get %d groups",groups.size());
    return RC::ABORT;
  }
  Tuple* row = groups.begin()->second;

  if(row->size()!=1){
    LOG_ERROR("Get %d field",row->size());
    return RC::ABORT;
  }

  value->type = row->get(0).get_type();
  switch (value->type)
  {
  case INTS:
    value->data = new int(((const IntValue&)row->get(0)).get_value());
    break;
  case FLOATS:
    value->data = new float(((const FloatValue&)row->get(0)).get_value());
    LOG_DEBUG("Get multiagg value %f",((const FloatValue&)row->get(0)).get_value());
    break;
  case CHARS:
    value->data=strdup(((const StringValue&)row->get(0)).get_value().c_str());
    break;
  case DATES:
    value->data = new int(((const DateValue&)row->get(0)).get_value());
    break;
  default:
    LOG_ERROR("Unsupported type");
    return RC::ABORT;
    break;
  }
  return RC::SUCCESS;
}