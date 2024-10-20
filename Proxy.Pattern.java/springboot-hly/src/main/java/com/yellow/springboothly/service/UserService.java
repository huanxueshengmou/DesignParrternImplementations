package com.yellow.springboothly.service;

import com.yellow.springboothly.pojo.User;

public interface UserService {
    //根据用户名查询用户
    User findByUserName(String username);
    //注册
    void register(String username,String password);
    //更新表信息
    void update(User user);
    //更新头像
    void updateAvatar(String avatar);
    //更新用户密码
    void updatePwd(String newpwd);
}
