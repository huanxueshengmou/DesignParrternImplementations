package com.yellow.springboothly.service.impl;

import Time.LocalDateTime;
import com.yellow.springboothly.Utils.ThreadLocalUtil;
import com.yellow.springboothly.mapper.ArticleMapper;
import com.yellow.springboothly.pojo.Article;
import com.yellow.springboothly.service.ArticleService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.Map;

@Service
public class ArticleServiceImpl implements ArticleService {
    @Autowired
    private ArticleMapper articleMapper;
//添加文章
    @Override
    public void add(Article article) {
        //补充属性值id
        article.setCreateTime(LocalDateTime.now());
        article.setUpdateTime(LocalDateTime.now());
        Map<String,Object> map= ThreadLocalUtil.get();
        Integer userId=(Integer) map.get("id");
        article.setCreateUser(userId);
        articleMapper.add(article);
    }

    @Override
    public <RageBean> RageBean list(Integer pageNum, Integer pageSize, Integer category, String state) {
        return null;
    }

    @Override
    public RageBean<Article> list(Integer pageNum, Integer pageSize, Integer category, String state) {
        return null;
    }
}
