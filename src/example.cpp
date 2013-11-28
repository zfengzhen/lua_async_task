#include <sys/time.h>
#include <unistd.h>
#include <string.h>
#include "async_task_mgr.h"

int main()
{
    int ret = 0;
    
    AsyncTaskMgr mgr;

    mgr.init("task_main.lua");
    // 1 假设收到一个客户端请求，创建一个TASK
    int task_id = 0;
    task_id = mgr.create_task(E_TASK_LOGIN);
   
    // 2 该请求需要传递的参数传入TASK 并启动, 假设为登录
    ret = mgr.resume(task_id);
    if ( ret == LUA_OK )
    {
        printf("task compelte!\n");
        mgr.close_task(task_id);
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
    // 3 收到OAuth验证回包
    printf("server frame recv oauth_veirfy pkg\n");
    ret = mgr.resume(task_id);
    if ( ret == LUA_OK )
    {
        printf("task compelte!\n");
        mgr.close_task(task_id);
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
    ret = mgr.resume(task_id);
    if ( ret == LUA_OK )
    {
        printf("task compelte!\n");
        mgr.close_task(task_id);
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
    ret = mgr.resume(task_id);
    if ( ret == LUA_OK )
    {
        printf("task compelte!\n");
        mgr.close_task(task_id);
    }
    else if ( ret == LUA_YIELD )
    {
        printf("task yield!\n");
    }
   
    return 0;
}
