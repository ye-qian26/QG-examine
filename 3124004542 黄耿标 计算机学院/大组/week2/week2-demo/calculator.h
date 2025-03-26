#include"dataLinkStack.h"
#include "operatorLinkStack.h"

//判断用户输入的式子是否符合规范
bool judgeFormula(char* formula);

//将用户输入的字符串转为字符串数组
void split_formula(const char* formula, char str[][20], int* str_count);

//利用链栈将中缀表达式转换为后缀表达式
void transform(char trans_str[100][20], char str[100][20], int len, int* newLen);

//比较运算符优先级
int compare(char x, char y);

//计算后缀表达式
double calculate(char trans_str[100][20], int len, int* isError);

//加法运算
double add(double x, double y);

//减法运算
double sub(double x, double y);

//乘法运算
double mul(double x, double y);

//除法运算
double divide(double x, double y);