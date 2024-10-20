package com.yellow.springboothly.service;

import com.yellow.springboothly.pojo.Article;

public interface ArticleService {
   //新增文章
    void add(Article article);

    RageBean<Article> list(Integer pageNum, Integer pageSize, Integer category, String state);


    //获取文章详情

    //更新文章

    //删除文章
}
