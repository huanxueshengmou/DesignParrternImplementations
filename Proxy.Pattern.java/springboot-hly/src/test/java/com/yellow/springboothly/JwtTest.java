package com.yellow.springboothly;

import com.auth0.jwt.JWT;
import com.auth0.jwt.JWTVerifier;
import com.auth0.jwt.algorithms.Algorithm;
import com.auth0.jwt.interfaces.Claim;
import com.auth0.jwt.interfaces.DecodedJWT;
import org.junit.Test;

import java.util.Date;
import java.util.HashMap;
import java.util.Map;
//生成令牌
public class JwtTest {
    @Test
    public void jetGen(){
        Map<String,Object> claims=new HashMap<>();
        claims.put("id","1");
        claims.put("username","张三");

        String token= JWT.create()
                .withClaim("user",claims)//添加获取
                //添加过期时间
                .withExpiresAt(new Date(System.currentTimeMillis()+1000*60*60*3))
                //指定算法配置密钥,"yellow"为密钥
                .sign(Algorithm.HMAC256("yellow"));

        System.out.println(token);
    }
    //测试认证密钥
    @Test
    public void testParse(){
        String token="eyJhbGciOiJIUzI1NiIsI" +
                "nR5cCI6IkpXVCJ9.eyJ1c2VyIj" +
                "p7ImlkIjoiMSIsInVzZXJuYW1l" +
                "Ijoi5byg5LiJIn0sImV4cCI6MT" +
                "cyOTMzOTM2NX0.tP5n6jcZkDxW" +
                "9OnTHEzczc4Ce3pQfqqewguchY" +
                "yj7nc";

        JWTVerifier jwtVerifier=JWT.require(Algorithm.HMAC256("yellow")).build();
        //验证token，生成一个解析后的JWT对象
        DecodedJWT decodedJWT=jwtVerifier.verify(token);
        Map<String, Claim> claims=decodedJWT.getClaims();
        System.out.println(claims.get("user"));

    }
}
