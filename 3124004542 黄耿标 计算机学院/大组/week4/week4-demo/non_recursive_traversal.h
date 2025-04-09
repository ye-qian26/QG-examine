#include<stdio.h>
#include<malloc.h>
#include<stdbool.h>
#include "binary_sort_tree.h"

//创建链栈节点
typedef struct StackNode {
	Node* node;              //数据域
	int isVisit;            //该节点是否被访问过的标记
	struct StackNode* next; //指针域
}StackNode, *LinkNodePtr;


//定义链栈结构
typedef struct LinkStack
{
	LinkNodePtr top;	  //栈顶指针
} LinkStack;

//初始化链栈
void initStack(LinkStack* s);

//判断链栈是否为空
bool isEmpty(LinkStack* s);

//入栈操作
void push(LinkStack* s, Node* node);

//出栈操作
Node* pop(LinkStack* s);

//非递归先序遍历
void preorderWithStack(Node* root);

//非递归先序遍历
void inorderWithStack(Node* root);

//获取栈顶元素标记
int getTopIsVisit(LinkStack* s);

//设置栈顶元素标记
void setTopIsVisit(LinkStack* s, int visit);

//非递归后序遍历
void postorderWithStack(Node* root);


//创建队列节点
typedef struct QueueNode {
	Node* node;
	struct QueueNode* next;
}QueueNode;
//创建队列结构
typedef struct Queue {
	QueueNode* front;  //第一个节点
	QueueNode* rear;   //最后一个节点
}Queue;

//初始化队列
void initQueue(Queue* q);

//判断队列是否为空
bool isQueueEmpty(Queue* q);

//入队
void enqueue(Queue* q, Node* node);

//出队
Node* dequeue(Queue* q);

//层次遍历
void levelorder(Node* root);