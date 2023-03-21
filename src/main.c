#include <stdio.h>
#include <string.h>
#include "../inc/read_write.h"
#include "../inc/grayscale.h"
#include "../inc/defs.h"
#include "../inc/sobel.h"
#include "../inc/gauss.h"
#include "../inc/laplace.h"
#include "../inc/kernel.h"
#include "../inc/median.h"
#include "../inc/edge_detection.h"
#include "../inc/temp.h"

int main(int argc, char *argv[]) 
{
    int rc = OK;
   
    if (argc < 4)
    {
        printf("usage: ./app.exe file_in.bmp file_out.bmp <operation>\n");
        return ARGS_ERROR;
    }
    BMPImage *image = NULL;

    char *file_in, *file_out = NULL;
    if (!rc)
    {
        file_in = argv[1];
        file_out = argv[2];
    }
    if (!rc)
        rc = read_bmp(file_in, &image);
    
    BMPImage *new_image = alloc_copy_image(image);

    if (!rc)
    {
        printFileHeader(image->fileheader);
        printImageHeader(image->imageheader);
    }

// grayscale
    if (!rc && strcmp(argv[3], "grayscale") == 0)
    {
        rc = grayscale(&new_image, image); // 
        
        write_bmp(file_out, new_image);
    }

//sobel
    if (!rc && strcmp(argv[3], "sobel") == 0 && argc == 6)
    {
        rc = Sobel_operator(&new_image, image, atoi(argv[4]), atoi(argv[5]));

        if (!rc && new_image)
            write_bmp(file_out, new_image);
    }
//laplace

    if (!rc && strcmp(argv[3], "laplace") == 0 && argc == 7)
    {
       rc = laplace_operator(&new_image, image, atoi(argv[4]), atoi(argv[5]), atoi(argv[6]));

        if (!rc && new_image)
            write_bmp(file_out, new_image);
    }

//gauss
    if (!rc && strcmp(argv[3], "gauss") == 0 && argc == 6)
    {
        rc = gauss_blur(&new_image, image, atoi(argv[4]), atof(argv[5]));
        
        if (!rc && new_image)
            write_bmp(file_out, new_image);
    }

//median filter
    if (!rc && strcmp(argv[3], "median") == 0 && argc == 5)

    {
        rc = median_filter(&new_image, image, atoi(argv[4]));

        if (!rc && new_image)
            write_bmp(file_out, new_image);
    }

//user kernel
    if (!rc && strcmp(argv[3], "user") == 0 && argc == 4)

    {
        kernel_t kernel;
        rc = read_kernel(&kernel, stdin);
        if (!rc)
        {
            rc = user_kernel(&new_image, image, &kernel);

            if (new_image)
                write_bmp(file_out, new_image);
        }
    }

// //edge detection
    if (!rc && strcmp(argv[3], "edge") == 0)

    if (!rc)
    {
        rc = edge_detection(&new_image, image);

        if (!rc && new_image)
            write_bmp(file_out, new_image);
    }
    free_image(image);
    free_image(new_image);


    return rc;
}
