//从文件中读取数据并调用函数进行排序
#include"sort.h"
//读取文件
int read(char* fileName, int** arr) {
	//打开文件
	FILE* file = fopen(fileName, "r");
	if (file == NULL) {
		printf("无法打开文件\n");
		return 0;
	}

	//从文件中读取数据
	int count = 0;
	int size = 100;
	//初定数组大小
	*arr = (int*)malloc(size * sizeof(int));
	if (*arr == NULL) {
		printf("内存分配失败\n");
		fclose(file);
		return 0;
	}

	int number;
	while (fscanf_s(file, "%d", &number) == 1) {
		//找得到数据
		if (count >= size) {
			size *= 2;
			*arr = (int*)realloc(*arr, size * sizeof(int));
			if (*arr == NULL) {
				printf("内存分配失败\n");
				fclose(file);
				return 0;
			}
		}
		
		//将数据存到数组
		(*arr)[count++] = number;
	}
	fclose(file);
	return count;
}

//测试函数
void test3(char* fileName) {
	int* arr;
	int dataSize = read(fileName, &arr);
	if (dataSize == 0) return;

	//创建临时数组
	int* tmp = (int*)malloc(dataSize * sizeof(int));
	CopyArray(tmp, arr, dataSize);
	clock_t start = clock(); //开始时间
	InsertSort(tmp, dataSize);
	clock_t diff = clock() - start; //运行时间
	printf("从文件 %s 读取出的数据量为 %d 时，插入 排序函数用时：%d ms\n", fileName, dataSize, diff);

	CopyArray(tmp, arr, dataSize);
	start = clock(); //开始时间
	MergeSort(tmp, 0, dataSize - 1);
	diff = clock() - start; //运行时间
	printf("从文件 %s 读取出的数据量为 %d 时，归并 排序函数用时：%d ms\n", fileName, dataSize, diff);

	CopyArray(tmp, arr, dataSize);
	start = clock(); //开始时间
	QuickSort(tmp, 0, dataSize - 1);
	diff = clock() - start; //运行时间
	printf("从文件 %s 读取出的数据量为 %d 时，快速 排序函数用时：%d ms\n", fileName, dataSize, diff);

	CopyArray(tmp, arr, dataSize);
	start = clock(); //开始时间
	CountSort(tmp, dataSize);
	diff = clock() - start; //运行时间
	printf("从文件 %s 读取出的数据量为 %d 时，计数 排序函数用时：%d ms\n", fileName, dataSize, diff);

	CopyArray(tmp, arr, dataSize);
	start = clock(); //开始时间
	RadixCountSort(tmp, dataSize);
	diff = clock() - start; //运行时间
	printf("从文件 %s 读取出的数据量为 %d 时，基数计数 排序函数用时：%d ms\n", fileName, dataSize, diff);
}


//int main() {
//	int dataSize[] = { 10000, 50000, 200000 };
//	int len = sizeof(dataSize) / sizeof(dataSize[0]);
//
//	for (int i = 0; i < len; i++) {
//		char fileName[20];
//		sprintf_s(fileName, sizeof(fileName),  "data_%d.txt", dataSize[i]);
//
//		test3(fileName);
//		printf("-------------------------------------\n");
//	}
//	return 0;
//}




