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

class AsyncTask
{
public:
    AsyncTask();
    ~AsyncTask();
    int Resume();
    int  Init(const char *lua_file, uint64_t task_id);
    void PushPkg(const char *pkg_buf, size_t pkg_len);
    inline uint64_t get_task_id() { return task_id; };
private:
    lua_State *state;
    lua_State *co;
    uint64_t task_id;
};

class AsyncTaskMgr
{
public:
    AsyncTaskMgr();
    ~AsyncTaskMgr();
    AsyncTask * CreateTask(const char *lua_file);
    void FiniTask(uint64_t task_id);

private:
    typedef std::map<uint64_t, AsyncTask *> AsyncTaskMap_T;
    AsyncTaskMap_T asynctask_map;
    int free_id;
};

#endif
