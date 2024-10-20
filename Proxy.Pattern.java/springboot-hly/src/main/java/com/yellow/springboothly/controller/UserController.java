package com.yellow.springboothly.controller;

import com.yellow.springboothly.Utils.JwtUtil;
import com.yellow.springboothly.Utils.ThreadLocalUtil;
import com.yellow.springboothly.pojo.Result;
import com.yellow.springboothly.Utils.JwtUtil;
import com.yellow.springboothly.pojo.User;
import com.yellow.springboothly.service.UserService;
import com.yellow.springboothly.service.impl.UserServiceImpl;
import jakarta.validation.constraints.Pattern;
import org.hibernate.validator.constraints.URL;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.util.StringUtils;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.*;

import java.util.HashMap;
import java.util.Map;

@RestController
@RequestMapping("/user")
public class UserController {
    @Autowired
    private UserService userService;
    @Autowired
    private UserServiceImpl userServiceImpl;

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

//使用拦截器
    @GetMapping("/userInfo")
    //根据用户id获取用户信息，通过请求头获取
    public Result<User> userInfo(/*@RequestHeader(name="Authorization") String token*/){
        //根据用户名查询用户信息
        //Map<String,Object> map=JwtUtil.parseToken(token);
        //String username=(String) map.get("username");
        Map<String,Object> map=ThreadLocalUtil.get();
        String username=(String) map.get("username");
        User user=userService.findByUserName(username);
        //将user响应给浏览器
        return Result.success(user);
    }

//未使用ThreadLocal前的代码
    /*@GetMapping("/userInfo")
    //根据用户id获取用户信息，通过请求头获取
    public Result<User> userInfo(@RequestHeader(name="Authorization") String token){
        //根据用户名查询用户信息
        Map<String,Object> map=JwtUtil.parseToken(token);
        String username=(String) map.get("username");
        User user=userService.findByUserName(username);
        //将user响应给浏览器
        return Result.success(user);
    }*/

    //更新表数据注解@RequestBody使mvc框架自动读取请求体里面的json格式数据
    @PutMapping("/update")//@Validated加入才能生效
    public Result update(@RequestBody @Validated User user){
        userService.update(user);
        return Result.success();
    }

    //更新头像avatarUrl头像地址@URL用于校验是否为url格式地址
    @PatchMapping("/updateAvatar")
    public Result updateAvatar(@RequestParam @URL String avatarUrl){
        userService.updateAvatar(avatarUrl);
        return Result.success();
    }

    //更新用户密码注解@RequestBody使mvc框架自动读取请求体里面的json格式数据转换成map集合数据
    @PatchMapping("/updatePwd")
    public Result updatePwd(@RequestBody Map<String,String> params){
        //校验参数
        //获取原密码
        String oldPwd=params.get("old_pwd");
        //新密码
        String newpwd=params.get("new_pwd");
        //确认密码
        String repwd=params.get("re_pwd");
        //校验不能为空
        if(!StringUtils.hasLength(oldPwd)||!StringUtils.hasLength(newpwd)||!StringUtils.hasLength(repwd)){
            return Result.error("缺少必要参数");
        }
        //原密码是否正确
        //调用user service根据用户名拿到原密码，和更新后的两个密码进行比对
        Map<String,Object> map=ThreadLocalUtil.get();
        String username=(String) map.get("username");
        User loginUser=userService.findByUserName(username);
        if (!loginUser.getPassword().equals(oldPwd)){
            return Result.error("原密码错误");
        }
        //校验newpwd与repwd是否一样
        if(!repwd.equals(newpwd)){
            return Result.error("两次填写密码不一样");
        }

        //调用service完成密码更改
        userService.updatePwd(newpwd);
        return Result.success();

    }

}
