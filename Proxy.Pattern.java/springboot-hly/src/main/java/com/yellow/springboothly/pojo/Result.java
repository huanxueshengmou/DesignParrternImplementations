package com.yellow.springboothly.pojo;

import lombok.AllArgsConstructor;
import lombok.NoArgsConstructor;
@AllArgsConstructor//全参构造
@NoArgsConstructor//无参构造
public class Result <T>{
    private Integer code;//业务状态
    private String message;//提升信息
    private T data;//响应数据
    public static <E> Result<E> success(E data){
        return new Result<>(0,"操作成功",null);
    }
    public static Result success(){
        return new Result(0,"操作成功",null);
    }
    public static Result error(String message){
        return new Result(1,message,null);
    }
}
