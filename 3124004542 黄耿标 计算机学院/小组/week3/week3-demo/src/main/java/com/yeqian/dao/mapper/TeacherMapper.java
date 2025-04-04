package com.yeqian.dao.mapper;

import com.yeqian.entity.Teacher;
import com.yeqian.util.mybatis.annotations.Insert;
import com.yeqian.util.mybatis.annotations.Param;
import com.yeqian.util.mybatis.annotations.Select;
import com.yeqian.util.mybatis.annotations.Update;

public interface TeacherMapper {

    /**
     * 老师注册
     * @param teacher
     */
    @Insert("insert teacher values(null, #{username}, #{password})")
    void addTeacher(Teacher teacher);

    /**
     * 根据姓名和密码查询老师
     * @param username
     * @param password
     * @return
     */
    @Select("select * from teacher where username = #{username} and password = #{password}")
    Teacher selectTeacher(@Param("username") String username, @Param("password") String password);

    /**
     * 根据姓名查询老师
     * @param username
     * @return
     */
    @Select("select * from teacher where username = #{username}")
    Teacher selectTeacherByName(@Param("username") String username);


    /**
     * 通过id查询老师
     * @param teacherId
     * @return
     */
    @Select("select * from teacher where id = #{teacherId}")
    Teacher selectTeacherById(@Param("teacherId") Integer teacherId);

    /**
     * 修改老师个人信息
     * @param teacher
     */
    @Update("update teacher set username = #{username}, password = #{password} where id = #{id}")
    void updateTeacher(Teacher teacher);
}
