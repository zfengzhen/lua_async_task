lua_async_task
==============

use lua coroutine to implement c++ asynchronous task

游戏后台中常见的一种架构
异步单进程架构

常见的单进程异步代码处理
请求 -> 保存session -> 异步逻辑（其他server服务）
异步逻辑回包 -> 恢复session -> 本地逻辑 -> 保存session -> 异步逻辑（其他server服务）

session保存的两种方式：
1、session较小，直接保存在网络包上，回包时获取
2、session较大，创建session和id的map，将session保存在共享内存上，网络包上带上session id，回包时根据id获取session

性能较好，可读性差，线性逻辑代码被拆分为许多不同的部分存在不同的代码里，需要根据不同的回调点去串连起来

采用lua协程进行异步逻辑处理
1、C++处理事件触发以及定时器触发
2、根据触发事件找到相应的Task，进入Task保存的Lua协程中继续执行
3、在Lua协程中遇到异步逻辑处理时，通过coroutine。yield放弃CPU，恢复到主逻辑

优点：
1、增加异步代码开发效率，所有逻辑按同步方式写入Lua脚本中
2、对于策划易变的逻辑，Lua脚本也会较容易修改，并且能够实现热更新
