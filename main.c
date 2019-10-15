#include "Matrixio.h"
#include "Matrixop.h"

int main() {
	int count_x, count_equ;
	printf("Enter count variable x: ");
	scanf("%d", &count_x);
	++count_x;                               // free element b
	printf("Enter count equations: ");
	scanf("%d", &count_equ);

	float* l_func = (float*)malloc(count_x * sizeof(float*));
	int* sign_equ = (int*)malloc(count_equ * sizeof(int*));
	float** mat = read_data(l_func, sign_equ, count_equ, count_x);

	standardization_matrix(mat, l_func, sign_equ, count_equ, count_x);
	matrix_print(mat, count_equ, count_x);
	swap_variables(mat, l_func, count_equ, count_x, 1, 0);

	matrix_print(mat, count_equ, count_x);
	printf("L: ");
	for (int i = 0; i < count_x; ++i)
		printf("%4f ", l_func[i]);
	printf("\n");

	free(l_func);
	free(sign_equ);
	matrix_free(mat, count_equ);
	return 0;
}