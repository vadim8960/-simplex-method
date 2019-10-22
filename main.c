#include "Matrixop.h"
#include <stdlib.h>

int main(int argc, char** argv) {
	int count_x, count_equ, error = 0;
	FILE* in = operate_terminal_command(argc, argv, &count_x, &count_equ, &error);

	if (error == 1) return 0;

	if (in == NULL){
		printf("Enter count variable x: ");
		scanf("%d", &count_x);
		printf("Enter count equations: ");
		scanf("%d", &count_equ);
	}

	++count_x;

	float* l_func = (float*)malloc(count_x * sizeof(float*));
	int* sign_equ = (int*)malloc(count_equ * sizeof(int*));
	char** var_arr  = (char**)malloc((count_equ + count_x) * sizeof(char**));
	for (int i = 0; i < count_x + count_equ; ++i)
		var_arr[i] = (char*)malloc(10 * sizeof(char*));
	float** mat; 

	for (int i = 1; i < count_x + count_equ; ++i) {
		char d[100];
		if (i < count_x)
			sprintf(d, "x%d", i);
		else 
			sprintf(d, "y%d", i - count_equ - 1);
		strcpy(&var_arr[i - 1][0], d);
	}

	if (error == 2)
		mat = read_data(l_func, sign_equ, count_equ, count_x);
	else
		mat = read_data(l_func, sign_equ, count_equ, count_x, in);

	matrix_print(mat, l_func, count_equ, count_x, var_arr, (char*)"Input matrix: ");

	standardization_matrix(mat, l_func, sign_equ, count_equ, count_x);

	matrix_print(mat, l_func, count_equ, count_x, var_arr, (char*)"Input matrix after standardization: ");

	float v = calc_min(mat, l_func, count_equ, count_x, &error, var_arr);
	if (!error)
		printf("Lmin = %f\n\n", v);
	else 
		printf("Error %d\n\n", error);

	if (in != NULL)
		fclose(in);
	free(var_arr);
	free(l_func);
	free(sign_equ);
	matrix_free(mat, count_equ);
	return 0;
}