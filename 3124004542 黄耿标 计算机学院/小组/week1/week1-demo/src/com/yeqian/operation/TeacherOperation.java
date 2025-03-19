package com.yeqian.operation;

import com.yeqian.pojo.Course;
import com.yeqian.pojo.Student;
import com.yeqian.pojo.Teacher;
import com.yeqian.util.CRUDUtils;

import java.util.ArrayList;

public class TeacherOperation extends Operation {
    //老师菜单
    public void start(Teacher teacher) {
        while (true) {
            System.out.println("===== 管理员菜单 =====");
            System.out.println("1.学生管理");
            System.out.println("2.课程管理");
            System.out.println("3.个人事务");
            System.out.println("4.退出");
            System.out.println("请选择操作（输入1-3）：");
            String choice = sc.nextLine();
            switch (choice) {
                case "1":
                    //学术管理
                    studentStart();
                    break;
                case "2":
                    //课程管理
                    courseStart();
                    break;
                case "3":
                    //个人事务
                    MyInformationStart(teacher);
                    break;
                case "4":
                    //退出
                    System.out.println("退出成功！");
                    return;
                default:
                    System.out.println("您输入的指令存在问题，请重新输入！");
            }
        }
    }

    /*个人事务界面*/
    private void MyInformationStart(Teacher teacher) {
        while (true) {
            System.out.println("==== 个人事务 ====");
            System.out.println("1.查看个人信息");
            System.out.println("2.修改密码");
            System.out.println("3.回到上一级");
            System.out.println("请选择操作（输入1-3）：");
            String choice = sc.nextLine();
            switch (choice) {
                case "1":
                    //查看个人信息
                    checkInformation(teacher);
                    break;
                case "2":
                    //修改密码
                    updateTeacherPassword(teacher);
                    break;
                case "3":
                    //退出
                    System.out.println("返回成功！");
                    return;
                default:
                    System.out.println("您输入的指令有问题，请重新输入！");
            }
        }
    }

    /*管理课程界面*/
    private void courseStart() {
        while (true) {
            System.out.println("==== 课程管理 ====");
            System.out.println("1.查询所有课程");
            System.out.println("2.修改课程学分");
            System.out.println("3.查询某课程的学生名单");
            System.out.println("4.增加课程");
            System.out.println("5.删除课程");
            System.out.println("6.修改课程开课情况");
            System.out.println("7.回到上一级");
            System.out.println("请选择操作（输入1-7）：");
            String choice = sc.nextLine();
            switch (choice) {
                case "1":
                    //查询所有课程
                    selectAllCourse();
                    break;
                case "2":
                    //修改课程学分
                    changeScore();
                    break;
                case "3":
                    //查询某课程的学生名单
                    selectCourseStudent();
                    break;
                case "4":
                    //增加课程
                    addCourse();
                    break;
                case "5":
                    //删除课程
                    deleteCourse();
                    break;
                case "6":
                    //修改课程开课情况
                    updateCourseStatus();
                    break;
                case "7":
                    //退出
                    System.out.println("返回成功！");
                    return;
                default:
                    System.out.println("您输入的指令有问题，请重新输入！");
            }
        }
    }

    /*管理学生界面*/
    private void studentStart() {
        while (true) {
            System.out.println("==== 学生管理 ====");
            System.out.println("1.查询所有学生");
            System.out.println("2.修改学生手机号");
            System.out.println("3.查询某学生的选课情况");
            System.out.println("4.回到上一级");
            System.out.println("请选择操作（输入1-4）：");
            String choice = sc.nextLine();
            switch (choice) {
                case "1":
                    //查询所有学生
                    checkAllStudents();
                    break;
                case "2":
                    //修改学生手机号
                    UpdateStudentTele();
                    break;
                case "3":
                    //查询某学生的选课情况
                    selectStudentCourse();
                    break;
                case "4":
                    //退出
                    System.out.println("返回成功！");
                    return;
                default:
                    System.out.println("您输入的指令有问题，请重新输入！");
            }
        }
    }

    /*方法：修改课程开课情况*/
    private void updateCourseStatus() {
        //1.得到所有课程信息
        ArrayList<Course> courses = judgeCourse();

        //2.判断是否存在课程信息
        if (courses.isEmpty()) {
            System.out.println("暂无课程信息~可前往添加~");
            return;
        }
        //3.展示所有课程
        printAllCourse(courses);

        //4.接收用户输入信息
        Course course;
        String choice;
        System.out.println("请输入您想修改的课程：（1-" + courses.size() + "):");
        while (true) {
            choice = sc.nextLine();
            //判断输入操作是否符合规范
            if (!judgeCourseSelect(choice, courses)) {
                System.out.println("输入错误，请重新输入：");
            } else {
                course = courses.get(Integer.parseInt(choice) - 1);
                //调用修改课程表开课情况方法
                int count = updateStatusDatabase(course);
                if (count > 0) {
                    System.out.println("修改" + course.getName() + "开课情况成功！");
                    break;
                } else {
                    System.out.println("修改" + course.getName() + "开课情况失败！");
                    break;
                }
            }
        }
    }

    /*方法：通过传入课程对象修改course表status*/
    private int updateStatusDatabase(Course course) {
        String name = course.getName();
        int status;
        if (course.getStatus() == 0) status = 1;
        else status = 0;

        course.setStatus(status);
        //1.定义sql语句
        String sql = "update course set status = ? where name = ?";
        //2.调用通用工具类
        return CRUDUtils.update(sql, status, name);
    }

    /*方法：删除课程*/
    private void deleteCourse() {
        //得到所有课程信息
        ArrayList<Course> courses = judgeCourse();
        if (courses.isEmpty()) {
            System.out.println("暂无课程数据~可前往添加");
            return;
        }
        //展示课程信息
        printAllCourse(courses);
        Course course;
        String choice;

        while (true) {
            System.out.println("请输入您想删除的课程（1-" + courses.size() + ")(输入0返回上一级）:");
            choice = sc.nextLine();
            if (choice.equals("0")) {
                System.out.println("返回成功！");
                return;
            }

            //判断格式是否是整数
            if (!judgeCourseSelect(choice, courses)) {
                System.out.println("输入错误，请重新输入！");
            } else {
                //处理实体类数据
                course = courses.get(Integer.parseInt(choice) - 1);
                if (!course.getStudents().isEmpty()) {
                    System.out.println("该课程目前有" + course.getStudents() + "已选择，无法删除");
                } else {
                    //调用方法删除课程数据
                    int count = deleteCourseDatabase(course);
                    if (count > 0) {
                        System.out.println("删除课程成功！");
                        return;
                    } else {
                        System.out.println("删除课程失败！");
                        return;
                    }
                }
            }
        }
    }

    /*方法：通过传入课程对象在course表中删除对应数据*/
    private int deleteCourseDatabase(Course course) {
        String name = course.getName();
        //定义sql语句
        String sql = "delete from course where name = ?";
        //调用通用工具类
        return CRUDUtils.update(sql, name);
    }

    /*方法：增加课程*/
    private void addCourse() {
        System.out.println("请输入您想添加的课程：");

        String name;
        while (true) {
            name = sc.nextLine();
            //判断课程中是否已存在该课程
            if (findCourseByName(name) != null) {
                System.out.println("该课程已存在，请重新输入：");
            } else break;
        }

        String score;
        while (true) {
            System.out.println("请输入课程学分：");
            score = sc.nextLine();
            //判断接收的学分是否符合规范
            if (score.matches("[1-4](\\.[05])?")) {
                Double score1 = Double.valueOf(score);
                int count = addCourseDatabase(name, score1);
                if (count > 0) {
                    System.out.println("添加课程成功！");
                    break;
                } else {
                    System.out.println("添加课程失败！");
                    break;
                }
            } else {
                System.out.println("您输入的格式有问题，请重新输入！");
            }
        }
    }

    /*方法：通过传入课程名称和学分在course表中添加数据*/
    private int addCourseDatabase(String name, Double score1) {
        String sql = "insert into course(name, score, status) values(?,?,0)";
        return CRUDUtils.update(sql, name, score1);
    }

    /*方法：查询指定课程的学生*/
    private void selectCourseStudent() {
        //获取所有课程信息
        ArrayList<Course> courses = judgeCourse();
        if (courses.isEmpty()) {
            System.out.println("暂无课程信息~可前往添加");
            return;
        }
        //展示所有课程
        System.out.println("所有课程如下：");
        for (int i = 0; i < courses.size(); i++) {
            System.out.println((i + 1) + "." + courses.get(i).getName());
        }

        Course course;
        String choice;
        System.out.println("请选择你想查询的课程（1-" + courses.size() + "):");
        while (true) {
            choice = sc.nextLine();
            //判断输入的操作是否符合规范
            if (judgeCourseSelect(choice, courses)) {
                //符合规范
                course = courses.get(Integer.parseInt(choice) - 1);
                break;
            } else {
                //不符合规范
                System.out.println("您输入的序号有误，请重新输入：");
            }
        }

        //得到了课程对象course
        System.out.println("选择了" + course.getName() + "这门课程的学生如下：");
        System.out.println(course.getStudents());
    }

    /*方法：查询指定学生所选课程*/
    private void selectStudentCourse() {
        //得到所有学生对象
        ArrayList<Student> students = checkAllStudents();
        if (students.isEmpty()) {
            System.out.println("暂无学生对象~等待学生注册~");
            return;
        }
        //展示所有学生信息
        for (int i = 0; i < students.size(); i++) {
            System.out.println((i + 1) + "." + students.get(i).getName());
        }

        Student student;
        String choice;
        System.out.println("请输入您想查询的学生（1-" + students.size() + "):");
        while (true) {
            choice = sc.nextLine();
            //判断输入的操作是否符合规范
            if (judgeStudentSelect(choice, students)) {
                //符合规范
                student = students.get(Integer.parseInt(choice) - 1);
                break;
            } else {
                //不符合规范
                System.out.println("您输入的序号有误，请重新输入：");
            }
        }

        System.out.println("学生" + student.getName() + ":");
        checkMyCourse(student);
    }

    /*方法：修改课程学分*/
    private void changeScore() {
        ArrayList<Course> courses = judgeCourse();
        //判断是否有课程信息
        if (courses.isEmpty()) {
            System.out.println("暂无课程信息~可前往添加~");
            return;
        }
        printAllCourse(courses);
        String choice;
        Course course;

        while (true) {
            System.out.println("请输入你要修改的课程（1-" + courses.size() + ")（输入0返回老师菜单界面）：");
            choice = sc.nextLine();

            if (choice.equals("0")) {
                System.out.println("返回成功！");
                return;
            }
            //判断格式是否正确
            if (!judgeCourseSelect(choice, courses)) {
                System.out.println("输入错误，请重新输入！");
            } else {
                //4.处理实体类数据
                course = courses.get(Integer.parseInt(choice) - 1);
                break;
            }
        }
        System.out.println("该课程的学分：" + course.getScore());
        while (true) {
            System.out.println("请输入您要修改的新学分（1.0-4.0）（例如：1.5 √  1.2 ×）：");
            String score = sc.nextLine();
            //判断接收的学分是否符合规范
            if (score.matches("[1-4](\\.[05])?")) {
                Double score1 = Double.valueOf(score);
                int count = updateScore(course, score1);
                if (count > 0) {
                    System.out.println("修改课程学分成功！");
                    break;
                } else {
                    System.out.println("修改课程学分失败！");
                    break;
                }
            } else {
                System.out.println("您输入的格式有问题，请重新输入！");
            }
        }
    }

    /*通过传入课程对象和学分信息修改course表*/
    private int updateScore(Course course, Double score) {
        String name = course.getName();
        course.setScore(score);

        //定义sql语句
        String sql = "update course set score = ? where name = ?";
        //执行语句
        return CRUDUtils.update(sql, score, name);
    }

    /*方法：查看个人信息*/
    private void checkInformation(Teacher teacher) {
        System.out.println("个人信息如下：");
        System.out.println("姓名：" + teacher.getUsername());
        System.out.println("密码：" + teacher.getPassword());
    }

    /*方法：老师修改密码*/
    private void updateTeacherPassword(Teacher teacher) {
        OUT:
        while (true) {
            System.out.println("请输入您当前的密码：（输入0返回上一级）");
            String password1 = sc.nextLine();
            if (password1.equals("0")) {
                System.out.println("返回成功！");
                return;
            }

            //1.判断当前密码是否输入正确
            if (!teacher.getPassword().equals(password1)) {
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
                        teacher.setPassword(password2);
                        break OUT;
                    }
                }
            }
        }

        //在数据库中修改信息
        //定义sql语句
        String sql = "update teacher set password = ? where username = ?";
        int count = CRUDUtils.update(sql, teacher.getPassword(), teacher.getUsername());
        if (count > 0) {
            System.out.println("修改密码成功！");
        }
    }

    /*方法：查询所有课程*/
    private void selectAllCourse() {
        //获取所有课程
        ArrayList<Course> courses = judgeCourse();
        if (courses.isEmpty()) {
            System.out.println("暂时还没有课程信息，可前往添加~");
            return;
        }

        System.out.println("课程信息如下（1表示开课，0表示未开课）：");
        for (int i = 0; i < courses.size(); i++) {
            System.out.println((i + 1) + "." + courses.get(i).getName() + " 开课情况：" +
                    courses.get(i).getStatus() + " 学分：" + courses.get(i).getScore());
            System.out.println("参加该课程的学生：" + courses.get(i).getStudents());
            System.out.println("-----------------------------");
        }
    }

    /*方法：修改学生手机号*/
    private void UpdateStudentTele() {
        if (checkAllStudents().isEmpty()) {
            System.out.println("暂无学生对象~等待学生注册~");
            return;
        }
        //存在学生对象，开始修改
        while (true) {
            System.out.println("请输入您想修改手机号的学生名字：");
            String choice = sc.nextLine();
            Student student = checkStudentByName(choice);
            //判断该学生是否存在
            if (student == null) {
                System.out.println("不存在该学生~请重新输入~");
            } else {
                //判断该学生是否有手机号
                if (student.getTele() != null) {
                    System.out.println("学生" + student.getName() + "的手机号为：" + student.getTele());
                } else {
                    System.out.println("学生" + student.getName() + "暂无手机号信息");
                }
                while (true) {
                    System.out.println("请输入您想修改的新手机号：");
                    String tele = sc.nextLine();
                    //判断输入的号码格式是否正确
                    if (tele.matches("1[3-9]\\d{9}")) {
                        //调用已有方法进行修改
                        student.setTele(tele);
                        int count = updateTele(student, tele);
                        if (count > 0) {
                            System.out.println("修改成功！");
                            System.out.println("学生" + student.getName() + "新手机号为：" + student.getTele());
                            return;
                        } else {
                            System.out.println("修改失败！");
                            return;
                        }
                    } else {
                        System.out.println("您输入的号码格式不正确，请重新输入~");
                    }
                }
            }
        }
    }
}
