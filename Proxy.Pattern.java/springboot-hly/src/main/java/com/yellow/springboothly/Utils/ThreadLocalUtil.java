package com.yellow.springboothly.Utils;
//工具类Threadlocal
public class ThreadLocalUtil {
    //提供Threadlocal对象
    private static final ThreadLocal THREAD_LOCAL=new ThreadLocal();
    //根据键获取值
    public static <T> T get(){
        return (T) THREAD_LOCAL.get();
    }
    //存储键信息
    public static void set(Object value){
        THREAD_LOCAL.set(value);
    }
    //清除Threadlocal防止内存泄露
    public static void remove(){
        THREAD_LOCAL.remove();
    }
}
