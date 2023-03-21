#include <math.h>
#include "../inc/kernel.h"
#include "../inc/defs.h"
#include "../inc/matrix.h"

void align_color(double *color)
{
    (*color) = (*color) > 255 ? 255 : (*color);
    (*color) = (*color) < 0 ? 0 : (*color);
}

RGB *get_pixel_in_position(BMPImage *image, int i, int j)
{
    return (image->pixel + (i * image->imageheader.biWidth + j));
}

void set_pixel_in_position(RGB *pixel, RGB new_pixel)
{
    if (pixel)
        *pixel = new_pixel;
}

void correct_pos(int *position, int value, int max_size)
{
    if (*position < 0 || *position > max_size)
        *position = value;
}

double get_matrix_data(double **mat, int i, int j)
{
    return mat[i][j];
}

int create_kernel(kernel_t *kernel, int size)
{
    kernel->dim = size;
    kernel->matrix = alloc_matrix(size, size);
    int rc = OK;
    if (!kernel->matrix)
        rc = MEMORY_ERROR;

    return rc;
}

int check_kernel_size(int size)
{
    if (size < 3 || size % 2 == 0)
        return 0;
    return 1;
}

int read_kernel(kernel_t *kernel, FILE *file)
{
    if (!file)
        return FILE_ERROR;

    int rc = OK;
    int size;
    if (fscanf(file, "%d", &size) != 1)
        rc = IO_ERROR;
    else
        rc = check_kernel_size(size) ? OK : SIZE_ERROR;
    
    if (!rc)
        rc = create_kernel(kernel, size);

    for (int i = 0; !rc && i < kernel->dim; i++)
        for (int j = 0; !rc && j < kernel->dim; j++)
            if (fscanf(file, "%lf", &kernel->matrix[i][j]) != 1)
                rc = IO_ERROR;

    return rc;
}

void convolution(BMPImage **new_image, BMPImage *old_image, kernel_t *kernel)
{
    RGB *new_pixel = NULL;
    for (int i = 0; i < (int) old_image->imageheader.biHeight; i++)
    {
        for (int j = 0; j < (int) old_image->imageheader.biWidth; j++)
        {
            new_pixel = apply_kernel(old_image, i, j, kernel);

            set_pixel_in_position(&((*new_image)->pixel[i * (*new_image)->imageheader.biWidth + j]), *new_pixel);
        }
    }
}

RGB *apply_kernel(BMPImage *image, int i, int j, kernel_t *kernel)
{
    int radius = kernel->dim / 2;
    double blue = 0, green = 0, red = 0;
    RGB *pixel;
    int x_position, y_position;
    for (int k = 0; k < kernel->dim; k++)
    {
        x_position = i + k - radius;
        correct_pos(&x_position, k, image->imageheader.biHeight);
        for (int l = 0; l < kernel->dim; l++)
        {
            y_position = j + l - radius;
            correct_pos(&y_position, l, image->imageheader.biWidth);

            pixel = get_pixel_in_position(image, x_position, y_position);

            double cur_kernel_val = get_matrix_data(kernel->matrix, k, l);

            blue += pixel->blue * cur_kernel_val;
            green += pixel->green * cur_kernel_val;
            red += pixel->red * cur_kernel_val;
        }
    }

    align_color(&red);
    align_color(&green);
    align_color(&blue);

    RGB *new_pixel = calloc(1, sizeof(RGB));
    if (!new_pixel)
        return NULL;

    new_pixel->blue = (uint8_t)blue;
    new_pixel->green = (uint8_t)green;
    new_pixel->red = (uint8_t)red;

    return new_pixel;
}

int user_kernel(BMPImage **new_image, BMPImage *image, kernel_t *kernel)
{
    int rc = OK;

    if (!image || ! *new_image || !kernel)
        rc = NULL_POINTER;

    if (!rc)
        convolution(new_image, image, kernel);

    return rc;
}

