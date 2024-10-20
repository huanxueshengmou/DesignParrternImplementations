package com.yellow.springboothly.anno;
import static java.lang.annotation.ElementType.*;
import static java.lang.annotation.RetentionPolicy.RUNTIME;


import com.yellow.springboothly.Validation.StateValidation;
import jakarta.validation.Constraint;
import jakarta.validation.Payload;
import jakarta.validation.constraints.NotEmpty;

import java.lang.annotation.Documented;
import java.lang.annotation.Repeatable;
import java.lang.annotation.Retention;
import java.lang.annotation.Target;
//自定义校验注解
@Documented
@Constraint(validatedBy ={StateValidation.class })//指定校验规则的类
@Target({FIELD})
@Retention(RUNTIME)

public @interface State{
  //提供校验失败后的信息
  String message() default "{jakarta.validation.constraints.NotEmpty.message}";
  //指定分组
  Class<?>[] groups() default {};
  //负载 获取到state注解的附加信息
  Class<? extends Payload>[] payload() default {};


}
