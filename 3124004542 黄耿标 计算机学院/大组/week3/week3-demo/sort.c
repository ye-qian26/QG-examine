
#include"sort.h"

// ��ӡ���麯��
void printArray(int arr[], int n) {
	int i;
	for (i = 0; i < n; i++)
		printf("%d ", arr[i]);
	printf("\n");
}

//��������
void InsertSort(int arr[], int n) {
	int key, i, j;
	for (i = 1; i < n; i++) {
		key = arr[i];
		j = i - 1;

		//����key�����������
		while (j >= 0 && arr[j] > key) {
			arr[j + 1] = arr[j];
			j = j - 1;
		}

		arr[j + 1] = key;
	}
}

//�鲢����
//�ϲ�����
void Merge(int arr[], int l, int m, int r) {
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	//��������ʱ����
	int* L = (int*)malloc(n1 * sizeof(int));
	int* R = (int*)malloc(n2 * sizeof(int));

	if (L == NULL || R == NULL) {
		printf("�ڴ����ʧ��\n");
		return;
	}
	//����ʱ���鸳ֵ
	for (i = 0; i < n1; i++) {
		L[i] = arr[l + i];
	}
	for (j = 0; j < n2; j++) {
		R[j] = arr[m + 1 + j];
	}


	i = 0;
	j = 0;
	k = l;
	//�ϲ�����
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

	//����ʣ�µ���
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
//����ݹ�
void MergeSort(int arr[], int l, int r) {
	if (l < r) {
		//�õ��м��
		int m = (l + r) / 2;

		//�ݹ�
		MergeSort(arr, l, m);
		MergeSort(arr, m + 1, r);

		//�ϲ�����
		Merge(arr, l, m, r);
	}
}



//��������
//��������Ԫ�صĺ���
void Swap(int* a, int* b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}
//�����������������Ϊ������
int Partition(int  arr[], int l, int r) {
	int pivot = arr[r];
	int j;
	int i = l;

	//��������������
	for (j = l; j < r; j++) {
		if (arr[j] < pivot) {
			Swap(&arr[i], &arr[j]);
			i++;
		}
	}
	Swap(&arr[i], &arr[r]);
	return i;
}
//����������
void QuickSort(int arr[], int l, int r) {
	if (l < r) {
		int pi = Partition(arr, l, r);

		QuickSort(arr, l, pi - 1);
		QuickSort(arr, pi + 1, r);
	}
}



//��������
void CountSort(int arr[], int n) {
	//������鳤��С��2��ֱ����������
	if (n < 2) return;
	
	//�ҳ������е����ֵ����Сֵ
	int max = arr[0], min = arr[0];
	for (int i = 0; i < n; i++) {
		if (arr[i] > max) {
			max = arr[i];
		} 
		if (arr[i] < min) {
			min = arr[i];
		}
	}

	//����һ����������
	int range = max - min + 1;
	int* count = (int*)calloc(range, sizeof(int));

	if (count == NULL) {
		printf("�ڴ����ʧ��\n");
		return;
	}
	//Ϊ�������鸳ֵ������ÿ��Ԫ�س��ֵĴ���
	for (int i = 0; i < n; i++) {
		count[arr[i] - min]++;
	}

	//�����ۻ�����
	for (int i = 1; i < range; i++) {
		count[i] += count[i - 1];
	}

	//����һ����ʱ�����������������
	int* tmp = (int*)malloc(n * sizeof(int));
	if (tmp == NULL) {
		printf("�ڴ����ʧ��\n");
		free(count);
		return;
	}

	//���ű���ԭʼ���飬�Ա�֤������ȶ���
	for (int i = n - 1; i >= 0; i--) {
		int index = count[arr[i] - min] - 1;
		tmp[index] = arr[i];
		count[arr[i] - min]--;
	}

	//����ʱ���鸴�Ƶ�ԭ����
	for (int i = 0; i < n; i++) {
		arr[i] = tmp[i];
	}

	// �ͷŶ�̬������ڴ�
	free(count);
	free(tmp);
}



//������������
//�������򣬰���ָ��λ����������
void CountingSort(int arr[], int n, int exp) {
	//������鳤��С��2����������
	if (n < 2) return;

	//������������
	int count[10] = { 0 };

	//Ϊ�������鸳ֵ������ָ��λ��Ԫ�س��ֵĴ���
	for (int i = 0; i < n; i++) {
		count[(arr[i] / exp) % 10]++;
	}

	//�����ۻ�����
	for (int i = 1; i < 10; i++) {
		count[i] += count[i - 1];
	}

	//������ʱ����
	int* tmp = (int*)malloc(n * sizeof(int));
	if (tmp == NULL) {
		printf("�ڴ����ʧ��\n");
		return;
	}

	//����ʱ���鸳ֵ����������
	for (int i = n - 1; i >= 0; i--) {
		tmp[count[(arr[i] / exp) % 10] - 1] = arr[i];
		count[(arr[i] / exp) % 10]--;
	}

	//����ʱ���鸳ֵ��ԭʼ����
	for (int i = 0; i < n; i++) {
		arr[i] = tmp[i];
	}
	free(tmp);
}
//������������
void RadixCountSort(int arr[], int n) {
	//�ҵ����ֵ
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




//���Ժ���
//�ڲ�ͬ�Ĵ��������Ĳ��Ժ���
void test(int dataSize) {
	//����һ����������
	int* arr = (int*)malloc(dataSize * sizeof(int));
	if (arr == NULL) {
		printf("�ڴ����ʧ��\n");
		return;
	}

	//Ϊ�������鸳���ֵ
	srand(time(NULL));
	for (int i = 0; i < dataSize; i++) {
		arr[i] = rand() % 1000;  //�õ�0��999�������
	}

	//����һ����ʱ����
	int* tmp = (int*)malloc(dataSize * sizeof(int));
	if (tmp == NULL) {
		printf("�ڴ����ʧ��\n");
		return;
	}
	CopyArray(tmp, arr, dataSize);
	clock_t start = clock(); //��ʼʱ��
	InsertSort(tmp, dataSize);
	clock_t diff = clock() - start; //����ʱ��
	printf("��������Ϊ %d ʱ������ ��������ʱ��%d ms\n", dataSize, diff);

	CopyArray(tmp, arr, dataSize);
	start = clock(); //��ʼʱ��
	MergeSort(tmp, 0, dataSize - 1);
	diff = clock() - start; //����ʱ��
	printf("��������Ϊ %d ʱ���鲢 ��������ʱ��%d ms\n", dataSize, diff);

	CopyArray(tmp, arr, dataSize);
	start = clock(); //��ʼʱ��
	QuickSort(tmp, 0, dataSize - 1);
	diff = clock() - start; //����ʱ��
	printf("��������Ϊ %d ʱ������ ��������ʱ��%d ms\n", dataSize, diff);

	CopyArray(tmp, arr, dataSize);
	start = clock(); //��ʼʱ��
	CountSort(tmp, dataSize);
	diff = clock() - start; //����ʱ��
	printf("��������Ϊ %d ʱ������ ��������ʱ��%d ms\n", dataSize, diff);

	CopyArray(tmp, arr, dataSize);
	start = clock(); //��ʼʱ��
	RadixCountSort(tmp, dataSize);
	diff = clock() - start; //����ʱ��
	printf("��������Ϊ %d ʱ���������� ��������ʱ��%d ms\n", dataSize, diff);

	free(arr);
}
//�ڴ���С�������Ĳ��Ժ���
void test2(int k) {
	//����һ����������
	int* arr = (int*)malloc(100 * sizeof(int));
	if (arr == NULL) {
		printf("�ڴ����ʧ��\n");
		return;
	}

	//Ϊ�������鸳���ֵ
	srand(time(NULL));
	for (int i = 0; i < 100; i++) {
		arr[i] = rand() % 1000;  //�õ�0��999�������
	}
	//����һ����ʱ����
	int tmp[100];

	clock_t start = clock(); //��ʼʱ��
	for (int i = 0; i < 100 * k; i++) {
		CopyArray(tmp, arr, 100);
		InsertSort(tmp, 100);
	}
	clock_t diff = clock() - start; //����ʱ��
	printf("��������Ϊ100���������Ϊ%dʱ��������������ʱ��%d ms\n", 100 * k, diff);

	start = clock(); //��ʼʱ��
	for (int i = 0; i < 100 * k; i++) {
		CopyArray(tmp, arr, 100);
		MergeSort(tmp, 0, 100 - 1);
	}
	diff = clock() - start; //����ʱ��
	printf("��������Ϊ100���������Ϊ%dʱ���鲢��������ʱ��%d ms\n", 100 * k, diff);

	start = clock(); //��ʼʱ��
	for (int i = 0; i < 100 * k; i++) {
		CopyArray(tmp, arr, 100);
		QuickSort(tmp, 0, 100 - 1);
	}
	diff = clock() - start; //����ʱ��
	printf("��������Ϊ100���������Ϊ%dʱ��������������ʱ��%d ms\n", 100 * k, diff);

	start = clock(); //��ʼʱ��
	for (int i = 0; i < 100 * k; i++) {
		CopyArray(tmp, arr, 100);
		CountSort(tmp, 100);
	}
	diff = clock() - start; //����ʱ��
	printf("��������Ϊ100���������Ϊ%dʱ��������������ʱ��%d ms\n", 100 * k, diff);

	start = clock(); //��ʼʱ��
	for (int i = 0; i < 100 * k; i++) {
		CopyArray(tmp, arr, 100);;
		RadixCountSort(tmp, 100);
	}
	diff = clock() - start; //����ʱ��
	printf("��������Ϊ100���������Ϊ%dʱ������������������ʱ��%d ms\n", 100 * k, diff);
}

//��������
void CopyArray(int tmp[], int arr[], int n) {
	for (int i = 0; i < n; i++) {
		tmp[i] = arr[i];
	}
}
int main() {
	//����1
	int dataSize[3] = { 10000, 50000, 200000 };
	 printf("��ͬ�������ڲ�ͬ�Ĵ���������������ʱ���£�\n");
	for (int i = 0; i < 3; i++) {
		test(dataSize[i]);
		printf("----------------------------------\n");
	}

	//����2
	int k[3] = { 100, 200, 300 };
	printf("��ͬ�������ڴ���С���ݵ�������ʱ���£�\n");
	for (int i = 0; i < 3; i++) {
		test2(k[i]);
		printf("----------------------------------\n");
	}
	return 0;
}





