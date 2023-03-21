#ifndef __GAUSS_H__
#define __GAUSS_H__

#define SIGMA 1.2
#define RADIUS 5

#include "structs.h"
#include "kernel.h"

double gaussian_function(double x, double y, double sigma);
void generate_kernel(kernel_t *kernel, int radius, double sigma);
// BMPImage *gauss_blur(BMPImage *image, int radius, double sigma);
int gauss_blur(BMPImage **new_image, BMPImage *image, int radius, double sigma);

// double gaussian_function(double x, double y, double sigma);
// double *generate_coef(int radius, double sigma);
// BMPImage *gauss_blur(BMPImage *image, int radius, double sigma);

#endif 
