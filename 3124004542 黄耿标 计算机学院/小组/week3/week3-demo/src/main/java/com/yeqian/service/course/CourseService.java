package com.yeqian.service.course;

import com.yeqian.entity.Course;
import com.yeqian.entity.StudentAndCourse;

import java.util.List;

public interface CourseService {

    /**
     * 查询所有课程
     * @return
     */
    List<Course> selectAllCourse();

    /**
     * 根据名称查询课程
     * @param courseName
     * @return
     */
    List<Course> selectCourseByCourseName(String courseName);

    /**
     * 添加课程数据
     * @param course
     */
    void addCourse(Course course);

    /**
     * 修改课程数据
     * @param course
     */
    void updateCourse(Course course);

    /**
     * 删除课程
     * @param id
     */
    void deleteCourseById(int id);

    /**
     * 查询学生所选课程
     * @param id
     * @return
     */
    List<StudentAndCourse> selectStudentAndCourseById(int id);
}
