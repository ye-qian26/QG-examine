#include<stdio.h>
#include<stdbool.h>
#include<malloc.h>
//������ջ�ڵ�ṹ
typedef struct StackNode
{
	int data;            //������
	struct StackNode* next;	  //ָ����
} StackNode, * LinkStackPtr;

//������ջ�ṹ
typedef struct LinkStack
{
	LinkStackPtr top;	  //ջ��ָ��
	int count;            //ջ��Ԫ�ظ���
} LinkStack;

//��ʼ����ջ
void initStack(LinkStack *s) {
	s->top = NULL;
	s->count = 0;
}

//�ж���ջ�Ƿ�Ϊ��
bool isEmpty(LinkStack* s) {
	return s->top == NULL;
}

//��ջ����
void push(LinkStack *s, int data) {
	StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
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
int pop(LinkStack* s) {
	if (isEmpty(s)) {
		printf("��ջΪ�գ��޷���ջ\n");
		return -1;
	}
	StackNode* p = s->top;
	int data = p->data;
	s->top = p->next;
	s->count--;
	free(p);
	return data;
}

//��ȡջ��Ԫ��
int getTop(LinkStack* s) {
	if (isEmpty(s)) {
		printf("��ջΪ�գ��޷���ȡջ��Ԫ��\n");
		return -1;
	}
	int data = s->top->data;
	return data;
}

//�ݻ���ջ
void destoryStack(LinkStack* s) {
	while (!isEmpty(s)) {
		pop(s);
	}
}

int main() {
	LinkStack s;
	//��ʼ����ջ
	initStack(&s);

	//��ջ
	push(&s, 1);
	push(&s, 2);
	push(&s, 3);

	printf("%d\n", s.count);

	//��ȡջ��Ԫ��
	printf("ջ��Ԫ�أ�%d\n", getTop(&s));

	//��ջ
	printf("��ջԪ�أ�%d\n", pop(&s));
	printf("��ջԪ�أ�%d\n", pop(&s));
	
	//�ݻ���ջ
	destoryStack(&s);
	return 0;
}
