#ifndef __MATRIXOP__
#define __MATRIXOP__

#include "Matrixio.h"

void standardization_matrix(float** mat, float* l_func, int* sign_equ, int count_equ, int count_x);
bool check_matrix(float** mat, int count_equ, int count_x);
void swap_variables(float** mat, float* l_func, int count_equ, int count_x, int index1, int index2);
bool check_answer(float** mat, float* l_func, int count_equ, int count_x);
void update_matrix(float** mat, float* l_func, int count_equ, int count_x, char** var_arr);
float calc_min(float** mat, float* l_func, int count_equ, int count_x, int* error, char** var_arr);

#endif /*__MATRIXOP__*/