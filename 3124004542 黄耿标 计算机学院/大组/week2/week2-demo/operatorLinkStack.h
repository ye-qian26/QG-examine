#include<stdio.h>
#include<stdbool.h>
#include<malloc.h>
#include<string.h>
#include <ctype.h>
//定义运算符链栈节点结构
typedef struct OperatorStackNode
{
	char data;           //数据域
	struct StackNode* next;	  //指针域
} OperatorStackNode, * OperatorLinkStackPtr;

//定义运算符链栈结构
typedef struct OperatorLinkStack
{
	OperatorLinkStackPtr top;	  //栈顶指针
	int count;            //栈中元素个数
} OperatorLinkStack;

//初始化链栈
void OinitStack(OperatorLinkStack* s);

//判断链栈是否为空
bool OisEmpty(OperatorLinkStack* s);

//入栈操作
void Opush(OperatorLinkStack* s, char data);

//出栈操作
char Opop(OperatorLinkStack* s);

//获取栈顶元素
char OgetTop(OperatorLinkStack* s);

//摧毁链栈
void OdestoryStack(OperatorLinkStack* s);