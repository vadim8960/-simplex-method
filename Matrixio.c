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

float* parse_data(/*float* sing_equ, */int count_x) {
	char str[100];
	float* arr = (float*)malloc(count_x * sizeof(float*));
	int index;
	fgets(str, 100, stdin);
	bool flag_sign = true;
	for (int i = 0; i < strlen(str); ++i) {
		if ('0' <= str[i] && str[i] <= '9' || str[i] == 'x') {
			char num[10] = {};
			bool flag_value = false;
			for (int index_num = 0; index_num < 10 && '0' <= str[i] && str[i] <= '9' || str[i] == '.'; ++index_num, ++i) {
				num[index_num] = str[i];
				flag_value = true;
			}
			if (!flag_value)
				num[0] = '1';

			while (str[i++] != 'x');
			char str_index[10] = {};
			for (int ind = 0; i < strlen(str) && '0' <= str[i] && str[i] <= '9'; ++ind, ++i) str_index[ind] = str[i];
			arr[atoi(str_index) - 1] = (flag_sign) ? atof(num) : -1 * atof(num);
		}
		if (str[i] == '+')
			flag_sign = true;
		if (str[i] == '-')
			flag_sign = false;
	}
	return arr;
}

float** read_data(float* l_func, int count_equ, int count_x) {
	printf("Enter equation system: \n");
	while ((getchar()) != '\n');
	float** mat = (float**)malloc(count_equ * sizeof(float**));
	for (int c = 0; c < count_equ; c++) {
		*(mat + c) = (float*)parse_data(count_x);
	}
	printf("Enter L function\nL = ");
	float* tmp = parse_data(count_x);
	for (int i = 0; i < count_x; ++i)
		l_func[i] = tmp[i];
	return mat;
}