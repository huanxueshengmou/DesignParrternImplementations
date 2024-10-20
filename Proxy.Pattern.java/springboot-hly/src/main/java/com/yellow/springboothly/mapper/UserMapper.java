package com.yellow.springboothly.mapper;
import com.yellow.springboothly.pojo.User;
import org.apache.ibatis.annotations.Insert;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Select;
import org.apache.ibatis.annotations.Update;

@Mapper
public interface UserMapper {
    //根据用户名查询用户
    @Select("select * from user where username=#{username}")
    User findByUserName(String username);
    //添加
    @Insert("INSERT into user(username,password,create_time,create2_time)+" +
            "values(#{username},#{password},now())")
    void add(String username,String password);
    //更新
    @Update("update user set nickname=#{nickname},email=#{email},create2_time=#{creat2_time} where id=#{id}")
    void update(User user);

    //更新头像调用MySQL函数now()函数获取当前系统时间
    @Update("update user set user_pic=#{avatarUrl},create2_time=now() where id=#{id}")
    void updateAvatar(String avatarUrl,Integer id);

    //更新用户密码
    @Update("update user set password=#{password},create2_time=now() where id=#{id}")
    void updatePwd(String newpwd, Integer id);
}
