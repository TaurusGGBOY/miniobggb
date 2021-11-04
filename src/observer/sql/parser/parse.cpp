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
// Created by Longda on 2021/4/13.
//

#include <mutex>
#include "sql/parser/parse.h"
#include "rc.h"
#include "common/log/log.h"
#include<regex>
#include "../../storage/common/date.h"

RC parse(char *st, Query *sqln);

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

void order_attr_init(OrderAttr *relation_attr, const char *relation_name, const char *attribute_name, const char* is_asc) {
  if (relation_name != nullptr) {
    relation_attr->relation_name = strdup(relation_name);
  } else {
    relation_attr->relation_name = nullptr;
  }
  relation_attr->attribute_name = strdup(attribute_name);
  if(is_asc != nullptr) {

    relation_attr->is_asc = strdup(is_asc);
  } else {
    auto buf="asc";
    relation_attr->is_asc = strdup(buf);
  }
}

void order_attr_destroy(OrderAttr *relation_attr) {
  free(relation_attr->relation_name);
  free(relation_attr->attribute_name);
  free(relation_attr->is_asc);
  relation_attr->relation_name = nullptr;
  relation_attr->attribute_name = nullptr;
  relation_attr->is_asc = nullptr;
}

void relation_attr_init(RelAttr *relation_attr, const char *relation_name, const char *attribute_name) {
  if (relation_name != nullptr) {
    relation_attr->relation_name = strdup(relation_name);
  } else {
    relation_attr->relation_name = nullptr;
  }
  relation_attr->attribute_name = strdup(attribute_name);
}

void relation_attr_destroy(RelAttr *relation_attr) {
  free(relation_attr->relation_name);
  free(relation_attr->attribute_name);
  relation_attr->relation_name = nullptr;
  relation_attr->attribute_name = nullptr;
}

void value_init_integer(Value *value, int v) {
  value->type = INTS;
  value->data = malloc(sizeof(v));
  memcpy(value->data, &v, sizeof(v));
}
void value_init_float(Value *value, float v) {
  value->type = FLOATS;
  value->data = malloc(sizeof(v));
  memcpy(value->data, &v, sizeof(v));
}
void value_init_string(Value *value, const char *v) {
  value->type = CHARS;
  value->data = strdup(v);
}
void value_init_date(Value *value, const char *v) {
  value->type = DATES;
  Date& date = Date::get_instance();
  int date_stamp = date.date_to_int(strdup(v));
  if(date_stamp < 0){
    value->data = nullptr;
  }else{
    value->data = malloc(sizeof(date_stamp));
    memcpy(value->data, &date_stamp, sizeof(date_stamp));
  }
}
void value_init_null(Value *value) {
  value->type = NULLS;
}
void value_destroy(Value *value) {
  value->type = UNDEFINED;
  free(value->data);
  value->data = nullptr;
}

void condition_init(Condition *condition, CompOp comp, 
                    int left_is_attr, RelAttr *left_attr, Value *left_value,
                    int right_is_attr, RelAttr *right_attr, Value *right_value,
                    Aggregates* agg_left, Aggregates* agg_right) {
  //传入的condition的空间已经被使用过，所以需要保证每一个成员都被赋予正确的初始值
  LOG_TRACE("Enter");
  if(condition->left_agg_value!=nullptr||condition->right_agg_value!=nullptr){
    LOG_WARN("pointer leakage!");
  }
  condition->left_agg_value=nullptr;
  condition->right_agg_value=nullptr;
  condition->left_value.data = nullptr;
  condition->right_value.data = nullptr;
  condition->left_attr.attribute_name = nullptr;
  condition->left_attr.relation_name = nullptr;
  condition->right_attr.attribute_name = nullptr;
  condition->right_attr.relation_name = nullptr;

  condition->comp = comp;
  condition->left_is_attr = left_is_attr;
  if (left_is_attr) {
    condition->left_attr = *left_attr;
  } else {
    if(left_value==nullptr){
      condition->left_agg_value = new Aggregates;
      aggregates_copy_init(condition->left_agg_value,agg_left);
      LOG_TRACE("Get left aggregates subquery");
    }
    else
      condition->left_value = *left_value;
  }

  condition->right_is_attr = right_is_attr;
  if (right_is_attr) {
    condition->right_attr = *right_attr;
  } else {
    if(right_value==nullptr){
      condition->right_agg_value = new Aggregates;
      aggregates_copy_init(condition->right_agg_value,agg_right);
      LOG_TRACE("Get right aggregates subquery");
    }
    else
      condition->right_value = *right_value;
  }
  LOG_TRACE("Out");
}


void value_copy(Value* target, Value* object){
  LOG_TRACE("Enter");
  target->type = object->type;
  if(object->data!=nullptr)
    target->data = strdup((char*)object->data);
  LOG_TRACE("Out");
}

void relattr_copy(RelAttr* target,RelAttr* object){
  LOG_TRACE("Enter");
  if(object->relation_name!=nullptr)
    target->relation_name = strdup(object->relation_name);
  if(object->attribute_name!=nullptr)
    target->attribute_name = strdup(object->attribute_name);
  LOG_TRACE("out");
}

void condition_copy(Condition *target, Condition* object){
  LOG_TRACE("Enter");
  //子查询不需要深拷贝因为已经被深拷贝过不会在退栈时被释放
  target->left_is_attr = object->left_is_attr;
  target->right_is_attr = object->right_is_attr;
  value_copy(&target->left_value,&object->left_value);
  value_copy(&target->right_value,&object->right_value);
  relattr_copy(&target->left_attr,&object->left_attr);
  relattr_copy(&target->right_attr,&object->right_attr);
  target->left_agg_value = object->left_agg_value;
  target->right_agg_value = object->right_agg_value;
  target->comp = object->comp;
  LOG_TRACE("Out");
}

void condition_destroy(Condition *condition) {
  if (condition->left_is_attr) {
    relation_attr_destroy(&condition->left_attr);
  } else {
    value_destroy(&condition->left_value);
  }
  if (condition->right_is_attr) {
    relation_attr_destroy(&condition->right_attr);
  } else {
    value_destroy(&condition->right_value);
  }
  if(condition->left_agg_value!=nullptr){
    aggregates_destroy(condition->left_agg_value);
    condition->left_agg_value = nullptr;
  }
  if(condition->right_agg_value!=nullptr){
    aggregates_destroy(condition->right_agg_value);
    condition->right_agg_value=nullptr;
    }
}

void attr_info_init(AttrInfo *attr_info, const char *name, AttrType type, size_t length) {
  attr_info_init_with_null(attr_info, name, type, length, 0);
}

void attr_info_init_with_null(AttrInfo *attr_info, const char *name, AttrType type, size_t length, int nullable) {
  LOG_INFO("%s, %d, %d", name, (int)type, length);
  attr_info->name = strdup(name);
  attr_info->type = type;
  attr_info->length = length;
  attr_info->nullable = nullable;
}

void attr_info_destroy(AttrInfo *attr_info) {
  free(attr_info->name);
  attr_info->name = nullptr;
}

//unused
void selects_init(Selects *selects, ...);
void selects_append_order_attr(Selects *selects, OrderAttr *rel_attr) {
  selects->order_attr[selects->order_attr_num++] = *rel_attr;
}
void selects_append_attribute(Selects *selects, RelAttr *rel_attr) {
  selects->attributes[selects->attr_num++] = *rel_attr;
}
void selects_append_relation(Selects *selects, const char *relation_name) {
  selects->relations[selects->relation_num++] = strdup(relation_name);
}

void selects_append_conditions(Selects *selects, Condition conditions[], size_t condition_num) {
  LOG_TRACE("Enter");
  assert(condition_num <= sizeof(selects->conditions)/sizeof(selects->conditions[0]));
  for (size_t i = 0; i < condition_num; i++) {
    //selects->conditions[i] = conditions[i];
    condition_copy(&selects->conditions[i],&conditions[i]);
  }
  selects->condition_num = condition_num;
  LOG_TRACE("Out");
}

void selects_destroy(Selects *selects) {
  for (size_t i = 0; i < selects->attr_num; i++) {
    relation_attr_destroy(&selects->attributes[i]);
  }
  selects->attr_num = 0;

  for (size_t i = 0; i < selects->relation_num; i++) {
    free(selects->relations[i]);
    selects->relations[i] = NULL;
  }
  selects->relation_num = 0;

  for (size_t i = 0; i < selects->condition_num; i++) {
    condition_destroy(&selects->conditions[i]);
  }
  selects->condition_num = 0;
  for(size_t i = 0; i < selects->order_attr_num; i++) {
    order_attr_destroy(&selects->order_attr[i]);
  }
  selects->order_attr_num=0;
}

void inserts_init(Inserts *inserts, const char *relation_name, Value values[MAX_NUM][MAX_NUM],size_t value_length_list[MAX_NUM],size_t value_num) {
  //assert(value_num <= sizeof(inserts->values)/sizeof(inserts->values[0]));

  inserts->relation_name = strdup(relation_name);
  for (size_t i = 0; i < value_num; i++) {
    for(int j=0;j<value_length_list[i];++j) {
      inserts->values_list[i][j]=values[i][j];
    }
    inserts->value_length_list[i]=value_length_list[i];
  }
  inserts->value_num = value_num;
  // LOG_DEBUG("values number is %d", value_num);
}
void inserts_destroy(Inserts *inserts) {
  free(inserts->relation_name);
  inserts->relation_name = nullptr;
  for (size_t i = 0; i < inserts->value_num; i++) {
    for(size_t j = 0;j<inserts->value_length_list[i];++j)
    value_destroy(&inserts->values_list[i][j]);
  }

  for (size_t i = 0; i < inserts->value_num; i++) {
    value_destroy(&inserts->values[i]);
  }
  inserts->value_num = 0;
}

void deletes_init_relation(Deletes *deletes, const char *relation_name) {
  deletes->relation_name = strdup(relation_name);
}

void deletes_set_conditions(Deletes *deletes, Condition conditions[], size_t condition_num) {
  assert(condition_num <= sizeof(deletes->conditions)/sizeof(deletes->conditions[0]));
  for (size_t i = 0; i < condition_num; i++) {
    deletes->conditions[i] = conditions[i];
  }
  deletes->condition_num = condition_num;
}
void deletes_destroy(Deletes *deletes) {
  for (size_t i = 0; i < deletes->condition_num; i++) {
    condition_destroy(&deletes->conditions[i]);
  }
  deletes->condition_num = 0;
  free(deletes->relation_name);
  deletes->relation_name = nullptr;
}

void updates_init(Updates *updates, const char *relation_name, const char *attribute_name,
                  Value *value, Condition conditions[], size_t condition_num) {
  updates->relation_name = strdup(relation_name);
  updates->attribute_name = strdup(attribute_name);
  updates->value = *value;
  //date input de shi const char *
  // date store int
  // date  values->gaichengyige

  assert(condition_num <= sizeof(updates->conditions)/sizeof(updates->conditions[0]));
  for (size_t i = 0; i < condition_num; i++) {
    updates->conditions[i] = conditions[i];
  }
  updates->condition_num = condition_num;
}

void updates_destroy(Updates *updates) {
  free(updates->relation_name);
  free(updates->attribute_name);
  updates->relation_name = nullptr;
  updates->attribute_name = nullptr;

  value_destroy(&updates->value);

  for (size_t i = 0; i < updates->condition_num; i++) {
    condition_destroy(&updates->conditions[i]);
  }
  updates->condition_num = 0;
}

void aggregates_init(Aggregates *aggregates,const char *relation_name, 
                      Condition conditions[], size_t condition_num)
{
  LOG_TRACE("Enter");
  //CONTEXT的空间在yacc中分配，此函数需分配aggregate中的指针
  aggregates->relation_name = strdup(relation_name);
  assert(condition_num <= sizeof(aggregates->conditions)/sizeof(aggregates->conditions[0]));
  for (size_t i = 0; i < condition_num; i++) {
    //aggregates->conditions[i] = conditions[i];
    condition_copy(&aggregates->conditions[i],&conditions[i]);
  }
  aggregates->condition_num = condition_num;
  LOG_TRACE("Out");
}
void aggregates_copy_init(Aggregates* target,Aggregates* object){
  target->relation_name = strdup(object->relation_name);
  LOG_DEBUG("relation name in aggregates_copy_init is %s",target->relation_name);
  for (size_t i = 0; i < object->condition_num; i++) {
    //target->conditions[i] = object->conditions[i];
    condition_copy(&target->conditions[i],&object->conditions[i]);
  }
  for(size_t i=0;i!=object->field_num;i++){
    target->field[i].aggregation_type = object->field[i].aggregation_type;
    target->field[i].attribute_name = strdup(object->field[i].attribute_name);
  }
  target->condition_num = object->condition_num;
  target->field_num = object->field_num;
}


void aggregates_destroy(Aggregates *aggregates){
  free(aggregates->relation_name);
  aggregates->relation_name = nullptr;
  for (size_t i = 0; i < aggregates->condition_num; i++) {
    condition_destroy(&aggregates->conditions[i]);
  }
  aggregates->condition_num = 0;
  //对aggfield中指针的销毁
  for (size_t i=0;i!=aggregates->field_num;i++){
    free(aggregates->field[aggregates->field_num].attribute_name);
    aggregates->field[aggregates->field_num].attribute_name = nullptr;
  }
  aggregates->field_num = 0;
}
void aggregates_append_field_itoa(Aggregates *aggregates,int number,
                           const char* type_name){
    std::string attr_name = std::to_string(number);
    aggregates_append_field(aggregates,attr_name.c_str(),type_name);
}
void aggregates_append_field(Aggregates *aggregates,const char *attribute_name,
                           const char* type_name)
{
  aggregates->field[aggregates->field_num].attribute_name = strdup(attribute_name);
  std::string typestr(type_name,strlen(type_name));
  if(std::regex_match(typestr,std::regex("[Mm][Aa][Xx]"))){
    aggregates->field[aggregates->field_num].aggregation_type = ATF_MAX;
    LOG_INFO("append aggregation type MAX");
  }
  else if(std::regex_match(typestr,std::regex("[Mm][Ii][Nn]"))){
    aggregates->field[aggregates->field_num].aggregation_type = ATF_MIN;
    LOG_INFO("append aggregation type MIN");
  }
  else if(std::regex_match(typestr,std::regex("[Ss][Uu][Mm]"))){
    aggregates->field[aggregates->field_num].aggregation_type = ATF_SUM;
    LOG_INFO("append aggregation type SUM");
  }else if(std::regex_match(typestr,std::regex("[Aa][Vv][Gg]"))){
    aggregates->field[aggregates->field_num].aggregation_type = ATF_AVG;
    LOG_INFO("append aggregation type AVG");
  }else if(std::regex_match(typestr,std::regex("[Cc][Oo][Uu][Nn][Tt]"))){
    aggregates->field[aggregates->field_num].aggregation_type = ATF_COUNT;
    LOG_INFO("append aggregation type COUNT");
  }else{
    LOG_ERROR("failed to parse aggregation type of %s(%s)!",typestr.c_str(),attribute_name);
  }
  aggregates->field_num++;
}

void create_table_append_attribute(CreateTable *create_table, AttrInfo *attr_info) {
  create_table->attributes[create_table->attribute_count++] = *attr_info;
}
void create_table_init_name(CreateTable *create_table, const char *relation_name) {
  create_table->relation_name = strdup(relation_name);
}
void create_table_destroy(CreateTable *create_table) {
  for (size_t i = 0; i < create_table->attribute_count; i++) {
    attr_info_destroy(&create_table->attributes[i]);
  }
  create_table->attribute_count = 0;
  free(create_table->relation_name);
  create_table->relation_name = nullptr;
}

void drop_table_init(DropTable *drop_table, const char *relation_name) {
  drop_table->relation_name = strdup(relation_name);
}
void drop_table_destroy(DropTable *drop_table) {
  free(drop_table->relation_name);
  drop_table->relation_name = nullptr;
}

void create_index_init(CreateIndex *create_index, const char *index_name, 
                       const char *relation_name, const char *attr_name, int unique) {
  create_index->index_name = strdup(index_name);
  create_index->relation_name = strdup(relation_name);
  create_index->attribute_name = strdup(attr_name);
  create_index->unique = unique;
}

void create_index_destroy(CreateIndex *create_index) {
  free(create_index->index_name);
  free(create_index->relation_name);
  free(create_index->attribute_name);

  create_index->index_name = nullptr;
  create_index->relation_name = nullptr;
  create_index->attribute_name = nullptr;
}

void drop_index_init(DropIndex *drop_index, const char *index_name) {
  drop_index->index_name = strdup(index_name);
}
void drop_index_destroy(DropIndex *drop_index) {
  free((char *)drop_index->index_name);
  drop_index->index_name = nullptr;
}

void desc_table_init(DescTable *desc_table, const char *relation_name) {
  desc_table->relation_name = strdup(relation_name);
}

void desc_table_destroy(DescTable *desc_table) {
  free((char *)desc_table->relation_name);
  desc_table->relation_name = nullptr;
}

void load_data_init(LoadData *load_data, const char *relation_name, const char *file_name) {
  load_data->relation_name = strdup(relation_name);

  if (file_name[0] == '\'' || file_name[0] == '\"') {
    file_name++;
  }
  char *dup_file_name = strdup(file_name);
  int len = strlen(dup_file_name);
  if (dup_file_name[len - 1] == '\'' || dup_file_name[len - 1] == '\"') {
    dup_file_name[len - 1] = 0;
  }
  load_data->file_name = dup_file_name;
}

void load_data_destroy(LoadData *load_data) {
  free((char *)load_data->relation_name);
  free((char *)load_data->file_name);
  load_data->relation_name = nullptr;
  load_data->file_name = nullptr;
}

void query_init(Query *query) {
  query->flag = SCF_ERROR;
  memset(&query->sstr, 0, sizeof(query->sstr));
}

Query *query_create() {
  Query *query = (Query *)malloc(sizeof(Query));
  if (nullptr == query) {
    LOG_ERROR("Failed to alloc memroy for query. size=%ld", sizeof(Query));
    return nullptr;
  }

  query_init(query);
  return query;
}

void query_reset(Query *query) {
  switch (query->flag) {
    case SCF_SELECT: {
      selects_destroy(&query->sstr.selection);
    }
    break;
    case SCF_INSERT: {
      inserts_destroy(&query->sstr.insertion);
    }
    break;
    case SCF_DELETE: {
      deletes_destroy(&query->sstr.deletion);
    }
    break;
    case SCF_UPDATE: {
      updates_destroy(&query->sstr.update);
    }
    break;
    case SCF_AGGREGATE:{
      aggregates_destroy(&query->sstr.aggregation);
    }
    break;
    case SCF_CREATE_TABLE: {
      create_table_destroy(&query->sstr.create_table);
    }
    break;
    case SCF_DROP_TABLE: {
      drop_table_destroy(&query->sstr.drop_table);
    }
    break;
    case SCF_CREATE_INDEX: {
      create_index_destroy(&query->sstr.create_index);
    }
    break;
    case SCF_DROP_INDEX: {
      drop_index_destroy(&query->sstr.drop_index);
    }
    break;
    case SCF_SYNC: {

    }
    break;
    case SCF_SHOW_TABLES:
    break;

    case SCF_DESC_TABLE: {
      desc_table_destroy(&query->sstr.desc_table);
    }
    break;

    case SCF_LOAD_DATA: {
      load_data_destroy(&query->sstr.load_data);
    }
    break;
    case SCF_BEGIN:
    case SCF_COMMIT:
    case SCF_ROLLBACK:
    case SCF_HELP:
    case SCF_EXIT:
    case SCF_ERROR:
    break;
  }
}

void query_destroy(Query *query) {
  query_reset(query);
  free(query);
}

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

////////////////////////////////////////////////////////////////////////////////

extern "C" int sql_parse(const char *st, Query  *sqls);

RC parse(const char *st, Query *sqln) {
  sql_parse(st, sqln);

  if (sqln->flag == SCF_ERROR)
    return SQL_SYNTAX;
  else
    return SUCCESS;
}