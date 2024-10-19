package com.yellow.springboothly.mapper;
import com.yellow.springboothly.pojo.User;
import org.apache.ibatis.annotations.Insert;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Select;

@Mapper
public interface UserMapper {
    //根据用户名查询用户
    @Select("select * from user where username=#{username}")
    User findByUserName(String username);
    //添加
    @Insert("INSERT into user(username,password,create_time,create2_time)+" +
            "values(#{username},#{password},now())")
    void add(String username,String password);
}
