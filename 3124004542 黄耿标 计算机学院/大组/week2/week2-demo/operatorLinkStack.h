#include<stdio.h>
#include<stdbool.h>
#include<malloc.h>
#include<string.h>
#include <ctype.h>
//�����������ջ�ڵ�ṹ
typedef struct OperatorStackNode
{
	char data;           //������
	struct StackNode* next;	  //ָ����
} OperatorStackNode, * OperatorLinkStackPtr;

//�����������ջ�ṹ
typedef struct OperatorLinkStack
{
	OperatorLinkStackPtr top;	  //ջ��ָ��
	int count;            //ջ��Ԫ�ظ���
} OperatorLinkStack;

//��ʼ����ջ
void OinitStack(OperatorLinkStack* s);

//�ж���ջ�Ƿ�Ϊ��
bool OisEmpty(OperatorLinkStack* s);

//��ջ����
void Opush(OperatorLinkStack* s, char data);

//��ջ����
char Opop(OperatorLinkStack* s);

//��ȡջ��Ԫ��
char OgetTop(OperatorLinkStack* s);

//�ݻ���ջ
void OdestoryStack(OperatorLinkStack* s);