#include"calculator.h"

//�ж��û������ʽ���Ƿ���Ϲ淶
bool judgeFormula(char* formula) {
	int len = strlen(formula);
	//�ж�ʽ�ӿ�ͷ��ĩβ�ǲ������ֻ���������
	if ((!isdigit(formula[0]) && formula[0] !=  '(') || (!isdigit(formula[len - 1]) && formula[len - 1] != ')')) return 0;

	for (int i = 0; i < len; i++) {
		if (strchr("+-*/.() ", formula[i]) == NULL && !isdigit(formula[i])) {
			return 0;
		}
		else if (formula[i] == '/') {
			//�ж��û������÷��Ƿ����
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

//���û�������ַ���תΪ�ַ�������
void split_formula(const char* formula, char str[][20], int* str_count) {
	int len = strlen(formula);
	int i = 0, j = 0, k = 0;
	//����ʽ��
	while (i < len) {
		//����ǿո�������
		if (isspace(formula[i])) {
			i++;
			continue;
		}

		//���������
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

		//����������
		else {
			str[k][0] = formula[i];
			str[k][1] = '\0';
			k++;
			i++;
		}
	}
	//�ַ������鳤��
	*str_count = k;
}

//������ջ����׺���ʽת��Ϊ��׺���ʽ
void transform(char trans_str[100][20],const char str[100][20], int len, int* newLen) {
	//��trans_str�ĸ����ַ�����ʼΪ��
	for (int j = 0; j < 100; j++) {
		trans_str[j][0] = '\0';
	}
	int i = 0, k = 0;
	OperatorLinkStack s;
	OinitStack(&s);
	//������׺���ʽ
	while (i < len) {
		//�����������
		if (strcmp(str[i], "(") == 0) {
			Opush(&s, '(');
			i++;
		}

		//�����������
		else if (strcmp(str[i], ")") == 0) {
			while (OgetTop(&s) != '(') {
				//��ջ��Ԫ�ز���������
				//�������ַ�ת��Ϊ�ַ���
				char tmp[2];
				tmp[0] = Opop(&s);
				tmp[1] = '\0';
				strcpy_s(trans_str[k++], sizeof(trans_str[k++]), tmp);
			}
			//ջ��Ԫ����������
			Opop(&s);
			i++;
		}

		//����������
		else if(strcmp(str[i],"+") == 0 || strcmp(str[i], "-") == 0 || strcmp(str[i], "*") == 0 || strcmp(str[i], "/") == 0) {
			char oper = str[i][0];
			while (1) {
				if (OisEmpty(&s)) {
					Opush(&s, oper);
					break;
				}
				else {
					if (compare(oper, OgetTop(&s)) != 1 && OgetTop(&s) != '(') {
						//��tmp���ȼ�������ջ�������ͬʱջ��Ԫ�ز�Ϊ������
						char tmp[2];
						tmp[0] = Opop(&s);
						tmp[1] = '\0';
						strcpy_s(trans_str[k++], sizeof(trans_str[k++]), tmp);
					}
					else {
						//tmp���ȼ�����ջ�����������ջ��Ϊ������
						Opush(&s, oper);
						break;
					}
				}
			}
			i++;
		}
		//���������
		else {
			strcpy_s(trans_str[k++], sizeof(trans_str[k++]), str[i++]);
		}
	}
	//�����꽫ջ������Ԫ��ȡ��
	while (!OisEmpty(&s)) {
		char tmp[2];
		tmp[0] = Opop(&s);
		tmp[1] = '\0';
		strcpy_s(trans_str[k++], sizeof(trans_str[k++]), tmp);
	}
	*newLen = k;
}

//�Ƚ���������ȼ�
int compare(char x, char y) {
	if (x == '*' || x == '/') {
		if (y == '+' || y == '-') {
			//x�����ȼ�����y
			return 1;
		}
		else {
			//x�����ȼ�����y
			return 0;
		}
	}
	else {
		//x��'+'��'-'
		if (y == '+' || y == '-') {
			//x�����ȼ�����y
			return 0;
		}
		else {
			//x�����ȼ�С��y
			return -1;
		}
	}
}

//�����׺���ʽ
double calculate(char trans_str[100][20], int len, int* isError) {
	int i = 0;
	DataLinkStack d;
	DinitStack(&d);
	while (i < len) {
		//���������ǼӺ�
		if (strcmp(trans_str[i], "+") == 0) {
			Dpush(&d, add(Dpop(&d), Dpop(&d)));
			i++;
		}
		//����
		else if (strcmp(trans_str[i], "-") == 0) {
			Dpush(&d, sub(Dpop(&d), Dpop(&d)));
			i++;
		}
		//�˺�
		else if (strcmp(trans_str[i], "*") == 0) {
			Dpush(&d, mul(Dpop(&d), Dpop(&d)));
			i++;
		}
		//����
		else if (strcmp(trans_str[i], "/") == 0) {
			if (DgetTop(&d) == 0) {
				//����Ϊ��
				//�Ѵ��������Ϊ0
				*isError = 0;
				return 0.0;
			}
			else {
				double divNumber = divide(Dpop(&d), Dpop(&d));
				Dpush(&d, divNumber);
				i++;
			}
		}
		//����
		else {
			const char* tmp = trans_str[i];
			double c;
			c = atof(tmp);
			if (c != 0) {
				Dpush(&d, c);
			}
			else {
				printf("�ַ�������ת��Ϊdouble����ʧ��\n");
				return 0.0;
			}
			i++;
		}
	}
	return Dpop(&d);
}

//�ӷ�����
double add(double x, double y) {
	return x + y;
}

//��������
double sub(double x, double y) {
	return x - y;
}

//�˷�����
double mul(double x, double y) {
	return x * y;
}

//��������
double divide(double x, double y) {
	return x / y;
}


