
#include"sort.h"

// 打印数组函数
void printArray(int arr[], int n) {
	int i;
	for (i = 0; i < n; i++)
		printf("%d ", arr[i]);
	printf("\n");
}

//插入排序法
void InsertSort(int arr[], int n) {
	int key, i, j;
	for (i = 1; i < n; i++) {
		key = arr[i];
		j = i - 1;

		//将比key大的数往后移
		while (j >= 0 && arr[j] > key) {
			arr[j + 1] = arr[j];
			j = j - 1;
		}

		arr[j + 1] = key;
	}
}

//归并排序法
//合并数组
void Merge(int arr[], int l, int m, int r) {
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	//创建建临时数组
	int* L = (int*)malloc(n1 * sizeof(int));
	int* R = (int*)malloc(n2 * sizeof(int));

	if (L == NULL || R == NULL) {
		printf("内存分配失败\n");
		return;
	}
	//给临时数组赋值
	for (i = 0; i < n1; i++) {
		L[i] = arr[l + i];
	}
	for (j = 0; j < n2; j++) {
		R[j] = arr[m + 1 + j];
	}


	i = 0;
	j = 0;
	k = l;
	//合并数组
	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			arr[k] = L[i];
			i++;
		}
		else {
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	//补充剩下的数
	while (i < n1) {
		arr[k] = L[i];
		i++;
		k++;
	}
	while (j < n2) {
		arr[k] = R[j];
		j++;
		k++;
	}

	free(L);
	free(R);
}
//排序递归
void MergeSort(int arr[], int l, int r) {
	if (l < r) {
		//得到中间点
		int m = (l + r) / 2;

		//递归
		MergeSort(arr, l, m);
		MergeSort(arr, m + 1, r);

		//合并数组
		Merge(arr, l, m, r);
	}
}



//快速排序法
//交换两个元素的函数
void Swap(int* a, int* b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}
//分区函数，将数组分为两部分
int Partition(int  arr[], int l, int r) {
	int pivot = arr[r];
	int j;
	int i = l;

	//遍历数组来分区
	for (j = l; j < r; j++) {
		if (arr[j] < pivot) {
			Swap(&arr[i], &arr[j]);
			i++;
		}
	}
	Swap(&arr[i], &arr[r]);
	return i;
}
//快速排序函数
void QuickSort(int arr[], int l, int r) {
	if (l < r) {
		int pi = Partition(arr, l, r);

		QuickSort(arr, l, pi - 1);
		QuickSort(arr, pi + 1, r);
	}
}



//计数排序法
void CountSort(int arr[], int n) {
	//如果数组长度小于2，直接跳出函数
	if (n < 2) return;
	
	//找出数组中的最大值和最小值
	int max = arr[0], min = arr[0];
	for (int i = 0; i < n; i++) {
		if (arr[i] > max) {
			max = arr[i];
		} 
		if (arr[i] < min) {
			min = arr[i];
		}
	}

	//创建一个计数数组
	int range = max - min + 1;
	int* count = (int*)calloc(range, sizeof(int));

	if (count == NULL) {
		printf("内存分配失败\n");
		return;
	}
	//为计数数组赋值，计算每个元素出现的次数
	for (int i = 0; i < n; i++) {
		count[arr[i] - min]++;
	}

	//计算累积次数
	for (int i = 1; i < range; i++) {
		count[i] += count[i - 1];
	}

	//创建一个临时数组存在排序后的数组
	int* tmp = (int*)malloc(n * sizeof(int));
	if (tmp == NULL) {
		printf("内存分配失败\n");
		free(count);
		return;
	}

	//倒着遍历原始数组，以保证排序的稳定性
	for (int i = n - 1; i >= 0; i--) {
		int index = count[arr[i] - min] - 1;
		tmp[index] = arr[i];
		count[arr[i] - min]--;
	}

	//将临时数组复制到原数组
	for (int i = 0; i < n; i++) {
		arr[i] = tmp[i];
	}

	// 释放动态分配的内存
	free(count);
	free(tmp);
}



//基数计数排序法
//计数排序，按照指定位数进行排序
void CountingSort(int arr[], int n, int exp) {
	//如果数组长度小于2，跳出函数
	if (n < 2) return;

	//创建计数数组
	int count[10] = { 0 };

	//为计数数组赋值，计算指定位数元素出现的次数
	for (int i = 0; i < n; i++) {
		count[(arr[i] / exp) % 10]++;
	}

	//计算累积数组
	for (int i = 1; i < 10; i++) {
		count[i] += count[i - 1];
	}

	//创建临时数组
	int* tmp = (int*)malloc(n * sizeof(int));
	if (tmp == NULL) {
		printf("内存分配失败\n");
		return;
	}

	//给临时数组赋值排序后的数组
	for (int i = n - 1; i >= 0; i--) {
		tmp[count[(arr[i] / exp) % 10] - 1] = arr[i];
		count[(arr[i] / exp) % 10]--;
	}

	//将临时数组赋值到原始数组
	for (int i = 0; i < n; i++) {
		arr[i] = tmp[i];
	}
	free(tmp);
}
//基数计数排序
void RadixCountSort(int arr[], int n) {
	//找到最大值
	int max = arr[0];
	for (int i = 0; i < n; i++) {
		if (arr[i] > max) {
			max = arr[i];
		}
	}

	for (int exp = 1; max / exp > 0; exp *= 10) {
		CountingSort(arr, n, exp);
	}
}




//测试函数
//在不同的大数据量的测试函数
void test(int dataSize) {
	//创建一个测试数组
	int* arr = (int*)malloc(dataSize * sizeof(int));
	if (arr == NULL) {
		printf("内存分配失败\n");
		return;
	}

	//为测试数组赋随机值
	srand(time(NULL));
	for (int i = 0; i < dataSize; i++) {
		arr[i] = rand() % 1000;  //得到0到999的随机数
	}

	//创建一个临时数组
	int* tmp = (int*)malloc(dataSize * sizeof(int));
	if (tmp == NULL) {
		printf("内存分配失败\n");
		return;
	}
	CopyArray(tmp, arr, dataSize);
	clock_t start = clock(); //开始时间
	InsertSort(tmp, dataSize);
	clock_t diff = clock() - start; //运行时间
	printf("当数据量为 %d 时，插入 排序函数用时：%d ms\n", dataSize, diff);

	CopyArray(tmp, arr, dataSize);
	start = clock(); //开始时间
	MergeSort(tmp, 0, dataSize - 1);
	diff = clock() - start; //运行时间
	printf("当数据量为 %d 时，归并 排序函数用时：%d ms\n", dataSize, diff);

	CopyArray(tmp, arr, dataSize);
	start = clock(); //开始时间
	QuickSort(tmp, 0, dataSize - 1);
	diff = clock() - start; //运行时间
	printf("当数据量为 %d 时，快速 排序函数用时：%d ms\n", dataSize, diff);

	CopyArray(tmp, arr, dataSize);
	start = clock(); //开始时间
	CountSort(tmp, dataSize);
	diff = clock() - start; //运行时间
	printf("当数据量为 %d 时，计数 排序函数用时：%d ms\n", dataSize, diff);

	CopyArray(tmp, arr, dataSize);
	start = clock(); //开始时间
	RadixCountSort(tmp, dataSize);
	diff = clock() - start; //运行时间
	printf("当数据量为 %d 时，基数计数 排序函数用时：%d ms\n", dataSize, diff);

	free(arr);
}
//在大量小数据量的测试函数
void test2(int k) {
	//创建一个测试数组
	int* arr = (int*)malloc(100 * sizeof(int));
	if (arr == NULL) {
		printf("内存分配失败\n");
		return;
	}

	//为测试数组赋随机值
	srand(time(NULL));
	for (int i = 0; i < 100; i++) {
		arr[i] = rand() % 1000;  //得到0到999的随机数
	}
	//创建一个临时数组
	int tmp[100];

	clock_t start = clock(); //开始时间
	for (int i = 0; i < 100 * k; i++) {
		CopyArray(tmp, arr, 100);
		InsertSort(tmp, 100);
	}
	clock_t diff = clock() - start; //运行时间
	printf("当数据量为100，排序次数为%d时，插入排序函数用时：%d ms\n", 100 * k, diff);

	start = clock(); //开始时间
	for (int i = 0; i < 100 * k; i++) {
		CopyArray(tmp, arr, 100);
		MergeSort(tmp, 0, 100 - 1);
	}
	diff = clock() - start; //运行时间
	printf("当数据量为100，排序次数为%d时，归并排序函数用时：%d ms\n", 100 * k, diff);

	start = clock(); //开始时间
	for (int i = 0; i < 100 * k; i++) {
		CopyArray(tmp, arr, 100);
		QuickSort(tmp, 0, 100 - 1);
	}
	diff = clock() - start; //运行时间
	printf("当数据量为100，排序次数为%d时，快速排序函数用时：%d ms\n", 100 * k, diff);

	start = clock(); //开始时间
	for (int i = 0; i < 100 * k; i++) {
		CopyArray(tmp, arr, 100);
		CountSort(tmp, 100);
	}
	diff = clock() - start; //运行时间
	printf("当数据量为100，排序次数为%d时，计数排序函数用时：%d ms\n", 100 * k, diff);

	start = clock(); //开始时间
	for (int i = 0; i < 100 * k; i++) {
		CopyArray(tmp, arr, 100);;
		RadixCountSort(tmp, 100);
	}
	diff = clock() - start; //运行时间
	printf("当数据量为100，排序次数为%d时，基数计数排序函数用时：%d ms\n", 100 * k, diff);
}

//复制数组
void CopyArray(int tmp[], int arr[], int n) {
	for (int i = 0; i < n; i++) {
		tmp[i] = arr[i];
	}
}
int main() {
	//测试1
	int dataSize[3] = { 10000, 50000, 200000 };
	 printf("不同排序函数在不同的大数据量的排序用时如下：\n");
	for (int i = 0; i < 3; i++) {
		test(dataSize[i]);
		printf("----------------------------------\n");
	}

	//测试2
	int k[3] = { 100, 200, 300 };
	printf("不同排序函数在大量小数据的排序用时如下：\n");
	for (int i = 0; i < 3; i++) {
		test2(k[i]);
		printf("----------------------------------\n");
	}
	return 0;
}





