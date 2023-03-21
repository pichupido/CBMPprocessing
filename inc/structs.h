#ifndef __STRUCTS_H__
#define __STRUCTS_H__

#include <stdlib.h>
#include <stdint.h>

#pragma pack(push, 1)
typedef struct BmpFileHeader {
    char bfType[2];
    uint32_t bfSize;
    uint32_t bfReserved;
    uint32_t bfOffBits;
} BMPFILEHEADER;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct BmpImageHeader {
    uint32_t biSize;
    uint32_t biWidth;
    uint32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    uint32_t biXPelsPerMeter;
    uint32_t biYPelPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
} BMPIMAGEHEADER;
#pragma pack(pop)


typedef struct
{
    double Y;
    double U;
    double V;
} YUV_t;


typedef struct
{
	uint8_t blue;
	uint8_t green;
	uint8_t red;
    YUV_t color_model; 
} RGB;

typedef struct 
{
    BMPFILEHEADER fileheader;
    BMPIMAGEHEADER imageheader;
    RGB *pixel; 
} BMPImage;


typedef struct 
{
    double **matrix;
    int dim;
} kernel_t;


#endif // __STRUCTS_H__
