#include "Matrixop.h"

int main(int argc, char** argv) {

	bool flag_fread = false;
	FILE* in;
	if (argc > 1) {
		if (argv[1][0] == '-' && argv[1][1] == 'f') {
			in = fopen(argv[2], "r");
			if (in == NULL) {
				printf("Not found %s\n", argv[2]);
				return 0;
			}
			flag_fread = true;
		} else {
			printf("Not correct format. For using read from file enter: -f filename\n");
			return 0;
		}

	}

	int count_x, count_equ, error = 0;
	printf("Enter count variable x: ");
	scanf("%d", &count_x);
	++count_x;                                // Для свободного члена
	printf("Enter count equations: ");
	scanf("%d", &count_equ);

	float* l_func = (float*)malloc(count_x * sizeof(float*));      // Функция для минимизации
	int* sign_equ = (int*)malloc(count_equ * sizeof(int*));        // Массив знаков для каждого выражения
	float** mat;                                                   // Матрица

	if (flag_fread)
		mat = read_data(l_func, sign_equ, count_equ, count_x, in);
	else
		mat = read_data(l_func, sign_equ, count_equ, count_x);

	standardization_matrix(mat, l_func, sign_equ, count_equ, count_x); // Привод матрицы к номральному виду

	float v = calc_min(mat, l_func, count_equ, count_x, &error);       // Процесс мнимизации
	if (!error)
		printf("Lmin = %f\n", v);
	else 
		printf("Error %d\n", error);                                   // Нет решения

	free(l_func);
	free(sign_equ);
	matrix_free(mat, count_equ);
	return 0;
}