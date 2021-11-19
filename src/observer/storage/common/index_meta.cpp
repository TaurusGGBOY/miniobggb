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
// Created by wangyunlai.wyl on 2021/5/18.
//

#include "storage/common/index_meta.h"
#include "storage/common/field_meta.h"
#include "storage/common/table_meta.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "rc.h"
#include "json/json.h"

const static Json::StaticString FIELD_NAME("name");
const static Json::StaticString FIELD_FIELD_NAME("field_name");
const static Json::StaticString FIELD_UNIQUE("unique");

RC IndexMeta::init(const char *name, const FieldMeta &field) {
  return init(name,field,false);
}

RC IndexMeta::init(const char *name, const FieldMeta &field, int unique) {
  if (nullptr == name || common::is_blank(name)) {
    return RC::INVALID_ARGUMENT;
  }

  name_ = name;
  field_ = field.name();
  unique_ = unique;
  return RC::SUCCESS;
}

RC IndexMeta::init(const char *name, std::vector<std::string> field_list) {
    if (nullptr == name || common::is_blank(name)) {
        return RC::INVALID_ARGUMENT;
    }
    name_ = name;
    for (int i = 0; i<field_list.size();i++){
      field_list_[i] = field_list[i];
    }
    unique_ = 0;
    return RC::SUCCESS;
}

void IndexMeta::to_json(Json::Value &json_value) const {
  json_value[FIELD_NAME] = name_;
  json_value[FIELD_FIELD_NAME] = field_;
  json_value[FIELD_UNIQUE] = unique_;
}

RC IndexMeta::from_json(const TableMeta &table, const Json::Value &json_value, IndexMeta &index) {
  const Json::Value &name_value = json_value[FIELD_NAME];
  const Json::Value &field_value = json_value[FIELD_FIELD_NAME];
  const Json::Value &unique_value = json_value[FIELD_UNIQUE];
  if (!name_value.isString()) {
    LOG_ERROR("Index name is not a string. json value=%s", name_value.toStyledString().c_str());
    return RC::GENERIC_ERROR;
  }

  if (!field_value.isString()) {
    LOG_ERROR("Field name of index [%s] is not a string. json value=%s",
              name_value.asCString(), field_value.toStyledString().c_str());
    return RC::GENERIC_ERROR;
  }

  if (!unique_value.isInt()) {
  LOG_ERROR("Field name of index [%s] is not a int. json value=%s",
            unique_value.asInt(), unique_value.toStyledString().c_str());
  return RC::GENERIC_ERROR;
  }

  const FieldMeta *field = table.field(field_value.asCString());
  if (nullptr == field) {
    LOG_ERROR("Deserialize index [%s]: no such field: %s", name_value.asCString(), field_value.asCString());
    return RC::SCHEMA_FIELD_MISSING;
  }

  return index.init(name_value.asCString(), *field, unique_value.asInt());
}

const char *IndexMeta::name() const {
  return name_.c_str();
}

const char *IndexMeta::field() const {
  return field_.c_str();
}

const int IndexMeta::unique() const{
  return unique_;
}

void IndexMeta::desc(std::ostream &os) const {
  os << "index name=" << name_
      << ", field=" << field_
      << ", unique=" << unique_;
}

const int IndexMeta::field_num() const{
  return field_num_;
}

  // return 0 if any one is same
 const int IndexMeta::have_one(std::vector<std::string> field_list) const{
    for (int i = 0; i < field_list.size(); i++) {
        for (int j = 0; j < field_num_; j++) {
            if (field_list_[j].compare(field_list[i]) == 0) {
                return 0;
            }
        }
    }
  return -1;
}

const int IndexMeta::compare_multi_index(std::vector<std::string> field_list) const{
  int cmp = 0;
  if(field_list_->size()!=field_list.size()){
    return field_list_->size()-field_list.size();
  }
  for (int i = 0; i < field_list.size(); i++) {
    cmp = field_list_[i].compare(field_list[i]);
      if (cmp != 0) {
          return cmp;
      }
  }
  return cmp;
}