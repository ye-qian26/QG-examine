#include<stdio.h>
#include<malloc.h>
#include<stdbool.h>
#include "binary_sort_tree.h"

//������ջ�ڵ�
typedef struct StackNode {
	Node* node;              //������
	int isVisit;            //�ýڵ��Ƿ񱻷��ʹ��ı��
	struct StackNode* next; //ָ����
}StackNode, *LinkNodePtr;


//������ջ�ṹ
typedef struct LinkStack
{
	LinkNodePtr top;	  //ջ��ָ��
} LinkStack;

//��ʼ����ջ
void initStack(LinkStack* s);

//�ж���ջ�Ƿ�Ϊ��
bool isEmpty(LinkStack* s);

//��ջ����
void push(LinkStack* s, Node* node);

//��ջ����
Node* pop(LinkStack* s);

//�ǵݹ��������
void preorderWithStack(Node* root);

//�ǵݹ��������
void inorderWithStack(Node* root);

//��ȡջ��Ԫ�ر��
int getTopIsVisit(LinkStack* s);

//����ջ��Ԫ�ر��
void setTopIsVisit(LinkStack* s, int visit);

//�ǵݹ�������
void postorderWithStack(Node* root);


//�������нڵ�
typedef struct QueueNode {
	Node* node;
	struct QueueNode* next;
}QueueNode;
//�������нṹ
typedef struct Queue {
	QueueNode* front;  //��һ���ڵ�
	QueueNode* rear;   //���һ���ڵ�
}Queue;

//��ʼ������
void initQueue(Queue* q);

//�ж϶����Ƿ�Ϊ��
bool isQueueEmpty(Queue* q);

//���
void enqueue(Queue* q, Node* node);

//����
Node* dequeue(Queue* q);

//��α���
void levelorder(Node* root);