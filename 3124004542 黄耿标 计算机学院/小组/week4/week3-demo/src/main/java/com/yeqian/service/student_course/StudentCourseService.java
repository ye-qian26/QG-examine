package com.yeqian.service.student_course;

import com.yeqian.entity.StudentCourse;

import java.util.List;

public interface StudentCourseService {

    /**
     * 学生选择课程
     */
    void addStudentCourse(StudentCourse studentCourse);

    /**
     * 学生退选课程
     */
    void deleteStudentCourse(StudentCourse studentCourse);

    /**
     * 根据学生id查询已选课程
     * @return
     */
    List<StudentCourse> selectStudentCourseByStudentId(Integer studentId);

    /**
     * 根据课程i查询对应学生
     * @return
     */
    List<StudentCourse> selectStudentByCourseId(Integer courseId);
}
