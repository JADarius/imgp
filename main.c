#include "imgp_bitmap.h"

int main()
{
    bitmap_headers headers;
    pixel_24 **pixel_matrix;

    headers = imgp_bitmap_set_headers("mountain.bmp");

    if (headers.error == 1)
        return 0;

    if (headers.info_header.bits_per_pixel == 24)
    {
        pixel_matrix = imgp_bitmap_init_matrix_24(headers);

        imgp_bitmap_read_24("mountain.bmp", headers, pixel_matrix);
        imgp_bitmap_write_24("output_24.bmp", headers, pixel_matrix);

        imgp_bitmap_free_pixel_matrix_24(pixel_matrix, headers);
    }

    return 0;
}