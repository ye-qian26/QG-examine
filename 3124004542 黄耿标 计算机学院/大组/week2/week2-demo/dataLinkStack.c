#include"dataLinkStack.h"

//��ʼ����ջ
void DinitStack(DataLinkStack* s) {
	s->top = NULL;
	s->count = 0;
}

//�ж���ջ�Ƿ�Ϊ��
bool DisEmpty(DataLinkStack* s) {
	return s->top == NULL;
}

//��ջ����
void Dpush(DataLinkStack* s, double data) {
	DataStackNode* newNode = (DataStackNode*)malloc(sizeof(DataStackNode));
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
double Dpop(DataLinkStack* s) {
	if (DisEmpty(s)) {
		printf("��ջΪ�գ��޷���ջ\n");
		return -1;
	}
	DataStackNode* p = s->top;
	double data = p->data;
	s->top = p->next;
	s->count--;
	free(p);
	return data;
}

//��ȡջ��Ԫ��
double DgetTop(DataLinkStack* s) {
	if (DisEmpty(s)) {
		printf("��ջΪ�գ��޷���ȡջ��Ԫ��\n");
		return -1;
	}
	double data = s->top->data;
	return data;
}

//�ݻ���ջ
void DdestoryStack(DataLinkStack* s) {
	while (!DisEmpty(s)) {
		Dpop(s);
	}
}