/**
* @file async_task_mgr.cpp
* @brief 异步任务管理器
* @author fergus
* @version 0.0.1
* @date 2013-12-06
*/

#include "async_task_mgr.h"

AsyncTask::AsyncTask()
{
    state = NULL;
    co = NULL;
}

AsyncTask::~AsyncTask()
{
    lua_close(state);
    state = NULL;
}

int AsyncTask::Resume()
{
    return lua_resume(co, state, 0);
}

void AsyncTask::PushPkg(const char *pkg_buf, size_t pkg_len)
{
    lua_pushlstring(state, pkg_buf, pkg_len);
    lua_setglobal(state, "PKG");
}

int AsyncTask::Init(const char *lua_file, uint64_t task_id)
{
    int ret = 0;

    state = luaL_newstate();
    if ( unlikely( state == NULL ) )
        return -1;
    
    luaL_openlibs(state);  

    ret = luaL_dofile(state, lua_file);
    if ( unlikely( ret != 0 ) )
        return -2;

    lua_getglobal(state, "TASK");
    ret = lua_isthread(state, -1);
    if ( unlikely( ret != 1 ) )
        return -2;
     
    co = lua_tothread(state, -1);
    lua_settop(state, 0);
    if ( unlikely ( co == NULL ) )
        return -3;

    this->task_id = task_id;

    return 0;
}

AsyncTaskMgr::AsyncTaskMgr()
{
    free_id = 1;
}

AsyncTaskMgr::~AsyncTaskMgr()
{

}

AsyncTask * AsyncTaskMgr::CreateTask(const char *lua_file)
{
    int ret = 0;

    AsyncTask * async_task = new AsyncTask();
    if ( unlikely( async_task == NULL ) )
        return NULL;

    ret = async_task->Init(lua_file, free_id);

    if ( unlikely( ret != 0 ) )
    {
        delete async_task;
        return NULL;
    }

    asynctask_map.insert( std::pair<uint64_t, AsyncTask *>( free_id , async_task ) );
    free_id++; 
    
    return async_task;
}

void AsyncTaskMgr::FiniTask(uint64_t task_id)
{
    AsyncTaskMap_T::iterator iter = asynctask_map.find( task_id );                                                          
    if( likely( iter != asynctask_map.end() ) )                                                                                               
    {                                                                                                                                 
        delete iter->second;                                                                                                         
        asynctask_map.erase( iter );                                                                                                
    }                                                                                                                                 

    return;   
}

