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

void swap_variables(float** mat, float* l_func, int count_equ, int count_x) {

}