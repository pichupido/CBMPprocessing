#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "../inc/matrix.h"

void mat_free(double **matrix, int n)
{
    for (int i = 0; i < n; i++)
        free(matrix[i]);
    free(matrix);
}

double **alloc_matrix(int n, int m)
{
    double **matrix = calloc(n, sizeof(double*));
    if (!matrix)
        return NULL;
    for (int i = 0; i < n; i++)
    {
        matrix[i] = malloc(m * sizeof(double));
        if (!matrix[i])
        {
            mat_free(matrix, i);
            return NULL;
        }
    }
    return matrix;
}


void mat_mult(kernel_t a, kernel_t b, kernel_t *result)
{
	double num;

	for (int i = 0; i < a.dim; i++)
		for (int j = 0; j < a.dim; j++)
		{
			num = 0.0;

			for (int k = 0; k < a.dim; k++)
				num += a.matrix[i][k] * b.matrix[k][j];
			result->matrix[i][j] = num;
		}
}

void sqrt_matrix(kernel_t *kernel)
{
    for (int i = 0; i < kernel->dim; i++)
        for (int j = 0; j < kernel->dim; j++)
            kernel->matrix[i][j] = sqrt(kernel->matrix[i][j]);
}

void sum_matrixes(kernel_t a, kernel_t b, kernel_t *result)
{
    for (int i = 0; i < a.dim; i++)
        for (int j = 0; j < a.dim; j++)
            result->matrix[i][j] = a.matrix[i][j] + b.matrix[i][j];
}


void print_matrix(kernel_t kernel)
{
    for (int i = 0; i < kernel.dim; i++)
    {
        for (int j = 0; j < kernel.dim; j++)
            printf("%.3lf ", kernel.matrix[i][j]);
        printf("\n");
    }
}
