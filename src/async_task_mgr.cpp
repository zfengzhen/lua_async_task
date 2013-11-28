/**
* @file async_task_mgr.cpp
* @brief 异步任务管理器
* @author fergus
* @version 0.0.1
* @date 2013-12-06
*/

#include "async_task_mgr.h"

const char *STR_TASK_LOGIN = "login";
const char *STR_TASK_NULL = "";

int AsyncTaskMgr::free_id = 11;

AsyncTaskMgr::AsyncTaskMgr()
{
    master_state = NULL;
}

AsyncTaskMgr::~AsyncTaskMgr()
{
    lua_close(master_state);
    master_state = NULL;
}

int AsyncTaskMgr::init(const char *lua_file)
{
    int ret = 0;

    master_state = luaL_newstate();
    if ( unlikely( master_state == NULL ) )
        return -1;
    
    luaL_openlibs(master_state);  

    ret = luaL_dofile(master_state, lua_file);
    if ( unlikely( ret != 0 ) )
        return -2;

    lua_newtable(master_state);
    lua_setglobal(master_state, "TASK_TABLE");

    return 0;
}

void AsyncTaskMgr::register_func(const char *func_name, lua_CFunction func)
{
    lua_register(master_state, func_name, func);
}

int AsyncTaskMgr::create_task(int task_type)
{
    int task_id = free_id++;

    lua_getglobal(master_state, "TASK_TABLE");
    lua_pushinteger(master_state, task_id);
    lua_State *co = lua_newthread(master_state);
    lua_settable(master_state, -3);
    lua_pushinteger(co, task_id);
    lua_setglobal(co, "TASK_ID");
    lua_getglobal(co, get_task_name(task_type));
    lua_settop(master_state, 0);

    return task_id;
}

void AsyncTaskMgr::push_data(int task_id, void *data)
{
    lua_getglobal(master_state, "TAST_TABLE");
    lua_pushinteger(master_state, task_id);
    lua_gettable(master_state, -2);

    lua_State *co = lua_tothread(master_state, -1);
    lua_settop(master_state, 0);

    if (co == NULL)
        return;

    lua_pushlightuserdata(co, data);
    lua_setglobal(co, "DATA");

    return;
}

int AsyncTaskMgr::resume(int task_id)
{
    lua_getglobal(master_state, "TASK_TABLE");
    lua_pushinteger(master_state, task_id);
    lua_gettable(master_state, -2);

    lua_State *co = lua_tothread(master_state, -1);
    lua_settop(master_state, 0);

    if (co == NULL)
        return -1;

    return lua_resume(co, master_state, 0);
}

void AsyncTaskMgr::close_task(int task_id)
{
    lua_getglobal(master_state, "TASK_TABLE");
    lua_pushinteger(master_state, task_id);
    lua_pushnil(master_state);
    lua_settable(master_state, -3);
    lua_settop(master_state, 0);

    return;
}

const char *AsyncTaskMgr::get_task_name(int task_type)
{
    switch(task_type)
    {
        case E_TASK_LOGIN:
            return STR_TASK_LOGIN;
        default:
            return STR_TASK_NULL;
    } 

    return STR_TASK_NULL;
}

