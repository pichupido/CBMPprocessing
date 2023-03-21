#include <stdio.h>
#include <math.h>
#include "../inc/gauss.h"
#include "../inc/defs.h"
#include "../inc/temp.h"

#define MY_PI acos(-1)

double gaussian_function(double x, double y, double sigma) 
{
    return exp(-(x * x + y * y) / (2 * sigma * sigma)) / (2 * MY_PI * sigma * sigma);
}

void generate_kernel(kernel_t *kernel, int radius, double sigma)
{
    double sum = 0.0;
    int rc = OK;

    int step = radius / 2;
    if (!rc)
    {
        for (int i = 0; i < radius; i++)
            for (int j = 0; j < radius; j++)
            {
                int x_pos = i - step;
                int y_pos = j - step;
                kernel->matrix[i][j] = gaussian_function(x_pos, y_pos, sigma);
                sum += kernel->matrix[i][j];
            }
        for (int i = 0; i < radius; i++)
            for (int j = 0; j < radius; j++)
                kernel->matrix[i][j] = kernel->matrix[i][j] / sum;
    }
}

int gauss_blur(BMPImage **new_image, BMPImage *image, int radius, double sigma)
{
    int rc = OK;

    if (!image || ! *new_image)
        rc = NULL_POINTER;

    kernel_t gaussian_kernel;
    if (!rc)
        rc = create_kernel(&gaussian_kernel, radius);
    if (!rc)
    {
        generate_kernel(&gaussian_kernel, radius, sigma);
        convolution(new_image, image, &gaussian_kernel);
    }
    return rc;
}
