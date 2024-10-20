package com.yellow.springboothly.mapper;

import com.yellow.springboothly.pojo.Article;
import org.apache.ibatis.annotations.Insert;
import org.apache.ibatis.annotations.Mapper;

@Mapper
public interface ArticleMapper {
   //新增文章
    @Insert("INSERT into article(title,content,cover_img,state_id,create_user,create_time,update_time)" +
            "velues(#{title},#{content},#{coverImg},#{createUser},now(),now()")
    void add(Article article);
}
