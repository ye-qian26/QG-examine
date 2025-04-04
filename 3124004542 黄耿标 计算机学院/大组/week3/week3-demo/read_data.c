//���ļ��ж�ȡ���ݲ����ú�����������
#include"sort.h"
//��ȡ�ļ�
int read(char* fileName, int** arr) {
	//���ļ�
	FILE* file = fopen(fileName, "r");
	if (file == NULL) {
		printf("�޷����ļ�\n");
		return 0;
	}

	//���ļ��ж�ȡ����
	int count = 0;
	int size = 100;
	//���������С
	*arr = (int*)malloc(size * sizeof(int));
	if (*arr == NULL) {
		printf("�ڴ����ʧ��\n");
		fclose(file);
		return 0;
	}

	int number;
	while (fscanf_s(file, "%d", &number) == 1) {
		//�ҵõ�����
		if (count >= size) {
			size *= 2;
			*arr = (int*)realloc(*arr, size * sizeof(int));
			if (*arr == NULL) {
				printf("�ڴ����ʧ��\n");
				fclose(file);
				return 0;
			}
		}
		
		//�����ݴ浽����
		(*arr)[count++] = number;
	}
	fclose(file);
	return count;
}

//���Ժ���
void test3(char* fileName) {
	int* arr;
	int dataSize = read(fileName, &arr);
	if (dataSize == 0) return;

	//������ʱ����
	int* tmp = (int*)malloc(dataSize * sizeof(int));
	CopyArray(tmp, arr, dataSize);
	clock_t start = clock(); //��ʼʱ��
	InsertSort(tmp, dataSize);
	clock_t diff = clock() - start; //����ʱ��
	printf("���ļ� %s ��ȡ����������Ϊ %d ʱ������ ��������ʱ��%d ms\n", fileName, dataSize, diff);

	CopyArray(tmp, arr, dataSize);
	start = clock(); //��ʼʱ��
	MergeSort(tmp, 0, dataSize - 1);
	diff = clock() - start; //����ʱ��
	printf("���ļ� %s ��ȡ����������Ϊ %d ʱ���鲢 ��������ʱ��%d ms\n", fileName, dataSize, diff);

	CopyArray(tmp, arr, dataSize);
	start = clock(); //��ʼʱ��
	QuickSort(tmp, 0, dataSize - 1);
	diff = clock() - start; //����ʱ��
	printf("���ļ� %s ��ȡ����������Ϊ %d ʱ������ ��������ʱ��%d ms\n", fileName, dataSize, diff);

	CopyArray(tmp, arr, dataSize);
	start = clock(); //��ʼʱ��
	CountSort(tmp, dataSize);
	diff = clock() - start; //����ʱ��
	printf("���ļ� %s ��ȡ����������Ϊ %d ʱ������ ��������ʱ��%d ms\n", fileName, dataSize, diff);

	CopyArray(tmp, arr, dataSize);
	start = clock(); //��ʼʱ��
	RadixCountSort(tmp, dataSize);
	diff = clock() - start; //����ʱ��
	printf("���ļ� %s ��ȡ����������Ϊ %d ʱ���������� ��������ʱ��%d ms\n", fileName, dataSize, diff);
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




