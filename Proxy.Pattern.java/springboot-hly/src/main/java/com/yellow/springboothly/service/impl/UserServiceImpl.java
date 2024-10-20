package com.yellow.springboothly.service.impl;

import Time.LocalDateTime;
import com.yellow.springboothly.Utils.ThreadLocalUtil;
import com.yellow.springboothly.mapper.UserMapper;
import com.yellow.springboothly.pojo.User;
import com.yellow.springboothly.service.UserService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.Map;

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

    @Override
    public void updateAvatar(String avatar) {
        //获取用户id,强转为int类型
        Map<String,Object> map= ThreadLocalUtil.get();
        Integer id=(Integer) map.get("id");
        usermapper.updateAvatar(avatar,id);
    }

    @Override
    public void update(User user) {
        user.setUpdateTime(LocalDateTime.now());
        usermapper.update(user);
    }

    @Override
    public void updatePwd(String newpwd) {
        Map<String,Object> map= ThreadLocalUtil.get();
        Integer id=(Integer) map.get("id");
        usermapper.updatePwd(newpwd,id);
    }
}
