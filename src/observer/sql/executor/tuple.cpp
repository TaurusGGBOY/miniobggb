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
  fields_.emplace_back(type, table_name, field_name);
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
  // TODO mark
  const TupleSchema &schema = tuple_set_.schema();
  Tuple tuple;
  const TableMeta &table_meta = table_->table_meta();
  for (const TupleField &field : schema.fields()) {
    const FieldMeta *field_meta = table_meta.field(field.field_name());
    assert(field_meta != nullptr);
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
};

RecordAggregater::RecordAggregater(Table& tab) : table_(tab){}

RecordAggregater::~ RecordAggregater(){
    //释放value，先判断类型避免delete void
    for(int i=0;i!=value_.size();i++){
      if(field_[i].second == ATF_COUNT){
        continue;
      }
      else{
        switch (field_[i].first->type())
        {
        case INTS:
        case DATES:
          delete (int*)value_[i];
          break;
        case FLOATS:
          delete (float*)value_[i];
          break;
        case CHARS:
          delete (char*)value_[i];
          break;
        default:
          break;
        }
      }
    }
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
      value_.push_back(nullptr);
      schema.add(INTS,table_.name(),schema_field_name(agg_field[i].attribute_name,agg_field[i].aggregation_type).c_str());
      continue;
    }
    else if(agg_field[i].aggregation_type == ATF_AVG){
      schema.add(FLOATS,table_.name(),schema_field_name(agg_field[i].attribute_name,agg_field[i].aggregation_type).c_str());
    }
    else{
      schema.add(fm->type(),table_.name(),schema_field_name(agg_field[i].attribute_name,agg_field[i].aggregation_type).c_str());
    }
    switch(fm->type()){
      //对不支持的类型插入一个空指针,目前只支持float,int
      case FLOATS:{
        float* tmp;
        if(agg_field[i].aggregation_type == ATF_MAX)
          tmp = new float(-std::numeric_limits<float>::max());
        else if(agg_field[i].aggregation_type == ATF_MIN)
          tmp = new float(std::numeric_limits<float>::max());
        else{
          tmp = new float(0);
        }
        value_.push_back(tmp);
      }
      break;
      case DATES:
      case INTS:{
        int* tmp;
        if(agg_field[i].aggregation_type == ATF_MAX)
          tmp = new int(INT32_MIN);
        else if(agg_field[i].aggregation_type == ATF_MIN)
          tmp = new int(INT32_MAX);
        else{
          tmp = new int(0);
        }
        value_.push_back(tmp);
      }
      break;
      case CHARS:{
        char* tmp = new char('\0');
        if(agg_field[i].aggregation_type == ATF_AVG || agg_field[i].aggregation_type == ATF_SUM){
          return RC::SCHEMA_FIELD_NOT_EXIST;
        }
        value_.push_back(tmp);
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
  for(int i=0;i!=field_.size();i++){
    if(value_[i]==nullptr){
      //不支持的类型
      continue;
    }
    void* field_data = malloc(sizeof(char)*field_[i].first->len());
    memcpy(field_data,(rec->data)+field_[i].first->offset(),field_[i].first->len());
    switch (field_[i].second)
    {
    //遍历过程对ATF_COUNT不做任何处理
    case ATF_MAX:
      {
        switch (field_[i].first->type())
        {
        case INTS:
        case DATES:
          *(int*)value_[i] = std::max(*(int*)value_[i],*(int*)field_data);
          break;
        case FLOATS:
          *(float*)value_[i] = std::max(*(float*)value_[i],*(float*)field_data);
          break;
        case CHARS:
          str_set_cmp(value_[i],field_data,true);
          break;
        default:
          return RC::SCHEMA_FIELD_TYPE_MISMATCH;
          break;
        }
      }
      break;
    case ATF_MIN:
      {
        switch (field_[i].first->type())
        {
        case INTS:
        case DATES:
          *(int*)value_[i] = std::min(*(int*)value_[i],*(int*)field_data);
          break;
        case FLOATS:
          *(float*)value_[i] = std::min(*(float*)value_[i],*(float*)field_data);
          break;
        case CHARS:
          str_set_cmp(value_[i],field_data,false);
          break;
        default:
          return RC::SCHEMA_FIELD_TYPE_MISMATCH;
          break;
        }
      }
      break;
    case ATF_SUM:
    case ATF_AVG:
      {
        switch (field_[i].first->type())
        {
        case INTS:
        case DATES:
          *(int*)value_[i] +=*(int*)field_data;
          break;
        case FLOATS:
          *(float*)value_[i] +=*(float*)field_data;
          break;
        default:
          return RC::SCHEMA_FIELD_TYPE_MISMATCH;
          break;
        }
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
    conditionvalue->type = FLOATS;
    conditionvalue->data = new float;
    if(rec_count==0){
      return RC::SCHEMA_FIELD_NOT_EXIST;
    }else{
      if(field_[0].first->type() == INTS)
        *((float*)conditionvalue->data) = (float)*(int*)value_[0]/(float)rec_count;
      else if(field_[0].first->type() == FLOATS)
        *((float*)conditionvalue->data) = *(float*)value_[0]/(float)rec_count;
      else if(field_[0].first->type() == DATES)
        *((int*)conditionvalue->data) = *(int*)value_[0]/rec_count;
      else
        return RC::SCHEMA_FIELD_NOT_EXIST;
    }
  }
    break;
  default:{
    conditionvalue->type = field_[0].first->type();
    switch(field_[0].first->type()){
      case INTS:
      case DATES:
        conditionvalue->data = new int(*(int*)value_[0]);
      break;
      case FLOATS:
        conditionvalue->data = new float(*(float*)value_[0]);
      break;
      case CHARS:
        conditionvalue->data = strdup((char*)value_[0]);
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
      tuple.add(rec_count);
      }
      break;
    case ATF_AVG:{
      if(rec_count==0){
        // float *ans = new float((float)*(int*)value_[i]/(float)rec_count);
        // free(value_[i]);
        // value_[i] = ans;
        tuple.add(-1);
      }else{
        if(field_[i].first->type() == INTS)
          tuple.add((float)*(int*)value_[i]/(float)rec_count);
        else if(field_[i].first->type() == FLOATS)
          tuple.add(*(float*)value_[i]/(float)rec_count);
        else if(field_[i].first->type() == DATES)
          tuple.add_date(*(int*)value_[i]/rec_count);
        else
          tuple.add(-1);
      }
    }
      break;
    default:{
      switch (field_[i].first->type())
      {
      case DATES:
        tuple.add_date(*(int*)value_[i]);
        break;
      case INTS:
        tuple.add(*(int*)value_[i]);
        break;
      case FLOATS:
        tuple.add(*(float*)value_[i]);
        break;
      case CHARS:
        tuple.add((char*)value_[i],std::min((int)strlen((char*)value_[i]),field_[i].first->len()));
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
