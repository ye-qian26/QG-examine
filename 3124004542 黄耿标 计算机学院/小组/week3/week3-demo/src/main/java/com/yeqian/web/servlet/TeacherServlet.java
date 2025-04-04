package com.yeqian.web.servlet;

import com.alibaba.fastjson.JSON;
import com.yeqian.entity.Student;
import com.yeqian.entity.Teacher;
import com.yeqian.service.teacher.TeacherService;
import com.yeqian.service.teacher.TeacherServiceImpl;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.BufferedReader;
import java.io.IOException;
import java.nio.charset.StandardCharsets;

@WebServlet("/teacher/*")
public class TeacherServlet extends BaseServlet {
    TeacherService teacherService = new TeacherServiceImpl();

    public void registerTeacher(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        //1.接收ajax数据
        BufferedReader br = req.getReader();
        String jsonString = br.readLine();
        //2.转为Teacher类
        Teacher teacher = JSON.parseObject(jsonString, Teacher.class);
        //3.执行service方法
        teacherService.addTeacher(teacher);
        //4.响应数据
        resp.setContentType("text/html;charset=utf-8");
        resp.getWriter().write("success");
    }


    public void loginTeacher(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        //1.获取get请求数据
        String username = req.getParameter("username");
        username = new String(username.getBytes(StandardCharsets.ISO_8859_1), StandardCharsets.UTF_8);
        String password = req.getParameter("password");
        //2.执行service方法
        Teacher teacher = teacherService.selectTeacher(username, password);
        if (teacher != null) {
            //4.响应数据
            //4.响应数据
            String jsonString = JSON.toJSONString(teacher);
            resp.setContentType("text/json;charset=utf-8");
            resp.getWriter().write(jsonString);
        } else {
            //4.响应数据
            resp.getWriter().write("fail");
        }

    }

    public void selectTeacherById(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        //1.处理乱码问题
        req.setCharacterEncoding("utf-8");
        //2.获取数据
        String jsonString = req.getReader().readLine();
        //3.转换为Integer类
        Integer id = JSON.parseObject(jsonString, Integer.class);
        //4.执行方法
        Teacher teacher = teacherService.selectTeacherById(id);
        //5.响应数据
        resp.setContentType("text/json;charset=utf-8");
        resp.getWriter().write(JSON.toJSONString(teacher));

    }

    public void updateTeacher(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        //1.接收ajax数据
        BufferedReader br = req.getReader();
        String jsonString = br.readLine();
        //2.转为Teacher类
        Teacher teacher = JSON.parseObject(jsonString, Teacher.class);
        //3.执行service方法
        teacherService.updateTeacher(teacher);
        //4.响应数据
        resp.setContentType("text/html;charset=utf-8");
        resp.getWriter().write("success");
    }

    public void selectTeacherByName(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        //1.解决乱码问题
        req.setCharacterEncoding("utf-8");
        //2.接收数据
        String username = req.getReader().readLine();
        //3.执行service方法
        Teacher teacher = teacherService.selectTeacherByName(username);
        //4.响应数据
        resp.setContentType("text/json;charset=utf-8");
        resp.getWriter().write(JSON.toJSONString(teacher));
    }
}
