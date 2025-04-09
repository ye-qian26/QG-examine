package com.yeqian.controller.filter;

import javax.servlet.*;
import javax.servlet.annotation.WebFilter;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;
import java.net.URLEncoder;

@WebFilter(urlPatterns = {"/student.html", "/teacher.html"})
public class LoginFilter implements Filter {

    @Override
    public void doFilter(ServletRequest servletRequest, ServletResponse servletResponse, FilterChain filterChain) throws IOException, ServletException {
        HttpServletRequest req = (HttpServletRequest) servletRequest;
        HttpServletResponse resp = (HttpServletResponse) servletResponse;

        //1.获取访问路径
        String requestURL = req.getRequestURL().toString();

        //2 .判断session中是否有数据
        HttpSession session = req.getSession();
        if (requestURL.contains("student.html")) {
            //如果访问的是学生界面
            Object student = session.getAttribute("student");
            if (student != null) {
                //session中有学生数据
                //放行
                filterChain.doFilter(servletRequest, servletResponse);
            } else {
                //session中无学生数据
                //提示信息并携带参数重定向到登录界面
                String loginMsg = "您尚未登录！";
                String redirectUrl = "/week3-demo/login.html?loginMsg=" + URLEncoder.encode(loginMsg, "UTF-8");
                //重定向
                resp.sendRedirect(redirectUrl);
            }
        } else if (requestURL.contains("teacher.html")) {
            //如果访问的是老师界面
            Object teacher = session.getAttribute("teacher");
            if (teacher != null) {
                //session中有老师数据
                //放行
                filterChain.doFilter(servletRequest, servletResponse);
            } else {
                //session无老师数据
                //提示信息并携带参数重定向到登录界面
                String loginMsg = "您尚未登录！";
                String redirectUrl = "/week3-demo/login.html?loginMsg=" + URLEncoder.encode(loginMsg, "UTF-8");
                //重定向
                resp.sendRedirect(redirectUrl);
            }
        }
    }

    @Override
    public void init(FilterConfig filterConfig) throws ServletException {

    }

    @Override
    public void destroy() {

    }
}
