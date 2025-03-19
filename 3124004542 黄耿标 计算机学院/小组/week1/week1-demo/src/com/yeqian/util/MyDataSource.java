package com.yeqian.util;

import javax.sql.DataSource;
import java.io.PrintWriter;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.sql.SQLFeatureNotSupportedException;
import java.util.LinkedList;
import java.util.Properties;
import java.util.logging.Logger;

public class MyDataSource implements DataSource {
    //定义集合属性用于存放连接
    private static LinkedList<Connection> pool = new LinkedList<>();

    //在静态代码块中，为连接池初始化五个连接
    private static Properties properties = new Properties();

    public LinkedList<Connection> getDateSourcePool() {
        //读取配置文件
        try {
            properties.load(MyDataSource.class.getClassLoader().getResourceAsStream("db.properties"));
            //获得配置信息
            String driverClass = properties.getProperty("driverClassName");
            String url = properties.getProperty("url");
            String username = properties.getProperty("username");
            String password = properties.getProperty("password");
            //注册驱动
            Class.forName(driverClass);
            //获取连接,并将连接添加到集合pool中
            for (int i = 0; i <= 5; i++) {
                Connection connection = DriverManager.getConnection(url, username, password);
                pool.add(connection);
            }
            return pool;
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public Connection getConnection() throws SQLException {
        try {
            //判断连接池中是否存在Connection可供使用
            if (pool != null && pool.size() > 0) {
                //池中有连接可用
                return pool.removeFirst();
            }
            //若无连接可用则等待其他线程使用完后再执行
            Thread.sleep(100);
            return getConnection();
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }
    }


    @Override
    public Connection getConnection(String username, String password) throws SQLException {
        return null;
    }

    @Override
    public PrintWriter getLogWriter() throws SQLException {
        return null;
    }

    @Override
    public void setLogWriter(PrintWriter out) throws SQLException {

    }

    @Override
    public void setLoginTimeout(int seconds) throws SQLException {

    }

    @Override
    public int getLoginTimeout() throws SQLException {
        return 0;
    }

    @Override
    public <T> T unwrap(Class<T> iface) throws SQLException {
        return null;
    }

    @Override
    public boolean isWrapperFor(Class<?> iface) throws SQLException {
        return false;
    }

    @Override
    public Logger getParentLogger() throws SQLFeatureNotSupportedException {
        return null;
    }
}
