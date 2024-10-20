package com.yellow.springboothly.mapper;

import com.yellow.springboothly.pojo.Category;
import org.apache.ibatis.annotations.Insert;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Select;
import org.apache.ibatis.annotations.Update;

import java.util.List;

@Mapper
public interface CategoryMapper {
    //新增文章分类
    @Insert("insert into category(category_name,category_alias,create_time,update_time)" +
            "values(#{categoryName},#{categoryAlias},now(),now())")
    void add(Category category);

//根据用户id获取所有
    @Select("select * from category where create_user=#{userId}")
    List<Category> list(Integer userId);

    //根据id查询列表分类信息
    @Select("select * from category where id=#{id}")
    Category findById(Integer id);


    //删除文章分类


    //更新文章分类
    //where id 表示根据id
    @Update("update category set category_name=#{categoryName},category_alias=#{categoryAlias},update_time=now() where id=#{id}")
    void update(Category category);






}
