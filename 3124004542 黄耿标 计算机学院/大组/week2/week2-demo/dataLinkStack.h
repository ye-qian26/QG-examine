#include<stdio.h>
#include<stdbool.h>
#include<malloc.h>
#include<string.h>
#include <stdlib.h>
//定义链栈节点结构
typedef struct DataStackNode
{
	double data;            //数据域
	struct DataStackNode* next;	  //指针域
} DataStackNode, * DataLinkStackPtr;

//定义链栈结构
typedef struct DataLinkStack
{
	DataLinkStackPtr top;	  //栈顶指针
	int count;            //栈中元素个数
} DataLinkStack;

//初始化链栈
void DinitStack(DataLinkStack* s);

//判断链栈是否为空
bool DisEmpty(DataLinkStack* s);

//入栈操作
void Dpush(DataLinkStack* s, double data);

//出栈操作
double Dpop(DataLinkStack* s);

//获取栈顶元素
double DgetTop(DataLinkStack* s);

//摧毁链栈
void DdestoryStack(DataLinkStack* s);
