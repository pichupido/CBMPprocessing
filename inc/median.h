#ifndef __MEDIAN_H__
#define __MEDIAN_H__

#include "structs.h"
#include "kernel.h"

// BMPImage *median_filter(BMPImage *image, int dim);
int median_filter(BMPImage **new_image, BMPImage *image, int dim);
RGB *apply_window(BMPImage *image, int i, int j, int dim);

#endif 
