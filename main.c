#include "Matrixio.h"
#include "Matrixop.h"

int main() {
	int count_x, count_equ, error = 0;
	printf("Enter count variable x: ");
	scanf("%d", &count_x);
	++count_x;                               // free element b
	printf("Enter count equations: ");
	scanf("%d", &count_equ);

	float* l_func = (float*)malloc(count_x * sizeof(float*));
	int* sign_equ = (int*)malloc(count_equ * sizeof(int*));
	float** mat = read_data(l_func, sign_equ, count_equ, count_x);

	standardization_matrix(mat, l_func, sign_equ, count_equ, count_x);

	float v = calc_min(mat, l_func, count_equ, count_x, &error);
	if (!error)
		printf("Lmin = %f\n", v);
	else 
		printf("Error %d\n", error);

	free(l_func);
	free(sign_equ);
	matrix_free(mat, count_equ);
	return 0;
}

/*

x1-x2+2x3=5
2x1-x2=-1
2x2-x3=1
-x1-x3=-2

*/