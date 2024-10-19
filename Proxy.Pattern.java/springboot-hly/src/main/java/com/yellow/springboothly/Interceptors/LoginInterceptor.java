package com.yellow.springboothly.Interceptors;

import com.yellow.springboothly.Utils.JwtUtil;
import com.yellow.springboothly.pojo.Result;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import org.springframework.stereotype.Component;
import org.springframework.web.servlet.HandlerInterceptor;

import java.util.Map;
//拦截器
@Component//将当前拦截对象注入loc容器中
public class LoginInterceptor implements HandlerInterceptor {
    @Override
    public boolean preHandle(HttpServletRequest request, HttpServletResponse response, Object handler) throws Exception {
        //令牌验证,Authorization请求头
        String token=request.getHeader("Authorization");
        //验证token，成功则可进入查询文章所有数据
        try {
            Map<String,Object> claims= JwtUtil.parseToken(token);
            return true;//验证成功，放行

        } catch (Exception e) {
            //http响应状态码为401
            response.setStatus(401);
            return false;//校验失败不放行
        }
    }
}
