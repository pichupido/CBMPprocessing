#ifndef __MATRIX_H__
#define __MATRIX_H__

#include "../inc/structs.h"

void mat_free(double **matrix, int n);
double **alloc_matrix(int n, int m);
void mat_mult(kernel_t a, kernel_t b, kernel_t *result);
void sqrt_matrix(kernel_t *kernel);
void sum_matrixes(kernel_t a, kernel_t b, kernel_t *result);
void print_matrix(kernel_t kernel);

#endif 
