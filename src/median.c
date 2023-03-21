#include <stdio.h>
#include "../inc/median.h"
#include "../inc/defs.h"

void sort(int *arr, int n)
{ 
    int i = 0, j = 0, temp=0;

    for (i = 0; i < n; i++)
        for(j = 0 ; j < n - 1; j++)
            if (arr[j] > arr[j + 1])
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
}

void init_arr(int *arr, int len)
{
    for (int i = 0; i < len; i++)
        arr[i] = 0;
}

int median_filter(BMPImage **new_image, BMPImage *image, int dim)
{
    int rc = OK;
    if (!image || ! *new_image)
        rc = NULL_POINTER;

    RGB *new_pixel = NULL;
    for (int i = 0; !rc && i < (int) image->imageheader.biHeight; i++)
        for (int j = 0; j < (int) image->imageheader.biWidth; j++)
        {
            new_pixel = apply_window(image, i, j, dim);
            set_pixel_in_position(&((*new_image)->pixel[i * (*new_image)->imageheader.biWidth + j]), *new_pixel);
        }

    return rc;
}


RGB *apply_window(BMPImage *image, int i, int j, int dim)
{
    int radius = dim / 2;
    int median = dim * dim / 2;

    int *r = calloc(dim * dim, sizeof(int));
    int *g = calloc(dim * dim, sizeof(int));
    int *b = calloc(dim * dim, sizeof(int));

    int q = 0;
    RGB *pixel;
    int x_pos, y_pos;
    for (int k = 0; k < dim; k++)
    {
        x_pos = i + k - radius;
        correct_pos(&x_pos, k, image->imageheader.biHeight);
        for (int l = 0; l < dim; l++)
        {
            y_pos = j + l - radius;
            correct_pos(&y_pos, l, image->imageheader.biWidth);

            pixel = get_pixel_in_position(image, x_pos, y_pos);

            r[q] = pixel->red;
            g[q] = pixel->green;
            b[q] = pixel->blue;
            q++;
        }
    }
    sort(r, dim * dim);
    sort(g, dim * dim);
    sort(b, dim * dim);

    RGB *new_pixel = calloc(1, sizeof(RGB));
    
    new_pixel->red = r[median];
    new_pixel->green = g[median];
    new_pixel->blue = b[median];

    if (r)
        free(r);
    if (g)
        free(g);
    if (b)
        free(b);

    return new_pixel;
}
