function main()
    print("start login task....")
    -- 1 接收到login请求
    print("login pkg: " .. PKG)
    print( "login pkg process")
    print("send pkg to OAuth server to atk_verify")
    coroutine.yield()

    -- 2 接收到oauth_verify回包
    print("oauth_verify pkg: " .. PKG)
    print("oauth_verify pkg process")
    print("send pkg to OAuth server to get friend list")
    coroutine.yield()

    -- 3 接收到get_friend_list回包
    print("get_friend_list pkg: " .. PKG)
    print("get_friend_list pkg process")
    print("send pkg to OAuth server to get friend detail")
    coroutine.yield()

    -- 4 接收到get_friend_detail回包
    print("get_friend_detail pkg: " .. PKG)
    print("get_friend_detail pkg process")
    print("send pkg to client . login over")

end

TASK = coroutine.create(main)
