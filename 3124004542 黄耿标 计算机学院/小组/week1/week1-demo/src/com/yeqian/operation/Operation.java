package com.yeqian.operation;

import com.yeqian.pojo.Course;
import com.yeqian.pojo.Student;
import com.yeqian.pojo.Teacher;
import com.yeqian.util.CRUDUtils;
import com.yeqian.util.JDBCUtils;
import com.yeqian.util.MyHandler;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Operation {
    public Scanner sc = new Scanner(System.in);
    public static JDBCUtils JDBCUtils = new JDBCUtils();

    /*方法：判断数据库是否有老师信息*/
    public boolean judgeTeacher() {
        //定义sql语句
        String sql = "select * from teacher";
        //MyHandler的匿名内部类
        MyHandler<List<Teacher>> handler = rs -> {
            List<Teacher> teachers = teacherHandler(rs);
            return teachers;
        };
        List<Teacher> teachers = CRUDUtils.query(sql, handler);
        return !teachers.isEmpty();
    }

    /*方法：判断数据库是否有学生信息*/
    public boolean judgeStudent() {
        //定义sql语句
        String sql = "select * from student";
        //MyHandler的匿名内部类
        MyHandler<List<Student>> handler = rs -> {
            List<Student> students = studentHandler(rs);
            return students;
        };
        List<Student> students = CRUDUtils.query(sql, handler);
        return !students.isEmpty();
    }

    /*方法：根据学生用户名查找学生信息*/
    public Student checkStudentByName(String name) {
        //定义sql语句
        String sql = "select * from student where name=?";
        //MyHandler的匿名内部类
        MyHandler<Student> handler = rs -> {
            ArrayList<Student> students = studentHandler(rs);
            if (students.isEmpty()) {
                return null;
            }
            return students.getFirst();
        };
        return CRUDUtils.query(sql, handler, name);
    }

    /*方法：根据老师用户名查找老师信息*/
    public Teacher checkTeacherByName(String name) {
        //1.获取数据库连接
        Connection conn = JDBCUtils.getConnection();

        //2.定义sql语句
        String sql = "select * from teacher where username=?";
        //MyHandler的匿名内部类
        MyHandler<Teacher> handler = rs -> {
            ArrayList<Teacher> teachers = teacherHandler(rs);
            if (teachers.isEmpty()) {
                return null;
            }
            return teachers.getFirst();
        };
        return CRUDUtils.query(sql, handler, name);
    }

    /*方法：通过课程名称查找课程，并返回课程对象*/
    public Course findCourseByName(String courseName) {
        if (courseName == null) {
            System.out.println("传入参数存在问题，请确认");
            return null;
        }
        //定义sql语句
        String sql = "select * from course where name = ?";
        //MyHandler的匿名内部类
        MyHandler<Course> handler = rs ->{
            ArrayList<Course> courses = courseHandler(rs);
            if (courses.isEmpty()) {
                return null;
            }
            return courses.getFirst();
        };
        return CRUDUtils.query(sql, handler, courseName);
    }

    /*方法：通过传入课程名称和学生名字修改课程表*/
    public int updateCourse(String courseName, String studentName) {
        //判断参数是否为空
        if (courseName == null || studentName == null) {
            System.out.println("传入参数存在问题，请确认！");
            return 0;
        }
        //参数不为空
        //定义sql语句
        String sql = "update course set student = ? where name = ?";
        //执行sql语句
        return CRUDUtils.update(sql, studentName, courseName);
    }

    /*方法：通过传入学生名字和课程名称修改学生表*/
    public int updateStudent(String studentName, String courseName) {
        //判断参数是否为空
        if (courseName == null || studentName == null) {
            System.out.println("传入参数存在问题，请确认！");
            return 0;
        }
        //定义sql语句
        String sql = "update student set course = ? where name = ?";
        //执行sql语句
        return CRUDUtils.update(sql, courseName, studentName);
    }

    /*方法：通过传入学生对象和手机号修改student表*/
    public int updateTele(Student student, String tele) {
        //定义sql语句
        String sql = "update student set tele = ? where name = ?";
        //执行sql语句
        return CRUDUtils.update(sql, tele, student.getName());
    }

    /*方法：判断是否有课程信息,并返回集合Courses*/
    public ArrayList<Course> judgeCourse() {
        //定义sql语句
        String sql = "select * from course";
        //MyHandler的匿名内部类
        MyHandler<ArrayList<Course>> handler = rs -> {
            ArrayList<Course> courses = courseHandler(rs);
            return courses;
        };
        return CRUDUtils.query(sql, handler);
    }

    /*方法：查询所有学生,并返回学生集合*/
    public ArrayList<Student> checkAllStudents() {
        //判断是否存在学生信息
        if (!judgeStudent()) {
            System.out.println("目前还没有学生信息，等待学生注册~");
            return null;
        }

        //定义sql语句
        String sql = "select * from student";
        //MyHandler的匿名内部类
        MyHandler<ArrayList<Student>> handler = rs -> {
            ArrayList<Student> students = studentHandler(rs);
            return students;
        };
        ArrayList<Student> students = CRUDUtils.query(sql, handler);
        //展示学生信息
        printAllStudents(students);
        return students;
    }

    /*方法：展示学生信息*/
    private void printAllStudents(ArrayList<Student> students) {
        if (students.isEmpty()) {
            return;
        }
        System.out.println("所有学生信息如下：");
        for (Student student : students) {
            System.out.println("姓名：" + student.getName());
            if (student.getTele() != null) {
                System.out.println("手机号：" + student.getTele());
            } else {
                System.out.println("手机号：无");
            }
            System.out.println("----------------------------");
        }
    }

    /*方法：展示课程信息*/
    public void printAllCourse(ArrayList<Course> courses) {
        System.out.println("课程信息如下（1表示开课，0表示未开课）：");
        for (int i = 0; i < courses.size(); i++) {
            System.out.println((i + 1) + "." + courses.get(i).getName() + " 开课情况：" +
                    courses.get(i).getStatus() + " 学分：" + courses.get(i).getScore());
        }
    }

    /*方法：查看学生所选课程*/
    public void checkMyCourse(Student student) {
        if (student.getCourses().isEmpty()) {
            System.out.println("暂无已选课程");
        } else {
            System.out.println("已选课程如下：");
            System.out.println(student.getCourses());
        }
    }

    /*方法；判断选择学生的操作是否符合规范*/
    public boolean judgeStudentSelect(String choice, ArrayList<Student> students) {
        //判断输入的操作是否符合规范
        if (choice.matches("\\d")) {
            int index = Integer.parseInt(choice);
            return index <= students.size() && index >= 1;
        } else {
            return false;
        }
    }

    /*方法；判断选择学生的操作是否符合规范*/
    public boolean judgeCourseSelect(String choice, ArrayList<Course> Course) {
        //判断输入的操作是否符合规范
        if (choice.matches("\\d")) {
            int index = Integer.parseInt(choice);
            return index <= Course.size() && index >= 1;
        } else {
            return false;
        }
    }

    /*方法：处理学生集*/
    public ArrayList<Student> studentHandler(ResultSet rs) throws Exception {
        ArrayList<Student> students = new ArrayList<>();
        Student s;
        while (rs.next()) {
            int id = rs.getInt("id");
            String name1 = rs.getString("name");
            String password = rs.getString("password");
            String course = rs.getString("course");
            String tele = rs.getString("tele");

            s = new Student();
            s.setId(id);
            s.setName(name1);
            s.setPassword(password);
            s.setCourse(course);
            s.setTele(tele);

            //当course不等于null时添加到s.getCourses()
            if (course != null) {
                if (course.contains(",")) {
                    //将course中以","为分隔符依次装进s.getCourses()中
                    String[] parts = course.split(",");
                    for (String part : parts) {
                        s.getCourses().add(part.trim());
                    }
                } else {
                    s.getCourses().add(course.trim());
                }
            }
            students.add(s);
        }
        return students;
    }

    /*方法：处理老师集*/
    public ArrayList<Teacher> teacherHandler(ResultSet rs) throws Exception {
        ArrayList<Teacher> teachers = new ArrayList<>();
        Teacher t;
        while (rs.next()) {
            int id = rs.getInt("id");
            String name1 = rs.getString("username");
            String password = rs.getString("password");

            t = new Teacher();

            t.setId(id);
            t.setUsername(name1);
            t.setPassword(password);
            teachers.add(t);
        }
        return teachers;
    }

    /*方法：处理课程集*/
    public ArrayList<Course> courseHandler(ResultSet rs) throws Exception {
        ArrayList<Course> courses = new ArrayList<>();
        Course course;
        while (rs.next()) {
            int id = rs.getInt("id");
            String name = rs.getString("name");
            int status = rs.getInt("status");
            double score = rs.getDouble("score");
            String student = rs.getString("student");

            course = new Course();
            course.setId(id);
            course.setName(name);
            course.setStatus(status);
            course.setScore(score);
            course.setStudent(student);

            if (course.getStudent() != null) {
                if (!course.getStudent().trim().isEmpty()) {
                    if (course.getStudent().contains(",")) {
                        //存在","
                        //以","为分隔符将对应学生信息依次存入course.getStudents()
                        String[] parts = course.getStudent().split(",");
                        for (String part : parts) {
                            course.getStudents().add(part.trim());
                        }
                    } else {
                        //不存在","
                        course.getStudents().add(course.getStudent().trim());
                    }
                }
            }
            courses.add(course);
        }
        return courses;
    }
}
