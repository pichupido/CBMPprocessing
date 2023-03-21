#include <stdio.h>
#include <math.h>
#include <inttypes.h>
#include "../inc/read_write.h"
#include "../inc/defs.h"
#include "../inc/temp.h"

void printFileHeader(BMPFILEHEADER fileHeader) 
{
    printf("~~~FILE HEADER INFO~~~");

    printf("\nType: %c%c.\n", fileHeader.bfType[0], fileHeader.bfType[1]);
    printf("Size: %d.\n", fileHeader.bfSize);
    printf("Verify (Must be 0): %d.\n", fileHeader.bfReserved);
    printf("Offset : %d.\n", fileHeader.bfOffBits);
}

void printImageHeader(BMPIMAGEHEADER imageHeader) 
{
    printf("\n~~~IMAGE HEADER INFO~~~");

    printf("\nSize of header: %d.\n", imageHeader.biSize);
    printf("Width: %d.\n", imageHeader.biWidth);
    printf("Height: %d.\n", imageHeader.biHeight);
    printf("Color Planes: %d.\n", imageHeader.biPlanes);
    printf("Bits per Pixel: %d.\n", imageHeader.biBitCount);
    printf("Compression: %d.\n", imageHeader.biCompression);
    printf("Image size: %d.\n", imageHeader.biSizeImage);
    printf("Preferred resolution in pixels per meter (X-Y): %u-%u.\n", imageHeader.biXPelsPerMeter,
           imageHeader.biYPelPerMeter);
    printf("Number color map: %d.\n", imageHeader.biClrUsed);
    printf("Number of significant colors: %d.\n", imageHeader.biClrImportant);
}

int read_bmp(char *path, BMPImage **image) 
{
    FILE *file = fopen(path, "rb");
    int rc = OK;

    *image = calloc(1, sizeof(BMPImage));

    if (!file)
    {
        printf("Could not open the file %s", path);
        rc = FILE_ERROR;
    }
 
    fread(&(*image)->fileheader, sizeof(BMPFILEHEADER), 1, file);
    if (!rc && ((*image)->fileheader.bfType[0] != 'B' || (*image)->fileheader.bfType[1] != 'M')) 
    {
        printf("The file %s is not a valid BMP.", ".bmp");
        rc = FILEHEADER_ERROR;
    }

    fread(&(*image)->imageheader, sizeof(BMPIMAGEHEADER), 1, file);
    if (!rc && ((*image)->imageheader.biSize != 40 || (*image)->imageheader.biCompression != 0 || (*image)->imageheader.biBitCount != 24))
    {
        printf("The file %s is not a valid BMP.", path);
        rc = IMAGEHEADER_ERROR;
    }

    int bpp = (*image)->imageheader.biBitCount / 8;

    int padded_size = (int) (4 * ceil((*image)->imageheader.biWidth / 4.0)) * bpp;
    int total_size = padded_size * (*image)->imageheader.biHeight;

    (*image)->pixel = (RGB*)calloc(total_size, sizeof(RGB)); // !!!!!!!! MEMORY ALLOCATE

    read_pixels(file, (*image));

    if (file)
        fclose(file);
    
    return rc;
}

void write_bmp(char *path, BMPImage *image)
{
    FILE *file = fopen(path, "wb");
    if (!file)
        return;

    fwrite(&(image->fileheader), sizeof(BMPFILEHEADER), 1, file);
    fwrite(&(image->imageheader), sizeof(BMPIMAGEHEADER), 1, file);
    fseek(file, image->fileheader.bfOffBits, SEEK_SET);

    write_pixels(file, image);

    if (file)
        fclose(file);
}


void set_pixel_yuv(RGB *pixel)
{
    (*pixel).color_model.Y = 0.299 * (*pixel).red + 0.587 * (*pixel).green + 0.114 * (*pixel).blue;
    (*pixel).color_model.U = (*pixel).blue - (*pixel).color_model.Y;
    (*pixel).color_model.V = (*pixel).red - (*pixel).color_model.Y;
}

static RGB *get_pixel_in_position(BMPImage *image, int i, int j)
{
    return &(image->pixel[i * image->imageheader.biWidth + j]);
}

void read_pixels(FILE *file, BMPImage *image)
{
    for (unsigned int i = 0; i < image->imageheader.biHeight; i++)
    {
        long begin = ftell(file);
        for (unsigned int j = 0; j < image->imageheader.biWidth; j++)
        {
            RGB *pixel = get_pixel_in_position(image, i, j);
            fread(&(pixel->blue), sizeof(uint8_t), 1, file);
            fread(&(pixel->green), sizeof(uint8_t), 1, file);
            fread(&(pixel->red), sizeof(uint8_t), 1, file);

            set_pixel_yuv(pixel);
        }
        long end = ftell(file);

        if (image->imageheader.biWidth % 4 != 0 && end - begin)
            fseek(file, 4 - (end - begin) % 4, SEEK_CUR);
    }
}

void write_pixels(FILE *file, BMPImage *image)
{
    for (unsigned int i = 0; i < image->imageheader.biHeight; i++)
    {
        long begin = ftell(file);
        for (unsigned int j = 0; j < image->imageheader.biWidth; j++)
        {
            RGB *pixel = get_pixel_in_position(image, i, j);
            fwrite(&(pixel->blue), sizeof(uint8_t), 1, file);
            fwrite(&(pixel->green), sizeof(uint8_t), 1, file);
            fwrite(&(pixel->red), sizeof(uint8_t), 1, file);            
        }
        long end = ftell(file);

        if (image->imageheader.biWidth % 4 != 0 && end - begin)
            fseek(file, 4 - (end - begin) % 4, SEEK_CUR);
    }
}

void free_image(BMPImage *image) 
{
    if (image->pixel)
        free(image->pixel);
    free(image);
}
