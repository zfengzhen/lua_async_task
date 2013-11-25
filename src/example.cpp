#include <sys/time.h>
#include <unistd.h>
#include <string.h>
#include "async_task_mgr.h"

int main()
{
    int ret = 0;
    
    AsyncTaskMgr mgr;
    AsyncTask *async_task;
    // 1 假设收到一个客户端请求，创建一个TASK
    async_task = mgr.CreateTask("login.lua");
    if ( async_task == NULL )
    {
        printf("create task error!\n");
        return -1;
    }

    // 2 该请求需要传递的参数传入TASK 并启动, 假设为登录
    char pkg_client[64] = "login"; 
    async_task->PushPkg((const char *)pkg_client, strlen(pkg_client));
    async_task->Resume();

    sleep(1);
    printf("...\n"); 
    sleep(1);
    printf("...\n"); 
    sleep(1);
    printf("...\n"); 
    // 3 收到OAuth验证回包
    printf("server frame recv oauth_veirfy pkg\n");
    char pkg_oauth_verify[64] = "pkg_oauth_verify"; 
    async_task->PushPkg((const char *)pkg_oauth_verify, strlen(pkg_oauth_verify));
    ret = async_task->Resume();

    if ( ret == LUA_OK )
    {
        printf("task compelte!\n");
        mgr.FiniTask(async_task->get_task_id());
    }
    else if ( ret == LUA_YIELD )
    {
        printf("task yield!\n");
    }
   
    sleep(1);
    printf("...\n"); 
    sleep(1);
    printf("...\n"); 
    sleep(1);
    printf("...\n"); 
    // 3 拉取OAuth好友列表
    printf("server frame recv get_friend_list pkg\n");
    char pkg_get_friend_list[64] = "pkg_get_friend_list"; 
    async_task->PushPkg((const char *)pkg_get_friend_list, strlen(pkg_get_friend_list));
    ret = async_task->Resume();
   
    if ( ret == LUA_OK )
    {
        printf("task compelte!\n");
        mgr.FiniTask(async_task->get_task_id());
    }
    else if ( ret == LUA_YIELD )
    {
        printf("task yield!\n");
    }
   
    sleep(1);
    printf("...\n"); 
    sleep(1);
    printf("...\n"); 
    sleep(1);
    printf("...\n"); 
    // 4 拉取OAuth好友详细信息
    printf("server frame recv get_friend_detail pkg\n");
    char pkg_get_friend_detail[64] = "pkg_get_friend_detail"; 
    async_task->PushPkg((const char *)pkg_get_friend_detail, strlen(pkg_get_friend_detail));
    ret = async_task->Resume();

    if ( ret == LUA_OK )
    {
        printf("task compelte!\n");
        mgr.FiniTask(async_task->get_task_id());
    }
    else if ( ret == LUA_YIELD )
    {
        printf("task yield!\n");
    }
   
    
    return 0;
}
