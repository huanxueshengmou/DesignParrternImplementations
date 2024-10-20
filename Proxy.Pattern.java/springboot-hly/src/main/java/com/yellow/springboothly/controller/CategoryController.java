package com.yellow.springboothly.controller;

import com.yellow.springboothly.pojo.Result;
import com.yellow.springboothly.service.CategoryService;
import com.yellow.springboothly.pojo.Category;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@RequestMapping("/category")
public class CategoryController {
    @Autowired
    private CategoryService categoryService;
    //增加文章
    @PostMapping
    public Result add(@RequestBody @Validated(Category.Add.class) Category category){
        categoryService.add(category);
        return Result.success();
    }

    //文章分类
    public Result<List<Category>> list(){
        List<Category> cs=categoryService.list();
        return Result.success(cs);
    }

    //获取文章分类信息
    @GetMapping("/detail")
    public Result<Category> detail(Integer id){
        Category c=categoryService.findById(id);
        return Result.success(c);
    }

    //修改文章分类,参数校验...(Category.Add.class)指定校验分组
    @PutMapping
    public Result update(@RequestBody @Validated(Category.Update.class) Category category){
        categoryService.update(category);
        return Result.success();
    }
}
