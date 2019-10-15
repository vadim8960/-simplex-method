#ifndef __MATRIXOP__
#define __MATRIXOP__

void standardization_matrix(float** mat, float* l_func, int* sign_equ, int count_equ, int count_x);

bool check_matrix(float** mat, int count_equ, int count_x);

void swap_variables(float** mat, float* l_func, int count_equ, int count_x);

#endif /*__MATRIXOP__*/