package com.yeqian.service.course;


import com.yeqian.entity.Course;
import com.yeqian.entity.StudentAndCourse;
import com.yeqian.dao.mapper.CourseMapper;
import com.yeqian.util.mybatis.proxy.MapperProxyFactory;

import java.util.List;

public class CourseServiceImpl implements CourseService {
    CourseMapper courseMapper = MapperProxyFactory.getProxy(CourseMapper.class);
    @Override
    public List<Course> selectAllCourse() {
        //2.执行方法
        return courseMapper.selectAllCourse();
    }

    @Override
    public List<Course> selectCourseByCourseName(String courseName) {
        //2.执行方法
        return courseMapper.selectCourseByCourseName(courseName);
    }

    @Override
    public void addCourse(Course course) {
        //2.执行方法
        courseMapper.addCourse(course);
    }

    @Override
    public void updateCourse(Course course) {
        //2.执行方法
        courseMapper.updateCourse(course);
    }

    @Override
    public void deleteCourseById(int id) {
        //2.执行方法
        courseMapper.deleteCourseById(id);
    }

    @Override
    public List<StudentAndCourse> selectStudentAndCourseById(int id) {
        //2.执行方法
        return courseMapper.selectStudentAndCourseById(id);
    }
}
