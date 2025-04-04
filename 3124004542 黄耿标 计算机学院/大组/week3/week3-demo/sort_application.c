#include<stdio.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>
//打印数组
void printArray1(int arr[], int n) {
	for (int i = 0; i < n; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}
//应用题1：排序0，1，2
void Sort1(int arr[], int n) {
	int p1 = 0, p0 = 0, p2 = n - 1;
	for (p1; p1 < n; p1++) {
		
		if (arr[p1] == 0) {
			int tmp = arr[p1];
			arr[p1] = arr[p0];
			arr[p0] = tmp;
			p0++;
		}
		if (arr[p1] == 2) {
			int tmp = arr[p1];
			arr[p1] = arr[p2];
			arr[p2] = tmp;
			p2--;
			p1--;
		}
		//当p1跟p2相遇时跳出函数
		if (p1 == p2) {
			return;
		}
	}
}


//应用题2：找出第k大/小的数
int Sort2(int arr[], int left, int right, int k, int command) {
	if (command != 0 && command != 1) {
		printf("要求出错\n");
		return -1;
	}
	if (command == 0) {
		//找第k小
		while (left <= right) {
			int pivot = arr[right];
			int i = left;
			//分区
			for (int j = left; j < right; j++) {
				if (arr[j] <= pivot) {
					int tmp = arr[i];
					arr[i] = arr[j];
					arr[j] = tmp;
					i++;
				}
			}
			//交换基准与最后索引i对应的数
			int tmp = arr[i];
			arr[i] = arr[right];
			arr[right] = tmp;

			if (i == k - 1) {
				return arr[i];
			}
			else if (i > k - 1) {
				right = i - 1;
			}
			else {
				left = i + 1;
			}
		}
	}

	if (command == 1) {
		//找第k大
		while (left <= right) {
			int pivot = arr[right];
			int i = left;
			//分区
			for (int j = left; j < right; j++) {
				if (arr[j] >= pivot) {
					int tmp = arr[i];
					arr[i] = arr[j];
					arr[j] = tmp;
					i++;
				}
			}
			//交换基准与最后索引i对应的数
			int tmp = arr[i];
			arr[i] = arr[right];
			arr[right] = tmp;

			if (i == k - 1) {
				return arr[i];
			}
			else if (i > k - 1) {
				right = i - 1;
			}
			else {
				left = i + 1;
			}
		}
	}
}

//int main() {
//	int arr[30];
//	
//	//srand(time(NULL));
//	//for (int i = 0; i < 30; i++) {
//	//	arr[i] = rand() % 3;  //随机生成0，1，2
//	//}
//	//int len = sizeof(arr) / sizeof(arr[0]);
//	//printf("原始数组：\n");
//	//printArray1(arr, 30);
//
//	//Sort1(arr, 30);
//
//	//printf("排序后数组：\n");
//	//printArray1(arr, 30);
//	
//	for (int i = 0; i < 30; i++) {
//		arr[i] = rand() % 30;  //随机生成0-29
//	}
//	int len = sizeof(arr) / sizeof(arr[0]);
//	printf("原始数组：\n");
//	printArray1(arr, 30);
//	int k = 1;
//	int command = 1;
//	//int command = 0;
//	int num = Sort2(arr, 0, len - 1, k, command);
//	//printf("该数组中第 %d 小的数为：%d", k, num);
//	printf("该数组中第 %d 大的数为：%d", k, num);
//	return 0;
//}