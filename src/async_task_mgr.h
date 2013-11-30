/**
* @file async_task_mgr.h
* @brief 异步任务管理器
* @author fergus
* @version 0.0.1
* @date 2013-12-06
*/

#include <stdint.h>
#include <map>

/*
优化分支预测，
编写代码时可以根据判断条件发生的概率来优化处理器的取指操作
unlikely 表示你可以确认该条件是极少发生的，相反likely表示该条件多数情况下会发生
*/
#if defined(__GNUC__)
    #define likely(x) __builtin_expect ((x), 1)
    #define unlikely(x) __builtin_expect ((x), 0)
#else
    #define likely(x) (x)
    #define unlikely(x) (x)
#endif

#ifndef ASYNC_TASK_MGR_H_
#define ASYNC_TASK_MGR_H_

extern "C" 
{
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
};

class AsyncTaskMgr
{
public:
    AsyncTaskMgr();
    ~AsyncTaskMgr();
    int init(const char *lua_file);
    void register_func(const char *func_name, lua_CFunction func); 
    int create_task(const char* lua_func, int task_id);
    void set_task_id(int task_id);
    void push_data(int task_id, const char* lua_var, void *data);
    void push_integer(int task_id, const char* lua_var, int num);
    void push_string(int task_id, const char* lua_var, const char*  str);
    int resume(int task_id);
    void close_task(int task_id);
private:
    lua_State *master_state;
};

#endif
