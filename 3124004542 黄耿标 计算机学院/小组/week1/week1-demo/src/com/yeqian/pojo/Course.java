package com.yeqian.pojo;

import java.util.ArrayList;
import java.util.List;

public class Course {
    private int id;
    private String name;
    private int status;
    private double score;
    private String student;
    private ArrayList<String> students = new ArrayList<>();

    public Course() {
    }

    public Course(int id, String name, int status, double score, String student) {
        this.id = id;
        this.name = name;
        this.status = status;
        this.score = score;
        this.student = student;
    }

    public String getStudent() {
        return student;
    }

    public void setStudent(String student) {
        this.student = student;
    }

    public ArrayList<String> getStudents() {
        return students;
    }

    public void setStudents(ArrayList<String> students) {
        this.students = students;
    }

    public double getScore() {
        return score;
    }

    public void setScore(double score) {
        this.score = score;
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

    public int getStatus() {
        return status;
    }

    public void setStatus(int status) {
        this.status = status;
    }

    @Override
    public String toString() {
        return "Course{" +
                "id=" + id +
                ", name='" + name + '\'' +
                ", status=" + status +
                ", score=" + score +
                '}';
    }
}
