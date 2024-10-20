package com.yellow.springboothly.pojo;

import Time.LocalDateTime;
import com.fasterxml.jackson.annotation.JsonFormat;
import jakarta.validation.constraints.NotEmpty;
import jakarta.validation.constraints.NotNull;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

@AllArgsConstructor//全参构造
@NoArgsConstructor//无参构造
@Data
public class Category {
@NotNull(groups =Update.class)//指定分组校验组
    private Integer id;
    @NotEmpty(groups = {Add.class,Update.class})
    private String categoryName;//分类名称
    @NotEmpty(groups = {Add.class,Update.class})
    private String categoryAlias;//分类别名
    private Integer createUser;//创建人id
    @JsonFormat(pattern ="yyyy-MM-dd HH:mm:ss")//指定日期格式
    private LocalDateTime CreateTime;
    @JsonFormat(pattern ="yyyy-MM-dd HH:mm:ss")
    private LocalDateTime UpdateTime;

    //分组校验
    //添加
    public interface Add/* extends Update此次为默认分组时才需要继承*/{

    }
    //更新
    public interface Update{

    }
}
