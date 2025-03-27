# 学习笔记【手写Mybatis框架】

## 【思路】

- mapper代理 --> 获取注解得到原始sql语句 -->  解析sql语句 --> 设置参数 --> 获取结果

### 1.mapper代理

- mapper代理接口

  ```java
  public interface UserMapper {
  
      @Select("select * from tb_user")
      List<User> selectAll();
  
      @Select("select * from tb_user where id = #{id}")
      User selectById(@Param("id")int id);
  
      @Update("update tb_user set name = #{name} where id = #{id}")
      void updateById(@Param("id") int id, @Param("name") String name);
  
      @Delete("delete from tb_user where id = #{id}")
      void deleteById(@Param("id") int id);
  
      @Insert("insert into tb_user values (null, #{name}, #{age})")
      void add(User user);
  
  }
  ```

  

- 设置MapperProxy代理类并继承Invocation接口重写invoke方法

  ``` java
  public class MapperProxy implements InvocationHandler {
      @Override
      public Object invoke(Object proxy, Method method, Object[] args) throws Throwable {
          //重写invoke方法
          ...
          return null;
      }
      
      //获取连接
      public static Connection getConnection() {
          try {
              //获取连接
              String url = "jdbc:mysql://127.0.0.1:3306/db2?useSSL=false&useServerPrepStmts=true";
              String username = "root";
              String password = "qnbz7089yq";
              Connection connection = DriverManager.getConnection(url,username,password);
              return connection;
          } catch (Exception e) {
              throw new RuntimeException(e);
          }
      }
  }
  ```

  

- 设置MapperProxyFactory代理来得到代理类

  ```java
  public class MapperProxyFactory {
      /**
       * 拿到代理类
       */
      public static <T> T  getProxy(Class<T> mapperClass) {
  		//返回代理接口
          return (T) Proxy.newProxyInstance(mapperClass.getClassLoader(), new Class[]{mapperClass}, new MapperProxy());
  
      }
  }
  
  ```

  

### 2.获取注解并得到原始sql语句

- 获取方法的注解并得到其属性value

  ```java
  @Override
  public Object invoke(Object proxy, Method method, Object[] args) throws Throwable {
      //重写invoke方法
      //1.获取Connection
      Connection connection = MapperProxy.getConnection();
  
      //获取注解
      Annotation[] annotations = method.getAnnotations();
      Annotation annotation = annotations[0];
      //对注解的不同进行if语句判断
      if (annotation instanceof Select) {
          //如果sql语句是Select语句
          //获取注解,原始sql语句
          Select select = method.getAnnotation(Select.class);
          String originalSql = select.value();
          ...
      }
      else if (annotation instanceof Update) {
          //如果sql语句是Update语句
          //获取注解,原始sql语句
          Select select = method.getAnnotation(Update.class);
          String originalSql = select.value();
          ...
      }
      else if (annotation instanceof Insert) {
          //如果sql语句是Insert语句
          //获取注解,原始sql语句
          Select select = method.getAnnotation(Insert.class);
          String originalSql = select.value();
          ...
      }
      else if (annotation instanceof Delete) {
          //如果sql语句是Delete语句
          //获取注解,原始sql语句
          Select select = method.getAnnotation(Delete.class);
          String originalSql = select.value();
          ...
      }
      return null;
  }
  ```

  

### 3.解析sql语句（#{} --> ?）

- 前置：标记处理器接口及其实现类，带有参数集合的标记处理器

  ```java
  //标记处理器接口
  public interface TokenHandler {
      String handleToken(String content);
  }
  
  /**
   * 所需参数集合处理器
   */
  public class ParameterMappingTokenHandler implements TokenHandler {
      //List集合用来放所需参数
      private List<String> parameterMappings = new ArrayList<String>();
  
      public List<String> getParameterMappings() {
          return parameterMappings;
      }
  
      //重写handleToken方法
      @Override
      public String handleToken(String content) {
          parameterMappings.add(content);
          return "?";
      }
  }
  
  public class GenericTokenParser {
      private String openToken; //开始标记
      private String closeToken; //结束标记
      private TokenHandler tokenHandler;//标记处理器
  
      //构造器
      public GenericTokenParser(String openToken, String closeToken, TokenHandler tokenHandler) {
          this.openToken = openToken;
          this.closeToken = closeToken;
          this.tokenHandler = tokenHandler;
      }
  
      //解析方法
      public String parse(String text) {
          // select * from tb_user where id = #{id} and name = #{name}
          StringBuilder result = new StringBuilder();
          //获取内容的字符数组
          char[] textChar = text.toCharArray();
          //标记点
          int offset = 0;
          int start = text.indexOf(this.openToken);
          while (start > -1) {
              //存在开始标记
              int end = text.indexOf(this.closeToken, start);
              if (end > -1) {
                  //存在结束标记
                  result.append(textChar, offset, start - offset);
                  offset = start + this.openToken.length();
                  String paramName = new String(textChar, offset, end - offset);
                  //调用相关tokenHandler处理器，并传入每次解析出来的参数名放到parameterMappings中
                  result.append(tokenHandler.handleToken(paramName));
                  offset = end + this.closeToken.length();
              } else {
                  //不存在结束标记
                  result.append(textChar, offset, text.length() - offset);
                  offset = text.length();
              }
              start = text.indexOf(this.openToken, offset);
          }
  
          //如果标记点位置小于内容长度，将result补齐
          if (offset < text.length()) {
              result.append(textChar, offset, text.length() - offset);
          }
          return result.toString();
      }
  }
  ```



### 4.设置参数

- 前置：字段类型处理器接口及所需实现类

  ```java
  /**
   * 字段类型处理器接口
   * @param <T>
   */
  public interface TypeHandler<T> {
  
      void setParameter(PreparedStatement ps, int i , T value) throws SQLException;
  
      T getResult(ResultSet rs, String columnName) throws SQLException;
  }
  
  
  /**
   * Integer 字段类型处理器实现类
   */
  public class IntegerTypeHandler implements TypeHandler<Integer> {
      @Override
      public void setParameter(PreparedStatement ps, int i, Integer value) throws SQLException {
          ps.setInt(i, value);
      }
  
      @Override
      public Integer getResult(ResultSet rs, String columnName) throws SQLException {
          return rs.getInt(columnName);
      }
  }
  
  /**
   * String 字段类型处理器实现类
   */
  public class StringTypeHandler implements TypeHandler<String> {
      @Override
      public void setParameter(PreparedStatement ps, int i, String value) throws SQLException {
          ps.setString(i, value);
      }
  
      @Override
      public String getResult(ResultSet rs, String columnName) throws SQLException {
          return rs.getString(columnName);
      }
  }
  ```

  

- 将设置参数封装成一个方法

  ```java
  public class MapperProxy implements InvocationHandler {
      //Map集合用来存放类与其对应的字段Handler处理器
      private static Map<Class, TypeHandler> typeHandlerMap = new HashMap<>();
  
      //调用无参构造器时添加相关Handler处理器
      static{
          //添加相关处理器
          typeHandlerMap.put(Integer.class, new IntegerTypeHandler());
          typeHandlerMap.put(String.class, new StringTypeHandler());
          try {
              //注册驱动
              Class.forName("com.mysql.jdbc.Driver");
          } catch (ClassNotFoundException e) {
              throw new RuntimeException(e);
          }
      }
      @Override
      public Object invoke(Object proxy, Method method, Object[] args) throws Throwable {
          //重写invoke方法
          ...
          return null;
      }
      
      //解析sql并设置参数（该方法适用于Select，Update，Delete，但不适用于Insert）
      private PreparedStatement getPreparedStatement(Method method, Object[] args, String originalSql, Connection connection) throws SQLException {
          //1.解析sql   #{} -> ?
          ParameterMappingTokenHandler tokenHandler = new ParameterMappingTokenHandler();
          String sql = new GenericTokenParser("#{", "}", tokenHandler).parse(originalSql);
          
          //2.获取所需参数集合
          List<String> parameterMappings = tokenHandler.getParameterMappings();
  
          //获取PreparedStatement对象
          PreparedStatement ps = connection.prepareStatement(sql);
  
          //3.Map集合用来装参数名和对应的值
          Map<String, Object> paramValuesMap = new HashMap<>();
  
          //得到方法的所有参数
          Parameter[] parameters = method.getParameters();
          for (int i = 0; i < parameters.length; i++) {
              Parameter parameter = parameters[i];
              //获取Param注解
              Param param = parameter.getAnnotation(Param.class);
              //得到Param注解的属性来获取参数名
              String paramName = param.value();
              //将参数名和对应值放入paramValuesMap
              paramValuesMap.put(paramName, args[i]);
          }
  
          //4.为sql设置参数值
          for (int i = 0; i < parameterMappings.size(); i++) {
              //得到所需参数名
              String paramName = parameterMappings.get(i);
              //得到所需参数名的对应值
              Object value = paramValuesMap.get(paramName);
              //通过传入对应参数类型来获取对应字段类型处理器来设置参数
              this.typeHandlerMap.get(value.getClass()).setParameter(ps, i + 1, value);
          }
          return ps;
      }
  }
  ```

  

### 5.获取结果

- 四种不同注解对应不同处理方法

- **Select**

  ```java
  if (annotation instanceof Select) {
      //如果注解是Select
      //2.获取注解,原始sql语句
      Select select = method.getAnnotation(Select.class);
      //得到原始sql
      String originalSql = select.value(); 
      
      //调用方法获取PreparedStatement对象（已解析sql并设置好参数）
      PreparedStatement ps = getPreparedStatement(method, args, originalSql, connection);
  
      //2.处理结果，获取ResultSet结果对象
      ResultSet rs = ps.executeQuery();
      
      //获取返回值类型（如果是list需得到其所指定泛型)，用来创建对应实体类
      Class resultType = null;
      Type type = method.getGenericReturnType();
      if (type instanceof Class){
          //不是泛型
          resultType = (Class)type;
      } else if(type instanceof ParameterizedType){
          //是泛型
          Type[] actualTypeArguments = ((ParameterizedType) type).getActualTypeArguments();
          resultType = (Class)actualTypeArguments[0];
      }
  
      //得到ResultSet遍历的字段
      ResultSetMetaData metaData = rs.getMetaData();
      List<String> columnNames = new ArrayList<>();
      for (int i = 0; i < metaData.getColumnCount(); i++) {
          columnNames.add(metaData.getColumnName(i + 1));
      }
  
      //3.Map集合装字段名和对应实体类的set方法
      Map<String, Method> methodMap = new HashMap<>();
      for (Method declaredMethod : resultType.getDeclaredMethods()) {
          String declaredMethodName = declaredMethod.getName();
          if (declaredMethodName.startsWith("set")) {
              //得到所有set方法名的后部分
              String methodName = declaredMethodName.substring(3);
              //将该名字的首字母小写
              methodName = methodName.substring(0, 1).toLowerCase() + methodName.substring(1);
              //将字段名和对应set方法放入methodMap集合中
              methodMap.put(methodName, declaredMethod);
          }
      }
  
      //得到实体类
      Object object = resultType.newInstance();
  
      //4.处理结果
      List<Object> lists = new ArrayList<>();
      while (rs.next()) {
          for (int j = 0; j < columnNames.size(); j++) {
              //得到ResultSet遍历到的字段名
              String columnName = columnNames.get(j);
              //得到对应方法
              Method setMethod = methodMap.get(columnName);
              //得到set方法的参数类型
              Class<?> clazz = setMethod.getParameterTypes()[0];
              //通过传入参数类型来获取对应字段类型处理器来实行set方法
              setMethod.invoke(object, this.typeHandlerMap.get(clazz).getResult(rs, columnName));
          }
          //添加到List集合
          lists.add(object);
      }
      Object result = null;
      //判断返回值类型是List还是实体类
      if (method.getReturnType().equals(List.class)) {
          //如果是List集合
          result = lists;
      } else {
          //如果是实体类
          result = lists.get(0);
      }
  
      //5.释放资源
      ps.close();
      rs.close();
      connection.close();
      return result;
  } 
  ```

  

- **Update**

  ```java
  else if (annotation instanceof Update){
      //如果是Update
      Update update = method.getAnnotation(Update.class);
      //得到原始sql
      String originalSql = update.value();
      //1.调用方法获取PreparedStatement对象（已解析sql并设置参数）
      PreparedStatement ps = getPreparedStatement(method, args, originalSql, connection);
      int count = ps.executeUpdate();
      if(count > 0){
          System.out.println("修改成功！");
      }
      //2.释放资源
      ps.close();
      connection.close();
  } 
  ```

  

- **Delete**

  ```java
  else if(annotation instanceof Delete){
      //如果是Delete
      Delete delete = method.getAnnotation(Delete.class);
      //得到原始sql
      String originalSql = delete.value();
      //1.调用方法获取PreparedStatement对象（已解析sql并设置参数）
      PreparedStatement ps = getPreparedStatement(method, args, originalSql, connection);
      int count = ps.executeUpdate();
      if(count > 0){
          System.out.println("删除成功！");
      }
      //2.释放资源
      ps.close();
      connection.close();
  }
  ```

  

- **Insert**

  因Insert相关方法一般传入的参数类型是一个实体类，所以不能直接调用getPrepardStatement方法

  ```java
  else if(annotation instanceof Insert){
      //如果是Insert
      Insert insert = method.getAnnotation(Insert.class);
      //得到原始sql
      String originalSql = insert.value();
  
      //1.获取返回类型
      Class<?>[] parameterTypes = method.getParameterTypes();
      Class<?> parameterType = parameterTypes[0];
      if(parameterType.isPrimitive()){
          //2.如果参数类型是基本类型，按原来设置参数方式执行
          PreparedStatement ps = getPreparedStatement(method, args, originalSql, connection);
          int count = ps.executeUpdate();
          if(count > 0){
              System.out.println("添加成功！");
          }
          ps.close();
          connection.close();
      } else {
          //2.如果参数类型是实体类
          //3.解析sql   #{} -> ?
          ParameterMappingTokenHandler tokenHandler = new ParameterMappingTokenHandler();
          String sql = new GenericTokenParser("#{", "}", tokenHandler).parse(originalSql);
          PreparedStatement ps = connection.prepareStatement(sql);
          
          //4.获得用户传入的实体类参数
          Object arg = args[0];
          //得到实体类所有字段名
          Field[] fields = parameterType.getDeclaredFields();
          
          //5.设置参数
          for (int i = 0; i < fields.length; i++) {
              //跳过id字段
              if (i > 0){
                  //得到字段
                  Field field = fields[i];
                  field.setAccessible(true);
                  //获取字段的值
                  Object value = field.get(arg);
                  //设置参数
                  this.typeHandlerMap.get(value.getClass()).setParameter(ps, i, value);
              }
          }
          int count = ps.executeUpdate();
          if(count > 0){
              System.out.println("添加成功！");
          }
          //6.释放资源
          ps.close();
          connection.close();
      }
  } 
  ```

  

## 【学习收获】

- 通过尝试手写mybatis框架，对注解和反射的使用更加熟悉，同时也对mybatis框架的基本实现思路有了理解，更加熟悉了Handler处理器的使用思路
- 通过解析sql语句提高了对于相关字符串的处理能力和思路
- 通过设置参数和获取结果这两方面也加深了我对字段类型处理器TypeHandler的理解