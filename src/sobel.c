#include <math.h>
#include "../inc/sobel.h"
#include "../inc/defs.h"
#include "../inc/matrix.h"
#include "../inc/kernel.h"
#include "../inc/temp.h"

void set_sobel_kernels(kernel_t *kernel_x, kernel_t *kernel_y)
{
    if (kernel_x)
    {
        kernel_x->matrix[0][0] = -1;
        kernel_x->matrix[0][1] = 0;
        kernel_x->matrix[0][2] = 1;

        kernel_x->matrix[1][0] = -2;
        kernel_x->matrix[1][1] = 0;
        kernel_x->matrix[1][2] = 2;

        kernel_x->matrix[2][0] = -1;
        kernel_x->matrix[2][1] = 0;
        kernel_x->matrix[2][2] = 1;
    }
    if (kernel_y)
    {
        kernel_y->matrix[0][0] = -1;
        kernel_y->matrix[0][1] = -2;
        kernel_y->matrix[0][2] = -1;

        kernel_y->matrix[1][0] = 0;
        kernel_y->matrix[1][1] = 0;
        kernel_y->matrix[1][2] = 0;
        
        kernel_y->matrix[2][0] = 1;
        kernel_y->matrix[2][1] = 2;
        kernel_y->matrix[2][2] = 1;
    }
}


static void set_pixel_rgb(RGB *pixel, uint8_t r, uint8_t g, uint8_t b)
{
    pixel->red = r;
    pixel->green = g;
    pixel->blue = b;
}

int Sobel_operator(BMPImage **new_image, BMPImage *image, int x_normalize, int y_normalize)
{
    int rc = OK;

    if (!image || ! *new_image)
        rc = NULL_POINTER;

    if (x_normalize == 0 && y_normalize == 0)
        rc = NULL_POINTER;

    kernel_t sobel_operator_x, sobel_operator_y;

    if (x_normalize && y_normalize)
    {
        if (!rc)
            rc = create_kernel(&sobel_operator_x, SOBEL_SIZE);
        if (!rc)
            rc = create_kernel(&sobel_operator_y, SOBEL_SIZE);

        kernel_t sobel_operator_xy;
        if (!rc)
            rc = create_kernel(&sobel_operator_xy, SOBEL_SIZE);

        if (!rc)
            set_sobel_kernels(&sobel_operator_x, &sobel_operator_y);
        
        if (*new_image == NULL)
            rc = MEMORY_ERROR;

        RGB *pixel_x, *pixel_y;
        for (int i = 0; !rc && i < (int)image->imageheader.biHeight; i++)
            for (int j = 0; j < (int)image->imageheader.biWidth; j++)
            {
                pixel_x = apply_kernel(image, i, j, &sobel_operator_x);
                pixel_y = apply_kernel(image, i, j, &sobel_operator_y);
                RGB normalized;

                double blue = sqrt(pixel_x->blue * pixel_x->blue + pixel_y->blue * pixel_y->blue);
                align_color(&blue);

                double green = sqrt(pixel_x->green * pixel_x->green + pixel_y->green * pixel_y->green);
                align_color(&green);

                double red = sqrt(pixel_x->red * pixel_x->red + pixel_y->red * pixel_y->red);
                align_color(&red);

                set_pixel_rgb(&normalized, (uint8_t) blue, (uint8_t) green, (uint8_t) red);
                set_pixel_in_position(get_pixel_in_position(*new_image, i, j), normalized);
            }
    }
    else if (x_normalize)
    {
        if (!rc)
            rc = create_kernel(&sobel_operator_x, SOBEL_SIZE);

        if (!rc)
            set_sobel_kernels(&sobel_operator_x, NULL);

        if (!rc && *new_image)
            convolution(new_image, image, &sobel_operator_x);
    }
    else if (y_normalize)
    {
        if (!rc)
            rc = create_kernel(&sobel_operator_y, SOBEL_SIZE);

        if (!rc)
            set_sobel_kernels(NULL, &sobel_operator_y);

        if (!rc && new_image)
            convolution(new_image, image, &sobel_operator_y);
    }

    return rc;
}
