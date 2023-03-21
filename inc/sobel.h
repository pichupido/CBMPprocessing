#ifndef __SOBEL_H__
#define __SOBEL_H__

#include "structs.h"

void set_sobel_kernels(kernel_t *kernel_x, kernel_t *kernel_y);
// void convolution(BMPImage *new_image, BMPImage *old_image, kernel_t *kernel);
void convolution(BMPImage **new_image, BMPImage *old_image, kernel_t *kernel);
// BMPImage *Sobel_operator(BMPImage *image, int x_normalize, int y_normalize);
// BMPImage *Sobel_operator(BMPImage **new_image, BMPImage *image, int x_normalize, int y_normalize);
int Sobel_operator(BMPImage **new_image, BMPImage *image, int x_normalize, int y_normalize);

#endif
