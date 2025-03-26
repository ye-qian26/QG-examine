#include<stdio.h>
#include<stdbool.h>
#include<malloc.h>
//定义链栈节点结构
typedef struct StackNode
{
	int data;            //数据域
	struct StackNode* next;	  //指针域
} StackNode, * LinkStackPtr;

//定义链栈结构
typedef struct LinkStack
{
	LinkStackPtr top;	  //栈顶指针
	int count;            //栈中元素个数
} LinkStack;

//初始化链栈
void initStack(LinkStack *s) {
	s->top = NULL;
	s->count = 0;
}

//判断链栈是否为空
bool isEmpty(LinkStack* s) {
	return s->top == NULL;
}

//入栈操作
void push(LinkStack *s, int data) {
	StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
	if (newNode == NULL) {
		printf("内存分配失败\n");
		return;
	}
	newNode->data = data;
	newNode->next = s->top;
	s->top = newNode;
	s->count++;
}

//出栈操作
int pop(LinkStack* s) {
	if (isEmpty(s)) {
		printf("链栈为空，无法出栈\n");
		return -1;
	}
	StackNode* p = s->top;
	int data = p->data;
	s->top = p->next;
	s->count--;
	free(p);
	return data;
}

//获取栈顶元素
int getTop(LinkStack* s) {
	if (isEmpty(s)) {
		printf("链栈为空，无法获取栈顶元素\n");
		return -1;
	}
	int data = s->top->data;
	return data;
}

//摧毁链栈
void destoryStack(LinkStack* s) {
	while (!isEmpty(s)) {
		pop(s);
	}
}

int main() {
	LinkStack s;
	//初始化链栈
	initStack(&s);

	//入栈
	push(&s, 1);
	push(&s, 2);
	push(&s, 3);

	printf("%d\n", s.count);

	//获取栈顶元素
	printf("栈顶元素：%d\n", getTop(&s));

	//出栈
	printf("出栈元素：%d\n", pop(&s));
	printf("出栈元素：%d\n", pop(&s));
	
	//摧毁链栈
	destoryStack(&s);
	return 0;
}
