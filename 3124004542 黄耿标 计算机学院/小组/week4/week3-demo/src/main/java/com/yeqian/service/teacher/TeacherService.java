package com.yeqian.service.teacher;

import com.yeqian.entity.Teacher;
import com.yeqian.util.mybatis.annotations.Param;
import com.yeqian.util.mybatis.annotations.Select;

public interface TeacherService {
    /**
     * 老师注册
     * @param teacher
     */
    void addTeacher(Teacher teacher);

    /**
     * 根据姓名和密码查询老师
     * @param username
     * @param password
     * @return
     */
    Teacher selectTeacher(String username, String password);

    /**
     * 根据姓名查询老师
     * @param username
     * @return
     */
    Teacher selectTeacherByName(String username);

    /**
     * 根据姓名查询老师（除了传进来的id对应的Teacher）
     * @param username
     * @param id
     * @return
     */
    Teacher selectTeacherByNameExceptId(String username, Integer id);


    /**
     * 通过id查询老师
     * @param teacherId
     * @return
     */
    Teacher selectTeacherById(Integer teacherId);


    /**
     * 修改老师个人信息
     * @param teacher
     */
    void updateTeacher(Teacher teacher);
}
