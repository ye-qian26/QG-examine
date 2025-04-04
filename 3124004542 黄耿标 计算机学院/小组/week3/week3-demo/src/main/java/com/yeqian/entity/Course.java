package com.yeqian.entity;

public class Course {
    private Integer id;
    private String courseName;
    private Integer status;
    private Double score;

    public Course() {
    }

    public Course(Integer id, String courseName, Integer status, Double score) {
        this.id = id;
        this.courseName = courseName;
        this.status = status;
        this.score = score;
    }

    public Integer getId() {
        return id;
    }

    public void setId(Integer id) {
        this.id = id;
    }

    public String getCourseName() {
        return courseName;
    }

    public void setCourseName(String courseName) {
        this.courseName = courseName;
    }

    public Integer getStatus() {
        return status;
    }

    //逻辑视图
    public String getStatusStr(){
        if (status == null){
            return "未知";
        }
        return status == 1 ? "开课" : "未开课";
    }

    public void setStatus(Integer status) {
        this.status = status;
    }

    public Double getScore() {
        return score;
    }

    public void setScore(Double score) {
        this.score = score;
    }

    @Override
    public String toString() {
        return "Course{" +
                "id=" + id +
                ", courseName='" + courseName + '\'' +
                ", status=" + status +
                ", score=" + score +
                '}';
    }
}
