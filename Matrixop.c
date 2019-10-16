#include "Matrixop.h"

void standardization_matrix(float** mat, float* l_func, int* sign_equ, int count_equ, int count_x) {
	for (int i = 0; i < count_equ; ++i) {
		bool flag_chsign = ( sign_equ[i] == 1 || sign_equ[i] == 3 || sign_equ[i] == 0 );
		mat[i][0] *= -1;
		for (int j = 0; j < count_x; ++j) 
			mat[i][j] *= ((flag_chsign) ? 1 : -1);
	}
	for (int i = 0; i < count_equ; ++i)
		for (int j = 1; j < count_x; ++j)
			mat[i][j] *= -1;

	for (int i = 1; i < count_x; ++i) {
		l_func[i] *= -1;
	}
}

bool check_matrix(float** mat, float* l_func, int count_equ, int count_x) {
	for (int i = 1; i < count_x; ++i) {
		if (l_func[i] > 0) {
			bool flag_ispos = false;
			for (int j = 0; j < count_equ; ++j) {
				if (mat[j][i] > 0) {
					flag_ispos = true;
				}
			}
			if (!flag_ispos)
				return false;
		}
	}
	return true;
}

bool check_answer(float** mat, float* l_func, int count_equ, int count_x) {
	bool flag_possign_mat = true, flag_negsign_l = true;
	for (int i = 0; i < count_equ; ++i)
		if (mat[i][0] < 0) {
			flag_possign_mat = false;
			break;
		}

	for (int i = 1; i < count_x; ++i) 
		if (l_func[i] > 0) {
			flag_negsign_l = false;
			break;
		}
	return (flag_possign_mat && flag_negsign_l);
}

void update_matrix(float** mat, float* l_func, int count_equ, int count_x) {
	int index1, index2;
	for (int i = 1; i < count_x; ++i) {
		if (l_func[i] > 0) {
			index2 = i;
			float min = 1000000.0f;
			for (int j = 0; j < count_equ; ++j) {
				if ((mat[j][i] > 0) && (mat[j][0] / mat[j][i] < min)) {
					min = mat[j][0] / mat[j][i];
					index1 = j;
				}
			}
			swap_variables(mat, l_func, count_equ, count_x, index1, index2);
			break;
		}
	}
}

/*
-5x1-x2+2x3<=2
-x1+x3+x4<=5
-3x1+5x4<=7
5x1-2x3
*/

void swap_variables(float** mat, float* l_func, int count_equ, int count_x, int index1, int index2) {
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
		l_func[i] += ( l_func[index2] * mat[index1][i] * mat[index1][index2] );
	}
	mat[index1][index2] = lambda;
}

float calc_min(float** mat, float* l_func, int count_equ, int count_x, int* error) {
	while (1) {
		
		// matrix_print(mat, count_equ, count_x);
		// l_function_print(l_func, count_x);

		if (!check_matrix(mat, l_func, count_equ, count_x)) {
			*error = 1;
			return 0;
		}

		if (check_answer(mat, l_func, count_equ, count_x)) {
			*error = 0;
			return l_func[0];
		}

		update_matrix(mat, l_func, count_equ, count_x);
	}
}
