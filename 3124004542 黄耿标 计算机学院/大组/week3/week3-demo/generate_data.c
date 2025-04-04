//生成数据并写入文件
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//生成数据并保存于文件中
void generate(char* fileName, int dataSize) {
	//打开文件
	FILE* file = fopen(fileName, "w");
	if (file == NULL) {
		printf("无法打开文件\n");
		return;
	}

	//为文件写数据
	srand(time(NULL));
	for (int i = 0; i < dataSize; i++) {
		int number = rand() % 1000;  //随机生成0-999的数
		fprintf_s(file, "%d\n", number);
	}

	//关闭文件
	fclose(file);
}


//int main() {
//	int dataSize[] = { 10000, 50000, 200000 };
//	int len = sizeof(dataSize) / sizeof(dataSize[0]);
//	for (int i = 0; i < len; i++) {
//		char fileName[20];
//		//为文件命名
//		sprintf_s(fileName, sizeof(fileName), "data_%d.txt", dataSize[i]);
//		//生成数据并保存到对应文件
//		generate(fileName, dataSize[i]);
//		printf("已生成数据量为 %d 的文件 %s\n", dataSize[i], fileName);
//	}
//	return 0;
//}