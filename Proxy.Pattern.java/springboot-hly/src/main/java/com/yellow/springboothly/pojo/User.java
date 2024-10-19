package com.yellow.springboothly.pojo;

import Time.LocalDateTime;
import com.fasterxml.jackson.annotation.JsonIgnore;
import lombok.Data;
@Data
public class User {

    private Integer id;
    private String username;
//让springmvc把当前对象转换成json字符串的时候，忽略password
//最终的json字符串中就没有password这个属性，保护密码不显示出来
    @JsonIgnore
    private String password;
    private String nickname;
    private String email;
    private String userPic;
    private LocalDateTime createTime;
    private LocalDateTime updateTime;



}
