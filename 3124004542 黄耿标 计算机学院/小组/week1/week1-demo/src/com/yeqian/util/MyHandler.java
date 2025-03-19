package com.yeqian.util;

import java.sql.ResultSet;

@FunctionalInterface
public interface MyHandler<T> {
    T handle(ResultSet rs) throws Exception;
}
