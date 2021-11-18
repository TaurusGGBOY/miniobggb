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
// Created by wangyunlai.wyl on 2021/6/7.
//

#ifndef __OBSERVER_SQL_PARSER_PARSE_DEFS_H__
#define __OBSERVER_SQL_PARSER_PARSE_DEFS_H__

#include <stddef.h>

#define MAX_NUM 20
#define MAX_REL_NAME 20
#define MAX_ATTR_NAME 20
#define MAX_ERROR_MESSAGE 20
#define MAX_DATA 50

//属性结构体
typedef struct {
  char *relation_name;   // relation name (may be NULL) 表名
  char *attribute_name;  // attribute name              属性名
  char *is_asc;
} OrderAttr;

enum AggregationTypeFlag{
  //语法解析生成的token也被定义为标识符，需避免重名
  ATF_NULL,
  ATF_SUM,
  ATF_AVG,
  ATF_MAX,
  ATF_MIN,
  ATF_COUNT
};

typedef struct {
  char *relation_name;   // relation name (may be NULL) 表名
  char *attribute_name;  // attribute name              属性名
  enum AggregationTypeFlag agg_type;
} RelAttr;

typedef enum {
  EQUAL_TO,     //"="     0
  LESS_EQUAL,   //"<="    1
  NOT_EQUAL,    //"<>"    2
  LESS_THAN,    //"<"     3
  GREAT_EQUAL,  //">="    4
  GREAT_THAN,   //">"     5
  IS_NULL,      //"IS NULL"     6
  IS_NOT_NULL,  //"IS NOT NULL"     7
  IN, //in 8
  NOT_IN,//not in 9
  NO_OP
} CompOp;

//属性值类型
typedef enum { UNDEFINED, CHARS, INTS, FLOATS,TEXT_PAGE_NUM, NULLS,BITMAPS,TEXT,DATES } AttrType;

//属性值
typedef struct _Value {
  AttrType type;  // type of value
  void *data;     // value
  //   bool operator+=(const _Value& right){
  //   if(right.type==type){
  //     switch (type)
  //     {
  //     case INTS:
  //       *(int*)data += *(int*)right.data;
  //       break;
  //     case FLOATS:
  //       *(float*)data += *(float*)right.data;
  //       break;
  //     case CHARS:{
  //         char *sp = (char*)malloc(sizeof(char) * (strlen((char*)data)+strlen((char*)right.data)));
  //         memcpy(sp,&data,strlen((char*)data));
  //         memcpy(sp+strlen((char*)data),&right.data,strlen((char*)right.data));
  //         free(data);
  //         data = sp;
  //       }
  //       break;
  //     default:
  //       LOG_ERROR("Unsupported attrtype plus");
  //       break;
  //     }
  //   } else{
  //     if(type==FLOATS && right.type==INTS){
  //       *(float*)data += *(int*)right.data;
  //     }
  //     else if(type==INTS && right.type==FLOATS){
  //       *(int*)data += *(float*)right.data;
  //     }else{
  //       LOG_ERROR("Unsupported attrtype cCreateIndexListonvert and plus");
  //     }
  //   }
  // };

  // bool operator-=(const _Value& right){
  //   if(right.type==type){
  //     switch (type)
  //     {
  //     case INTS:
  //       *(int*)data -= *(int*)right.data;
  //       break;
  //     case FLOATS:
  //       *(float*)data -= *(float*)right.data;
  //       break;
  //     default:
  //       LOG_ERROR("Unsupported attrtype plus");
  //       break;
  //     }
  //   } else{
  //     if(type==FLOATS && right.type==INTS){
  //       *(float*)data -= *(int*)right.data;
  //     }
  //     else if(type==INTS && right.type==FLOATS){
  //       *(int*)data -= *(float*)right.data;
  //     }else{
  //       LOG_ERROR("Unsupported attrtype convert and plus");
  //     }
  //   }
  // }
} Value;


typedef struct _Condition {
  int left_is_attr;    // TRUE if left-hand side is an attribute
                       // 1时，操作符左边是属性名，0时，是属性值
  Value left_value;    // left-hand side value if left_is_attr = FALSE
  RelAttr left_attr;   // left-hand side attribute
  struct _Aggregates* left_agg_value;
  CompOp comp;         // comparison operator
  int right_is_attr;   // TRUE if right-hand side is an attribute
                       // 1时，操作符右边是属性名，0时，是属性值
  RelAttr right_attr;  // right-hand side attribute if right_is_attr = TRUE 右边的属性
  Value right_value;   // right-hand side value if right_is_attr = FALSE
  struct _Aggregates* right_agg_value;

  //in subselect
  struct _Selects* in_select;
  //std::unordered_set<int>* in_set; This is stored in right_value;
} Condition;

typedef struct _Groupby{
  RelAttr* attr[MAX_NUM];
  size_t attr_num;
}Groupby;

// struct of select
typedef struct _Selects {
  size_t    attr_num;               // Length of attrs in Select clause
  RelAttr   attributes[MAX_NUM];    // attrs in Select clause
  size_t    relation_num;           // Length of relations in Fro clause
  char *    relations[MAX_NUM];     // relations in From clause
  OrderAttr order_attr[MAX_NUM];
  size_t    order_attr_num;
  RelAttr   group_attr[MAX_NUM];
  size_t    group_attr_num;
  size_t    condition_num;          // Length of conditions in Where clause
  Condition conditions[MAX_NUM];    // conditions in Where clause
} Selects;

// struct of insert
typedef struct {
  char *relation_name;    // Relation to insert into
  size_t value_num;       // Length of values
  Value values[MAX_NUM];  // values to insert
  Value values_list[MAX_NUM][MAX_NUM];
  size_t value_length_list[MAX_NUM];
} Inserts;

// struct of delete
typedef struct {
  char *relation_name;            // Relation to delete from
  size_t condition_num;           // Length of conditions in Where clause
  Condition conditions[MAX_NUM];  // conditions in Where clause
} Deletes;

// struct of update
typedef struct {
  char *relation_name;            // Relation to update
  char *attribute_name;           // Attribute to update
  Value value;                    // update value
  size_t condition_num;           // Length of conditions in Where clause
  Condition conditions[MAX_NUM];  // conditions in Where clause
} Updates;

typedef struct {
  char *name;     // Attribute name
  AttrType type;  // Type of attribute
  size_t length;  // Length of attribute
  int nullable;
} AttrInfo;

// struct of craete_table
typedef struct {
  char *relation_name;           // Relation name
  size_t attribute_count;        // Length of attribute
  AttrInfo attributes[MAX_NUM];  // attributes
} CreateTable;

// struct of drop_table
typedef struct {
  char *relation_name;  // Relation name
} DropTable;

// struct of create_index
typedef struct {
  char *index_name;      // Index name
  char *relation_name;   // Relation name
  char *attribute_name;  // Attribute name
  int unique;
} CreateIndex;

typedef struct{
  size_t index_num;
  CreateIndex index[MAX_NUM];
  const char *index_name;
  const char *relation_name;
}CreateIndexList;

// struct of  drop_index
typedef struct {
  const char *index_name;  // Index name
} DropIndex;

typedef struct {
  const char *relation_name;
} DescTable;

typedef struct {
  const char *relation_name;
  const char *file_name;
} LoadData;




typedef struct{
  //聚合的字段以及字段上的聚合类型
  char* relation_name;
  char* attribute_name;
  enum AggregationTypeFlag aggregation_type;
}AggregatesField;

typedef struct _Aggregates{
  AggregatesField field[MAX_NUM];
  size_t    relation_num;           // Length of relations in Fro clause
  char *    relation_name[MAX_NUM];
  int field_num;
  size_t condition_num;
  Condition conditions[MAX_NUM];
}Aggregates;

union Queries {
  Selects selection;
  Inserts insertion;
  Deletes deletion;
  Updates update;
  CreateTable create_table;
  DropTable drop_table;
  DropIndex drop_index;
  DescTable desc_table;
  LoadData load_data;
  Aggregates aggregation;
  char *errors;
  CreateIndexList create_index_list;
};
typedef union Queries SubQuries;

// 修改yacc中相关数字编码为宏定义
enum SqlCommandFlag {
  SCF_ERROR = 0,
  SCF_SELECT,
  SCF_INSERT,
  SCF_UPDATE,
  SCF_DELETE,
  SCF_CREATE_TABLE,
  SCF_DROP_TABLE,
  SCF_CREATE_INDEX,
  SCF_DROP_INDEX,
  SCF_SYNC,
  SCF_SHOW_TABLES,
  SCF_DESC_TABLE,
  SCF_BEGIN,
  SCF_COMMIT,
  SCF_ROLLBACK,
  SCF_LOAD_DATA,
  SCF_HELP,
  SCF_EXIT,
  SCF_AGGREGATE
};
// struct of flag and sql_struct
typedef struct Query {
  enum SqlCommandFlag flag;
  union Queries sstr;
} Query;

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

void order_attr_init(OrderAttr *relation_attr, const char *relation_name, const char *attribute_name, const char* is_asc);
void order_attr_destroy(OrderAttr *relation_attr);
void relation_attr_init(RelAttr *relation_attr, const char *relation_name, const char *attribute_name, const char* type_name);
void relation_attr_destroy(RelAttr *relation_attr);

void value_init_integer(Value *value, int v);
void value_init_float(Value *value, float v);
void value_init_string(Value *value, const char *v);
void value_init_date(Value *value, const char *v);
void value_init_null(Value *value);
void value_copy(Value* target, Value* object);
void value_destroy(Value *value);

void condition_init(Condition *condition, CompOp comp, int left_is_attr, RelAttr *left_attr, Value *left_value, int right_is_attr, RelAttr *right_attr, Value *right_value, Aggregates* agg_left,Aggregates* agg_right);
void condition_copy(Condition *target, Condition* object);
void condition_destroy(Condition *condition);
void condition_set_inselect(Condition *condition, Selects* sub_select);

void attr_info_init_with_null(AttrInfo *attr_info, const char *name, AttrType type, size_t length, int nullable);
void attr_info_init(AttrInfo *attr_info, const char *name, AttrType type, size_t length);
void attr_info_destroy(AttrInfo *attr_info);
void relattr_copy(RelAttr* target,RelAttr* object);

void selects_init(Selects *selects);
void selects_copy_init(Selects* target,Selects* object);
void selects_append_order_attr(Selects *selects, OrderAttr *rel_attr);
void selects_append_attribute(Selects *selects, RelAttr *rel_attr);
void selects_append_group_attr(Selects *selects, RelAttr *rel_attr);
void selects_append_relation(Selects *selects, const char *relation_name);
void selects_append_conditions(Selects *selects, Condition conditions[], size_t condition_num);
void selects_destroy(Selects *selects);

void inserts_init(Inserts *inserts, const char *relation_name, Value values[MAX_NUM][MAX_NUM], size_t value_length_list[MAX_NUM],size_t value_num);
void inserts_destroy(Inserts *inserts);

void deletes_init_relation(Deletes *deletes, const char *relation_name);
void deletes_set_conditions(Deletes *deletes, Condition conditions[], size_t condition_num);
void deletes_destroy(Deletes *deletes);

void updates_init(Updates *updates, const char *relation_name, const char *attribute_name, Value *value,
    Condition conditions[], size_t condition_num);
void updates_destroy(Updates *updates);

void aggregates_init(Aggregates *aggregates,const char *relation_name,Condition conditions[], size_t condition_num);
void aggregates_copy_init(Aggregates* target,Aggregates* object);
void aggregates_destroy(Aggregates *aggregates);
void aggregates_append_field_itoa(Aggregates *aggregates,int number,const char* type_name);
void aggregates_append_field(Aggregates *aggregates,const char* relation_name,const char *attribute_name,const char *type_name);
void aggregates_append_relation(Aggregates *aggregates, const char *relation_name);
void aggregates_check_implicit_relation(Aggregates *aggregates);

void create_table_append_attribute(CreateTable *create_table, AttrInfo *attr_info);
void create_table_init_name(CreateTable *create_table, const char *relation_name);
void create_table_destroy(CreateTable *create_table);

void drop_table_init(DropTable *drop_table, const char *relation_name);
void drop_table_destroy(DropTable *drop_table);

void create_index_init(CreateIndex *create_index, const char *index_name, const char *relation_name, const char *attr_name, int unique);
void create_index_destroy(CreateIndex *create_index);
void create_index_list_append(CreateIndexList *create_index_list, CreateIndex *create_index);
void create_index_set_first(CreateIndexList *create_index_list, CreateIndex *create_index);
void create_index_list_init(CreateIndexList *create_index_list, const char* index_name, const char *relation_name);
void create_index_list_destroy(CreateIndexList *create_index_list);
void create_index_init_short(CreateIndex *create_index, const char *attr_name);


void drop_index_init(DropIndex *drop_index, const char *index_name);
void drop_index_destroy(DropIndex *drop_index);

void desc_table_init(DescTable *desc_table, const char *relation_name);
void desc_table_destroy(DescTable *desc_table);

void load_data_init(LoadData *load_data, const char *relation_name, const char *file_name);
void load_data_destroy(LoadData *load_data);

void query_init(Query *query);
Query *query_create();  // create and init
void query_reset(Query *query);
void query_destroy(Query *query);  // reset and delete

void query_stack_pop(SubQuries* sub, int isselect);
enum AggregationTypeFlag match_aggtype(const char* type_name);
#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // __OBSERVER_SQL_PARSER_PARSE_DEFS_H__