# MiniOB

## 运行

根目录(miniobggb)下运行服务端

```
build/bin/observer -f etc/observer.ini
```

运行客户端

```
build/bin/obclient 
```

默认通过6789端口进行连接，日志文件存储在

build/bin/obserever.log.*

## oceanbase模块

| 模块          | 位置                         | 备注                                         |
| ------------- | ---------------------------- | -------------------------------------------- |
| 网络          | src/observer/net             |                                              |
| sql解析       | src/observer/sql/parser/     | lex_sql.l负责词法解析 yacc_sql.l负责语法解析 |
| 计划执行      | src/observer/sql/executor/   | 主要是execute_stage.cpp                      |
| 会话管理      | src/observer/sql/session/    | 主要是session_stage.cpp                      |
| 元数据管理    | src/observer/storage/common/ |                                              |
| 客户端        | src/obclient/                |                                              |
| 执行计划缓存* | src/observer/plan_cache/     | 将第一次执行的计划缓存在内存中               |
| 语言解析*     | src/observer/parser/         | resolve_stage.cpp                            |
| 查询缓存*     | src/observer/query_cache/    | 将查询结果缓存在内存中                       |

*留作决赛做查询优化实现

