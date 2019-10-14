#ifndef __MATRIXIO__
#define __MATRIXIO__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int** matrix_malloc(int size_x, int size_y);

void matrix_free(float** arr, int size_x);

void matrix_print(float** arr, int size_x, int size_y);

float* parse_data(/*float* sing_equ, */int count_x);

float** read_data(float* l_func, int count_equ, int count_x);

#endif /*__MATRIXIO__*/