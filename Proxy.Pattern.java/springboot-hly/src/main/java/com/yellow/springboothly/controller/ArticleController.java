package com.yellow.springboothly.controller;

import com.yellow.springboothly.Utils.JwtUtil;
import com.yellow.springboothly.pojo.Result;
import jakarta.servlet.http.HttpServletResponse;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestHeader;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import java.util.Map;

//登录认证,登录后才可以进入文章查询数据
@RestController
@RequestMapping("/article")
public class ArticleController {
    @GetMapping("/list")
//用拦截器校验令牌
    //Authorization为请求头，用来获取token
    public Result<String> list(){
        return Result.success("所有的文章数据");
    }


//一般令牌校验方法，缺点在需要校验多时过于繁琐
    /*//Authorization为请求头，用来获取token
    public Result<String> list(@RequestHeader(name="Authorization") String token, HttpServletResponse response){
        *//*//验证token，成功则可进入查询文章所有数据
        try {
            Map<String,Object> claims=JwtUtil.parseToken(token);
            return Result.success("所有的文章数据...");

        } catch (Exception e) {
            //http响应状态码为401
            //校验失败
            response.setStatus(401);
            return Result.error("未登录");
        }*/

}
