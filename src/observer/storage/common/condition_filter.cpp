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
// Created by Wangyunlai on 2021/5/7.
//

#include <stddef.h>
#include "condition_filter.h"
#include "record_manager.h"
#include "common/log/log.h"
#include "storage/common/table.h"
#include "storage/common/date.h"
#include "storage/common/bitmap.h"
#include "sql/executor/tuple.h"
#include "storage/default/default_handler.h"

using namespace common;

ConditionFilter::~ConditionFilter()
{}

DefaultConditionFilter::DefaultConditionFilter()
{
  left_.is_attr = false;
  left_.attr_length = 0;
  left_.attr_offset = 0;
  left_.value = nullptr;
  left_.table_name="";
  left_.attr_pos = 0;

  right_.is_attr = false;
  right_.attr_length = 0;
  right_.attr_offset = 0;
  right_.value = nullptr;
  right_.table_name="";
  right_.attr_pos = 0;
}
DefaultConditionFilter::~DefaultConditionFilter()
{}

RC DefaultConditionFilter::init(const ConDesc &left, const ConDesc &right, AttrType attr_type, CompOp comp_op)
{
  LOG_TRACE("Enter");
  if (attr_type < CHARS || attr_type > DATES) {
    LOG_ERROR("Invalid condition with unsupported attribute type: %d", attr_type);
    return RC::INVALID_ARGUMENT;
  }

  if (comp_op < EQUAL_TO || comp_op >= NO_OP) {
    LOG_ERROR("Invalid condition with unsupported compare operation: %d", comp_op);
    return RC::INVALID_ARGUMENT;
  }
  left_ = left;
  right_ = right;
  attr_type_ = attr_type;
  comp_op_ = comp_op;
  return RC::SUCCESS;
}

RC DefaultConditionFilter::init(Table &table, const Condition &condition)
{
  LOG_TRACE("Enter");
  const TableMeta &table_meta = table.table_meta();
  ConDesc left;
  ConDesc right;

  AttrType type_left = UNDEFINED;
  AttrType type_right = UNDEFINED;

  if (1 == condition.left_is_attr) {
    left.is_attr = true;
    const FieldMeta *field_left = table_meta.field(condition.left_attr.attribute_name);
    LOG_DEBUG("get left condition field %s",condition.left_attr.attribute_name);
    if (nullptr == field_left) {
      LOG_WARN("No such field in condition. %s.%s", table.name(), condition.left_attr.attribute_name);
      return RC::SCHEMA_FIELD_MISSING;
    }
    left.attr_length = field_left->len();
    left.attr_offset = field_left->offset();
    left.table_name = strdup(table.name());
    left.attr_pos = table_meta.field_index(field_left->name());
    left.value = nullptr;
    type_left = field_left->type();
  } else {
    left.is_attr = false;
    LOG_DEBUG("get left condition value %d",*(int*)condition.left_value.data);
    left.value = condition.left_value.data;  // 校验type 或者转换类型
    type_left = condition.left_value.type;
    left.attr_length = 0;
    left.attr_offset = 0;
  }

  if (1 == condition.right_is_attr) {
    right.is_attr = true;
    const FieldMeta *field_right = table_meta.field(condition.right_attr.attribute_name);
    LOG_DEBUG("get right condition field %s",condition.right_attr.attribute_name);
    if (nullptr == field_right) {
      LOG_WARN("No such field in condition. %s.%s", table.name(), condition.right_attr.attribute_name);
      return RC::SCHEMA_FIELD_MISSING;
    }
    right.attr_length = field_right->len();
    right.attr_offset = field_right->offset();
    right.table_name = strdup(table.name());
    right.attr_pos = table_meta.field_index(field_right->name());
    right.value = nullptr;
    type_right = field_right->type();
  } else {
    LOG_DEBUG("get right condition value %d",*(int*)condition.right_value.data);
    right.is_attr = false;
    right.value = condition.right_value.data;
    type_right = condition.right_value.type;

    right.attr_length = 0;
    right.attr_offset = 0;
  }
  LOG_DEBUG("get comp %d",condition.comp);

  // 校验和转换
  //  if (!field_type_compare_compatible_table[type_left][type_right]) {
  //    // 不能比较的两个字段， 要把信息传给客户端
  //    return RC::SCHEMA_FIELD_TYPE_MISMATCH;
  //  }
  if(condition.comp == IN && type_left!=type_right){
    return RC::SCHEMA_FIELD_TYPE_MISMATCH;
  }
  if(condition.comp == IN && right.is_attr){
    LOG_ERROR("Right attr of in select");
  }

  // 整数跟浮点数之间的对比
  if (type_left != type_right) {
    if(type_left == DATES && type_right ==CHARS){
      Date &date = Date::get_instance();
      int date_int = date.date_to_int((const char*)condition.right_value.data);
      if(date_int < 0){
        return RC::SCHEMA_FIELD_TYPE_MISMATCH;
      }
      // TODO memory leakage
      right.value = new int(date_int);
      type_right = DATES;
    }else if(type_left==CHARS && type_right==DATES){
      Date &date = Date::get_instance();
      int date_int = date.date_to_int((const char *)condition.left_value.data); 
      if (date_int < 0){
        return RC::SCHEMA_FIELD_TYPE_MISMATCH;
      }
      // TODO memory leakage
      left.value = new int(date_int);
      type_left = DATES;
    }else if(type_left==INTS && type_right==FLOATS){
      if(left.is_attr){
        differ_type = true;
      }
      else{
        left.value = new float(*(int*)condition.left_value.data);
      }
    }else if(type_left==FLOATS && type_right==INTS){
      if(left.is_attr){
        right.value = new float(*(int*)condition.right_value.data);
      }
      else{
        differ_type = true;
        type_left = INTS;
      }
    }else if (type_left==NULLS){
      left.value=nullptr;
      if(type_right==NULLS){
        right.value = nullptr;
      }
    }else if (type_right==NULLS){
      right.value=nullptr;
      if(type_left==NULLS){
        left.value = nullptr;
      }
    }else{
      return RC::SCHEMA_FIELD_TYPE_MISMATCH;
    }
  }
  LOG_TRACE("exit");
  return init(left, right, type_left, condition.comp);
}

bool DefaultConditionFilter::filter(const Record &rec) const
{
  LOG_TRACE("enter");
  char *left_value = nullptr;
  char *right_value = nullptr;

  int bitmap_offset  = 4;
  Bitmap &bitmap = Bitmap::get_instance();

  if (bitmap.get_null_at_index(rec.data + bitmap_offset, left_.attr_pos - 2) == 1){
    left_value = nullptr;
  }else{
    if (left_.is_attr) {  // value
        left_value = (char*)(rec.data + left_.attr_offset);
    } else {
        if (left_.value != nullptr)
            left_value = (char*)left_.value;
        else 
            left_value = nullptr;
    }
  }

  if (bitmap.get_null_at_index(rec.data + bitmap_offset, right_.attr_pos - 2) == 1) {
      right_value = nullptr;
  } else {
      if (right_.is_attr) {
          right_value = (char*)(rec.data + right_.attr_offset);
      } else {
          if (right_.value != nullptr) {
              right_value = (char*)right_.value;
          } else {
              right_value = nullptr;
          }
      }
  }

  if(comp_op_==IN){
    LOG_TRACE("count in");
    std::unordered_set<int>* in_set = (std::unordered_set<int>*) right_.value;
    LOG_TRACE("filter value %d",*reinterpret_cast<int*>(left_value));
    return in_set->count(*reinterpret_cast<int*>(left_value));
  }

  float cmp_result = 0;
  if(left_value != nullptr && right_value != nullptr){
    switch (attr_type_) {
      case CHARS: {  // 字符串都是定长的，直接比较
        // 按照C字符串风格来定
        cmp_result = (float)strcmp(left_value, right_value);
      } break;
      case DATES:
      case INTS: {
        // 没有考虑大小端问题
        // 对int和float，要考虑字节对齐问题,有些平台下直接转换可能会跪
        if(differ_type){
          float left;
          float right;
          if(left_.is_attr){
            left = (float)*(int*)left_value;
            right = *(float*)right_value;
          }
          else{
            left = *(float*)left_value;
            right = (float)*(int*)right_value;
          }
          cmp_result = left - right;
        }
        else{
          int left = *(int *)left_value;
          int right = *(int *)right_value;
          cmp_result = (float)(left - right);
        }
        
      } break;
      case FLOATS: {
        float left = *(float *)left_value;
        float right = *(float *)right_value;
        cmp_result = left - right;
      } break;
      default: {
      }
    }
  }
  
  switch (comp_op_)
  {
    case EQUAL_TO:
      if (left_value == nullptr || right_value == nullptr){
        return false;
      }
      else{
        return 0 == cmp_result;
      }
    case LESS_EQUAL:
      if (left_value == nullptr || right_value == nullptr){
        return false;
      }
      else{
        return cmp_result <= 0;
      }
    case NOT_EQUAL:
      if (left_value == nullptr || right_value == nullptr){
        return false;
      }
      else{
        return cmp_result != 0;
      }
    case LESS_THAN:
      if (left_value == nullptr || right_value == nullptr){
        return false;
      }
      else{
        return cmp_result < 0;
      }
    case GREAT_EQUAL:
      if (left_value == nullptr || right_value == nullptr){
        return false;
      }
      else{
        return cmp_result >= 0;
      }
    case GREAT_THAN:
      if (left_value == nullptr || right_value == nullptr){
        return false;
      }
      else{
        return cmp_result > 0;
      }
    case IS_NULL:
      return left_value == nullptr && right_value == nullptr;
    case IS_NOT_NULL:
      return left_value != nullptr  || right_value != nullptr;
    default:
      break;
  }

  LOG_PANIC("Never should print this.");
  return cmp_result;  // should not go here
}

CompositeConditionFilter::~CompositeConditionFilter()
{
  if (memory_owner_) {
    delete[] filters_;
    filters_ = nullptr;
  }
}

RC CompositeConditionFilter::init(const ConditionFilter *filters[], int filter_num, bool own_memory)
{
  filters_ = filters;
  filter_num_ = filter_num;
  memory_owner_ = own_memory;
  return RC::SUCCESS;
}
RC CompositeConditionFilter::init(const ConditionFilter *filters[], int filter_num)
{
  return init(filters, filter_num, false);
}

RC CompositeConditionFilter::init(Table &table, const Condition *conditions, int condition_num)
{
  LOG_TRACE("Enter");
  if (condition_num == 0) {
    return RC::SUCCESS;
  }
  if (conditions == nullptr) {
    return RC::INVALID_ARGUMENT;
  }

  RC rc = RC::SUCCESS;
  ConditionFilter **condition_filters = new ConditionFilter *[condition_num];
  for (int i = 0; i < condition_num; i++) {
    DefaultConditionFilter *default_condition_filter = new DefaultConditionFilter();
    rc = default_condition_filter->init(table, conditions[i]);
    if (rc != RC::SUCCESS) {
      delete default_condition_filter;
      for (int j = i - 1; j >= 0; j--) {
        delete condition_filters[j];
        condition_filters[j] = nullptr;
      }
      delete[] condition_filters;
      condition_filters = nullptr;
      return rc;
    }
    condition_filters[i] = default_condition_filter;
  }
  return init((const ConditionFilter **)condition_filters, condition_num, true);
}

bool CompositeConditionFilter::filter(const Record &rec) const
{
  for (int i = 0; i < filter_num_; i++) {
    if (!filters_[i]->filter(rec)) {
      return false;
    }
  }
  return true;
}

static RC record_reader_select_value(Record* record,void* context){
  SetRecordConverter &converter = *(SetRecordConverter*)context;
  return converter.add_record(record);
}

RC ConditionSubQueryhandler::select_to_value(Selects* select,Value* value){
  LOG_TRACE("Enter");
  RC rc;
  rc = check_main_query(select->conditions,select->condition_num);
  if(rc!=RC::SUCCESS)
    return rc;
  if(select->relation_num!=1||select->attr_num!=1){
    LOG_WARN("Get relation num %d attr num %d",select->relation_num,select->attr_num);
    return RC::SCHEMA_FIELD_REDUNDAN;
  }
  Table* table = DefaultHandler::get_default().find_table(db_name,select->relations[0]);
  LOG_TRACE("Enter");
  if (nullptr == table) {
    LOG_WARN("No such table [%s] in db [%s]", select->relations[0], db_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }
  LOG_TRACE("Enter");
  const FieldMeta* fm = table->table_meta_.field(select->attributes->attribute_name);
  if(fm==nullptr)
    return RC::SCHEMA_FIELD_NOT_EXIST;
  LOG_TRACE("Enter");
  value->data = new std::unordered_set<int>;
  value->type = fm->type();
  LOG_TRACE("Enter");
  CompositeConditionFilter condition_filter;
  rc = condition_filter.init(*table,select->conditions,select->condition_num);
  if(rc!=RC::SUCCESS)
    return rc;
  SetRecordConverter setconverter(table,(std::unordered_set<int>*) value->data, fm);
  rc = table->scan_record(this->trx, &condition_filter,-1,(void*)&setconverter,record_reader_select_value);
  return rc;
}

static RC record_reader_aggregate_adapter(Record* record,void* context){
  RecordAggregater &aggregater = *(RecordAggregater*)context;
  return aggregater.update_record(record);
}
//提供在查询条件中将聚合字段作为返回值,返回一个标量
RC ConditionSubQueryhandler::aggregate_value(Trx* trx,Table* table,char* attr_name, AggregationTypeFlag flag, 
                    Value* value_,CompositeConditionFilter* filter){
    AggregatesField field{attr_name,flag};
    RecordAggregater aggregater(*table);
    RC rc = aggregater.set_field(&field,1);
    if(rc !=SUCCESS)
      return rc;
    rc = table->scan_record(trx, filter, -1, (void *)&aggregater, record_reader_aggregate_adapter);
    if(rc !=SUCCESS)
      return rc;
    rc = aggregater.get_condition_value(value_);
    return rc;
}
RC ConditionSubQueryhandler::aggregate_to_value(Aggregates* aggregate, Value* value){
  LOG_TRACE("Enter");
  RC rc;
  for(size_t i=0;i!=aggregate->condition_num;i++){
    if(!aggregate->conditions[i].left_is_attr&&aggregate->conditions[i].left_agg_value!=nullptr){
      LOG_DEBUG("The field name of subagg is %s",aggregate->conditions[i].left_agg_value->field->attribute_name);
      rc = aggregate_to_value(aggregate->conditions[i].left_agg_value,&aggregate->conditions[i].left_value);
      if(aggregate->conditions[i].left_value.type==INTS)
        LOG_DEBUG("get value %d",*(int*)aggregate->conditions[i].left_value.data);
    }
    if(rc!=RC::SUCCESS)
      return rc;
    if(!aggregate->conditions[i].right_is_attr&&aggregate->conditions[i].right_agg_value!=nullptr){
      LOG_DEBUG("The field name of subagg is %s",aggregate->conditions[i].right_agg_value->field->attribute_name);
      rc = aggregate_to_value(aggregate->conditions[i].right_agg_value,&aggregate->conditions[i].right_value);
      if(aggregate->conditions[i].right_value.type==INTS)
        LOG_DEBUG("get value %d",*(int*)aggregate->conditions[i].right_value.data);
    }
    if(rc!=RC::SUCCESS)
      return rc;
    if(aggregate->conditions[i].in_select!=nullptr){
      rc = select_to_value(aggregate->conditions[i].in_select,&aggregate->conditions[i].right_value);
    }
  }
  LOG_TRACE("Enter");
  //处理aggreagates
  if(aggregate->field_num>1)
    return RC::SCHEMA_FIELD_REDUNDAN;
  Table* table = DefaultHandler::get_default().find_table(db_name,aggregate->relation_name);
  if (nullptr == table) {
    LOG_WARN("No such table [%s] in db [%s]", aggregate->relation_name, db_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }
  CompositeConditionFilter condition_filter;
  rc = condition_filter.init(*table,aggregate->conditions,aggregate->condition_num);
  if(rc!=RC::SUCCESS)
    return rc;
  rc = aggregate_value(trx,table,aggregate->field->attribute_name,aggregate->field->aggregation_type,value,&condition_filter);
  if(rc!=RC::SUCCESS)
    return rc;
  LOG_TRACE("Out");
  return rc;
  
}

RC ConditionSubQueryhandler::check_main_query(Condition* condition,int condition_num){
  RC rc;
  LOG_TRACE("Start condition subquery check");
  for(size_t i=0;i!=condition_num;i++){
    if((condition+i)->in_select!=nullptr){
      LOG_TRACE("Get sub select");
      rc = select_to_value((condition+i)->in_select,&(condition+i)->right_value);
    }
    if(rc!=RC::SUCCESS)
      return rc;
    if(!(condition+i)->left_is_attr&&(condition+i)->left_agg_value!=nullptr){
      LOG_DEBUG("The field name of subagg is %s",(condition+i)->left_agg_value->field->attribute_name);
      rc = aggregate_to_value((condition+i)->left_agg_value,&(condition+i)->left_value);
      if((condition+i)->left_value.type==INTS)
        LOG_DEBUG("get value %d",*(int*)(condition+i)->left_value.data);
    }
    if(rc!=RC::SUCCESS)
      return rc;
    if(!(condition+i)->right_is_attr&&(condition+i)->right_agg_value!=nullptr){
      LOG_DEBUG("The field name of subagg is %s",(condition+i)->right_agg_value->field->attribute_name);
      rc = aggregate_to_value((condition+i)->right_agg_value,&(condition+i)->right_value);
      if((condition+i)->right_value.type==INTS)
        LOG_DEBUG("get value %d",*(int*)(condition+i)->right_value.data);
    }
    if(rc!=RC::SUCCESS)
      return rc;
    
  }
  LOG_TRACE("End condition subquery check");
  return rc;
}