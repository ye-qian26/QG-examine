//�������ݲ�д���ļ�
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//�������ݲ��������ļ���
void generate(char* fileName, int dataSize) {
	//���ļ�
	FILE* file = fopen(fileName, "w");
	if (file == NULL) {
		printf("�޷����ļ�\n");
		return;
	}

	//Ϊ�ļ�д����
	srand(time(NULL));
	for (int i = 0; i < dataSize; i++) {
		int number = rand() % 1000;  //�������0-999����
		fprintf_s(file, "%d\n", number);
	}

	//�ر��ļ�
	fclose(file);
}


//int main() {
//	int dataSize[] = { 10000, 50000, 200000 };
//	int len = sizeof(dataSize) / sizeof(dataSize[0]);
//	for (int i = 0; i < len; i++) {
//		char fileName[20];
//		//Ϊ�ļ�����
//		sprintf_s(fileName, sizeof(fileName), "data_%d.txt", dataSize[i]);
//		//�������ݲ����浽��Ӧ�ļ�
//		generate(fileName, dataSize[i]);
//		printf("������������Ϊ %d ���ļ� %s\n", dataSize[i], fileName);
//	}
//	return 0;
//}