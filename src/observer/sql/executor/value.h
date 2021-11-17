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

#ifndef __OBSERVER_SQL_EXECUTOR_VALUE_H_
#define __OBSERVER_SQL_EXECUTOR_VALUE_H_

#include "common/log/log.h"

#include <string.h>

#include <string>
#include <ostream>
#include <storage/common/date.h>
#include "sql/parser/parse.h"
#include "common/log/log.h"

class TupleValue {
public:
  TupleValue() = default;
  virtual ~TupleValue() = default;

  virtual void to_string(std::ostream &os) const = 0;
  virtual int compare(const TupleValue &other) const = 0;
  virtual AttrType get_type() const = 0;
  virtual void plus(const TupleValue& right);
  virtual void compare_and_set(const TupleValue& right,bool greater);
private:
};

class IntValue : public TupleValue {
public:
  explicit IntValue(int value) : value_(value) {
  }

  void to_string(std::ostream &os) const override {
    os << value_;
  }

  int compare(const TupleValue &other) const override;
  

  AttrType get_type() const override{
    return AttrType::INTS;
  }

  int get_value() const{
    return this->value_;
  }

  void compare_and_set(const TupleValue& right,bool greater){
    if(right.get_type()==INTS){
      const IntValue& int_right = (const IntValue &)right;
      if(greater)
        this->value_=std::max(int_right.value_,this->value_);
      else
        this->value_=std::min(int_right.value_,this->value_);

    }
    else
      LOG_ERROR("Unsupported type");
  }

  void set_value(int value){
    this->value_ = value;
  }

  void plus(const TupleValue& right){
    //类型校验在check multi table condition中保证
    if(right.get_type()==INTS){
      const IntValue& int_right = (const IntValue &)right;
      this->value_+=int_right.value_;
    }
    else
      LOG_ERROR("Unsupported plus");
  }

private:
  int value_;
};

class FloatValue : public TupleValue {
public:
  explicit FloatValue(float value) : value_(value) {
  }

  void to_string(std::ostream &os) const override {
    char buf[60];
    sprintf(buf, "%.2f", value_);
    int len = strlen(buf);
    if(buf[len-1]=='0'){
      buf[len-1]='\0';
      if(buf[len-2]=='0'){
        buf[len-2]='\0';
        if(buf[len-3]=='.'){
        buf[len-3]='\0';
        }
      }
    }
    std::string s = buf;
    os << s;
  }

  float get_value() const{
    return this->value_;
  }

  void set_value(float value){
    this->value_ = value;
  }

  void compare_and_set(const TupleValue& right,bool greater){
    if(right.get_type()==FLOATS){
      const FloatValue& float_right = (const FloatValue &)right;
      if(greater)
        this->value_=std::max(float_right.value_,this->value_);
      else
        this->value_=std::min(float_right.value_,this->value_);

    }
    else
      LOG_ERROR("Unsupported type");
  }

  int compare(const TupleValue &other) const override {
    float result;
    if(other.get_type()==FLOATS){
      const FloatValue & float_other = (const FloatValue &)other;
      result = value_ - float_other.value_;
    }
    else if(other.get_type()==INTS){
      const IntValue& int_other = (const IntValue &)other;
      result = value_ - (float)int_other.get_value();
    }
    else{
      LOG_ERROR("Unsupported compare");
    }
    if (result > 0.0001) { //浮点数做差在0.0001之内都视为相等
      return 1;
    }
    if (result < -0.0001) {
      return -1;
    }
    return 0;
  }

  AttrType get_type() const override{
    return AttrType::FLOATS;
  }

  void plus(const TupleValue& right){
    //类型校验在check multi table condition中保证
    if(right.get_type()==FLOATS){
      const FloatValue& float_right = (const FloatValue &)right;
      this->value_+=float_right.value_;
    }
    else if(right.get_type()==INTS){
      const IntValue& int_right = (const IntValue &)right;
      this->value_+=int_right.get_value();
    }
    else
      LOG_ERROR("Unsupported plus");
  }

private:
  float value_;
};

class StringValue : public TupleValue {
public:
  StringValue(const char *value, int len) : value_(value, len){
  }
  explicit StringValue(const char *value) : value_(value) {
  }

  void to_string(std::ostream &os) const override {
    os << value_;
  }

  int compare(const TupleValue &other) const override {
    const StringValue &string_other = (const StringValue &)other;
    return strcmp(value_.c_str(), string_other.value_.c_str());
  }
  AttrType get_type() const override{
    return AttrType::CHARS;
  }

  std::string get_value() const{
    return this->value_;
  }

  void compare_and_set(const TupleValue& right,bool greater){
    if(right.get_type()==CHARS){
      const StringValue& str_right = (const StringValue &)right;
      if(greater)
        this->value_=std::max(str_right.value_,this->value_);
      else
        this->value_=std::min(str_right.value_,this->value_);

    }
    else
      LOG_ERROR("Unsupported type");
  }

private:
  std::string value_;
};

class TextValue : public TupleValue {
public:
  TextValue(const char* data1,int len1,const char* data2,int len2) {
    value_.append(data1,2048);
    value_.append(data2,2048);
  }
  void to_string(std::ostream &os) const override {
    printf("value size is %d",value_.size());
    os << value_.c_str();
  }
  int compare(const TupleValue &other) const override {
    const TextValue &string_other = (const TextValue &)other;
    return strcmp(value_.c_str(), string_other.value_.c_str());
  }

  AttrType get_type() const override{
    return TEXT;
  }
private:
  std::string value_;
};

class DateValue : public TupleValue {
public:
  explicit DateValue(int value) : value_(value) {
  }

  void to_string(std::ostream &os) const override {
    Date& date = Date::get_instance();
    char buf[40];
    date.int_to_date(value_,buf);
    std::string s = buf;
    os << s;
  }

  int compare(const TupleValue &other) const override {
    const DateValue & int_other = (const DateValue &)other;
    return value_ - int_other.value_;
  }

  int get_value() const{
    return this->value_;
  }

  void compare_and_set(const TupleValue& right,bool greater){
    if(right.get_type()==DATES){
      const DateValue& date_right = (const DateValue &)right;
      if(greater)
        this->value_=std::max(date_right.value_,this->value_);
      else
        this->value_=std::min(date_right.value_,this->value_);

    }
    else
      LOG_ERROR("Unsupported type");
  }

  AttrType get_type() const override{
    return AttrType::DATES;
  }

private:
  int value_;
};

class NullValue : public TupleValue {
public:
  explicit NullValue() {
    value_= NULL;
  }

  void to_string(std::ostream &os) const override {
    os << "null";
  }

  int compare(const TupleValue &other) const override {
    return -1;
  }

  AttrType get_type() const override{
    return AttrType::NULLS;
  }

private:
  int value_;
};


#endif //__OBSERVER_SQL_EXECUTOR_VALUE_H_
