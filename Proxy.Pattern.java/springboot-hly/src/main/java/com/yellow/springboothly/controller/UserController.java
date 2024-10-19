package com.yellow.springboothly.controller;

import com.yellow.springboothly.Utils.JwtUtil;
import com.yellow.springboothly.pojo.Result;
import com.yellow.springboothly.Utils.JwtUtil;
import com.yellow.springboothly.pojo.User;
import com.yellow.springboothly.service.UserService;
import jakarta.validation.constraints.Pattern;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;
import java.util.HashMap;
import java.util.Map;

@RestController
@RequestMapping("/user")
public class UserController {
    @Autowired
    private UserService userService;

    @PostMapping("/register")
    public Result register(String username, String password){
        //校验//此处可用注解校验，并且要对校验失败异常处理和需要导入依赖坐标
        if(username!=null&&username.length()>=5&&username.length()<=16
        &&password!=null&&password.length()>=5&&password.length()<=16){
            //查询
            User u=userService.findByUserName(username);
            if(u==null){
                //没有被占用---注册
                userService.register(username,password);
                return Result.success();
            }else {
                //占用
                return Result.error("用户名以被占用");
            }
        }else {
            return Result.error("参数不合法");
        }

    }
    @PostMapping("/login")
    public Result<String> login(@Pattern(regexp = "^\\${5,16}$") String username,@Pattern(regexp = "^\\${5,16}$") String password){
        //根据用户名查询用户
        User loginUser = userService.findByUserName(username);

        //判断该用户是否存在
        if(loginUser==null){
            return Result.error("用户名错误！！！");
        }
        //判断密码是否正确
        if(password.equals(loginUser.getPassword())){
            //登录成功
            Map<String,Object> claims=new HashMap<>();
            claims.put("id",loginUser.getId());
            claims.put("username",loginUser.getUsername());
            String token=JwtUtil.genToken(claims);
            return Result.success(token);
        }
        return Result.error("密码错误!!!");
    }
}
