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

#include <string>
#include <sstream>
#include <set>

#include "execute_stage.h"

#include "common/io/io.h"
#include "common/log/log.h"
#include "common/seda/timer_stage.h"
#include "common/lang/string.h"
#include "session/session.h"
#include "event/storage_event.h"
#include "event/sql_event.h"
#include "event/session_event.h"
#include "event/execution_plan_event.h"
#include "sql/executor/execution_node.h"
#include "sql/executor/tuple.h"
#include "storage/common/table.h"
#include "storage/default/default_handler.h"
#include "storage/common/condition_filter.h"
#include "storage/trx/trx.h"
#include <algorithm>

using namespace common;

RC create_selection_executor(Trx *trx, const Selects &selects, const char *db, const char *table_name, SelectExeNode &select_node);

//! Constructor
ExecuteStage::ExecuteStage(const char *tag) : Stage(tag) {}

//! Destructor
ExecuteStage::~ExecuteStage() {}

//! Parse properties, instantiate a stage object
Stage *ExecuteStage::make_stage(const std::string &tag) {
  ExecuteStage *stage = new (std::nothrow) ExecuteStage(tag.c_str());
  if (stage == nullptr) {
    LOG_ERROR("new ExecuteStage failed");
    return nullptr;
  }
  stage->set_properties();
  return stage;
}

//! Set properties for this object set in stage specific properties
bool ExecuteStage::set_properties() {
  //  std::string stageNameStr(stageName);
  //  std::map<std::string, std::string> section = theGlobalProperties()->get(
  //    stageNameStr);
  //
  //  std::map<std::string, std::string>::iterator it;
  //
  //  std::string key;

  return true;
}

//! Initialize stage params and validate outputs
bool ExecuteStage::initialize() {
  LOG_TRACE("Enter");

  std::list<Stage *>::iterator stgp = next_stage_list_.begin();
  default_storage_stage_ = *(stgp++);
  mem_storage_stage_ = *(stgp++);

  LOG_TRACE("Exit");
  return true;
}

//! Cleanup after disconnection
void ExecuteStage::cleanup() {
  LOG_TRACE("Enter");

  LOG_TRACE("Exit");
}

void ExecuteStage::handle_event(StageEvent *event) {
  LOG_TRACE("Enter\n");

  handle_request(event);

  LOG_TRACE("Exit\n");
  return;
}

void ExecuteStage::callback_event(StageEvent *event, CallbackContext *context) {
  LOG_TRACE("Enter\n");

  // here finish read all data from disk or network, but do nothing here.
  ExecutionPlanEvent *exe_event = static_cast<ExecutionPlanEvent *>(event);
  SQLStageEvent *sql_event = exe_event->sql_event();
  sql_event->done_immediate();

  LOG_TRACE("Exit\n");
  return;
}

void ExecuteStage::handle_request(common::StageEvent *event) {
  ExecutionPlanEvent *exe_event = static_cast<ExecutionPlanEvent *>(event);
  SessionEvent *session_event = exe_event->sql_event()->session_event();
  Query *sql = exe_event->sqls();
  const char *current_db = session_event->get_client()->session->get_current_db().c_str();

  CompletionCallback *cb = new (std::nothrow) CompletionCallback(this, nullptr);
  if (cb == nullptr) {
    LOG_ERROR("Failed to new callback for ExecutionPlanEvent");
    exe_event->done_immediate();
    return;
  }
  exe_event->push_callback(cb);

  switch (sql->flag) {
    case SCF_SELECT: { // select
      do_select(current_db, sql, exe_event->sql_event()->session_event());
      exe_event->done_immediate();
    }
    break;
    case SCF_AGGREGATE:{
      do_aggreagate(current_db,sql,exe_event->sql_event()->session_event());
      exe_event->done_immediate();
    }
    break;
    case SCF_INSERT:
    case SCF_UPDATE:
    case SCF_DELETE:
    case SCF_CREATE_TABLE:
    case SCF_SHOW_TABLES:
    case SCF_DESC_TABLE:
    case SCF_DROP_TABLE:
    case SCF_CREATE_INDEX:
    case SCF_DROP_INDEX:
    case SCF_LOAD_DATA: {
      StorageEvent *storage_event = new (std::nothrow) StorageEvent(exe_event);
      if (storage_event == nullptr) {
        LOG_ERROR("Failed to new StorageEvent");
        event->done_immediate();
        return;
      }

      default_storage_stage_->handle_event(storage_event);
    }
    break;
    case SCF_SYNC: {
      RC rc = DefaultHandler::get_default().sync();
      session_event->set_response(strrc(rc));
      exe_event->done_immediate();
    }
    break;
    case SCF_BEGIN: {
      session_event->get_client()->session->set_trx_multi_operation_mode(true);
      session_event->set_response(strrc(RC::SUCCESS));
      exe_event->done_immediate();
    }
    break;
    case SCF_COMMIT: {
      Trx *trx = session_event->get_client()->session->current_trx();
      RC rc = trx->commit();
      session_event->get_client()->session->set_trx_multi_operation_mode(false);
      session_event->set_response(strrc(rc));
      exe_event->done_immediate();
    }
    break;
    case SCF_ROLLBACK: {
      Trx *trx = session_event->get_client()->session->current_trx();
      RC rc = trx->rollback();
      session_event->get_client()->session->set_trx_multi_operation_mode(false);
      session_event->set_response(strrc(rc));
      exe_event->done_immediate();
    }
    break;
    case SCF_HELP: {
      const char *response = "show tables;\n"
          "drop tables `table name`\n"
          "desc `table name`;\n"
          "create table `table name` (`column name` `column type`, ...);\n"
          "create index `index name` on `table` (`column`);\n"
          "insert into `table` values(`value1`,`value2`);\n"
          "update `table` set column=value [where `column`=`value`];\n"
          "delete from `table` [where `column`=`value`];\n"
          "select [ * | `columns` ] from `table`;\n"
          "select max(`column`) from `table`;\n"
          ;
      session_event->set_response(response);
      exe_event->done_immediate();
    }
    break;
    case SCF_EXIT: {
      // do nothing
      const char *response = "Unsupported\n";
      session_event->set_response(response);
      exe_event->done_immediate();
    }
    break;
    default: {
      exe_event->done_immediate();
      LOG_ERROR("Unsupported command=%d\n", sql->flag);
    }
  }
}

void end_trx_if_need(Session *session, Trx *trx, bool all_right) {
  if (!session->is_trx_multi_operation_mode()) {
    if (all_right) {
      trx->commit();
    } else {
      trx->rollback();
    }
  }
}

bool check_one_condition(const CompOp &cmp, std::pair<int,int>& cond_record, Tuple& tuple)
{
    std::stringstream s1,s2;
    tuple.get(cond_record.first).to_string(s1);
    tuple.get(cond_record.second).to_string(s2);
    LOG_DEBUG("check %s and %s", s1.str().c_str(),s2.str().c_str());
    int cmp_res=tuple.get(cond_record.first).compare(tuple.get(cond_record.second));
    switch (cmp) {
      case EQUAL_TO:
        return 0 == cmp_res;
      case LESS_EQUAL:
        return cmp_res <= 0;
      case NOT_EQUAL:
        return cmp_res != 0;
      case LESS_THAN:
        return cmp_res < 0;
      case GREAT_EQUAL:
        return cmp_res >= 0;
      case GREAT_THAN:
        return cmp_res > 0;
      default:
        break;
    }
    LOG_PANIC("Never should print this.");
    return cmp_res;  // should not go here
}

bool check_all_condition(const Selects &selects, std::vector<std::pair<int,int>>& cond_record, Tuple& tuple) {
  for(int i=0;i<cond_record.size();++i) {
    if (cond_record[i].first == -1) {
      continue;
    }
    if(!check_one_condition(selects.conditions[i].comp,cond_record[i],tuple)){
      return false;
    }
  }
  return true;
}

bool check_multi_table_condition(TupleSchema& schema,const Selects& selects, std::vector<std::pair<int,int>>& cond_record) {
  size_t count=0;
  for(int i=0;i< selects.condition_num;++i){
    auto curr=selects.conditions[i];
    //多表查询不允许表名为空
    if(curr.left_is_attr && curr.left_attr.relation_name== nullptr) {
      LOG_DEBUG("multi table select:relation name is null");
      return false;
    }
    if(curr.right_is_attr && curr.right_attr.relation_name == nullptr) {
      LOG_DEBUG("multi table select:relation name is null");
      return false;
    }
    //都不为空需要判断字段是否存在
    if(curr.right_is_attr && curr.left_is_attr) {
      auto l_attr=curr.left_attr;
      auto r_attr=curr.right_attr;
      int l_match=-1;
      int r_match=-1;
      for(int i=0;i<schema.fields().size();++i) {
        if(strcmp(schema.field(i).table_name(),l_attr.relation_name)==0 && strcmp(schema.field(i).field_name(),l_attr.attribute_name)==0) {
          l_match=i;
        }
        if(strcmp(schema.field(i).table_name(),r_attr.relation_name)==0 && strcmp(schema.field(i).field_name(),r_attr.attribute_name)==0) {
          r_match=i;
        }
      }
      //如果比较的类型不同，失败
      if(schema.field(l_match).type() != schema.field(r_match).type()) {
        LOG_DEBUG("multi table select:condition value type is not same");
        return false;
      }
      //左右两个字段如果一个不存在，返回失败 ,不应该出现
      if(l_match==-1 || r_match==-1) {
        return false;
      }
      cond_record.emplace_back(std::make_pair(l_match,r_match));
      count+=1;
    } else {
      //如果不是双端都是attr，说明是单表condition，之前用过了，标记一下
      cond_record.emplace_back(std::make_pair(-1,-1));
    }
  }
  LOG_DEBUG("condition record size is %d", count);
  return true;
}
//lds:打印多表数据
void print_tuple_sets(std::vector<TupleSet>& tuple_sets, int index, std::vector<const Tuple*>& tuples,std::ostream &os, std::vector<std::pair<int,int>>& print_order ,
                      const Selects &selects,std::vector<std::pair<int,int>>& cond_record ,TupleSet& res ,bool finished=false) {
  if(finished) {
    return;
  }
  if(index==tuple_sets.size()){
    Tuple curr;
    for(int i=0;i<print_order.size();++i) {
      int j = print_order[i].first;
      int k = print_order[i].second;
      curr.add(tuples[j]->values()[k]);
    }
    if(check_all_condition(selects,cond_record,curr)){
      res.add(std::move(curr));
    }
    return ;
  }

  auto& ts=tuple_sets[index].tuples();

  if(ts.empty()) {
    finished=true;
    return;
  }

  for(auto& t:ts) {
    tuples.push_back(&t);
    print_tuple_sets(tuple_sets,index+1,tuples,os,print_order,selects,cond_record,res,finished);
    tuples.pop_back();
  }
}

std::vector<std::pair<int,int>> get_print_order(const Selects &selects, std::vector<TupleSet>& tuple_sets, TupleSchema& schema) {
  std::vector<std::pair<int,int>> print_order;
  //只有一个查询字段才可能出现全局星号
  LOG_DEBUG("llds selects attr num is %d", selects.attr_num);
  if(selects.attr_num == 1) {
    //如果只有一个字段，该查询字段如果未设定表，则必须是*，不然就是非法查询
    LOG_DEBUG("llds selects relation_name is %s.%s", selects.attributes[0].relation_name,selects.attributes[0].attribute_name);
    if(selects.attributes[0].relation_name == nullptr && strcmp(selects.attributes[0].attribute_name,"*") == 0 ) {
      for (int j=tuple_sets.size()-1; j>=0; --j) {
        for (int k=0;k<tuple_sets[j].get_schema().fields().size();++k) {
          print_order.push_back({j,k});
          schema.add(tuple_sets[j].get_schema().field(k).type(),tuple_sets[j].get_schema().field(k).table_name(),tuple_sets[j].get_schema().field(k).field_name());
        }
      }
      LOG_DEBUG("llds print_order size is %d",print_order.size());
      return print_order;
    } else if(selects.attributes[0].relation_name == nullptr && strcmp(selects.attributes[0].attribute_name,"*") != 0) {
      //do nothing, error
      LOG_DEBUG("llds print_order size is %d",print_order.size());
      return print_order;
    }
  }

  for(int i=selects.attr_num-1;i>=0;--i) {
    for(int j=0;j<tuple_sets.size();++j){
      for (int k=0;k<tuple_sets[j].get_schema().fields().size();++k){
        //不能再出现全局*，所以不会出现无表名的情况
        if(selects.attributes[i].relation_name == nullptr) {
          print_order.clear();
          return print_order;
        }
        //如果表名不同，继续找
        if(strcmp(selects.attributes[i].relation_name,tuple_sets[j].get_schema().field(k).table_name()) != 0 ) {
          continue;
        }
        //如果字段名不为*或者字段名不相等，继续找
        if((strcmp("*", selects.attributes[i].attribute_name) != 0) && (strcmp(selects.attributes[i].attribute_name,tuple_sets[j].get_schema().field(k).field_name()) != 0)) {
          continue;
        }
        print_order.push_back({j,k});
        schema.add(tuple_sets[j].get_schema().field(k).type(),tuple_sets[j].get_schema().field(k).table_name(),tuple_sets[j].get_schema().field(k).field_name());
      }
    }
  }
  return print_order;
}
bool order_tuples(const Selects &selects, TupleSet& tuple_set, int size) {
  //check and get order fields
  if(selects.order_attr_num==0) {
    return true;
  }
  std::set<int> count;//防止order字段重复
  std::vector<std::pair<int,bool>> order_fields;
  //重复代码比较多
  //遍历所有的可排序字段，找到tuple.sets中的对应字段
  if(size > 1) {
    //遍历排序字段，逆序遍历
    auto& schema = tuple_set.get_schema().fields();
    for(int i=selects.order_attr_num-1; i>=0; --i) {
      auto attr = selects.order_attr[i];
      //多表情况排序字段表名不能为空
      if(attr.relation_name == nullptr) {
        return false;
      }
      //遍历所有的表
      for(int j=0;j<schema.size();++j) {
        if(strcmp(schema[j].field_name(),attr.attribute_name) != 0 || strcmp(schema[j].table_name(),attr.relation_name) != 0) {
          continue;
        }
        bool is_asc = false;
        if(strcasecmp("asc",attr.is_asc) == 0) {
          is_asc = true;
        } else if( (strcasecmp("desc",attr.is_asc) == 0) ) {
          is_asc =false;
        } else {
          return false;
        }
        count.insert(j);
        order_fields.push_back({j,is_asc});
      }
    }
  } else {
    auto& schema = tuple_set.get_schema().fields();
    for(int i=selects.order_attr_num-1; i>=0; --i) {
      auto attr = selects.order_attr[i];
      //只有单表情况下，order by可以不带表名
      if(attr.relation_name!= nullptr && strcmp(attr.relation_name, schema.front().table_name()) != 0) {
        return false;
      }
      //记录每个表需要排序的字段编号及升/降序
      for(int j=0;j<schema.size();++j) {
        if(strcmp(schema[j].field_name(),attr.attribute_name) != 0) {
          continue;
        }
        bool is_asc = false;
        if(strcasecmp("asc",attr.is_asc) == 0) {
          is_asc = true;
        } else if( (strcasecmp("desc",attr.is_asc) == 0) ) {
          is_asc =false;
        } else {
          return false;
        }
        count.insert(j);
        order_fields.push_back({j,is_asc});
      }
    }
  }
  //m说明少于排序字段数量，数名有排序字段不在查询字段内，报failure
  if(count.size() < selects.order_attr_num) {
    return false;
  }
  //开始排序
  tuple_set.sort(Comparator(order_fields));
  return true;
}

// 这里没有对输入的某些信息做合法性校验，比如查询的列名、where条件中的列名等，没有做必要的合法性校验
// 需要补充上这一部分. 校验部分也可以放在resolve，不过跟execution放一起也没有关系
RC ExecuteStage::do_select(const char *db, Query *sql, SessionEvent *session_event) {

  LOG_DEBUG("llds start do select");
  RC rc = RC::SUCCESS;
  Session *session = session_event->get_client()->session;
  Trx *trx = session->current_trx();
  const Selects &selects = sql->sstr.selection;
  // 把所有的表和只跟这张表关联的condition都拿出来，生成最底层的select 执行节点
  std::vector<SelectExeNode *> select_nodes;
  for (size_t i = 0; i < selects.relation_num; i++) {
    const char *table_name = selects.relations[i];
    SelectExeNode *select_node = new SelectExeNode;
    rc = create_selection_executor(trx, selects, db, table_name, *select_node);
    if (rc != RC::SUCCESS) {
      delete select_node;
      for (SelectExeNode *& tmp_node: select_nodes) {
        delete tmp_node;
      }
      session_event->set_response("FAILURE\n");
      end_trx_if_need(session, trx, false);
      return rc;
    }
    select_nodes.push_back(select_node);
  }

  if (select_nodes.empty()) {
    LOG_ERROR("No table given");
    end_trx_if_need(session, trx, false);
    return RC::SQL_SYNTAX;
  }

  std::vector<TupleSet> tuple_sets;
  for (SelectExeNode *&node: select_nodes) {
    TupleSet tuple_set;
    rc = node->execute(tuple_set);
    if (rc != RC::SUCCESS) {
      for (SelectExeNode *& tmp_node: select_nodes) {
        delete tmp_node;
      }
      end_trx_if_need(session, trx, false);
      return rc;
    } else {
      tuple_sets.push_back(std::move(tuple_set));
    }
  }

  std::stringstream ss;
  if (tuple_sets.size() > 1) {
    // 本次查询了多张表，需要做join操作
    LOG_DEBUG("print multi table tuple set");
    std::reverse(tuple_sets.begin(),tuple_sets.end());
    TupleSchema schema;
    for(auto& t:tuple_sets) {
      schema.append(t.get_schema());
    }
    std::vector<std::pair<int,int>> cond_record;
    while(true) {
      if(!check_multi_table_condition(schema,selects,cond_record)) {
        ss.clear();
        ss << "FAILURE\n";
        LOG_DEBUG("check multi table condition failure");
        break;
      }
      std::vector<std::pair<int,int>> print_order;
      for(int i=0;i<tuple_sets.size();i++) {
        for(int j=0;j<tuple_sets[i].get_schema().fields().size();++j){
          print_order.push_back({i,j});
        }
      }
      std::vector<const Tuple*> tuples;
      //schema.print(ss);
      TupleSet mid_tuple_set;
      std::vector<TupleSet> res_set;
      res_set.emplace_back(std::move(mid_tuple_set));
      res_set.back().set_schema(schema);
      //算笛卡尔积，过滤数据
      print_tuple_sets(tuple_sets,0,tuples,ss,print_order,selects,cond_record,res_set.back());
      //排序
      if(!order_tuples(selects,res_set.back(),tuple_sets.size())) {
        ss.clear();
        ss << "FAILURE\n";
        LOG_DEBUG("order tuple condition failure");
        break;
      }
      //获取打印顺序

      TupleSchema res_schema;
      print_order=get_print_order(selects,res_set,res_schema);
      if(print_order.empty()) {
        ss.clear();
        ss << "FAILURE\n";
        LOG_DEBUG("get print order condition failure");
        break;
      }
      //获取最终打印表
      //TupleSet res;
      //res.set_schema(res_schema);
      //tuples.clear();
      //cond_record.clear();
      //print_tuple_sets(res_set,0,tuples,ss,print_order,selects,cond_record,res);
      res_set.back().print_by_order(ss,print_order);
      break;
    }


  } else {
    // 当前只查询一张表，直接返回结果即可
    if(order_tuples(selects,tuple_sets.front(),1)) {
      tuple_sets.front().print(ss);
    } else {
      ss.clear();
      ss << "FAILURE\n";
    }
  }

  for (SelectExeNode *& tmp_node: select_nodes) {
    delete tmp_node;
  }
  session_event->set_response(ss.str());
  end_trx_if_need(session, trx, true);
  return rc;
}

bool match_table(const Selects &selects, const char *table_name_in_condition, const char *table_name_to_match) {
  if (table_name_in_condition != nullptr) {
    return 0 == strcmp(table_name_in_condition, table_name_to_match);
  }

  return selects.relation_num == 1;
}

bool match_table(const Aggregates &aggregates, const char *table_name_in_condition, const char *table_name_to_match) {
  if (table_name_in_condition != nullptr) {
    return 0 == strcmp(table_name_in_condition, table_name_to_match);
  }

  return true;
}


static RC record_reader_aggregate_adapter(Record* record,void* context){
  RecordAggregater &aggregater = *(RecordAggregater*)context;
  return aggregater.update_record(record);
}
//提供在查询条件中将聚合字段作为返回值,返回一个标量
RC aggregate_value(Trx* trx,Table* table,char* attr_name, AggregationTypeFlag flag, 
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

RC ExecuteStage::do_aggreagate(const char *db, Query *sql, SessionEvent *session_event){
  Session *session = session_event->get_client()->session;
  Trx *trx = session->current_trx();
  const Aggregates &aggregates = sql->sstr.aggregation;
  char* table_name = sql->sstr.aggregation.relation_name;
  Table* table = DefaultHandler::get_default().find_table(db,table_name);
  if (nullptr == table) {
    LOG_WARN("No such table [%s] in db [%s]", table_name, db);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }
  

  //这里不直接使用compositefilter的原因是担心需要多表查询的聚合
  std::vector<DefaultConditionFilter *> condition_filters;
  for (size_t i = 0; i < aggregates.condition_num; i++) {
    const Condition &condition = aggregates.conditions[i];
    if ((condition.left_is_attr == 0 && condition.right_is_attr == 0) || // 两边都是值
        (condition.left_is_attr == 1 && condition.right_is_attr == 0 && match_table(aggregates, condition.left_attr.relation_name, sql->sstr.aggregation.relation_name)) ||  // 左边是属性右边是值
        (condition.left_is_attr == 0 && condition.right_is_attr == 1 && match_table(aggregates, condition.right_attr.relation_name, sql->sstr.aggregation.relation_name)) ||  // 左边是值，右边是属性名
        (condition.left_is_attr == 1 && condition.right_is_attr == 1 &&
            match_table(aggregates, condition.left_attr.relation_name, sql->sstr.aggregation.relation_name) && match_table(aggregates, condition.right_attr.relation_name, sql->sstr.aggregation.relation_name)) // 左右都是属性名，并且表名都符合
        ) {
      DefaultConditionFilter *condition_filter = new DefaultConditionFilter();
      RC rc = condition_filter->init(*table, condition);
      if (rc != RC::SUCCESS) {
        delete condition_filter;
        session_event->set_response("FAILURE\n");
        for (DefaultConditionFilter * &filter : condition_filters) {
          delete filter;
        }
        return rc;
      }
      condition_filters.push_back(condition_filter);
    }
  }

  CompositeConditionFilter filter;
  filter.init((const ConditionFilter **)condition_filters.data(), condition_filters.size());

  RecordAggregater aggregater(*table);
  RC rc = aggregater.set_field(aggregates.field,aggregates.field_num);
  if(rc!=RC::SUCCESS){
    session_event->set_response("FAILURE\n");
    return rc;
  }
  rc = table->scan_record(trx, &filter, -1, (void *)&aggregater, record_reader_aggregate_adapter);
  if(rc!=RC::SUCCESS){
    session_event->set_response("FAILURE\n");
    return rc;
  }
  std::stringstream ss;
  aggregater.agg_done();
  TupleSet* tuple_set = aggregater.get_tupleset();
  tuple_set->print(ss);
  session_event->set_response(ss.str());
  end_trx_if_need(session, trx, true);
  return rc;
}

static RC schema_add_field(Table *table, const char *field_name, TupleSchema &schema) {
  const FieldMeta *field_meta = table->table_meta().field(field_name);
  if (nullptr == field_meta) {
    LOG_WARN("No such field. %s.%s", table->name(), field_name);
    return RC::SCHEMA_FIELD_MISSING;
  }

  schema.add_if_not_exists(field_meta->type(), table->name(), field_meta->name());
  return RC::SUCCESS;
}

// 把所有的表和只跟这张表关联的condition都拿出来，生成最底层的select 执行节点
RC create_selection_executor(Trx *trx, const Selects &selects, const char *db, const char *table_name, SelectExeNode &select_node) {
  // 列出跟这张表关联的Attr
  TupleSchema schema;
  Table * table = DefaultHandler::get_default().find_table(db, table_name);
  if (nullptr == table) {
    LOG_WARN("No such table [%s] in db [%s]", table_name, db);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  for (int i = selects.attr_num - 1; i >= 0; i--) {
    const RelAttr &attr = selects.attributes[i];
    if (nullptr == attr.relation_name || 0 == strcmp(table_name, attr.relation_name)) {
      if (0 == strcmp("*", attr.attribute_name)) {
        // 列出这张表所有字段
        TupleSchema::from_table(table, schema);
        break; // 没有校验，给出* 之后，再写字段的错误
      } else {
        // 列出这张表相关字段
        RC rc = schema_add_field(table, attr.attribute_name, schema);
        if (rc != RC::SUCCESS) {
          return rc;
        }
      }
    }
  }

  // 找出仅与此表相关的过滤条件, 或者都是值的过滤条件
  std::vector<DefaultConditionFilter *> condition_filters;
  for (size_t i = 0; i < selects.condition_num; i++) {
    const Condition &condition = selects.conditions[i];
    if ((condition.left_is_attr == 0 && condition.right_is_attr == 0) || // 两边都是值
        (condition.left_is_attr == 1 && condition.right_is_attr == 0 && match_table(selects, condition.left_attr.relation_name, table_name)) ||  // 左边是属性右边是值
        (condition.left_is_attr == 0 && condition.right_is_attr == 1 && match_table(selects, condition.right_attr.relation_name, table_name)) ||  // 左边是值，右边是属性名
        (condition.left_is_attr == 1 && condition.right_is_attr == 1 &&
            match_table(selects, condition.left_attr.relation_name, table_name) && match_table(selects, condition.right_attr.relation_name, table_name)) // 左右都是属性名，并且表名都符合
        ) {
      DefaultConditionFilter *condition_filter = new DefaultConditionFilter();
      RC rc = condition_filter->init(*table, condition);
      if (rc != RC::SUCCESS) {
        delete condition_filter;
        for (DefaultConditionFilter * &filter : condition_filters) {
          delete filter;
        }
        return rc;
      }
      condition_filters.push_back(condition_filter);
    }
    //如果两边都是attr，拿属于自己的去查表，多表查询做过滤需要
    else if( condition.left_is_attr == 1 && condition.right_is_attr == 1) {
      if(condition.left_attr.relation_name==nullptr || condition.right_attr.relation_name == nullptr) {
        return RC::INVALID_ARGUMENT;
      }
      if(strcmp(condition.left_attr.relation_name,table_name) == 0 ) {
        RC rc = schema_add_field(table, condition.left_attr.attribute_name, schema);
        if (rc != RC::SUCCESS) {
          return rc;
        }
      }
      if(strcmp(condition.right_attr.relation_name,table_name) == 0) {
        RC rc = schema_add_field(table, condition.right_attr.attribute_name, schema);
        if (rc != RC::SUCCESS) {
          return rc;
        }
      }
    }
  }

  return select_node.init(trx, table, std::move(schema), std::move(condition_filters));
}

