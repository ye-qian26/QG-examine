package com.yeqian.service.student;

import com.yeqian.entity.Student;
import com.yeqian.entity.StudentAndCourse;
import com.yeqian.util.mybatis.annotations.Param;
import com.yeqian.util.mybatis.annotations.Select;

import java.util.List;

public interface StudentService {

    /**
     * 学生注册
     * @param student
     */
    void addStudent(Student student);

    /**
     * 根据姓名和密码查询学生
     * @param studentName
     * @param password
     * @return
     */
    Student selectStudent(String studentName, String password);

    /**
     * 根据姓名查询学生
     * @param studentName
     * @return
     */
    Student selectStudentByName(String studentName);

    /**
     * 修改学生数据
     * @param student
     */
    void updateStudent(Student student);

    /**
     * 根据学生id查询学生数据
     * @param id
     * @return
     */
    Student selectStudentById(Integer id);

    /**
     * 查询所有学生
     * @return
     */
    List<Student> selectAllStudent();

    /**
     * 查询指定课程下的学生
     * @param id
     * @return
     */
    List<StudentAndCourse> selectStudentAndCourseById(int id);

    /**
     * 根据姓名查询学生（除了传入的id对应的student）
     * @param studentName
     * @param id
     * @return
     */
    Student selectStudentByNameExceptId(String studentName, int id);
}
