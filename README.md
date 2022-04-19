# miniob赛题

## 背景

> 本次大赛赛题, 是在一个miniob(mini数据库)库的基础上, 让参数选手实现数据库的非常基础的功能, 功能分为入门（预选赛）, 中级（决赛）, 高阶（黑客松） 3个阶段。 入门门槛较低, 适合所有参赛选手。 面向的对象主要是在校学生，数据库爱好者, 或者对基础技术有一定兴趣的爱好者, 并且考题对诸多模块做了简化，比如不考虑并发操作, 事务比较简单。 目标是让不熟悉数据库设计和实现的同学能够快速的了解与深入学习数据库内核，期望通过miniob相关训练之后，能够对各个数据库内核模块的功能与它们之间的关联有所了解，并能够在使用时，设计出高效的SQL, 并帮助降低学习OceanBase 内核的学习门槛。

## 组织

这篇文章会先聊一聊赛题，然后讲一讲miniob的架构，前置知识等，再去讲题目怎么做，最后会给一些调试时候的小技巧等

## 赛题

主页： [背景 | lectures-on-dbms-implementation (oceanbase-partner.github.io)](https://oceanbase-partner.github.io/lectures-on-dbms-implementation/miniob-topics) 

![](https://gitee.com/agaogao/photobed/raw/master/img/%E8%A1%A81_1.png)

![](https://gitee.com/agaogao/photobed/raw/master/img/%E8%A1%A81_2.png)

| 必做选做 | 名称                             | 分值 | 描述                                                         |
| -------- | -------------------------------- | ---- | ------------------------------------------------------------ |
| 必做     | 优化buffer pool                  | 10   | 实现LRU淘汰算法或其它淘汰算法                                |
| 必做     | 查询元数据校验<br/>select-meta   | 10   | 查询语句中存在不存在的列名、表名等，需要返回失败。<br/>需要检查代码，判断是否需要返回错误的地方都返回错误了。 |
| 必做     | drop table<br/>drop-table        | 10   | 删除表。清除表相关的资源。                                   |
| 必做     | 实现update功能<br/>update        | 10   | update单个字段即可                                           |
| 必做     | 增加date字段<br/>date            | 10   | date测试不会超过2038年2月，不会小于1970年1月1号。<br/>注意处理非法的date输入，需要返回FAILURE。 |
| 必做     | 多表查询<br/>select-tables       | 10   | 支持多张表的笛卡尔积关联查询。<br/>需要实现select * from t1,t2; <br/>select t1.*,t2.* from t1,t2;以及select t1.id,t2.id from t1,t2;<br/>查询可能会带条件。查询结果展示格式参考单表查询。<br/>每一列必须带有表信息 |
| 必做     | 聚合运算<br/>aggregation-func    | 10   | 需要实现max/min/count/avg.<br/>包含聚合字段时，只会出现聚合字段。<br/>聚合函数中的参数不会是表达式，比如age +1 |
| 选做     | 多表join操作<br/>join-tables     | 20   | 需要支持join多张表。需要考虑大表问题，<br/>不要直接使用笛卡尔积再过滤 |
| 选做     | 一次插入多条数据<br/>insert      | 10   | 一次插入的数据要同时成功或失败。                             |
| 选做     | 唯一索引<br/>unique              | 10   | 唯一索引：create unique index                                |
| 选做     | 支持NULL类型<br/>null            | 10   | 包括但不限于建表、查询和插入。<br/>默认情况不允许为NULL，使用nullable关键字表示字段允许为NULL。<br/>Null不区分大小写。<br/>注意NULL字段的对比规则是NULL与**任何** 数据对比，都是FALSE。 |
| 选做     | 简单子查询<br/>simple-sub-query  | 10   | 支持简单的IN(NOT IN)语句；<br/>支持与子查询结果做比较运算；<br/>支持子查询中带聚合函数。<br/>子查询中不会与主查询做关联。 |
| 选做     | 多列索引<br/>multi-index         | 20   | 单个索引关联了多个字段                                       |
| 选做     | 超长字段<br/>text                | 20   | 超长字段的长度可能超出一页，比如常见的text,blob等。<br/>这里仅要求实现text（text 长度固定4096字节），可以当做字符串实现。<br/>注意：当前的查询，只能支持一次返回少量数据，需要扩展<br/>如果输入的字符串长度，超过4096，那么应该保存4096字节，剩余的数据截断 |
| 选做     | 查询支持表达式<br/>expression    | 20   | 查询中支持运算表达式，这里的运算表达式包括 +-*/。<br/>仅支持基本数据的运算即可，不对date字段做考察。<br/>运算出现异常，按照NULL规则处理。<br/>只需要考虑select。 |
| 选做     | 复杂子查询<br/>complex-sub-query | 20   | 子查询在WHERE条件中，子查询语句支持多张表与AND条件表达式，<br/>查询条件支持max/min等。<br/>注意考虑一下子查询与父表相关联的情况。 |
| 选做     | 排序<br/>order-by                | 10   | 支持oder by功能。不指定排序顺序默认为升序(asc)。<br/>不需要支持oder by字段为数字的情况，比如select * from t order by 1; |
| 选做     | 分组<br/>group-by                | 20   | 支持group by功能。group by中的聚合函数也不要求支持表达式     |

## 架构

### SQL引擎

借用一下Oceanbase的架构图 [OceanBase 社区版](https://open.oceanbase.com/docs/community/oceanbase-database/V3.1.1/overall-architecture) 

![](https://gitee.com/agaogao/photobed/raw/master/img/20220104193943.png)

在miniob中是有这几个阶段的函数，但是实际只实现了Parser和Executor两个阶段，Resolver，Transformer，Optimizer，Code Generator这四个阶段直接调用下一个阶段的接口

### 存储引擎

B+树

## 模块

![](https://gitee.com/agaogao/photobed/raw/master/img/20220104192131.png)

+ 网络模块：客户端和服务器是通过套接字连接的，这部分不用修改
+ SQL解析：句法解析和语法解析，这部分很重要
+ 计划执行：没有实现计划
+ 会话管理：没有实现会话
+ 元数据管理：这个是存储在storage/common，很重要
+ 客户端：这部分不用修改
+ 执行计划缓存：未实现
+ 语言解析：未实现
+ 查询缓存：未实现

## 已实现

### SQL

首先将版本回退到初始化

```bash
git reset 38d788abb9435
```

看`src/observer/storage/default/default_storage_stage.cpp/void DefaultStorageStage::handle_event(StageEvent *event)`里面的swtich语句，可以通过看标志位查看已经实现或者将要实现的功能

+ SCF_INSERT：已实现对单个记录的插入，**需要修改**
+ SCF_UPDATE：未实现更新记录
+ SCF_DELETE：已实现删除记录，**需要修改**
+ SCF_CREATE_TABLE：已实现创建表，**需要修改**
+ SCF_DROP_TABLE：未实现删除表
+ SCF_CREATE_INDEX：已实现创建索引，**需要修改**
+ SCF_SHOW_TABLES：已实现展示有哪些表，不用修改
+ SCF_DESC_TABLE：已实现描述表，不用修改
+ SCF_LOAD_DATA：已实现从文件导入数据，不用修改

### 统计文件改动次数

用下面的脚本统计开赛以来修改的文件的次数 [git 如何统计一段时间文件（或文件夹）的修改次数 - 简书 (jianshu.com)](https://www.jianshu.com/p/07ed6d0836e5) 

```bash
git --no-pager log --format=format:'%h' --no-merges --since 2021-10-16 | \
awk '{system(" git --no-pager diff  --stat-name-width=300 --name-only "$1" "$1"~") }'| \
awk '{fs[$0]+=1} END{for(f in fs) printf("%d\t%s\r\n",fs[f],f) }' | sort -k 2
```

```bash
改动次数 文件名
3       src/observer/rc.h
52      src/observer/sql/executor/execute_stage.cpp
2       src/observer/sql/executor/execute_stage.h
1       src/observer/sql/executor/execution_node.cpp
53      src/observer/sql/executor/tuple.cpp
20      src/observer/sql/executor/tuple.h
3       src/observer/sql/executor/value.cpp
11      src/observer/sql/executor/value.h
25      src/observer/sql/parser/lex_sql.l
33      src/observer/sql/parser/lex.yy.c
3       src/observer/sql/parser/lex.yy.h
38      src/observer/sql/parser/parse.cpp
23      src/observer/sql/parser/parse_defs.h
1       src/observer/sql/parser/parse_stage.cpp
48      src/observer/sql/parser/yacc_sql.tab.c
37      src/observer/sql/parser/yacc_sql.tab.h
43      src/observer/sql/parser/yacc_sql.y
4       src/observer/storage/common/bitmap.cpp
4       src/observer/storage/common/bitmap.h
13      src/observer/storage/common/bplus_tree.cpp
6       src/observer/storage/common/bplus_tree.h
8       src/observer/storage/common/bplus_tree_index.cpp
5       src/observer/storage/common/bplus_tree_index.h
40      src/observer/storage/common/condition_filter.cpp
6       src/observer/storage/common/condition_filter.h
7       src/observer/storage/common/date.cpp
4       src/observer/storage/common/date.h
2       src/observer/storage/common/db.cpp
1       src/observer/storage/common/db.h
5       src/observer/storage/common/field_meta.cpp
3       src/observer/storage/common/field_meta.h
2       src/observer/storage/common/index.cpp
8       src/observer/storage/common/index.h
9       src/observer/storage/common/index_meta.cpp
8       src/observer/storage/common/index_meta.h
4       src/observer/storage/common/record_manager.cpp
1       src/observer/storage/common/record_manager.h
33      src/observer/storage/common/table.cpp
13      src/observer/storage/common/table.h
11      src/observer/storage/common/table_meta.cpp
3       src/observer/storage/common/table_meta.h
10      src/observer/storage/default/default_handler.cpp
5       src/observer/storage/default/default_handler.h
9       src/observer/storage/default/default_storage_stage.cpp
2       src/observer/storage/default/disk_buffer_pool.cpp
2       src/observer/storage/default/disk_buffer_pool.h
2       src/observer/storage/trx/trx.cpp
```

可以看到的是修改主要集中在下面四个地方

+ `sql/parser`：词法解析和语法解析
+ `sql/executor`：sql语句的执行阶段
+ `storage/common`：存储阶段的数据结构
+ `storage/default`：存储阶段的默认调用，缓冲池等

## 前置知识

### SEDA

这篇文章写得非常好 [SEDA架构_lxlzhn的博客-CSDN博客_seda架构](https://blog.csdn.net/lxlzhn/article/details/8163380) 

简而言之就是把一个过程（process）分拆为不同的阶段（stage），每个阶段再维护一个队列，简化了编程，可以进行资源的监控，调控和调度

## 项目结构

+ src
  + obclient：客户端的代码
  + observer：服务器的代码
    + event：事件相关，这部分基本不需要修改
    + handler：定义了一个通用的handler用来传递，这部分不用修改
    + net：服务器端的通信模块的代码，这部分不用修改
    + session：会话相关的代码，这部分不用修改
    + sql：sql语句传进来之后，解析，优化，执行等
    + storage：b+树，缓冲池，基本事务

## 项目的运行

先开服务器端`build/bin/observer -f etc/observer.ini`

然后开客户端`build/bin/obclient`

测试，运行`show tables;`

如果有错（那必然有错），参考 [OceanBase大赛miniob代码架构框架设计和说明 | lectures-on-dbms-implementation (oceanbase-partner.github.io)](https://oceanbase-partner.github.io/lectures-on-dbms-implementation/miniob-introduction) 

## 调用栈

稍微配置一下vscode（也许附录会记得说这个怎么配置，吧），给`create_table`打个断点，然后单步调试，看一下调用栈

```c++
Table::create
Db::create_table
DefaultHandler::create_table
DefaultStorageStage::handle_event
ExecuteStage::handle_request
ExecuteStage::handle_event
OptimizeStage::handle_event
ParseStage::handle_event
PlanCacheStage::handle_event
QueryCacheStage::handle_event
ResolveStage::handle_event
SessionStage::handle_request
SessionStage::handle_event
libcommon.so.1!common::Threadpool::run_thread
libpthread.so.0!start_thread
libc.so.6!clone() 
```

### Parse阶段

有很多地方是啥都不处理就流转到下一个event了，这里挑比较重要的`ParseStage::handle_event`说一说，这个阶段是把传进来的sql语句进行词法解析和语法解析的，讲解析出来的语句转换成数据结构存储起来，下面就上源代码（**后面的代码为了阅读方便，都做了删减处理**）

```c++
void ParseStage::handle_event(StageEvent *event) { 
    // 1. 处理这个事件，返回新事件
  StageEvent *new_event = handle_request(event);
    // 2. 标记老事件完成
  CompletionCallback *cb = new (std::nothrow) CompletionCallback(this, nullptr);
  event->push_callback(cb);
    // 3. 把新事件流转到下一个阶段
  optimize_stage_->handle_event(new_event);
  return;
}
```

看一下处理event的部分`handle_request`

```c++
StageEvent *ParseStage::handle_request(StageEvent *event) {
  SQLStageEvent *sql_event = static_cast<SQLStageEvent *>(event);
  const std::string &sql = sql_event->get_sql();
  Query *result = query_create();
    // 1. 解析sql
  RC ret = parse(sql.c_str(), result);
  return new ExecutionPlanEvent(sql_event, result);
}
```

看一下`parse`

```c++
RC parse(const char *st, Query *sqln) {
    // 1. 解析sql
  sql_parse(st, sqln);

  if (sqln->flag == SCF_ERROR)
    return SQL_SYNTAX;
  else
    return SUCCESS;
}

int sql_parse(const char *s, Query *sqls){
	ParserContext context;
	memset(&context, 0, sizeof(context));

	yyscan_t scanner;
	yylex_init_extra(&context, &scanner);
	context.ssql = sqls;
	scan_string(s, scanner);
    // 2. 解析sql
	int result = yyparse(scanner);
	yylex_destroy(scanner);
	return result;
}
```

这个`yyparse`是`yacc_sql.tab.c`生成的

而这个`yacc_sql.tab.c`是`yacc_sql.y`自动生成的

`yacc_sql.y`就是使用`bison`进行语法解析的模块

`yacc_sql.y`又会调用词法解析是吧，用的`lex.yy.c`

`lex.yy.c`又是`flex`的`lex_sql.l`生成的文件

### 词法解析

打开`lex_sql.l`，举个例子

```flex
[Ii][Nn][Nn][Ee][Rr][[:space:]][Jj][Oo][Ii][Nn]  RETURN_TOKEN(INNER_JOIN);
```

这句话也很简单，就是个正则，在不区分大小写的情况下，并且中间任意空格，来匹配`INNER_JOIN`这个词，然后在后面语法解析的时候会用上

这里有遇到的坑可以说一下

1. 词法的匹配是按照代码从上至下的顺序开始匹配的，所以如果你觉得某个词一部分前面出现过，那最好注意一下顺序，一般来说，解析的时候也会报warning。比如`NULLABLE`和`NULL`，如果`NULL`放在前面，就可能会匹配不到`NULLABLE`
2. 忘了（麻）

### 语法解析

打开`lex_sql.l`，举个例子

```bison
// 1. 这个命名感觉随便搞，没有什么实际作用
create_table:		/*create table 语句的语法解析树*/
// 2. 语法解析，按照LL(1)文法进行匹配
    create_table_token ID LBRACE attr_def attr_def_list RBRACE SEMICOLON 
		{
		// 3. 添加个标志位，显示这个语句到底是干什么的
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// 4. 一个写在parse.cpp中的函数
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, $2);
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
    ;

```

拿`create table t (id int, weight int) ; `举例

+ create_table_token：`create table`这个词
+ ID：`[A-Za-z_]+[A-Za-z0-9_]*`，也就是开头必须是英文字母，然后后面可以是数字，这里就是`t`
+ LBRACE：左括号
+ attr_def：可以看成`id int`
+ attr_def_list：递归定义在这里是`，weight int`，可以一直匹配下去
+ RBRACE：右括号
+ SEMICOLON：分号

语法分析的坑不是一般的多，他并不是从左往右匹配这么简单，遇到有歧义的地方，就必须要去了解一下LL(1)文法的部分

因为本科的时候最不喜欢编译原理，所以这里就不继续讲了，给出一波参考给大家

 [Flex(scanner)/Bison(parser)工作原理 - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/120812270) 

 [程序语言与编译系统课程研讨会 第5讲 基于Flex和Bison的编译实验_哔哩哔哩_bilibili](https://www.bilibili.com/video/BV17b4y1S7cU?from=search&seid=12436005774937996200&spm_id_from=333.337.0.0) 

## 题目

> 很多代码WangAShao有，就不放了，参考 [Jackson wang - 知乎 (zhihu.com)](https://www.zhihu.com/people/di-si-ren-cheng-74-98/posts) 

### 元数据（select-meta）

来哥专门强调了一下，先要做这个，不然后面的都做不出来，主要就是一个，如果元数据校验出错的时候返回`Failure`而不是默认的`no data`

首先，界定一下哪些是元数据。在这个题目里，元数据仅指代表（table），列（column）。要在创建表以及增删改查中，校验表名及列名是否是合法的。还不涉及表和列的相关性质（如非空列插入null没让校验）

具体的元数据在`TableMeta`这个类中

```c++
private:
  std::string   name_; // 表名
  std::vector<FieldMeta>  fields_; // 包含sys_fields 列
  std::vector<IndexMeta>  indexes_; // 索引
  int  record_size_ = 0; // 行计数器
  static std::vector<FieldMeta> sys_fields_; // 系统列 初始只有个事务列 后面会添加null位图列

```

运行一个create语句`create table dt (id int, birth date);`，可以看到`miniob/db/sys`下会生成俩文件`dt.data`和`dt.table`，这个是在创建表的时候，序列化函数生成的，其中`.data`是数据库中存放的行数据，是二进制存储的，没法直接看，`.table`是元数据

直接看`.table`，里面存储了列的元数据，索引信息，以及表名这三个

其中列的元数据又有以下部分

```c++
		{
			"len" : 4,
			"name" : "id",
			"nullable" : 0,
			"offset" : 8,
			"type" : "ints",
			"visible" : true
		},

```

+ len：字节长度，4字节
+ name：列名
+ nullable：是否可以为空，为了方便0为false，1为true
+ type：数据类型为整型，一共只支持几种类型，这个后面解释
+ visible：是否可见，可以设置一个列不可见，这样select的时候就不用打印出来了

然后看了这么多，最后发现想多了，他最后其实就是让你把某个地方返回`no data`的地方改成Failure，要么有这个表，返回一个空表，带表头，要么没这个表，返回一个`Failure`

那么根据题目来说哪些地方需要改呢？看这段代码

```c++
void SessionStage::callback_event
  int len = sev->get_response_len();
  if (len <= 0 || response == nullptr) {
    response = "No data\n";
    len = strlen(response) + 1;
  }
  return;
}

```

也就说是，如果在一个session的最后，事件回调发现你的返回是空的时候，它就给你返回的`No data`，也就是找，失败的地方，提前response加上`Failure`就行

参考 [lectures-on-dbms-implementation (oceanbase-partner.github.io)](https://oceanbase-partner.github.io/lectures-on-dbms-implementation/miniob-select-meta-implementation.html) 

就俩地方要加

+ 语法解析如果就出错了 比如`select * from;`这种，就要返回`failure`
+ CREATE_TABLE在`void DefaultStorageStage::handle_event`是官方加过了的，失败就返回`FAILURE`
+ 主要是在select阶段，如果`RC ExecuteStage::do_select`中，如果有一个`rc!=RC::SUCCESS`，就要注意是不是返回`FAILURE`了，当然有可能有特殊情况，这个再说

so easy，10分到手是吧

### 删表（drop-table）

直接定位到`RC Db::drop_table(const char* table_name)`

参考上面的create_table代码做一个逆操作

需要做的事情如下

+ 先找到这个表，如果没有就返回失败
+ 删除`.table`，删除`.data`，删除索引文件，删除缓冲池中的文件
+ 从打开表中删除表
+ 析构表

### 更新（update）

直接定位`RC update_record(Record *rec) `

做法也是简单粗暴，扫表，先删除满足条件的记录，然后添加新的记录进去，具体的做法就是在`scan_table`扫表的时候，加入个函数指针，如果满足条件的话，就会调用这个函数，也就是`update_record`函数

而在update的时候需要做的事情有这些

+ 删除索引中的记录
+ 添加新记录到索引
+ 修改磁盘上的记录（其实是在内存页中，这个时候修改了以后，缓冲池会标记这个页dirty，后面再刷到磁盘）

听起来很简单，坑就来了，比如说，我有一列是唯一键（unique）然后添加的新记录，刚好和另一行冲突了怎么说？所以这里还要向后兼容，本来应该用事务trx，但是这个时候还不会用这个trx就手动实现了事务，如果插入的时候冲突了，就回滚，重新插入原索引

这个地方给后面留了俩坑，nullable的列怎么办？日期需不需要特殊处理？这也没办法，当时也没想到，只能做到了再说

### 日期（date）

参考 [lectures-on-dbms-implementation (oceanbase-partner.github.io)](https://oceanbase-partner.github.io/lectures-on-dbms-implementation/miniob-date-implementation.html) 

日期就很麻烦了，要修改的有下面几个点

+ create_table：需要创建一个`DateValue`类继承`TupleValue`来进行存储日期信息，以及做比较等工作
+ insert：插入的时候还要同时插入到索引里面去
+ delete：这个主要是一个where
+ update：在更新阶段还要校验一下date
+ select：校验日期合法性，日期比较
+ create_index：我们的实现是把date当做INTS来比较的

我们实现了一个date类来对字符串进行校验，转换，为了偷懒我们直接使用了#include <regex> #include <chrono> #include <ctime>，将时间转换为一个整数，这个整数为现在的时间到1970-1-1的小时数

为什么没有使用简单点的`int hours = y*10000+m*100+d`，因为这个hash不是个双射，不能对hours进行运算之后还能保持他们原来的日期的加减的性质

比较坑的一点是，中途date出现了好几次的问题，但是不知道为什么，后来才发现，哦原来我们是东八区，东八区的时间+8才是一个整24小时的时间……牛牛牛，这个问题搞了两三天

一些tips

+ 在语法解析阶段的时候把日期当字符串输入就行了
+ 日期合法性校验的时候可以直接找一个长正则匹配掉，但是很慢，也可以先用正则匹配`xxxx-xx-xx`这种类似结构，再对里面的年月日进行校验。注意`2000-2-29`这种
+ 需要给AttrType添加DATES，注意，如果添加在FLOATS之前就不用改很多地方了
+ 要改的地方不少，tuple.cpp，value.h，parse.h，bplus_tree.cpp，condition_filter.cpp，table.cpp……

### 多表查询（select-tables）

这部分不是我做的，不过大概知道点思路

语法解析官方已经做好了，每一个表的查询，会生成一个选择执行器，执行选择执行器会返回一个tuple_set，tuple就是可能要输出的某一行，为什么不是record，因为可能有聚合之类的操作，导致行里面的列有变化

`if (tuple_sets.size() > 1) {`就说明是多表，要进行处理

我们是使用了一个`print_tuple_sets`来打印多表数据的，这里用到的就是笛卡尔积，也称直积，就是说我`t1`的每一个tuple都和`t2`的每一个tuple，合并成一个新的tuple，假设两个都有`n`个tuple，那最后一共有$n^2$个tuple，在这里因为样例比较简单，是可以直接用暴力，先合成大表，再过滤。但是后面inner join会有个500\*500\*500的样例，所以在这里就最好先实现dfs的方法，先看满不满足条件，如果满足，再merge，不满足就找下一个tuple了

并且在合并了之后的tuple还要走`check_all_condition`来过滤where后面的条件，特别是有多表之间的条件

其中还要注意的是，表头是要修改的，多表情况下可能输出`t1.id`这种表头，会提前记录表名和列名，在自己写的`void TupleSchema::print`中输出表头

### 聚合（aggregation-func）

聚合也不是我做的

聚合遇到了一个大坑，就是一开始没有说后面会出现聚合和普通查询同时存在的情况，看了看后面好像也不会有这个情况，就把聚合提出来做了个`do_aggregate`，结果后面发现子查询里可能会出现这种情况……

看了看@WangAShao的队的做法是，在`do_select`的时候判断是否是聚合节点，如果是，就不用原本的`node.execute()`，使用新写的聚合函数`node.excute_aggre()`，确实这才是正确的，避免了重写

做聚合就是在这个excute_aggre中扫表，扫表的中途进行聚合，操作如下

+ min，max：记录途中最大最小值
+ avg，sum：对满足条件的值进行累加，avg还要记录满足条件的个数用来除
+ count：计数（需要区分count(id)和count(\*)）

### 多表join（join-tables）

这里用的就是最朴素的simple-inner-join，上面提到了用的dfs，需要先筛选条件，再去merge下一个tuple

### 插入多条数据（inserts）

这个题主要的点在于事务，例如，向有唯一索引的列进行插入的时候，中间某一条失败就要进行回滚

这里用到了官方给的简单的事务`trx`，如果某一个插入的时候失败，事务就要回滚

### 唯一索引（unique）

首先需要的是在`index_meta.h`加一个标志位unique，然后要改的地方可太多了

你加了这个标志位，`create_index`的时候得传进来吧？然后序列化和反序列化索引的时候需要加进去吧？创建唯一索引的时候需要把所有的record里面对应的列都插到b+树里面。插入的时候需要判断是否已经有了这个值了是吧？更新的时候呢？

我的做法是写了一个`UniqueIndexInserter`，里面有个`std::set<int> set_`用来保存出现过的元素，不管是啥都先转成`int`，因为列基本都只有4个字节，不担心爆，如果`set_.count(xx)>0`了，那就不好意思，插入失败，回滚吧

### NULL类型(null)

一开始有三个想法

1. 用一个特殊值如`FFFFFF`来标志空位，难点：可能会有数据刚好为`FFFFFF`
2. 给每一列加一个标志位，难点：field->offset全要变化，同时field取出来的value也要特殊处理
3. 在系统列增加一个null列，难点：要实现bitmap，取field要处理

直接pass掉想法1，虽然可能数据现在可能没这么大，但是后面不好说

然后觉得想法2可行，一开始走入了错误的思路，就是给每一列加一个标志位，标志这一列是否为空，这引入了几个问题

1. 标志位必须要占用一个字节，否则没法字节对齐，不能用一个bit
2. 对于非null列来说，冗余开销很大
3. 很多地方offset是写死了的4，也就是要改成8，特别是一些涉及到b+树上面的比较，很复杂

都要写完了，最后推导重来实现的想法3

思路说一下

+ 不管是否有空列，给`sysfield`添加一个`null_field`，四个字节就好，可以支持标志32个列
+ 创建一个Bitmap类，对四个字节进行处理，如果某一个value为null，且根据field_meta，这一些nullable，就设置这个位置的bit为1，反之0
+ 需要注意的是，这列要放在sys_field，且visible为false，中途还有很多下标的转换，麻烦的不行
+ 所有涉及比较的地方，都要特判null
+ 新增`is null`，`is not null` 运算

### 简单子查询（simple-sub-query）

这部分是队友搞的

写了个`query_stack_pop`,把子查询先压入栈中，因为题目说了不会有相关子查询，所有先把子查询做了，然后把子查询语句换成一个值即可

然后再执行上述的select语句

### 多列索引(multi-index)

题目已经简化了一些，要求全匹配才走索引，如果是最左匹配，工作量还要++

修改以下31个地方，特别麻烦的就是B+树，B+数以前只考虑了比较单个键，现在的需求是比较多个键，那么需要在以前所有比较的时候都要修改，而且一改就是一大堆

感觉很多人这部分是没做的，就是增删改查的时候直接不走索引，因为索引如果不和唯一索引一起考察就不会出现问题

![](https://gitee.com/agaogao/photobed/raw/master/img/%E8%A1%A82_1.png)

![](https://gitee.com/agaogao/photobed/raw/master/img/%E8%A1%A82_2.png)

| 编号 | 要修改的部分                                            | 问题                             | 完成 |
| ---- | ------------------------------------------------------- | -------------------------------- | ---- |
| 1    | 语法解析                                                |                                  | √    |
| 2    | parse_defs.h中的CreateIndex改为数组                     |                                  | √    |
| 3    | parse_defs.h中的DropIndex                               |                                  | x    |
| 4    | default_storage_stage中的SCF_CREATE_INDEX               |                                  | √    |
| 5    | DefaultHandler::create_index                            |                                  | √    |
| 6    | Table::create_index                                     |                                  | √    |
| 7    | table_meta_.index(                                      |                                  | √    |
| 8    | table_meta_.find_index_by_field                         | 如果有一个列加过索引了就不能加了 | √    |
| 9    | IndexMeta                                               |                                  | √    |
| 10   | BplusTreeIndex                                          |                                  |      |
| 11   | BplusTreeIndex::create                                  |                                  |      |
| 12   | TableMeta::serialize(                                   |                                  | x    |
| 13   | TableMeta::deserialize                                  |                                  | x    |
| 14   | Index                                                   |                                  |      |
| 15   | BplusTreeHandler::create                                |                                  |      |
| 16   | BplusTreeHandler::insert_entry                          |                                  | x    |
| 17   | BplusTreeHandler::find_leaf                             |                                  |      |
| 18   | CmpKey                                                  |                                  |      |
| 19   | CompareKey                                              |                                  |      |
| 20   | find_index_for_scan                                     | select实现要用                   |      |
| 21   | find_index_for_scan_by_list                             | select实现要用                   |      |
| 22   | get_next_idx_in_memory                                  | select实现要用                   |      |
| 23   | satisfy_conditions                                      | select实现要用                   |      |
| 24   | open_scan改为多个                                       | select实现要用                   |      |
| 25   | scan_record 加一个compositeConditionFilter的 （或者改） | select实现要用                   |      |
| 26   | create_scanner要保存多个com_op和value                   | select实现要用                   |      |
| 27   | BplusTreeScanner open                                   | select实现要用                   |      |
| 28   | find_first_index_satisfied                              | select实现要用                   |      |
| 29   | insert_into_leaf                                        |                                  |      |
| 30   | insert_into_leaf_after_split                            |                                  |      |
| 31   | insert_into_parent                                      |                                  |      |

### 超长字段（text）

队友写的

> create table时使用了text关键字，在表字段中使用长度为8的text_page_num表示text字段，这个字段中存储两个page num，这两个page num存放具体的text字段的内容。
>
> insert 数据时找出两个空闲页（没有空闲的就alloc），放入text字段的数据，然后记录两个page num，存放到record中
>
> delete数据时发现有text_page_num字段，则先删除两个数据页中的数据，再删除record
>
> update,condition 差不多同上

看`disk_buffer_poll.h`，可以看到的是，每个页的大小为`1<<12=4KB`，测试的时候会有4K的数据，因为还要存一些header，一个Page不够，所以就需要开两个Page来存

修改完了以后要mark_dirty，用于后面写回

### 条件表达式（expression）

我们的做法是先用正则匹配这所有合法的条件表达式

`([\-]?[\+\-\*\/\(\)A-Za-z0-9\._]+[\+\-\*/]+[A-Za-z0-9\._]+[\(\)A-Za-z0-9\.\+\-\*/_]*)|(\-+[\(\)A-Za-z0-9\._]+)  yylval->string=strdup(yytext);RETURN_TOKEN(EXPRESSION);`

然后把匹配的这部分作为字符串传入查询执行阶段，在查询执行阶段再通过查询的时候tuple里的value来替换表达式中的变量，再用一个四则运算解析算出最后结果，进行比较

大佬在上一篇里面有评论

![](https://gitee.com/agaogao/photobed/raw/master/img/20220111150913.png)

想了一下，这一步我们相当于放在了执行阶段做，但是我们正则效率是有点低是真的，大家可以参考大佬这部分的思路（果然我还是最不喜欢编译原理……）

### 复杂子查询（complex-sub-query）

复杂子查询就很麻烦了，其中还有二义性的问题，详情搜索相关子查询

然后有聚合，有多表，最后实在有几个样例写不出来了，把测试脚本放一放

```sql
select * from at where name in(select name from nt) and id in(select len from test);
select * from at where (select max(at.id) from at)=(select max(test.len) from test);
select * from at where (select max(at.id) from at) = 4;
select * from at where 4= (select max(at.id) from at);
select * from test where len <=(select avg(at.id) from at where at.id>test.id);
select * from test where test.id<(select avg(ft.para) from ft where ft.para>test.wid);
complex-sub-query: result file difference(`-` is yours and `+` is base)
 SELECT * FROM CSQ_1 WHERE FEAT1 <> (SELECT AVG(CSQ_2.FEAT2) FROM CSQ_2 WHERE CSQ_2.FEAT2 > CSQ_1.FEAT1);

```

### 排序（order-by）

排序没有很复杂，就是在做`do_select`之后，得到了tuple_set，然后对tuple_set进行一下排序然后输出去就行

### 分组（group-by）

group-by要麻烦一点，在parse阶段记录一下要通过什么字段进行group-by，然后在do_select做完之后扫tuple_set，边扫边记录对应字段，处理规则上面聚合有说，同时还要记录group-by后面跟的字段的set，最后输出的时候对应输出即可，和聚合一样，这里的表头也是要修改的

### LRU（lru）

本来说要检查这一部分，但是最后没有检查

原代码中是实现了LRU的，因为原缓冲池的大小仅为50，所以只用遍历一遍就能知道哪个桶是最近没有使用过的。算法复杂度为O(n)。

但是看ob的意思是要实现O(1)的方法，那么最简单的实现方法就是哈希表加双向链表

+ 创建一个Map<int,Node>，其中键为索引号（1-50），Node为池结点，里面是一个页
+ 创建一个`Node* head`，当做头结点，创建一个`Node* tail`当尾结点，选择头插法或者尾插法都可以，我这里选择了尾插法，头结点是最老的

+ get：直接从Map中获取Node，如果获取到了，就删除该结点，加入到尾部
+ put：如果缓冲池已经满了，删除`head->next`结点，插入新节点到尾部

## 一些小技巧

+ vscode可以自己配置debug非常方便，`launch.json`中输入启动命令，`task.json`中还可以设置一些启动之前要执行的命令如make之类的，一键就能执行
+ trace log的时候可以加自己的名字之类的东西，grep或者ctrl+F自己的名字，直接出你想看的东西
+ 在线文档很好用，一个项目开一个文档，所有人都可以同时看和编辑
+ gitlen插件可以实时显示blame，谁写的屎山一目了然

## 总结

上一篇文章基本都总结过了，然后这两天又复盘了一下，感觉其实有很大一部分都没有那么难，主要还是一开始没用上单步调试，导致看调用栈的时候一直用的是log，调用栈很深的时候看起来很麻烦，日志也很大（之前队友mac的内存就满了……）

有几个比较困难的，如复杂子查询，多列索引，确实需要很多时间去做

最主要的还是计划，而不是敲代码。如果能在一开始看题阶段就能够想到后面do_select中会加这么多功能，就应该多讨论一下，然后给后面的代码留个地儿

还有就是对数据库不熟悉，有很多语法上面的问题有歧义，导致写代码的时候出错，只有一次次和测试样例校对才能知道出在哪里

总之，对于普通关系型数据库，我们也有了个大概的了解，可能效率不怎么样，但是整个流程应该还是打通了没问题，对于下一步学习mysql和NewSQL一定会有所帮助