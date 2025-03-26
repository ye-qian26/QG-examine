# QG-examine
## QG考核

### 一轮

#### **【第一周】**

- week1-demo项目在com.yeqian.test包下的Test类启动即可

- 数据库内容如下：

  ```mysql
  -- 创建老师（管理员）表
  DROP TABLE
  IF EXISTS teacher;
  
  CREATE TABLE teacher (
  	id INT PRIMARY KEY auto_increment,
  	-- 主键
  	username VARCHAR (32),
  	-- 用户名
  	PASSWORD VARCHAR (32) 
      -- 密码
  );
  
  
  -- 创建学生表
  DROP TABLE
  IF EXISTS student;
  
  CREATE TABLE student (
  	id INT PRIMARY KEY auto_increment,
      -- 主键
  	NAME VARCHAR (32),
      -- 学生姓名
  	PASSWORD VARCHAR (32),
      -- 密码
  	course VARCHAR (64),
      -- 所选课程
  	tele VARCHAR (32)
      -- 手机号
  );
  
  -- 创建课程表
  DROP TABLE
  IF EXISTS course;
  
  CREATE TABLE course (
  	id INT PRIMARY KEY auto_increment,
  	-- 主键
  	NAME VARCHAR (32),
  	-- 课程名
  	STATUS INT,
  	-- 状态：1：开课  0：未开课
  	score DOUBLE,
  	-- 学分
  	student VARCHAR (64)
      -- 门下学生
  );
  
  -- 添加课程信息
  INSERT INTO course (NAME, STATUS, score)
  VALUES
  	('语文', 1, 2),
  	('数学', 0, 3),
  	('英语', 0, 3),
  	('化学', 1, 1),
  	('生物', 0, 1),
  	('物理', 0, 2);
  ```


#### 【第二周】

##### 【大组】

- **四则运算计算器**先屏蔽LinkStack.c，然后在test.c启动即可（师兄我的计算器没做到脸滚键盘不出错（还是对C不太熟..），只对一点格式做了判断，例如开头和末尾只能是数字或括号，字符串只能是数字和运算符及其他符号组成；但多个运算符合在一起，如：”++“，还是会出现问题..）

**【小组】**

- week2-demo**登录注册界面**分别为login.html 和 register.html

