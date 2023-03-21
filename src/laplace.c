#include <stdio.h>
#include "../inc/laplace.h"
#include "../inc/matrix.h"
#include "../inc/kernel.h"
#include "../inc/defs.h"

double **get_positive_laplace_operator()
{
    double **pos_op = alloc_matrix(3, 3);
    pos_op[0][0] = 0;
    pos_op[0][1] = 1;
    pos_op[0][2] = 0;
    pos_op[1][0] = 1;
    pos_op[1][1] = -4;
    pos_op[1][2] = 1;
    pos_op[2][0] = 0;
    pos_op[2][1] = 1;
    pos_op[2][2] = 0;

    return pos_op;
}

double **get_negative_laplace_operator()
{
    double **neg_op = alloc_matrix(3, 3);

    neg_op[0][0] = 0;
    neg_op[0][1] = -1;
    neg_op[0][2] = 0;
    neg_op[1][0] = -1;
    neg_op[1][1] = 4;
    neg_op[1][2] = -1;
    neg_op[2][0] = 0;
    neg_op[2][1] = -1;
    neg_op[2][2] = 0;

    return neg_op;
}

double **get_diagonal_laplace_operator()
{    
    double **diag_op = alloc_matrix(3, 3);

    diag_op[0][0] = 1;
    diag_op[0][1] = 1;
    diag_op[0][2] = 1;
    diag_op[1][0] = 1;
    diag_op[1][1] = -8;
    diag_op[1][2] = 1;
    diag_op[2][0] = 1;
    diag_op[2][1] = 1;
    diag_op[2][2] = 1;

    return diag_op;
}

int laplace_operator(BMPImage **new_image, BMPImage *image, int pos, int neg, int diagonal)
{
    if (!pos && !neg && !diagonal)
        return LAPLACE_ERROR;
    if (pos + neg + diagonal > 1)
        return LAPLACE_ERROR;
    
    int rc = OK;

    double **operator_matrix = alloc_matrix(3, 3);
    if (! operator_matrix)
        rc = MEMORY_ERROR;
    
    if (!rc && pos)
        operator_matrix = get_positive_laplace_operator();
    else if (!rc && neg)
        operator_matrix = get_negative_laplace_operator();
    else if (!rc)
        operator_matrix = get_diagonal_laplace_operator();

    kernel_t laplace;
    laplace.matrix = operator_matrix;
    laplace.dim = 3;

    if (!rc)
        convolution(new_image, image, &laplace);
    
    if (operator_matrix)
        mat_free(operator_matrix, laplace.dim);

    return rc;
}

