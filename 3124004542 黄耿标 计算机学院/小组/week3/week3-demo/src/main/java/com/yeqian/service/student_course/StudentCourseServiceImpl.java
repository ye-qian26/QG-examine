package com.yeqian.service.student_course;

import com.yeqian.entity.StudentCourse;
import com.yeqian.dao.mapper.StudentCourseMapper;
import com.yeqian.util.mybatis.proxy.MapperProxyFactory;

import java.util.List;

public class StudentCourseServiceImpl implements StudentCourseService {
    StudentCourseMapper mapper = MapperProxyFactory.getProxy(StudentCourseMapper.class);

    @Override
    public void addStudentCourse(StudentCourse studentCourse) {
        //2.执行方法
        mapper.addStudentCourse(studentCourse);
    }

    @Override
    public void deleteStudentCourse(StudentCourse studentCourse) {
        //2.执行方法
        mapper.deleteStudentCourse(studentCourse);
    }

    @Override
    public List<StudentCourse> selectStudentCourseByStudentId(Integer studentId) {
        //2.执行方法
        List<StudentCourse> studentCourses = mapper.selectStudentCourseByStudentId(studentId);
        return studentCourses;
    }

    @Override
    public List<StudentCourse> selectStudentByCourseId(Integer courseId) {
        List<StudentCourse> studentCourses = mapper.selectStudentByCourseId(courseId);
        return studentCourses;
    }
}
