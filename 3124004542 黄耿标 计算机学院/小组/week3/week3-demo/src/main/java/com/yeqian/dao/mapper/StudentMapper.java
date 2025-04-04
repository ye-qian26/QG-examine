package com.yeqian.dao.mapper;

import com.yeqian.entity.Student;
import com.yeqian.entity.StudentAndCourse;
import com.yeqian.util.mybatis.annotations.Insert;
import com.yeqian.util.mybatis.annotations.Param;
import com.yeqian.util.mybatis.annotations.Select;
import com.yeqian.util.mybatis.annotations.Update;

import java.util.List;

public interface StudentMapper {

    /**
     * 添加学生
     * @param student
     */
    @Insert("insert into student values (null, #{StudentName}, #{password}, #{tele})")
    void addStudent(Student student);


    /**
     * 根据姓名和密码查询学生
     * @param studentName
     * @param password
     * @return
     */
    @Select("select * from student where student_name = #{studentName} and password = #{password}")
    Student selectStudent(@Param("studentName") String studentName,@Param("password") String password);

    /**
     * 根据姓名查询学生
     * @param studentName
     * @return
     */
    @Select("select * from student where student_name = #{studentName}")
    Student selectStudentByName(@Param("studentName") String studentName);

    /**
     * 修改学生数据
     * @param student
     */
    @Update("update student set student_name = #{studentName}, password = #{password}, tele = #{tele} where id = #{id}")
    void updateStudent(Student student);

    /**
     * 根据学生id查询学生数据
     * @param id
     * @return
     */
    @Select("select * from student where id = #{id}")
    Student selectStudentById(@Param("id") Integer id);

    /**
     * 查询所有学生
     * @return
     */
    @Select("select * from student")
    List<Student> selectAllStudent();

    /**
     * 查询指定课程下的学生
     * @param id
     * @return
     */
    @Select("select c.course_name, s.student_name from course c " +
            "join student_course sc on c.id = sc.course_id " +
            "join student s on s.id = sc.student_id " +
            "where c.id = #{id};")
    List<StudentAndCourse> selectStudentAndCourseById(@Param("id") int id);

}
