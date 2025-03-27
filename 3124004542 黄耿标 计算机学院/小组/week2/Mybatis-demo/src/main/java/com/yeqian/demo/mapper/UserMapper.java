package com.yeqian.demo.mapper;

import com.yeqian.demo.entity.User;
import com.yeqian.mybatis.annotations.*;

import java.util.List;

public interface UserMapper {

    @Select("select * from tb_user")
    List<User> selectAll();

    @Select("select * from tb_user where id = #{id}")
    User selectById(@Param("id")int id);

    @Update("update tb_user set name = #{name} where id = #{id}")
    void updateById(@Param("id") int id, @Param("name") String name);

    @Delete("delete from tb_user where id = #{id}")
    void deleteById(@Param("id") int id);

    @Insert("insert into tb_user values (null, #{name}, #{age})")
    void add(User user);

}
