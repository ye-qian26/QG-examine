package com.yeqian.web.servlet;

import com.alibaba.fastjson.JSON;
import com.yeqian.entity.Course;
import com.yeqian.entity.StudentAndCourse;
import com.yeqian.service.course.CourseService;
import com.yeqian.service.course.CourseServiceImpl;

import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.util.List;

@WebServlet("/course/*")
public class CourseServlet extends BaseServlet {
    CourseService courseService = new CourseServiceImpl();

    public void selectAllCourse(HttpServletRequest req, HttpServletResponse resp) throws IOException {
        //1.执行方法
        List<Course> courses = courseService.selectAllCourse();
        //2.转为json数据
        String jsonString = JSON.toJSONString(courses);
        //3.写数据
        resp.setContentType("text/json;charset=utf-8");
        resp.getWriter().write(jsonString);
    }

    public void selectCourseByCourseName(HttpServletRequest req, HttpServletResponse resp) throws IOException {
        //1.接收数据
        String courseName = req.getParameter("courseName");
        //2.解决乱码问题
        courseName = new String(courseName.getBytes(StandardCharsets.ISO_8859_1), StandardCharsets.UTF_8);
        //3.改造courseName:模糊表达式
        courseName = "%" + courseName + "%";
        //3.执行方法
        List<Course> courses = courseService.selectCourseByCourseName(courseName);
        //4.转为json数据
        String jsonString = JSON.toJSONString(courses);
        //3.写数据
        resp.setContentType("text/json;charset=utf-8");
        resp.getWriter().write(jsonString);
    }

    public void addCourse(HttpServletRequest req, HttpServletResponse resp) throws IOException {
        //1.解决乱码问题
        req.setCharacterEncoding("utf-8");
        //2.接收数据
        String jsonString = req.getReader().readLine();
        //3.转为Course类
        Course course = JSON.parseObject(jsonString, Course.class);
        //4.执行service方法
        courseService.addCourse(course);
        //5.响应数据
        resp.getWriter().write("success");
    }

    public void updateCourse(HttpServletRequest req, HttpServletResponse resp) throws IOException {
        //1.解决乱码问题
        req.setCharacterEncoding("utf-8");
        //2.接收数据
        String jsonString = req.getReader().readLine();
        //3.转为Course类
        Course course = JSON.parseObject(jsonString, Course.class);
        //4.执行service方法
        courseService.updateCourse(course);
        //5.响应数据
        resp.getWriter().write("success");
    }


    public void deleteCourseById(HttpServletRequest req, HttpServletResponse resp) throws IOException {
        //1.解决乱码问题
        req.setCharacterEncoding("utf-8");
        //2.接收数据
        String jsonString = req.getReader().readLine();
        //3.转为Course类
        int id = JSON.parseObject(jsonString, Integer.class);
        //4.执行service方法
        courseService.deleteCourseById(id);
        //5.响应数据
        resp.getWriter().write("success");
    }

    public void selectStudentAndCourseById(HttpServletRequest req, HttpServletResponse resp) throws IOException {
        //1.解决乱码问题
        req.setCharacterEncoding("utf-8");
        //2.接收数据
        String jsonString = req.getReader().readLine();
        //3.转为Course类
        int id = JSON.parseObject(jsonString, Integer.class);
        //4.执行service方法
        List<StudentAndCourse> studentAndCourses = courseService.selectStudentAndCourseById(id);
        if (studentAndCourses != null && !studentAndCourses.isEmpty()) {
            resp.setContentType("text/json;charset=utf-8");
            resp.getWriter().write(JSON.toJSONString(studentAndCourses));
        } else {
            resp.getWriter().write("fail");
        }
    }
}
