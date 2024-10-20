package com.yellow.springboothly.service;

import com.yellow.springboothly.pojo.Category;
import com.yellow.springboothly.pojo.Result;

import java.util.List;

public interface CategoryService {
    //新增文章分类
    void add(Category category);
    //列表查询
    //获取当前用户id
    List<Category> list();

    //根据id查询列表分类信息
    Category findById(Integer id);

    //更新文章分类
    void update(Category category);
}
