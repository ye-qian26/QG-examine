#include"calculator.h"
int main() {
	char str[100][20];
	//将每个字符串初始为空
	for (int j = 0; j < 100; j++) {
		str[j][0] = '\0';
	}
	int str_count;
	char formula[100];
	while (1) {
		printf("请输入您想计算的式子（输入0退出系统）：\n");
		fgets(formula, sizeof(formula), stdin);
		formula[strcspn(formula, "\n")] = '\0';
		if (strcmp(formula, "0") == 0) {
			printf("退出成功！欢迎下次光临！\n");
			break;
		}

		if (!judgeFormula(formula)) {
			printf("您输入的式子有问题！请重新输入\n");
		}
		else {
			//式子符合规范
			split_formula(formula, str, &str_count);
			/*for (int i = 0; i < str_count; i++) {
				printf("%s\n", str[i]);
			}
			printf("--------------------------\n");*/

			//将中缀表达式转化为后缀表达式
			char trans_str[100][20];
			int newLen;
			transform(trans_str, str, str_count, &newLen);
			/*for (int i = 0; i < newLen; i++) {
				printf("%s\n", trans_str[i]);
			}
			printf("--------------------------\n");*/


			//设置错误参数（1表示无错误，0表示出错）
			int isError = 1;
			double result = calculate(trans_str, newLen, &isError);

			if (isError == 0) {
				printf("式子出错，请检查\n");
			}
			else {
				printf("运算结果为：%.2f\n", result);
			}
		}
	}

	return 0;
}
