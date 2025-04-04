package com.yeqian.web.servlet;

import com.alibaba.fastjson.JSON;
import com.yeqian.entity.StudentCourse;
import com.yeqian.service.student_course.StudentCourseService;
import com.yeqian.service.student_course.StudentCourseServiceImpl;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.List;

@WebServlet("/studentCourse/*")
public class StudentCourseServlet extends BaseServlet {
    StudentCourseService studentCourseService = new StudentCourseServiceImpl();

    /**
     * 学生选择课程
     * @param req
     * @param resp
     * @throws ServletException
     * @throws IOException
     */
    public void chooseCourse(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        //1.解决乱码问题
        req.setCharacterEncoding("utf-8");
        //2.获取数据
        String jsonString = req.getReader().readLine();
        //3.转为StudentCourse类
        StudentCourse studentCourse = JSON.parseObject(jsonString, StudentCourse.class);
        //4.执行方法
        studentCourseService.addStudentCourse(studentCourse);
        //5.响应数据
        resp.getWriter().write("success");
    }

    /**
     * 学生退选课程
     * @param req
     * @param resp
     * @throws ServletException
     * @throws IOException
     */
    public void dropCourse(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        //1.解决乱码问题
        req.setCharacterEncoding("utf-8");
        //2.获取数据
        String jsonString = req.getReader().readLine();
        //3.转为StudentCourse类
        StudentCourse studentCourse = JSON.parseObject(jsonString, StudentCourse.class);
        //4.执行方法
        studentCourseService.deleteStudentCourse(studentCourse);
        //5.响应数据
        resp.getWriter().write("success");
    }

    public void selectStudentCourseByStudentId(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        //1.解决乱码问题
        req.setCharacterEncoding("utf-8");
        //2.获取数据
        String jsonString = req.getReader().readLine();
        //3.转为StudentCourse类
        int studentId = JSON.parseObject(jsonString, Integer.class);
        //4.执行方法
        List<StudentCourse> studentCourses = studentCourseService.selectStudentCourseByStudentId(studentId);
        //5.得到所选课程id数组
        if (studentCourses != null && !studentCourses.isEmpty()) {
            int[] ids = new int[studentCourses.size()];
            for (int i = 0; i < studentCourses.size(); i++) {
                ids[i] = studentCourses.get(i).getCourseId();
            }
            //6.转为json数据
            String jsonString1 = JSON.toJSONString(ids);
            //7.响应数据
            resp.setContentType("text/json;charset=utf-8");
            resp.getWriter().write(jsonString1);
        } else {
            resp.getWriter().write("fail");
        }
    }

    public void selectStudentByCourseId(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        //1.解决乱码问题
        req.setCharacterEncoding("utf-8");
        //2.获取数据
        String jsonString = req.getReader().readLine();
        //3.转为StudentCourse类
        int courseId = JSON.parseObject(jsonString, Integer.class);
        //4.执行方法
        List<StudentCourse> studentCourses = studentCourseService.selectStudentByCourseId(courseId);
        //5.得到所选课程id数组
        if (studentCourses != null && !studentCourses.isEmpty()) {
            int[] ids = new int[studentCourses.size()];
            for (int i = 0; i < studentCourses.size(); i++) {
                ids[i] = studentCourses.get(i).getStudentId();
            }
            //6.转为json数据
            String jsonString1 = JSON.toJSONString(ids);
            //7.响应数据
            resp.setContentType("text/json;charset=utf-8");
            resp.getWriter().write(jsonString1);
        } else {
            resp.getWriter().write("fail");
        }
    }
}
