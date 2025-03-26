#include "operatorLinkStack.h"
//��ʼ����ջ
void OinitStack(OperatorLinkStack* s) {
	s->top = NULL;
	s->count = 0;
}

//�ж���ջ�Ƿ�Ϊ��
bool OisEmpty(OperatorLinkStack* s) {
	return s->top == NULL;
}

//��ջ����
void Opush(OperatorLinkStack* s, char data) {
	OperatorStackNode* newNode = (OperatorStackNode*)malloc(sizeof(OperatorStackNode));
	if (newNode == NULL) {
		printf("�ڴ����ʧ��\n");
		return;
	}
	newNode->data = data;
	newNode->next = s->top;
	s->top = newNode;
	s->count++;
}

//��ջ����
char Opop(OperatorLinkStack* s) {
	if (OisEmpty(s)) {
		printf("��ջΪ�գ��޷���ջ\n");
		return -1;
	}
	OperatorStackNode* p = s->top;
	char data = p->data;
	s->top = p->next;
	s->count--;
	free(p);
	return data;
}

//��ȡջ��Ԫ��
char OgetTop(OperatorLinkStack* s) {
	if (OisEmpty(s)) {
		printf("��ջΪ�գ��޷���ȡջ��Ԫ��\n");
		return NULL;
	}
	char data = s->top->data;
	return data;
}

//�ݻ���ջ
void OdestoryStack(OperatorLinkStack* s) {
	while (!OisEmpty(s)) {
		Opop(s);
	}
}