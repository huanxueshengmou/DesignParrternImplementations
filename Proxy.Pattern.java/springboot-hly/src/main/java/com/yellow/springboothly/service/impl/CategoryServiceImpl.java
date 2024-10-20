package com.yellow.springboothly.service.impl;

import Time.LocalDateTime;
import com.yellow.springboothly.Utils.ThreadLocalUtil;
import com.yellow.springboothly.mapper.CategoryMapper;
import com.yellow.springboothly.pojo.Category;
import com.yellow.springboothly.service.CategoryService;
import org.apache.ibatis.annotations.Select;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;
import java.util.Map;

@Service//将类交给容器
public class CategoryServiceImpl implements CategoryService {
    @Autowired
    private CategoryMapper categoryMapper;
    @Override
    public void add(Category category) {
        //补充属性值
        category.setCreateTime(LocalDateTime.now());
        category.setUpdateTime(LocalDateTime.now());
        Map<String,Object> map= ThreadLocalUtil.get();
        Integer userId=(Integer) map.get("id");
        category.setCreateUser(userId);
        categoryMapper.add(category);
    }
//文章分类查询
    @Override
    public List<Category> list() {
        //获取id
        Map<String,Object> map=ThreadLocalUtil.get();
        Integer userId=(Integer) map.get("id");
        return categoryMapper.list(userId);
    }
//根据id查询列表分类信息
    @Override
    public Category findById(Integer id) {
        Category c=categoryMapper.findById(id);
        return c;
    }

    //更新文章分类
    @Override
    public void update(Category category) {
        category.setUpdateTime(LocalDateTime.now());
        categoryMapper.update(category);
    }

}
