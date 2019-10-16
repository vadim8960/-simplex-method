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

void matrix_print(float** arr, int size_x, int size_y) {
	printf("Matrix: \n");
	for (int i = 0; i < size_x; ++i) {
		for (int j = 0; j < size_y; ++j)
			printf("%4f ", arr[i][j]);
		printf("\n");
	}
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
			printf("simlex - program for solve Simplex method\n\n");
			printf("usage: ./simplex -h\n");
			printf("usage: ./simplex -c\n");
			printf("usage: ./simplex [-f filename] [-e count_equation] [-x count_x]\n\n");
			printf("Options:\n");
			printf("  -f                            set input file\n");
			printf("  -c                            console input\n");
			printf("  -e                            set count equations\n");
			printf("  -x                            set count x\n");
			printf("  -h                            display help message and exit\n");
			return 0;
		} else if (argv[1][0] == '-' && argv[1][1] == 'f') {
			in = fopen(argv[2], "r");
			if (in == NULL) {
				if (argv[2] == NULL)
					printf("No input file\n");
				else 
					printf("Not found %s\n", argv[2]);
				*error = 1;
				return NULL;
			}
			if (argc < 5) {
				printf("Not correct format. For info enter -h\n");
				*error = 1;
				return NULL;
			}
			if (argv[3][0] == '-' && argv[3][1] == 'e') {
				*count_equ = atoi(argv[4]);
			} 
			if (argc < 7) {
				printf("Not correct format. For info enter -h\n");
				*error = 1;
				return NULL;
			}
			if (argv[5][0] == '-' && argv[5][1] == 'x') {
				*count_x = atoi(argv[6]);
			} 
		} else if (argv[1][0] == '-' && argv[1][1] == 'c') {
			*error = 2;
			return NULL;
		} else {
			printf("Not correct format. For info enter -h\n");
			*error = 1;
			return NULL;
		}
	}
	return in;
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

			if (flag_end_equ) {
				arr[0] = (flag_sign) ? atof(num) : -1 * atof(num);
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
	printf("Enter equation system: \n");
	while ((getchar()) != '\n');
	float** mat = (float**)malloc(count_equ * sizeof(float**));
	for (int c = 0; c < count_equ; c++) {
		*(mat + c) = (float*)parse_data(&sign_equ[c], count_x, stdin);
	}
	printf("Enter L function\nL = ");
	float* tmp = parse_data(&sign_equ[0], count_x, stdin);
	for (int i = 0; i < count_x; ++i)
		l_func[i] = tmp[i];
	return mat;
}