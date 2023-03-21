#ifndef __READ_WRITE_H__
#define __READ_WRITE_H__

#include <stdio.h>
#include "../inc/structs.h"

void printFileHeader(BMPFILEHEADER fileHeader);
void printImageHeader(BMPIMAGEHEADER imageHeader);
// int read_bmp(char *path, BMPImage *image);
int read_bmp(char *path, BMPImage **image);
void read_pixels(FILE *file, BMPImage *image);
void write_pixels(FILE *file, BMPImage *image);
void write_bmp(char *path, BMPImage *image);
void free_image(BMPImage *image);
void set_pixel_yuv(RGB *pixel);

#endif // __READ_WRITE_H__
