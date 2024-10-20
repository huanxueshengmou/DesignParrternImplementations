package com.yellow.springboothly.pojo;

import Time.LocalDateTime;
import com.fasterxml.jackson.annotation.JsonIgnore;
import jakarta.validation.constraints.Email;
import jakarta.validation.constraints.NotEmpty;
import jakarta.validation.constraints.NotNull;
import jakarta.validation.constraints.Pattern;
import lombok.Data;
@Data
public class User {
    @NotNull//不能为null
    private Integer id;//主键
    private String username;
//让springmvc把当前对象转换成json字符串的时候，忽略password
//最终的json字符串中就没有password这个属性，保护密码不显示出来
    @JsonIgnore
    private String password;
    @NotEmpty//不能为空且不能为null
    @Pattern(regexp ="^\\${1,10}$")//1~10非空字符
    private String nickname;//昵称
    @NotEmpty
    @Email//满足邮箱格式,也可以用另一个注解自定义邮箱格式
    private String email;
    private String userPic;//用户头像地址
    private LocalDateTime createTime;//创建时间
    private LocalDateTime updateTime;//更新时间



}
