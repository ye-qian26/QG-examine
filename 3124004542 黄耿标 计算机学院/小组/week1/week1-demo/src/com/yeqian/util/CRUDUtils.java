package com.yeqian.util;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

//通用增删改查工具类
public class CRUDUtils {
    private static JDBCUtils jdbcUtils = new JDBCUtils();
    /**
     * 通用的执行查询的方法
     *
     * @param sql      SQL语句
     * @param handler  处理结果集
     * @param params   占位符的值
     * @param <T>      具体操作的实体类
     * @return 返回特定的泛型
     */
    public static <T> T query(String sql, MyHandler<T> handler, Object... params) {
        Connection conn = null;
        PreparedStatement pstmt = null;
        ResultSet rs = null;
        try {
            //获取连接
            conn = jdbcUtils.getConnection();
            //获取PreparedStatement对象
            pstmt = conn.prepareStatement(sql);
            //设置占位符
            for (int i = 0; i < params.length; i++) {
                pstmt.setObject(i + 1, params[i]);
            }
            //处理结果集
            rs = pstmt.executeQuery();
            return handler.handle(rs);
        } catch (Exception e) {
            throw new RuntimeException(e);
        } finally {
            //释放资源
            jdbcUtils.close(rs, pstmt, conn);
        }
    }

    /**
     *
     * @param sql     SQL语句
     * @param params  占位符的值
     * @return update 更新的条数
     */
    public static int update(String sql, Object... params) {

        Connection conn = null;
        PreparedStatement pstmt = null;
        try {
            //获取连接
            conn = jdbcUtils.getConnection();
            //获取PreparedStatement对象
            pstmt = conn.prepareStatement(sql);
            //设置占位符
            for (int i = 0; i < params.length; i++) {
                pstmt.setObject(i + 1, params[i]);
            }
            //返回更新数据的条数
            return pstmt.executeUpdate();
        } catch (Exception e) {
            //处理异常
            System.out.println("增删改出现异常");
            throw new RuntimeException(e);
        } finally {
            //释放资源
            jdbcUtils.close(pstmt, conn);
        }
    }
}
