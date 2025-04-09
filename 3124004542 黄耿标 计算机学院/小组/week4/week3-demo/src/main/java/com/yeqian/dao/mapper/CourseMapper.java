package com.yeqian.dao.mapper;

import com.yeqian.entity.Course;
import com.yeqian.entity.StudentAndCourse;
import com.yeqian.util.mybatis.annotations.*;

import java.util.List;

public interface CourseMapper {

    /**
     * 查询所有课程
     * @return
     */
    @Select("select * from course")
    List<Course> selectAllCourse();

    /**
     * 根据名称查询课程
     * @param courseName
     * @return
     */
    @Select("select * from course where course_name like #{courseName}")
    List<Course> selectCourseByCourseName(@Param("courseName") String courseName);

    /**
     * 添加课程数据
     * @param course
     */
    @Insert("insert into course values(null, #{courseName}, #{score}, #{status})")
    void addCourse(Course course);

    /**
     * 修改课程数据
     * @param course
     */
    @Update("update course set course_name = #{courseName}, score = #{score}, status = #{status} where id = #{id}")
    void updateCourse(Course course);

    /**
     * 删除课程
     * @param id
     */
    @Delete("delete from course where id = #{id}")
    void deleteCourseById(@Param("id") int id);

    /**
     * 查询学生所选课程
     * @param id
     * @return
     */
    @Select("select s.student_name, c.course_name from student s " +
            "join student_course sc on s.id = sc.student_id " +
            "join course c on c.id = sc.course_id " +
            "where s.id = #{id};")
    List<StudentAndCourse> selectStudentAndCourseById(@Param("id") int id);
}
