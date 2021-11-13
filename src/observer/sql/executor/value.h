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

class TupleValue {
public:
  TupleValue() = default;
  virtual ~TupleValue() = default;

  virtual void to_string(std::ostream &os) const = 0;
  virtual int compare(const TupleValue &other) const = 0;
private:
};

class IntValue : public TupleValue {
public:
  explicit IntValue(int value) : value_(value) {
  }

  void to_string(std::ostream &os) const override {
    os << value_;
  }

  int compare(const TupleValue &other) const override {
    const IntValue & int_other = (const IntValue &)other;
    return value_ - int_other.value_;
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

  int compare(const TupleValue &other) const override {
    const FloatValue & float_other = (const FloatValue &)other;
    float result = value_ - float_other.value_;
    if (result > 0) { // 浮点数没有考虑精度问题
      return 1;
    }
    if (result < 0) {
      return -1;
    }
    return 0;
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

private:
  int value_;
};


#endif //__OBSERVER_SQL_EXECUTOR_VALUE_H_
