package com.yeqian.operation;

import com.yeqian.pojo.Course;
import com.yeqian.pojo.Student;
import com.yeqian.util.CRUDUtils;

import java.util.ArrayList;

public class StudentOperation extends Operation {

    //开始界面
    public void start(Student student) {
        System.out.println(student.getName() + "您好！欢迎您进入学生系统~");
        while (true) {
            System.out.println("===== 学生菜单 =====");
            System.out.println("1.查看可选课程");
            System.out.println("2.选择课程");
            System.out.println("3.退选课程");
            System.out.println("4.查看已选课程");
            System.out.println("5.修改手机号");
            System.out.println("6.查看个人信息");
            System.out.println("7.修改密码");
            System.out.println("8.退出");
            System.out.println("请选择操作（输入1-8）：");
            String choice = sc.nextLine();
            switch (choice) {
                case "1":
                    //查看可选课程
                    checkAllCourse();
                    break;
                case "2":
                    //选择课程
                    selectCourse(student);
                    break;
                case "3":
                    //退选课程
                    deleteSelectCourse(student);
                    break;
                case "4":
                    //查看已选课程
                    checkMyCourse(student);
                    break;
                case "5":
                    //修改手机号
                    updateTeleByStudent(student);
                    break;
                case "6":
                    //查看个人信息
                    checkInformation(student);
                    break;
                case "7":
                    //修改密码
                    updateStudentPassword(student);
                    break;
                case "8":
                    //退出
                    System.out.println("退出成功！");
                    return;
                default:
                    System.out.println("您输入的操作有问题，请重新输入！");
            }
        }
    }

    /*方法：退选课程*/
    private void deleteSelectCourse(Student student) {
        //判断是否有课程信息
        if (student.getCourses().isEmpty()) {
            System.out.println("暂无课程~");
            return;
        }

        //有课程信息
        ArrayList<Course> courses = new ArrayList<>();
        //展示课程信息
        System.out.println("您的课程信息如下：");
        for (int i = 0; i < student.getCourses().size(); i++) {
            Course courseByName = findCourseByName(student.getCourses().get(i));
            courses.add(courseByName);
        }

        printAllCourse(courses);
        String choice;
        Course course;
        String courseName;
        while (true) {
            System.out.println("请选择您想退选的课程（1-" + courses.size() + "）(输入0返回学生菜单界面）：");
            choice = sc.nextLine();
            if (choice.equals("0")) {
                System.out.println("返回成功！");
                return;
            }
            //判断格式是否是整数
            if (!judgeCourseSelect(choice, courses)) {
                System.out.println("输入错误，请重新输入！");
            } else {
                //4.处理实体类数据
                course = courses.get(Integer.parseInt(choice) - 1);
                //判断课程是否已经开课
                if (course.getStatus() == 1) {
                    System.out.println("该课程已经开课，无法退选~");
                } else {
                    courseName = course.getName().trim();
                    break;
                }
            }
        }
        //在学生的课程集合中删除该课程
        student.getCourses().remove(courseName);
        //在课程的学生集合中删除该学生
        course.getStudents().remove(student.getName());

        //对数据库中student表进行操作
        StringBuilder coursesName = new StringBuilder();
        for (int i = 0; i < student.getCourses().size(); i++) {
            if (i < student.getCourses().size() - 1) {
                coursesName.append(student.getCourses().get(i)).append(",");
            } else {
                coursesName.append(student.getCourses().get(i));
            }
        }
        student.setCourse(coursesName.toString());
        //调用修改学生表方法
        int count1 = updateStudent(student.getName(), coursesName.toString());

        //对数据库中course表进行操作
        StringBuilder studentsName = new StringBuilder();
        for (int i = 0; i < course.getStudents().size(); i++) {
            if (i < course.getStudents().size() - 1) {
                studentsName.append(course.getStudents().get(i)).append(",");
            } else {
                studentsName.append(course.getStudents().get(i));
            }
        }
        course.setStudent(studentsName.toString());
        //调用修改课程表方法
        int count2 = updateCourse(course.getName(), studentsName.toString());

        //判断两个表是否都完成了修改
        if (count1 > 0 && count2 > 0) {
            System.out.println("退选课程成功！");
        } else {
            System.out.println("退选课程失败!");
        }
    }

    /*方法：查看个人信息*/
    private void checkInformation(Student student) {
        System.out.println("您的个人信息如下：");
        System.out.println("姓名：" + student.getName());
        if (student.getTele() == null) {
            System.out.println("手机号：无");
        } else {
            System.out.println("手机号：" + student.getTele());
        }
    }

    /*方法：修改密码*/
    private void updateStudentPassword(Student student) {
        OUT:
        while (true) {
            System.out.println("请输入您当前的密码：（输入0返回上一级）");
            String password1 = sc.nextLine();
            if (password1.equals("0")) {
                System.out.println("返回成功！");
                return;
            }

            //1.判断当前密码是否输入正确
            if (!student.getPassword().equals(password1)) {
                System.out.println("密码错误");
            } else {
                while (true) {
                    //2.密码正确，开始输入新密码
                    System.out.println("请您输入新密码：");
                    String password2 = sc.nextLine();
                    System.out.println("请确认新密码：");
                    String password3 = sc.nextLine();

                    //3.判断两次输入的新密码是否一致
                    if (!password2.equals(password3)) {
                        System.out.println("两次密码不一致，请重新输入");
                    } else {
                        student.setPassword(password2);
                        break OUT;
                    }
                }
            }
        }

        //在数据库中修改信息
        //定义sql语句
        String sql = "update student set password = ? where name = ?";
        //执行sql语句
        int count = CRUDUtils.update(sql, student.getPassword(), student.getName());
        if (count > 0) {
            System.out.println("修改密码成功！");
        }
    }

    /*方法：选择课程*/
    private void selectCourse(Student student) {
        //1.获取已有课程,并判断是否有课程信息
        ArrayList<Course> courses = judgeCourse();
        if (courses.isEmpty()) {
            System.out.println("暂无课程信息，等老师添加~");
            return;
        }

        System.out.println("您当前的课程门数：" + student.getCourses().size());
        //判断课程是否达到五门
        if (student.getCourses().size() >= 5) {
            System.out.println("已选课程已达到五门，无法再添加课程~");
            return;
        }

        //2.展示可选课程供选择
        printAllCourse(courses);

        //3.学生选择课程
        String choice;
        Course course;
        String courseName;
        while (true) {
            System.out.println("请输入你要选择的课程（1-" + courses.size() + ")（输入0返回学生菜单界面）：");
            choice = sc.nextLine();

            if (choice.equals("0")) {
                System.out.println("返回成功！");
            }
            //判断格式是否是整数
            if (!judgeCourseSelect(choice, courses)) {
                System.out.println("输入错误，请重新输入！");
            } else {
                //4.处理实体类数据
                course = courses.get(Integer.parseInt(choice) - 1);
                courseName = course.getName();
                //判断课程是否重复
                if (student.getCourses().contains(courseName)) {
                    System.out.println("该课程已存在于您的课程中~");
                } else break;
            }
        }

        //处理课程表
        if (course.getStudents().isEmpty()) {
            course.setStudent(student.getName());
        } else {
            course.setStudent(course.getStudent() + "," + student.getName());
        }
        int count1 = updateCourse(courseName, course.getStudent());

        //处理学生表
        if (student.getCourses().isEmpty()) {
            student.setCourse(courseName);
        } else {
            student.setCourse(student.getCourse() + "," + courseName);
        }
        student.getCourses().add(courseName);
        int count2 = updateStudent(student.getName(), student.getCourse());
        if (count1 > 0 && count2 > 0) {
            System.out.println("选课成功！");
        } else {
            System.out.println("选课失败！");
        }
    }

    /*方法：学生修改手机号*/
    private void updateTeleByStudent(Student student) {
        if (student.getTele() == null) {
            System.out.println("您目前没有手机号信息");
        } else {
            System.out.println("您目前的手机号为：" + student.getTele());
        }

        String tele = null;
        while (true) {
            System.out.println("请输入您的新手机号:");
            tele = sc.nextLine();
            if (!tele.matches("1[3-9]\\d{9}")) {
                System.out.println("您输入的号码格式不正确，请重新输入");
            } else {
                break;
            }
        }
        int count = updateTele(student, tele);
        if (count > 0) {
            System.out.println("修改成功！");
            System.out.println("您的新手机号为：" + tele);
        } else {
            System.out.println("修改手机号失败！");
        }
    }

    /*方法：查询可选课程*/
    private void checkAllCourse() {
        ArrayList<Course> courses = judgeCourse();

        if (courses.isEmpty()) {
            System.out.println("目前还没有课程信息，等老师添加~");
        } else {
            printAllCourse(courses);
        }
    }
}
