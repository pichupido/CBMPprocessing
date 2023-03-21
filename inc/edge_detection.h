#ifndef __EDGE_DETECTION_H__
#define __EDGE_DETECTION_H__

#include "structs.h"
#include "kernel.h"

// BMPImage *edge_detection(BMPImage *image);
int edge_detection(BMPImage **new_image, BMPImage *image);

#endif 

