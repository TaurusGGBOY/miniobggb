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

#ifndef __OBSERVER_SQL_EXECUTOR_TUPLE_H_
#define __OBSERVER_SQL_EXECUTOR_TUPLE_H_

#include <memory>
#include <vector>
#include <algorithm>

#include "sql/parser/parse.h"
#include "sql/executor/value.h"
#include "storage/common/table_meta.h"
#include "storage/common/record_manager.h"
#include<unordered_set>
#include<unordered_map>

class Table;

class Tuple {
public:
  Tuple() = default;

  Tuple(const Tuple &other);

  ~Tuple();

  Tuple(Tuple &&other) noexcept ;
  Tuple & operator=(Tuple &&other) noexcept ;

  void add(TupleValue *value);
  void add(const std::shared_ptr<TupleValue> &other);
  void add(int value);
  void add(float value);
  void add(const char *s, int len);
  void add_date(int value);
  void add_null();
  void add(const char*d1,int len1, const char* d2,int len2);

  const std::vector<std::shared_ptr<TupleValue>> &values() const {
    return values_;
  }

  int size() const {
    return values_.size();
  }

  const TupleValue &get(int index) const {
    return *values_[index];
  }

  const std::shared_ptr<TupleValue> &get_pointer(int index) const {
    return values_[index];
  }

private:
  std::vector<std::shared_ptr<TupleValue>>  values_;
};

class TupleField {
public:
  TupleField(AttrType type, const char *table_name, const char *field_name) :
          type_(type), table_name_(table_name), field_name_(field_name){
  }

  AttrType  type() const{
    return type_;
  }

  const char *table_name() const {
    return table_name_.c_str();
  }
  const char *field_name() const {
    return field_name_.c_str();
  }

  std::string to_string() const;
private:
  AttrType  type_;
  std::string table_name_;
  std::string field_name_;
};

class TupleSchema {
public:
  TupleSchema() = default;
  ~TupleSchema() = default;

  void add(AttrType type, const char *table_name, const char *field_name);
  void add_if_not_exists(AttrType type, const char *table_name, const char *field_name);
  // void merge(const TupleSchema &other);
  void append(const TupleSchema &other);

  const std::vector<TupleField> &fields() const {
    return fields_;
  }

  const TupleField &field(int index) const {
    return fields_[index];
  }

  int index_of_field(const char *table_name, const char *field_name) const;
  void clear() {
    fields_.clear();
  }

  int size() const{
    return fields_.size();
  }
  void print_by_order(std::ostream &os, std::vector<std::pair<int,int>>& order) const;
  void print(std::ostream &os, bool table_name) const;
public:
  static void from_table(const Table *table, TupleSchema &schema);
private:
  std::vector<TupleField> fields_;
};

struct Comparator {
  Comparator(std::vector<std::pair<int,bool>>& list):compar_list(list) {
  }
  bool operator()(Tuple& t1, Tuple&t2) {
    for(int i=0;i<compar_list.size();++i) {
      int index=compar_list[i].first;
      bool is_asc=compar_list[i].second;
      if(t1.get(index).compare(t2.get(index))==0) {
        continue;
      }
      else if(t1.get(index).compare(t2.get(index)) < 0) {
        if(is_asc) {
          return true;
        } else {
          return false;
        }
      }
      else {
        if(is_asc) {
          return false;
        } else {
          return true;
        }
      }
    }
    return false;
  }
  std::vector<std::pair<int,bool>>& compar_list;
};

class TupleSet {
public:
  TupleSet() = default;
  TupleSet(TupleSet &&other);
  explicit TupleSet(const TupleSchema &schema) : schema_(schema) {
  }
  TupleSet &operator =(TupleSet &&other);

  ~TupleSet() = default;

  void set_schema(const TupleSchema &schema);
  void set_schema(const TupleSchema &&schema);

  const TupleSchema &get_schema() const;

  void add(Tuple && tuple);

  void clear();

  bool is_empty() const;
  int size() const;
  const Tuple &get(int index) const;
  const std::vector<Tuple> &tuples() const;
  void print_by_order(std::ostream &os, std::vector<std::pair<int,int>>& print_order) const;
  void print(std::ostream &os, bool table_name=false) const;
public:
  const TupleSchema &schema() const {
    return schema_;
  }
  void sort(Comparator cmp) {
    std::sort(tuples_.begin(),tuples_.end(),cmp);
  }
private:
  std::vector<Tuple> tuples_;
  TupleSchema schema_;
};

class GroupTupleSet{
  //支持多表聚合和group by
public:
  GroupTupleSet(TupleSet* input,Selects* select,const std::vector<std::pair<int,int>>& order_);
  ~GroupTupleSet();
  std::string schema_field_name(const char *attr_name,enum AggregationTypeFlag flag);
  std::string get_key(const Tuple& row);
  RC set_by_field(Selects* select);
  RC aggregates();
  void init_tuple(Tuple* init, const Tuple& ref);
  RC to_value(Value* value);
  void print(std::ostream &os,bool table_name);
private:
  std::unordered_map<std::string,Tuple*> groups;
  std::unordered_map<std::string,int> count;
  TupleSchema schema_;
  //存储group by字段在笛卡尔积集合中的坐标
  std::vector<int> by_index;
  //存储输出tuple中第几个列需要被聚合以及类型
  std::vector<std::pair<int,AggregationTypeFlag>> agg_index;
  TupleSet* input_;
  //存储输出tuple中第几个列对应在输入tuple中的列
  const std::vector<std::pair<int,int>>& order_;
};


class TupleRecordConverter {
public:
  TupleRecordConverter(Table *table, TupleSet &tuple_set);

  void add_record(const char *record);
private:
  Table *table_;
  TupleSet &tuple_set_;
};

class SetRecordConverter{
public:
  SetRecordConverter(Table* table,std::unordered_set<int>* in_set,const FieldMeta* fm);
  RC add_record(Record* rec);
private:
  Table* table_;
  std::unordered_set<int>* in_set_;
  const FieldMeta* fm_;
};

class RecordAggregater {
  //聚合的adapter
  //CHAR和DATE只支持COUNT
  public:
  RecordAggregater(Table& tab);
  ~RecordAggregater();
  RC set_field(const AggregatesField* agg_field,int agg_field_num);
  RC update_record(Record* rec);
  void agg_done();
  RC get_condition_value(Value* conditionvalue);
  TupleSet* get_tupleset();



  private:
  Table& table_;
  
  int rec_count=0;
  TupleSet tupleset;
  std::vector<std::pair<const FieldMeta*,AggregationTypeFlag>> field_;
  //存储结果vector
  std::vector<void*> value_;
  //生成输出的表头格式
  std::string schema_field_name(const char *attr_name,enum AggregationTypeFlag flag);
};



#endif //__OBSERVER_SQL_EXECUTOR_TUPLE_H_
