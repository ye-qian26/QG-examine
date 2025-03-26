#include<stdio.h>
#include<stdbool.h>
#include<malloc.h>
#include<string.h>
#include <stdlib.h>
//������ջ�ڵ�ṹ
typedef struct DataStackNode
{
	double data;            //������
	struct DataStackNode* next;	  //ָ����
} DataStackNode, * DataLinkStackPtr;

//������ջ�ṹ
typedef struct DataLinkStack
{
	DataLinkStackPtr top;	  //ջ��ָ��
	int count;            //ջ��Ԫ�ظ���
} DataLinkStack;

//��ʼ����ջ
void DinitStack(DataLinkStack* s);

//�ж���ջ�Ƿ�Ϊ��
bool DisEmpty(DataLinkStack* s);

//��ջ����
void Dpush(DataLinkStack* s, double data);

//��ջ����
double Dpop(DataLinkStack* s);

//��ȡջ��Ԫ��
double DgetTop(DataLinkStack* s);

//�ݻ���ջ
void DdestoryStack(DataLinkStack* s);
