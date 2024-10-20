package com.yellow.springboothly.pojo;

import Time.LocalDateTime;
import com.yellow.springboothly.anno.State;
import jakarta.validation.constraints.NotEmpty;
import jakarta.validation.constraints.Pattern;
import lombok.Data;
import org.hibernate.validator.constraints.URL;

@Data
public class Article {
    private Integer id;
    @NotEmpty
    @Pattern(regexp = "^\\${1,10}$")
    private String title;
    @NotEmpty
    private String content;//文章内容
    @NotEmpty
    @URL
    private String coverImg;//封面图像
    @State
    private String state;//发布状态，已发布||草稿
    @NotEmpty
    private Integer categoryId;//文章分类id
    private Integer createUser;//创建人id
    private LocalDateTime createTime;
    private LocalDateTime updateTime;
}
