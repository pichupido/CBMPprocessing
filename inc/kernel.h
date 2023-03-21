#ifndef __KERNEL_H__
#define __KERNEL_H__

#include <stdio.h>
#include "structs.h"

void align_color(double *color);
RGB *get_pixel_in_position(BMPImage *image, int i, int j);
void set_pixel_in_position(RGB *pixel, RGB new_pixel);
void correct_pos(int *position, int value, int max_size);
double get_matrix_data(double **mat, int i, int j);
int create_kernel(kernel_t *kernel, int size);
// void convolution(BMPImage *new_image, BMPImage *old_image, kernel_t *kernel);
void convolution(BMPImage **new_image, BMPImage *old_image, kernel_t *kernel);
RGB *apply_kernel(BMPImage *image, int i, int j, kernel_t *kernel);
// BMPImage *user_kernel(BMPImage *image, kernel_t *kernel);
int user_kernel(BMPImage **new_image, BMPImage *image, kernel_t *kernel);
int check_kernel_size(int size);
int read_kernel(kernel_t *kernel, FILE *file);
// uint32_t bytes_per_pixel(BMPImage *image);


#endif
