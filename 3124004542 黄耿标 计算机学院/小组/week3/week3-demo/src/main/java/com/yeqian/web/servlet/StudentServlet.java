package com.yeqian.web.servlet;

import com.alibaba.fastjson.JSON;
import com.yeqian.entity.Student;
import com.yeqian.entity.StudentAndCourse;
import com.yeqian.service.student.StudentService;
import com.yeqian.service.student.StudentServiceImpl;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.BufferedReader;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.util.List;

@WebServlet("/student/*")
public class StudentServlet extends BaseServlet{
    StudentService studentService = new StudentServiceImpl();

    /**
     * 学生注册
     * @param req
     * @param resp
     * @throws ServletException
     * @throws IOException
     */
    public void registerStudent(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        //1.处理乱码问题
        req.setCharacterEncoding("utf-8");
        //2.接收数据
        BufferedReader br = req.getReader();
        String jsonString = br.readLine();
        //3.转为Student类
        Student student = JSON.parseObject(jsonString, Student.class);
        //4.执行service方法
        studentService.addStudent(student);
        //5.响应数据
        resp.getWriter().write("success");
    }

    /**
     * 学生登录
     * @param req
     * @param resp
     * @throws ServletException
     * @throws IOException
     */
    public void loginStudent(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        //1.处理乱码问题
        req.setCharacterEncoding("utf-8");
        //2.获取get请求数据
        String studentName = req.getParameter("studentName");
        studentName = new String(studentName.getBytes(StandardCharsets.ISO_8859_1), StandardCharsets.UTF_8);
        String password = req.getParameter("password");
        //3.执行service方法
        Student student = studentService.selectStudent(studentName, password);
        if (student != null) {
            //4.响应数据
            String jsonString = JSON.toJSONString(student);
            resp.setContentType("text/json;charset=utf-8");
            resp.getWriter().write(jsonString);
        } else {
            //4.响应数据
            resp.getWriter().write("fail");
        }
    }

    /**
     * 修改学生数据
     * @param req
     * @param resp
     * @throws ServletException
     * @throws IOException
     */
    public void updateStudent(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        //1.处理乱码问题
        req.setCharacterEncoding("utf-8");
        //2.获取get请求数据
        BufferedReader br = req.getReader();
        String jsonString = br.readLine();
        //3.转为Student类
        Student student = JSON.parseObject(jsonString, Student.class);
        //4。执行service方法
        studentService.updateStudent(student);
        //5.响应数据
        resp.getWriter().write("success");
    }

    /**
     * 通过id查询学生
     * @param req
     * @param resp
     * @throws ServletException
     * @throws IOException
     */
    public void selectStudentById(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        //1.处理乱码问题
        req.setCharacterEncoding("utf-8");
        //2.获取数据
        String jsonString = req.getReader().readLine();
        //3.转换为Integer类
        Integer id = JSON.parseObject(jsonString, Integer.class);
        //4.执行方法
        Student student = studentService.selectStudentById(id);
        //5.响应数据
        resp.setContentType("text/json;charset=utf-8");
        resp.getWriter().write(JSON.toJSONString(student));
    }

    /**
     * 查询所有学生
     * @param req
     * @param resp
     * @throws ServletException
     * @throws IOException
     */
    public void selectAllStudent(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        //1.执行方法
        List<Student> students = studentService.selectAllStudent();
        //2.响应数据
        resp.setContentType("text/json;charset=utf-8");
        resp.getWriter().write(JSON.toJSONString(students));
    }

    /**
     * 查询指定课程下的学生
     * @param req
     * @param resp
     * @throws IOException
     */
    public void selectStudentAndCourseById(HttpServletRequest req, HttpServletResponse resp) throws IOException {
        //1.解决乱码问题
        req.setCharacterEncoding("utf-8");
        //2.接收数据
        String jsonString = req.getReader().readLine();
        //3.转为Course类
        int id = JSON.parseObject(jsonString, Integer.class);
        //4.执行service方法
        List<StudentAndCourse> studentAndCourses = studentService.selectStudentAndCourseById(id);
        if (studentAndCourses != null && !studentAndCourses.isEmpty()) {
            resp.setContentType("text/json;charset=utf-8");
            resp.getWriter().write(JSON.toJSONString(studentAndCourses));
        } else {
            resp.getWriter().write("fail");
        }
    }

    /**
     * 通过学生姓名查询学生
     * @param req
     * @param resp
     * @throws ServletException
     * @throws IOException
     */
    public void selectStudentByName(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        //1.解决乱码问题
        req.setCharacterEncoding("utf-8");
        //2.接收数据
        String studentName = req.getReader().readLine();
        //3.执行service方法
        Student student = studentService.selectStudentByName(studentName);
        //4.响应数据
        resp.setContentType("text/json;charset=utf-8");
        resp.getWriter().write(JSON.toJSONString(student));
    }
}
