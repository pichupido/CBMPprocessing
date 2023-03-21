#include "../inc/temp.h"
#include "../inc/defs.h"

BMPImage *alloc_copy_image(BMPImage *image)
{
    int rc = OK;

    if (!image)
        rc = NULL_POINTER;

    int unpadded_size;
    int total_size;
    BMPImage *new_image = NULL;

    if (!rc)
    {
        unpadded_size = image->imageheader.biWidth * bytes_per_pixel(image);
        total_size = unpadded_size * image->imageheader.biHeight;
    }

    if (!rc)
        new_image = calloc(1, sizeof(BMPImage));
    if (!new_image)
        rc = MEMORY_ERROR;

    if (!rc)
        new_image->pixel = (RGB *) calloc(total_size, sizeof(RGB));
    if (!new_image->pixel)
        rc = MEMORY_ERROR;

    if (!rc)
    {
        new_image->fileheader = image->fileheader;
        new_image->imageheader = image->imageheader;
    }

    return rc == OK ? new_image : NULL;
}

uint32_t bytes_per_pixel(BMPImage *image)
{
    return (uint32_t) image->imageheader.biBitCount / 8;
}
