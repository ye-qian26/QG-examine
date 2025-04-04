package com.yeqian.service.student;

import com.yeqian.entity.Student;
import com.yeqian.entity.StudentAndCourse;
import com.yeqian.dao.mapper.StudentMapper;
import com.yeqian.util.mybatis.proxy.MapperProxyFactory;

import java.util.List;

public class StudentServiceImpl implements StudentService {
    StudentMapper studentMapper = MapperProxyFactory.getProxy(StudentMapper.class);

    @Override
    public void addStudent(Student student) {
        //1.获取mapper
        //2.执行方法
        studentMapper.addStudent(student);
    }

    @Override
    public Student selectStudent(String studentName, String password) {
        //2.执行方法
        return studentMapper.selectStudent(studentName, password);
    }

    @Override
    public Student selectStudentByName(String studentName) {
        //2.执行方法
        return studentMapper.selectStudentByName(studentName);
    }

    @Override
    public void updateStudent(Student student) {
        //2.执行方法
        studentMapper.updateStudent(student);
    }

    @Override
    public Student selectStudentById(Integer id) {
        //2.执行方法
        return studentMapper.selectStudentById(id);
    }

    @Override
    public List<Student> selectAllStudent() {
        //2.执行方法
        return studentMapper.selectAllStudent();
    }

    @Override
    public List<StudentAndCourse> selectStudentAndCourseById(int id) {
        //2.执行方法
        return studentMapper.selectStudentAndCourseById(id);
    }
}
