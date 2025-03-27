package com.yeqian.mybatis;

import com.yeqian.demo.entity.User;
import com.yeqian.demo.mapper.UserMapper;
import com.yeqian.mybatis.proxy.MapperProxyFactory;

import java.util.List;

public class Test {

    public static void main(String[] args) {
        UserMapper userMapper = MapperProxyFactory.getProxy(UserMapper.class);

        //测试方法：查询。根据id查询
        List<User> users = userMapper.selectAll();
        System.out.println("所有数据：" + users);
        User user = userMapper.selectById(1);
        System.out.println(user);

        //测试方法：通过id修改相关字段
        //userMapper.updateById(2, "zhaoliu");

        //测试方法：通过id删除数据
        //userMapper.deleteById(2);

        //测试方法：添加数据
        //userMapper.add(new User(null, "yeqian", 19));
    }
}
