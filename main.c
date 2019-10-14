#include "Matrixio.h"

int main() {
	int count_x, count_equ;
	printf("Enter count variable x: ");
	scanf("%d", &count_x);
	printf("Enter count equations: ");
	scanf("%d", &count_equ);
	float* l_func = (float*)malloc(count_x * sizeof(float*));
	// float* l_func = NULL;
	float** mat = read_data(l_func, count_equ, count_x);
	matrix_print(mat, count_equ, count_x);
	printf("L = ");
	for (int i = 0; i < count_x; ++i)
		printf("%4f ", l_func[i]);
	printf("\n");
	matrix_free(mat, count_equ);
	return 0;
}