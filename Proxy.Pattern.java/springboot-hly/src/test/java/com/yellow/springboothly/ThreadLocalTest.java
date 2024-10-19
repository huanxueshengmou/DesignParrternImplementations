package com.yellow.springboothly;

//注意注解@Test导包，导错包会导致线程没有输出成功
import org.junit.jupiter.api.Test;

public class ThreadLocalTest {
    @Test
    public void testThreadLocalSetAndGet(){
        //提供一个ThreadLocal对象
        ThreadLocal tl=new ThreadLocal();

        //开启两个线程
        new Thread(()->{
            tl.set("许立国");
            System.out.println(Thread.currentThread().getName()+":"+tl.get());
            System.out.println(Thread.currentThread().getName()+":"+tl.get());
            System.out.println(Thread.currentThread().getName()+":"+tl.get());
        },"忠心耿耿").start();

        new Thread(()->{
            tl.set("王麻子");
            System.out.println(Thread.currentThread().getName()+":"+tl.get());
            System.out.println(Thread.currentThread().getName()+":"+tl.get());
            System.out.println(Thread.currentThread().getName()+":"+tl.get());
        },"心慈手软").start();
    }
}
