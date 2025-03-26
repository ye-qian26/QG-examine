#include"dataLinkStack.h"

//初始化链栈
void DinitStack(DataLinkStack* s) {
	s->top = NULL;
	s->count = 0;
}

//判断链栈是否为空
bool DisEmpty(DataLinkStack* s) {
	return s->top == NULL;
}

//入栈操作
void Dpush(DataLinkStack* s, double data) {
	DataStackNode* newNode = (DataStackNode*)malloc(sizeof(DataStackNode));
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
double Dpop(DataLinkStack* s) {
	if (DisEmpty(s)) {
		printf("链栈为空，无法出栈\n");
		return -1;
	}
	DataStackNode* p = s->top;
	double data = p->data;
	s->top = p->next;
	s->count--;
	free(p);
	return data;
}

//获取栈顶元素
double DgetTop(DataLinkStack* s) {
	if (DisEmpty(s)) {
		printf("链栈为空，无法获取栈顶元素\n");
		return -1;
	}
	double data = s->top->data;
	return data;
}

//摧毁链栈
void DdestoryStack(DataLinkStack* s) {
	while (!DisEmpty(s)) {
		Dpop(s);
	}
}