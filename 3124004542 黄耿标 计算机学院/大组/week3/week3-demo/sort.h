#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

// ��ӡ���麯��
void printArray(int arr[], int n);

//��������
void InsertSort(int arr[], int n);

//�鲢����
//�ϲ�����
void Merge(int arr[], int l, int m, int r);
//����ݹ�
void MergeSort(int arr[], int l, int r);

//��������
//��������Ԫ�صĺ���
void Swap(int* a, int* b);
//�����������������Ϊ������
int Partition(int  arr[], int l, int r);
//����������
void QuickSort(int arr[], int l, int r);

//��������
void CountSort(int arr[], int n);

//������������
//�������򣬰���ָ��λ����������
void CountingSort(int arr[], int n, int exp);
//������������
void RadixCountSort(int arr[], int n);

//���Ժ���
//�ڲ�ͬ�Ĵ��������Ĳ��Ժ���
void test(int dataSize);
//�ڴ���С�������Ĳ��Ժ���
void test2(int k);

//��������
void CopyArray(int tmp[], int arr[], int n);