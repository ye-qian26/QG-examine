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

  
