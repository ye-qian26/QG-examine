package com.yeqian.dao.mapper;

import com.yeqian.entity.StudentCourse;
import com.yeqian.util.mybatis.annotations.Delete;
import com.yeqian.util.mybatis.annotations.Insert;
import com.yeqian.util.mybatis.annotations.Param;
import com.yeqian.util.mybatis.annotations.Select;

import java.util.List;

public interface StudentCourseMapper {

    /**
     * 学生选择课程
     * @param studentCourse
     */
    @Insert("insert into student_course values(null, #{studentId}, #{courseId})")
    void addStudentCourse(StudentCourse studentCourse);

    /**
     * 学生退选课程
     * @param studentCourse
     */
    @Delete("delete from student_course where student_id = #{studentId} and course_id = #{courseId}")
    void deleteStudentCourse(StudentCourse studentCourse);

    /**
     * 根据学生id查询已选课程
     * @param studentId
     * @return
     */
    @Select("select * from student_course where student_id = #{studentId}")
    List<StudentCourse> selectStudentCourseByStudentId(@Param("studentId") Integer studentId);

    /**
     * 根据课程i查询对应学生
     * @param courseId
     * @return
     */
    @Select("select * from student_course where course_id = #{courseId}")
    List<StudentCourse> selectStudentByCourseId(@Param("courseId") Integer courseId);
}
