package com.yeqian.pojo;

import java.util.ArrayList;

public class Student {
    private int id;
    private String name;
    private String password;
    private String tele;
    private String course;
    private ArrayList<String> courses = new ArrayList<>();

    public Student() {
    }

    public Student(int id, String name, String password, String tele, ArrayList<String> courses) {
        this.id = id;
        this.name = name;
        this.password = password;
        this.tele = tele;
        this.courses = courses;
    }

    public ArrayList<String> getCourses() {
        return courses;
    }

    public void setCourses(ArrayList<String> courses) {
        this.courses = courses;
    }

    public String getCourse() {
        return course;
    }

    public void setCourse(String course) {
        this.course = course;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }


    public String getTele() {
        return tele;
    }

    public void setTele(String tele) {
        this.tele = tele;
    }

    @Override
    public String toString() {
        return "Student{" +
                "id=" + id +
                ", name='" + name + '\'' +
                ", password='" + password + '\'' +
                ", tele='" + tele + '\'' +
                ", course='" + course + '\'' +
                ", courses=" + courses +
                '}';
    }
}
