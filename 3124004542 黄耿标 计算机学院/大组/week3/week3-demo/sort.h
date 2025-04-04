#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

// 打印数组函数
void printArray(int arr[], int n);

//插入排序法
void InsertSort(int arr[], int n);

//归并排序法
//合并数组
void Merge(int arr[], int l, int m, int r);
//排序递归
void MergeSort(int arr[], int l, int r);

//快速排序法
//交换两个元素的函数
void Swap(int* a, int* b);
//分区函数，将数组分为两部分
int Partition(int  arr[], int l, int r);
//快速排序函数
void QuickSort(int arr[], int l, int r);

//计数排序法
void CountSort(int arr[], int n);

//基数计数排序法
//计数排序，按照指定位数进行排序
void CountingSort(int arr[], int n, int exp);
//基数计数排序
void RadixCountSort(int arr[], int n);

//测试函数
//在不同的大数据量的测试函数
void test(int dataSize);
//在大量小数据量的测试函数
void test2(int k);

//复制数组
void CopyArray(int tmp[], int arr[], int n);