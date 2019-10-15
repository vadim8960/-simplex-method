#include "Matrixop.h"

void standardization_matrix(float** mat, float* l_func, int* sign_equ, int count_equ, int count_x) {
	for (int i = 0; i < count_equ; ++i) {
		bool flag_chsign = ( sign_equ[i] == 2 || sign_equ[i] == 4 );
		for (int j = 0; j < count_x; ++j) 
			mat[i][j] *= ((flag_chsign) ? 1 : -1);
	}
	for (int i = 0; i < count_x; ++i)
		l_func[i] *= -1;
}

bool check_matrix(float** mat, int count_equ, int count_x) {

}

void swap_variables(float** mat, float* l_func, int count_equ, int count_x, int index1, int index2) {
	++index2;
	float lambda = 1 / mat[index1][index2];
	for (int i = 0; i < count_x; ++i)
		if (i != index2)
			mat[index1][i] *= lambda;
	for (int i = 0; i < count_equ; ++i)
		if (i != index1)
			mat[i][index2] *= (-1 * lambda);

	l_func[index2] *= (-1 * lambda);

	for (int i = 0; i < count_equ; ++i) {
		if (i == index1) continue;
		for (int j = 0; j < count_x; ++j) {
			if (j == index2) continue;
			mat[i][j] += ( mat[i][index2] * mat[index1][j] * mat[index1][index2] );
		}
	}

	for (int i = 0; i < count_x; ++i) {
		if (i == index2) continue;
		l_func[i] += ( mat[0][index2] * mat[index1][i] * mat[index1][index2] );
	}
	mat[index1][index2] = lambda;
}