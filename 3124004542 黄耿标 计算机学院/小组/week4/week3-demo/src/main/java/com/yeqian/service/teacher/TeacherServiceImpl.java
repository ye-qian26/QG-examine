package com.yeqian.service.teacher;

import com.yeqian.entity.Teacher;
import com.yeqian.dao.mapper.TeacherMapper;
import com.yeqian.util.mybatis.proxy.MapperProxyFactory;

public class TeacherServiceImpl implements TeacherService {
    TeacherMapper teacherMapper = MapperProxyFactory.getProxy(TeacherMapper.class);

    @Override
    public void addTeacher(Teacher teacher) {
        //2.执行方法
        teacherMapper.addTeacher(teacher);
    }

    @Override
    public Teacher selectTeacher(String username, String password) {
        //2.执行方法
        return teacherMapper.selectTeacher(username, password);
    }

    @Override
    public Teacher selectTeacherByName(String username) {
        //2.执行方法
        return teacherMapper.selectTeacherByName(username);
    }

    @Override
    public Teacher selectTeacherByNameExceptId(String username, Integer id) {
        //2.执行方法
        return teacherMapper.selectTeacherByNameExceptId(username, id);
    }

    @Override
    public Teacher selectTeacherById(Integer teacherId) {
        //2.执行方法
        return teacherMapper.selectTeacherById(teacherId);
    }

    @Override
    public void updateTeacher(Teacher teacher) {
        //2.执行方法
        teacherMapper.updateTeacher(teacher);
    }
}
