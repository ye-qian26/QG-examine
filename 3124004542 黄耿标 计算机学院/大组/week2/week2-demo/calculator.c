#include"calculator.h"

//判断用户输入的式子是否符合规范
bool judgeFormula(char* formula) {
	int len = strlen(formula);
	//判断式子开头和末尾是不是数字或左右括号
	if ((!isdigit(formula[0]) && formula[0] !=  '(') || (!isdigit(formula[len - 1]) && formula[len - 1] != ')')) return 0;

	for (int i = 0; i < len; i++) {
		if (strchr("+-*/.() ", formula[i]) == NULL && !isdigit(formula[i])) {
			return 0;
		}
		else if (formula[i] == '/') {
			//判断用户除法用法是否错误
			int a = i + 1;
			while (a < strlen(formula)) {
				if (!isspace(formula[a]) && formula[a] == '0') {
					return 0;
				}
				else if (isspace(formula[a])) a++;
				else break;
			}
		}
	}
	return 1;
}

//将用户输入的字符串转为字符串数组
void split_formula(const char* formula, char str[][20], int* str_count) {
	int len = strlen(formula);
	int i = 0, j = 0, k = 0;
	//遍历式子
	while (i < len) {
		//如果是空格则跳过
		if (isspace(formula[i])) {
			i++;
			continue;
		}

		//如果是数字
		if (isdigit(formula[i])) {
			j = 0;
			while (i < len) {
				if (isdigit(formula[i])) {
					str[k][j++] = formula[i++];
				}
				else if (formula[i] == '.') {
					str[k][j++] = formula[i++];
				}
				else break;
			}
			str[k][j] = '\0';
			k++;
		}

		//如果是运算符
		else {
			str[k][0] = formula[i];
			str[k][1] = '\0';
			k++;
			i++;
		}
	}
	//字符串数组长度
	*str_count = k;
}

//利用链栈将中缀表达式转换为后缀表达式
void transform(char trans_str[100][20],const char str[100][20], int len, int* newLen) {
	//将trans_str的各个字符串初始为空
	for (int j = 0; j < 100; j++) {
		trans_str[j][0] = '\0';
	}
	int i = 0, k = 0;
	OperatorLinkStack s;
	OinitStack(&s);
	//遍历中缀表达式
	while (i < len) {
		//如果是左括号
		if (strcmp(str[i], "(") == 0) {
			Opush(&s, '(');
			i++;
		}

		//如果是右括号
		else if (strcmp(str[i], ")") == 0) {
			while (OgetTop(&s) != '(') {
				//若栈顶元素不是左括号
				//将单个字符转换为字符串
				char tmp[2];
				tmp[0] = Opop(&s);
				tmp[1] = '\0';
				strcpy_s(trans_str[k++], sizeof(trans_str[k++]), tmp);
			}
			//栈顶元素是左括号
			Opop(&s);
			i++;
		}

		//如果是运算符
		else if(strcmp(str[i],"+") == 0 || strcmp(str[i], "-") == 0 || strcmp(str[i], "*") == 0 || strcmp(str[i], "/") == 0) {
			char oper = str[i][0];
			while (1) {
				if (OisEmpty(&s)) {
					Opush(&s, oper);
					break;
				}
				else {
					if (compare(oper, OgetTop(&s)) != 1 && OgetTop(&s) != '(') {
						//若tmp优先级不大于栈顶运算符同时栈顶元素不为左括号
						char tmp[2];
						tmp[0] = Opop(&s);
						tmp[1] = '\0';
						strcpy_s(trans_str[k++], sizeof(trans_str[k++]), tmp);
					}
					else {
						//tmp优先级大于栈顶运算符或者栈顶为左括号
						Opush(&s, oper);
						break;
					}
				}
			}
			i++;
		}
		//如果是数字
		else {
			strcpy_s(trans_str[k++], sizeof(trans_str[k++]), str[i++]);
		}
	}
	//遍历完将栈中所有元素取出
	while (!OisEmpty(&s)) {
		char tmp[2];
		tmp[0] = Opop(&s);
		tmp[1] = '\0';
		strcpy_s(trans_str[k++], sizeof(trans_str[k++]), tmp);
	}
	*newLen = k;
}

//比较运算符优先级
int compare(char x, char y) {
	if (x == '*' || x == '/') {
		if (y == '+' || y == '-') {
			//x的优先级大于y
			return 1;
		}
		else {
			//x的优先级等于y
			return 0;
		}
	}
	else {
		//x是'+'或'-'
		if (y == '+' || y == '-') {
			//x的优先级等于y
			return 0;
		}
		else {
			//x的优先级小于y
			return -1;
		}
	}
}

//计算后缀表达式
double calculate(char trans_str[100][20], int len, int* isError) {
	int i = 0;
	DataLinkStack d;
	DinitStack(&d);
	while (i < len) {
		//如果运算符是加号
		if (strcmp(trans_str[i], "+") == 0) {
			Dpush(&d, add(Dpop(&d), Dpop(&d)));
			i++;
		}
		//减号
		else if (strcmp(trans_str[i], "-") == 0) {
			Dpush(&d, sub(Dpop(&d), Dpop(&d)));
			i++;
		}
		//乘号
		else if (strcmp(trans_str[i], "*") == 0) {
			Dpush(&d, mul(Dpop(&d), Dpop(&d)));
			i++;
		}
		//除号
		else if (strcmp(trans_str[i], "/") == 0) {
			if (DgetTop(&d) == 0) {
				//除数为零
				//把错误参数设为0
				*isError = 0;
				return 0.0;
			}
			else {
				double divNumber = divide(Dpop(&d), Dpop(&d));
				Dpush(&d, divNumber);
				i++;
			}
		}
		//数字
		else {
			const char* tmp = trans_str[i];
			double c;
			c = atof(tmp);
			if (c != 0) {
				Dpush(&d, c);
			}
			else {
				printf("字符串数据转换为double类型失败\n");
				return 0.0;
			}
			i++;
		}
	}
	return Dpop(&d);
}

//加法运算
double add(double x, double y) {
	return x + y;
}

//减法运算
double sub(double x, double y) {
	return x - y;
}

//乘法运算
double mul(double x, double y) {
	return x * y;
}

//除法运算
double divide(double x, double y) {
	return x / y;
}


