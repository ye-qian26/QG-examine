#include"calculator.h"
int main() {
	char str[100][20];
	//��ÿ���ַ�����ʼΪ��
	for (int j = 0; j < 100; j++) {
		str[j][0] = '\0';
	}
	int str_count;
	char formula[100];
	while (1) {
		printf("��������������ʽ�ӣ�����0�˳�ϵͳ����\n");
		fgets(formula, sizeof(formula), stdin);
		formula[strcspn(formula, "\n")] = '\0';
		if (strcmp(formula, "0") == 0) {
			printf("�˳��ɹ�����ӭ�´ι��٣�\n");
			break;
		}

		if (!judgeFormula(formula)) {
			printf("�������ʽ�������⣡����������\n");
		}
		else {
			//ʽ�ӷ��Ϲ淶
			split_formula(formula, str, &str_count);
			/*for (int i = 0; i < str_count; i++) {
				printf("%s\n", str[i]);
			}
			printf("--------------------------\n");*/

			//����׺���ʽת��Ϊ��׺���ʽ
			char trans_str[100][20];
			int newLen;
			transform(trans_str, str, str_count, &newLen);
			/*for (int i = 0; i < newLen; i++) {
				printf("%s\n", trans_str[i]);
			}
			printf("--------------------------\n");*/


			//���ô��������1��ʾ�޴���0��ʾ����
			int isError = 1;
			double result = calculate(trans_str, newLen, &isError);

			if (isError == 0) {
				printf("ʽ�ӳ�������\n");
			}
			else {
				printf("������Ϊ��%.2f\n", result);
			}
		}
	}

	return 0;
}
