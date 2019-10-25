#include "Matrixio.h"

int** matrix_malloc(int size_x, int size_y) {
	int** arr = (int**)malloc(size_x * sizeof(int**));
	for (int i = 0 ; i < size_x; ++i) 
		arr[i] = (int*)malloc(size_y * sizeof(int*));
	return arr;
}

void matrix_free(float** arr, int size_x) {
	for (int i = 0; i < size_x; ++i)
		free(arr[i]);
	free(arr);
}

int len_int(int a) {
	char s[100];
	sprintf(s, "%d", a);
	return strlen(s);
}

void matrix_print(float** arr, float* l_func, int size_x, int size_y, char** var_arr, char* name) {
	printf("%s\n", name);
	int* space = (int*)malloc(size_y * sizeof(int*));

	for (int i = 0; i < size_y; ++i) {
		int max_len = -1;
		for (int j = 0; j < size_x; ++j) {
			char t_str[100];
			sprintf(t_str, "%10f", arr[j][i]);
			int l = strlen(t_str);
			if (l > max_len) {
				max_len = strlen(t_str);
			}
		}
		space[i] = max_len;
	}

	printf("    ");

	for (int i = 0; i < size_y; ++i) {
		int j;
		for (j = 0; j < space[i] / 2 - 1; ++j)
			printf(" ");

		if (!i) printf("b");
		else { 
			printf("%s", var_arr[i - 1]);
			j += len_int(i);
		}
		for (; j < space[i]; ++j)
			printf(" ");
	}
	printf("\n");

	printf("L ");
	for (int i = 0; i < size_y; ++i) {
		printf("%11f", l_func[i]);
	}
	printf("\n");

	int var_iter = 0;
	for (int i = 0; i < size_x; ++i) {
		printf("%s", var_arr[size_y + i - 1]);
		for (int j = 0; j < size_y; ++j)
			printf("%11f", arr[i][j]);
		printf("\n");
	}
	printf("\n");
}

void l_function_print(float* arr, int count_x) {
	printf("L = ");
	for (int i = 0; i < count_x; ++i)
		printf("%4f ", arr[i]);
	printf("\n");
}

FILE* operate_terminal_command(int argc, char** argv, int* count_x, int* count_equ, int* error) {
	FILE* in;
	if (argc > 1) {
		if (argv[1][0] == '-' && argv[1][1] == 'h') {
			printf("simlex - программа для решения задачи линейного программирования с помощью Симплес метода\n\n");
			printf("использование: ./simplex -h\n");
			printf("использование: ./simplex -c\n");
			printf("использование: ./simplex [-f имя файла] [-e количество уравнений] [-x количество переменных]\n\n");
			printf("Параметры:\n");
			printf("  -f                            имя файла данных\n");
			printf("  -c                            ввод через консоль\n");
			printf("  -e                            количество уравнений\n");
			printf("  -x                            количество переменных\n");
			printf("  -h                            вывести инструкцию и выйти\n");
			*error = 1;
			return 0;
		} else if (argv[1][0] == '-' && argv[1][1] == 'f') {
			in = fopen(argv[2], "r");
			if (in == NULL) {
				if (argv[2] == NULL)
					printf("Нет входного файла\n");
				else 
					printf("Не найден файл %s\n", argv[2]);
				*error = 1;
				return NULL;
			}
			if (argc < 5) {
				printf("Некорректный ввод. Для информации введите -h\n");
				*error = 1;
				return NULL;
			}
			if (argv[3][0] == '-' && argv[3][1] == 'e') {
				*count_equ = atoi(argv[4]);
			} 
			if (argc < 7) {
				printf("Некорректный ввод. Для информации введите -h\n");
				*error = 1;
				return NULL;
			}
			if (argv[5][0] == '-' && argv[5][1] == 'x') {
				*count_x = atoi(argv[6]);
			} 
			return in;
		} else if (argv[1][0] == '-' && argv[1][1] == 'c') {
			*error = 2;
			return NULL;
		} else {
			printf("Некорректный ввод. Для информации введите -h\n");
			*error = 1;
			return NULL;
		}
	}
	printf("Некорректный ввод. Для информации введите -h\n");
	*error = 1;
	return NULL;
}

/*
 *	Sign equation
 * 0 - =
 * 1 - >
 * 2 - <
 * 3 - >=
 * 4 - <=
 */

float* parse_data(int* sing_equ, int count_x, FILE* in) {
	char str[100];
	float* arr = (float*)malloc(count_x * sizeof(float*));
	int index;
	fgets(str, 100, in);
	bool flag_sign = true, flag_end_equ = false;
	for (int i = 0; i < strlen(str); ++i) {
		if (str[i] == '-')
			flag_sign = false;
		if ('0' <= str[i] && str[i] <= '9' || str[i] == 'x') {
			char num[10] = {};
			bool flag_value = false;
			for (int index_num = 0; index_num < 10 && '0' <= str[i] && str[i] <= '9' || str[i] == '.'; ++index_num, ++i) {
				num[index_num] = str[i];
				flag_value = true;
			}
			if (!flag_value)
				num[0] = '1';

			bool flag_var = false;
			for (int j = i; str[j] != '+' && str[j] != '-' && j < strlen(str); ++j) {
				if (str[j] == 'x' || str[j] == '*') {
					flag_var = true;
					break;
				}
			}

			if (!flag_var) {
				float v = atof(num);
				if (flag_end_equ) v *= -1;
				arr[0] += (flag_sign) ? v : -1 * v;
				i--;
				continue;
			}

			while (str[i++] != 'x');
			char str_index[10] = {};
			for (int ind = 0; i < strlen(str) && '0' <= str[i] && str[i] <= '9'; ++ind, ++i) str_index[ind] = str[i];
			arr[atoi(str_index)] += ((flag_sign) ? atof(num) : -1 * atof(num));
			flag_sign = true;
			--i;
		}

		if (str[i] == '=') {
			*sing_equ = 0;
			flag_end_equ = true;
		} else if (str[i] == '>') {
			if (str[i + 1] == '=') { 
				*sing_equ = 3; 
				++i;
			}
			else *sing_equ = 1;
			flag_end_equ = true;
		} else if (str[i] == '<'){
			if (str[i + 1] == '=') {
				*sing_equ = 4;
				++i;
			}
			else *sing_equ = 2;
			flag_end_equ = true;
		}

	}
	return arr;
}

float** read_data(float* l_func, int* sign_equ, int count_equ, int count_x, FILE* in) {
	float** mat = (float**)malloc(count_equ * sizeof(float**));
	for (int c = 0; c < count_equ; c++) {
		*(mat + c) = (float*)parse_data(&sign_equ[c], count_x, in);
	}
	float* tmp = parse_data(&sign_equ[0], count_x, in);
	for (int i = 0; i < count_x; ++i)
		l_func[i] = tmp[i];
	return mat;
}

float** read_data(float* l_func, int* sign_equ, int count_equ, int count_x) {
	printf("Введите систему уравнений/неравенств: \n");
	while ((getchar()) != '\n');
	float** mat = (float**)malloc(count_equ * sizeof(float**));
	for (int c = 0; c < count_equ; c++) {
		*(mat + c) = (float*)parse_data(&sign_equ[c], count_x, stdin);
	}
	printf("Введите функцию L\nL = ");
	float* tmp = parse_data(&sign_equ[0], count_x, stdin);
	for (int i = 0; i < count_x; ++i)
		l_func[i] = tmp[i];
	return mat;
}