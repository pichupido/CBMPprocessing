#include "../inc/edge_detection.h"
#include "../inc/defs.h"
#include "../inc/grayscale.h"
#include "../inc/gauss.h"
#include "../inc/laplace.h"
#include "../inc/sobel.h"
#include "../inc/read_write.h"
#include "../inc/temp.h"

int edge_detection(BMPImage **new_image, BMPImage *image)
{
    int rc = OK;
    if (!image)
        rc = NULL_POINTER;

    if (!rc)
        grayscale(&image, image);
    write_bmp("gray.bmp", image);


    if (!rc)
        rc = gauss_blur(new_image, image, RADIUS, SIGMA);
    write_bmp("gauss.bmp", *new_image); //

    BMPImage *laplace = alloc_copy_image(*new_image);

    if (!rc && laplace)
        rc = laplace_operator(&laplace, *new_image, OFF, OFF, ON);
    write_bmp("laplace.bmp", laplace);
    

    int edge_value;
    printf("Enter edge value: ");
    if (!rc && scanf("%d", &edge_value) != 1)
        rc = IO_ERROR;
    if (!rc && (edge_value < 0 || edge_value > 255))
        rc = COMPONENT_ERROR;

    RGB *pixel;
    if (!rc)
        for (int i = 0; i < (int)laplace->imageheader.biHeight; i++)
            for (int j = 0; j < (int)laplace->imageheader.biWidth; j++)
            {
                pixel = get_pixel_in_position(laplace, i, j);
                if (pixel->blue > edge_value)
                    pixel->blue = pixel->green = pixel->red = 255;
                else
                    pixel->blue = pixel->green = pixel->red = 0;
                set_pixel_in_position(get_pixel_in_position(laplace, i, j), *pixel);
            }
    write_bmp("./lalala/edge.bmp", laplace);
    free_image(laplace);
    return rc;
}

