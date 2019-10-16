#include "Matrixop.h"

int main(int argc, char** argv) {

	int count_x, count_equ, error = 0;
	FILE* in = operate_terminal_command(argc, argv, &count_x, &count_equ, &error);

	if (error == 1) return 0;

	if (in == NULL){
		printf("Enter count variable x: ");
		scanf("%d", &count_x);
		++count_x;
		printf("Enter count equations: ");
		scanf("%d", &count_equ);
	}

	float* l_func = (float*)malloc(count_x * sizeof(float*));
	int* sign_equ = (int*)malloc(count_equ * sizeof(int*));
	float** mat; 
	printf("%d %d\n", count_equ, count_x);
	if (error == 2)
		mat = read_data(l_func, sign_equ, count_equ, count_x);
	else
		mat = read_data(l_func, sign_equ, count_equ, count_x, in);
	standardization_matrix(mat, l_func, sign_equ, count_equ, count_x);

	float v = calc_min(mat, l_func, count_equ, count_x, &error);
	if (!error)
		printf("Lmin = %f\n", v);
	else 
		printf("Error %d\n", error);

	if (in != NULL)
		fclose(in);
	free(l_func);
	free(sign_equ);
	matrix_free(mat, count_equ);
	return 0;
}