package com.yeqian.util;


import java.sql.*;
import java.util.LinkedList;

public class JDBCUtils {
    private static LinkedList<Connection> pool = new LinkedList<>();
    private static MyDataSource myDataSource = new MyDataSource();

    static {
        try {
            //获取连接池对象
            pool = myDataSource.getDateSourcePool();

        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }

    public Connection getConnection() {
        //获取数据库连接
        try {
             Connection conn = myDataSource.getConnection();
            return conn;
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }


    public void close(ResultSet rs, PreparedStatement pstmt, Connection conn) {
        try {
            rs.close();
            pstmt.close();
            //用完连接将连接归还连接池中
            pool.add(conn);
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }

    public void close( PreparedStatement pstmt, Connection conn) {
        try {
            pstmt.close();
            //用完连接将连接归还连接池中
            pool.add(conn);
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }


}
