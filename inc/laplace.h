#ifndef __LAPLACE_H__
#define __LAPLACE_H__

#include "structs.h"

double **get_positive_laplace_operator();
double **get_negative_laplace_operator();
double **get_diagonal_laplace_operator();
// BMPImage *laplace_operator(BMPImage *image, int pos, int neg, int diagonal);
int laplace_operator(BMPImage **new_image, BMPImage *image, int pos, int neg, int diagonal);

#endif 
