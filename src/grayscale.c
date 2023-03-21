#include <math.h>
#include "../inc/read_write.h"
#include "../inc/grayscale.h"
#include "../inc/temp.h"
#include "../inc/defs.h"

static void set_pixel_rgb_same(RGB *pixel, uint8_t val)
{
    pixel->red = val;
    pixel->green = val;
    pixel->blue = val;
}

int grayscale(BMPImage **grayscaled, BMPImage *color)
{
    int rc = OK;
    if (!color || ! *grayscaled)
        rc = NULL_POINTER;

    if (! *grayscaled)
        rc = MEMORY_ERROR;

    if (!rc)
        for (unsigned int i = 0; i < color->imageheader.biWidth * color->imageheader.biHeight; i++)
        {
            uint8_t val = (uint8_t)color->pixel[i].color_model.Y;

            set_pixel_rgb_same(&((*grayscaled)->pixel[i]), val);
        }

    return rc;
}

