package com.yellow.springboothly.service.impl;

import com.yellow.springboothly.mapper.UserMapper;
import com.yellow.springboothly.pojo.User;
import com.yellow.springboothly.service.UserService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

@Service//注入容器
public class UserServiceImpl implements UserService
{
    @Autowired
    private UserMapper usermapper;
    @Override
    public User findByUserName(String username) {
        User u=usermapper.findByUserName(username);
        return u;
    }

    @Override
    public void register(String username, String password) {
        //添加
        usermapper.add(username,password);

    }
}
