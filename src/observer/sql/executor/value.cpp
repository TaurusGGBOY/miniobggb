/* Copyright (c) 2021 Xie Meiyi(xiemeiyi@hust.edu.cn) and OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */
#include "sql/executor/value.h"

int IntValue::compare(const TupleValue &other) const {
    float result;
    if(other.get_type()==FLOATS){
      const FloatValue & float_other = (const FloatValue &)other;
      result = (float)value_ - float_other.get_value();
    }
    else if(other.get_type()==INTS){
      const IntValue& int_other = (const IntValue &)other;
      result = value_ - int_other.get_value();
    }
    else if(other.get_type()==NULLS){
      return 1;
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
void TupleValue::plus(const TupleValue& right){
  LOG_ERROR("never should use");
}

void TupleValue::compare_and_set(const TupleValue& right, bool greater){
  LOG_ERROR("never should use");
}
