#ifndef IMGP_BITMAP_H
#define IMGP_BITMAP_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "imgp_utils.h"

//struct representing the bitmap header structure
typedef struct 
{
    BITMAPFILEHEADER file_header;
    BITMAPINFOHEADER info_header;
    int error;
} bitmap_headers;

//prints the contents of the two image headers (for debug)
void imgp_bitmap_print_headers(bitmap_headers h);
//reads the headers of the bitmap file
bitmap_headers imgp_bitmap_set_headers(const char* path);
//get file headers for transpose
bitmap_headers imgp_bitmap_rotate_right_headers(bitmap_headers data);
//32 bit functions
//initializes the pixel matrix (32 bit)
pixel_32 **imgp_bitmap_init_matrix_32(bitmap_headers headers);
//reads the pixel data of the bitmap file (pixels are represented in 32 bits)
void imgp_bitmap_read_32(const char *path, bitmap_headers data, pixel_32** pixel_matrix);
//writes the pixel data to a bitmap file (pixels are represented in 32 bits)
void imgp_bitmap_write_32(const char* path, bitmap_headers data, pixel_32 **pixel_matrix);
//gets the pixel at (i, j) in the pixel matrix (the first element is at (0, 0))
pixel_32 imgp_bitmap_get_pixel_32(bitmap_headers data, pixel_32 **pixel_matrix, int i, int j);
//sets the pixel at (i, j) to a new one in the pixel matrix (the first element is at (0, 0))
void imgp_bitmap_set_pixel_32(bitmap_headers data, pixel_32 **pixel_matrix, int i, int j, pixel_32 new_pixel);


//rotates the pixel matrix to right (transpose) 32 bit
pixel_32** imgp_bitmap_rotate_right_32(bitmap_headers data, pixel_32 **pixel_matrix);
//frees the pixel data
void imgp_bitmap_free_pixel_matrix_32(pixel_32 **pixel_matrix, bitmap_headers data);
//selects an area of the image
pixel_32 **imgp_bitmap_crop_32(bitmap_headers data, pixel_32 **pixel_matrix, point pos_1, point pos_2, bitmap_headers *crop_fhd);

//24 bit functions
//initializes the pixel matrix (24 bit)
pixel_24 **imgp_bitmap_init_matrix_24(bitmap_headers headers);
//reads the pixel data of the bitmap file (pixels are represented in 24 bits)
void imgp_bitmap_read_24(const char *path, bitmap_headers data, pixel_24** pixel_matrix);
//writes the pixel data to a bitmap file (pixels are represented in 24 bits)
void imgp_bitmap_write_24(const char* path, bitmap_headers data, pixel_24 **pixel_matrix);
//rotates the pixel matrix to right (transpose) 24 bit
pixel_24** imgp_bitmap_rotate_right_24(bitmap_headers data, pixel_24 **pixel_matrix);


//frees the pixel data
void imgp_bitmap_free_pixel_matrix_24(pixel_24 **pixel_matrix, bitmap_headers data);
//selects an area of the image
pixel_24 **imgp_bitmap_crop_24(bitmap_headers data, pixel_24 **pixel_matrix, point pos_1, point pos_2, bitmap_headers *crop_fhd);
//modifies the image brightness between -1.0 and 1.0 (24 bit) 
void imgp_bitmap_adjust_brightness_24(bitmap_headers data, pixel_24 **pixel_matrix, float value);
#endif