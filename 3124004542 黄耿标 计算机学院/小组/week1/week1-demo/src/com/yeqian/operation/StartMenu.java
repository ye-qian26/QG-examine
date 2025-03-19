package com.yeqian.operation;

import com.yeqian.pojo.Student;
import com.yeqian.pojo.Teacher;
import com.yeqian.util.CRUDUtils;

public class StartMenu extends Operation {
    public void start() {
        while (true) {
            System.out.println("===========================");
            System.out.println("👨‍🎓学生选课管理系统");
            System.out.println("===========================");
            System.out.println("1.登录");
            System.out.println("2.注册");
            System.out.println("3.退出");
            System.out.println("请选择操作(输入1-3)：");
            String choice = sc.nextLine();
            switch (choice) {
                case "1":
                    //登录操作
                    login();
                    break;
                case "2":
                    //注册操作
                    try {
                        register();
                    } catch (Exception e) {
                        throw new RuntimeException(e);
                    }
                    break;
                case "3":
                    //退出系统
                    System.out.println("退出系统成功~欢迎您下次光临~");
                    return;
                default :
                    System.out.println("您输入的操作不符合规范，请重新输入！");
            }
        }

    }

    /*方法：注册界面*/
    private void register() throws Exception {
        String name = null;
        while (true) {
            System.out.println("===== 用户注册 =====");
            System.out.println("请输入用户名：");
            name = sc.nextLine();

            if (checkStudentByName(name) != null || checkTeacherByName(name) != null) {
                System.out.println("该用户名已存在，请重新输入");
            } else {
                break;
            }
        }

        String password1 = null;
        String password2 = null;
        while (true) {
            System.out.println("请输入密码：");
            password1 = sc.nextLine();
            System.out.println("请确认密码：");
            password2 = sc.nextLine();

            //判断用户输入的两次密码是否一致
            if (password1.equals(password2)) {
                break;
            } else {
                System.out.println("您两次输入的密码不一致，请重新输入！");
            }
        }

        String identify = null;
        while (true) {
            System.out.println("请选择角色（输入1代表学生，2代表老师）：");
            identify = sc.nextLine();

            //判断用户输入的角色选择指令是否有问题
            if (identify.equals("1") || identify.equals("2")) {
                break;
            } else {
                System.out.println("您输入的角色选择有问题，请重新选择！");
            }
        }

        if (identify.equals("1")) {
            //注册学生身份
            //定义sql语句
            String sql = "insert into student(name, password) values(?,?)";
            int count1 = CRUDUtils.update(sql, name, password1);
            if (count1 > 0) {
                System.out.println("注册成功！请返回主界面登录~");
            }
        } else {
            //注册老师身份
            //2.定义sql语句
            String sql = "insert into teacher(username, password) values(?,?)";
            int count = CRUDUtils.update(sql, name, password1);
            if (count > 0) {
                System.out.println("注册成功！请返回主界面登录~");
            }
        }
    }

    /*方法：登录界面*/
    private void login() {
        //1.调用方法判断数据库是否有信息
        if (!judgeTeacher() && !judgeStudent()) {
            System.out.println("数据库中并没有任何信息，先去注册！");
            return;
        }

        String name = null;
        String password = null;
        while (true) {
            System.out.println("===== 用户登录 =====");
            System.out.println("请输入用户名：");
            name = sc.nextLine();
            System.out.println("请输入密码：");
            password = sc.nextLine();

            //2.判断所输入用户名是否有对应信息
            if (checkStudentByName(name) == null && checkTeacherByName(name) == null) {
                System.out.println("该用户名不存在，请重新输入");
            } else break;

        }
        //用户名有对应信息
        //获取对应对象
        Student student = checkStudentByName(name);
        Teacher teacher = checkTeacherByName(name);
        if (student != null) {
            //判断密码是否正确
            if (student.getPassword().equals(password)) {
                System.out.println("登录成功！你的角色是：学生");
                StudentOperation studentOperation = new StudentOperation();
                studentOperation.start(student);
            } else {
                System.out.println("密码错误！");
            }
        }

        if (teacher != null) {
            //判断密码是否正确
            if (teacher.getPassword().equals(password)) {
                System.out.println("登录成功！你的角色是：老师");
                TeacherOperation teacherOperation = new TeacherOperation();
                teacherOperation.start(teacher);
            } else {
                System.out.println("密码错误！");
            }
        }
    }
}
