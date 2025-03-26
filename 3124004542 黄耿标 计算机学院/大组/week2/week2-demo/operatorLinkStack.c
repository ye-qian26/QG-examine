#include "operatorLinkStack.h"
//初始化链栈
void OinitStack(OperatorLinkStack* s) {
	s->top = NULL;
	s->count = 0;
}

//判断链栈是否为空
bool OisEmpty(OperatorLinkStack* s) {
	return s->top == NULL;
}

//入栈操作
void Opush(OperatorLinkStack* s, char data) {
	OperatorStackNode* newNode = (OperatorStackNode*)malloc(sizeof(OperatorStackNode));
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
char Opop(OperatorLinkStack* s) {
	if (OisEmpty(s)) {
		printf("链栈为空，无法出栈\n");
		return -1;
	}
	OperatorStackNode* p = s->top;
	char data = p->data;
	s->top = p->next;
	s->count--;
	free(p);
	return data;
}

//获取栈顶元素
char OgetTop(OperatorLinkStack* s) {
	if (OisEmpty(s)) {
		printf("链栈为空，无法获取栈顶元素\n");
		return NULL;
	}
	char data = s->top->data;
	return data;
}

//摧毁链栈
void OdestoryStack(OperatorLinkStack* s) {
	while (!OisEmpty(s)) {
		Opop(s);
	}
}