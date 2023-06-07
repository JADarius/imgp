#ifndef IMGP_UTILS_H
#define IMGP_UTILS_H

//header file that contains structs and functions for basic functionality

//the number of color channels for True Color
#define TRUE_COLOR_CHANNELS 3

//1 byte
typedef unsigned char BYTE;
//4 bytes (unsigned)
typedef unsigned int DWORD;
//4 bytes
typedef int LONG;
//2 bytes
typedef unsigned short WORD;

//__attribute__((packed)) is used to make sure the fields maintain their supposed sizes

//pixel representation in 24 bits (True Color)
typedef struct 
{
    BYTE r;
    BYTE g;
    BYTE b;
}__attribute__((packed)) pixel_24;

//pixel representation in 32 bits (4 channels)
typedef struct 
{
    BYTE r;
    BYTE g;
    BYTE b;
    BYTE a;
}__attribute__((packed)) pixel_32;

//point representation (x, y)
typedef struct 
{
    unsigned int x;
    unsigned int y;
}__attribute__((packed)) point;

//struct representing the file header of the bitmap file (14 bytes)
typedef struct 
{
    WORD file_identity;
    DWORD file_size;
    WORD reserved_1;
    WORD reserved_2;
    DWORD offset;
} __attribute__((packed)) BITMAPFILEHEADER;

//struct representing the information header of the bitmap (40 bytes)
typedef struct 
{
    DWORD info_header_size;
    LONG bitmap_width;
    LONG bitmap_height;
    WORD color_planes_number;
    WORD bits_per_pixel;
    DWORD compression_method;
    DWORD image_size;
    LONG horizontal_resolution;
    LONG vertical_resolution;
    DWORD pallete_color_number;
    DWORD important_colors_number;
}__attribute__((packed)) BITMAPINFOHEADER;

//function used to convert 32 bit pixel values from BGRA to RGBA (the reading is done in BGRA). It can also convert RGBA to BGRA
void imgp_swap_pixel_32_rb_values(pixel_32* p);
//function used to convert 24 bit pixel values from BGR to RGB (the reading is done in BGR). It can also convert RGB to BGR
void imgp_swap_pixel_24_rb_values(pixel_24* p);

#endif