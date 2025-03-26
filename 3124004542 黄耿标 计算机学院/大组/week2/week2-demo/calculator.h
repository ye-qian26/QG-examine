#include"dataLinkStack.h"
#include "operatorLinkStack.h"

//�ж��û������ʽ���Ƿ���Ϲ淶
bool judgeFormula(char* formula);

//���û�������ַ���תΪ�ַ�������
void split_formula(const char* formula, char str[][20], int* str_count);

//������ջ����׺���ʽת��Ϊ��׺���ʽ
void transform(char trans_str[100][20], char str[100][20], int len, int* newLen);

//�Ƚ���������ȼ�
int compare(char x, char y);

//�����׺���ʽ
double calculate(char trans_str[100][20], int len, int* isError);

//�ӷ�����
double add(double x, double y);

//��������
double sub(double x, double y);

//�˷�����
double mul(double x, double y);

//��������
double divide(double x, double y);