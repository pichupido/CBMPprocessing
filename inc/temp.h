#ifndef __TEMP_H__
#define __TEMP_H__

#include "structs.h"

BMPImage *alloc_copy_image(BMPImage *image);
// BMPImage *alloc_copy_image(BMPImage **image);
uint32_t bytes_per_pixel(BMPImage *image);

#endif 
