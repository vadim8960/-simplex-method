#ifndef __MATRIXIO__
#define __MATRIXIO__

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int** matrix_malloc(int size_x, int size_y);
void matrix_free(float** arr, int size_x);
void matrix_print(float** arr, float* l_func, int size_x, int size_y, char** var_arr, char* name);
void l_function_print(float* arr, int count_x);
float* parse_data(int* sing_equ, int count_x, FILE* in);
FILE* operate_terminal_command(int argc, char** argv, int* count_x, int* count_equ, int* error);
float** read_data(float* l_func, int* sign_equ, int count_equ, int count_x, FILE* in);
float** read_data(float* l_func, int* sign_equ, int count_equ, int count_x);

#endif /*__MATRIXIO__*/