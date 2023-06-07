#include "imgp_bitmap.h"
#include "imgp_utils.h"

int min(int a, int b)
{
    if (a <= b)
        return a;

    return b;
}

int max(int a, int b)
{
    if (a <= b)
        return b;

    return a;
}

void imgp_bitmap_print_headers(bitmap_headers h)
{
    // file header
    printf("%hu\n", h.file_header.file_identity);
    printf("%u\n", h.file_header.file_size);
    printf("%hd\n", h.file_header.reserved_1);
    printf("%hd\n", h.file_header.reserved_2);
    printf("%u\n\n", h.file_header.offset);

    // info header
    printf("%u\n", h.info_header.info_header_size);
    printf("%d\n", h.info_header.bitmap_width);
    printf("%d\n", h.info_header.bitmap_width);
    printf("%hd\n", h.info_header.color_planes_number);
    printf("%hd\n", h.info_header.bits_per_pixel);
    printf("%u\n", h.info_header.compression_method);
    printf("%u\n", h.info_header.image_size);
    printf("%d\n", h.info_header.vertical_resolution);
    printf("%d\n", h.info_header.horizontal_resolution);
    printf("%u\n", h.info_header.pallete_color_number);
    printf("%u\n", h.info_header.important_colors_number);
}

bitmap_headers imgp_bitmap_set_headers(const char *path)
{
    FILE *f = fopen(path, "rb");

    bitmap_headers fhd;
    fhd.error = 0;

    // checks if the stream is valid
    if (f == NULL)
    {
        perror("imgp_bitmap_set_headers: FILE f is NULL");
        fhd.error = 1;
        return fhd;
    }

    // reads the first 14 bytes (the ones that represent the file header)
    fread(&fhd.file_header, sizeof(fhd.file_header), 1, f);

    // check if the file header information is valid
    if (fhd.file_header.file_identity != 0x4D42)
        perror("imgp_bitmap_set_headers: file identity does not match");

    // reads the next 40 bytes (the ones that represent the information header)
    fread(&fhd.info_header, sizeof(fhd.info_header), 1, f);

    printf("%s\n", "<bitmap width> <bitmap height> <image size in bytes> <number of bits per pixel>");
    printf("%d%s%d%s%d%s%d\n", fhd.info_header.bitmap_width, " ", fhd.info_header.bitmap_height, " ", fhd.info_header.image_size, " ",
           fhd.info_header.bits_per_pixel);

    fclose(f);

    return fhd;
}

pixel_32 **imgp_bitmap_init_matrix_32(bitmap_headers headers)
{
    pixel_32 **pixel_matrix = malloc(headers.info_header.bitmap_height * sizeof(pixel_32 *));

    for (int i = 0; i < headers.info_header.bitmap_height; i++)
        pixel_matrix[i] = malloc(headers.info_header.bitmap_width * sizeof(pixel_32));

    return pixel_matrix;
}

void imgp_bitmap_read_32(const char *path, bitmap_headers data, pixel_32** pixel_matrix)
{
    FILE *f = fopen(path, "rb");

    // size of the pixel matrix
    int size = data.info_header.bitmap_width * data.info_header.bitmap_height;

    // jumps to the start position of the pixel matrix
    fseek(f, data.file_header.offset, SEEK_SET);

    for (int i = data.info_header.bitmap_height - 1; i >= 0; i--)
        for (int j = 0; j < data.info_header.bitmap_width; j++)
        {
            // reads and stores the 4 bytes correspoding to each index
            BYTE aux[4];
            fread(aux, 4, 1, f);

            // sets the BGRA values
            pixel_matrix[i][j].r = aux[0];
            pixel_matrix[i][j].g = aux[1];
            pixel_matrix[i][j].b = aux[2];
            pixel_matrix[i][j].a = aux[3];

            // converts the BGRA values to RGBA
            imgp_swap_pixel_32_rb_values(&pixel_matrix[i][j]);
        }

    fclose(f);
}

bitmap_headers imgp_bitmap_rotate_right_headers(bitmap_headers data)
{
    bitmap_headers fhd;
    fhd = data;

    LONG aux;

    aux = fhd.info_header.bitmap_width;
    fhd.info_header.bitmap_width = fhd.info_header.bitmap_height;
    fhd.info_header.bitmap_height = aux;

    printf("%s\n", "<bitmap width> <bitmap height> <image size in bytes> <number of bits per pixel>");
    printf("%d%s%d%s%d%s%d\n", fhd.info_header.bitmap_width, " ", fhd.info_header.bitmap_height, " ", fhd.info_header.image_size, " ",
           fhd.info_header.bits_per_pixel);

    return fhd;
}

// 32 bit functions
void imgp_bitmap_write_32(const char *path, bitmap_headers data, pixel_32 **pixel_matrix)
{
    bitmap_headers fhd;
    int pixel_matrix_size = 4 * data.info_header.bitmap_width * data.info_header.bitmap_height;

    // file header information
    fhd.file_header.file_identity = 0x4D42;
    fhd.file_header.file_size = sizeof(fhd.file_header) + sizeof(fhd.info_header) + pixel_matrix_size;
    fhd.file_header.reserved_1 = 0;
    fhd.file_header.reserved_2 = 0;
    fhd.file_header.offset = fhd.file_header.file_size - pixel_matrix_size;

    // info header information
    fhd.info_header.info_header_size = 40;
    fhd.info_header.bitmap_width = data.info_header.bitmap_width;
    fhd.info_header.bitmap_height = data.info_header.bitmap_height;
    fhd.info_header.color_planes_number = 1;
    fhd.info_header.bits_per_pixel = 32;
    fhd.info_header.compression_method = 0;
    fhd.info_header.image_size = pixel_matrix_size;
    fhd.info_header.horizontal_resolution = 0;
    fhd.info_header.vertical_resolution = 0;
    fhd.info_header.pallete_color_number = 0;
    fhd.info_header.important_colors_number = 0;

    // swaping RGBA to BGRA pixels due to file nature
    for (int i = data.info_header.bitmap_height - 1; i >= 0; i--)
        for (int j = 0; j < data.info_header.bitmap_width; j++)
            imgp_swap_pixel_32_rb_values(&pixel_matrix[i][j]);

    // writing to bitmap file
    FILE *f = fopen(path, "wb");

    fwrite(&fhd.file_header, 1, sizeof(fhd.file_header), f);
    fwrite(&fhd.info_header, 1, sizeof(fhd.info_header), f);

    fseek(f, fhd.file_header.offset, SEEK_SET);

    for (int i = data.info_header.bitmap_height - 1; i >= 0; i--)
        for (int j = 0; j < data.info_header.bitmap_width; j++)
            fwrite((BYTE *)(&pixel_matrix[i][j]), 1, 4, f);

    // reswaping (BGRA to RGBA)
    for (int i = data.info_header.bitmap_height - 1; i >= 0; i--)
        for (int j = 0; j < data.info_header.bitmap_width; j++)
            imgp_swap_pixel_32_rb_values(&pixel_matrix[i][j]);

    fclose(f);
}

pixel_32 imgp_get_pixel_32(bitmap_headers data, pixel_32 **pixel_matrix, int i, int j)
{
    return pixel_matrix[i][j];
}

void imgp_set_pixel_32_at(bitmap_headers data, pixel_32 **pixel_matrix, int i, int j, pixel_32 new_pixel)
{
    pixel_matrix[j][i].r = new_pixel.r;
    pixel_matrix[j][i].g = new_pixel.g;
    pixel_matrix[j][i].b = new_pixel.b;
    pixel_matrix[j][i].a = new_pixel.a;
}

pixel_32** imgp_bitmap_rotate_right_32(bitmap_headers data, pixel_32 **pixel_matrix)
{
    pixel_32 **r_img = malloc(data.info_header.bitmap_height * sizeof(pixel_32 *));

    // the new image has reversed sizes (the width of the old image is the height of the new image and same for height)
    for (int i = 0; i < data.info_header.bitmap_height; i++)
        r_img[i] = malloc(data.info_header.bitmap_width * sizeof(pixel_32));

    // transpose
    for (int i = data.info_header.bitmap_height - 1; i >= 0; i--)
        for (int j = 0; j < data.info_header.bitmap_width; j++)
            r_img[i][j] = pixel_matrix[j][i];

    // reverses columns (due to faulty transpose algorithm?)
    for (int i = data.info_header.bitmap_height - 1; i >= 0; i--)
        for (int j = 0; j < data.info_header.bitmap_width / 2; j++)
        {
            pixel_32 aux = r_img[i][data.info_header.bitmap_width - j - 1];
            r_img[i][data.info_header.bitmap_width - j - 1] = r_img[i][j];
            r_img[i][j] = aux;
        }

    return r_img;
}

void imgp_bitmap_free_pixel_matrix_32(pixel_32 **pixel_matrix, bitmap_headers data)
{
    for (int i = 0; i < data.info_header.bitmap_height; i++)
        free(pixel_matrix[i]);

    free(pixel_matrix);
}

pixel_32 **imgp_bitmap_crop_32(bitmap_headers data, pixel_32 **pixel_matrix, point pos_1, point pos_2, bitmap_headers *crop_fhd)
{
    // error handling
    if (pos_1.x < 0 || pos_1.x > data.info_header.bitmap_width)
        return NULL;

    if (pos_1.y < 0 || pos_1.y > data.info_header.bitmap_height)
        return NULL;

    if (pos_2.x < 0 || pos_2.x > data.info_header.bitmap_width)
        return NULL;

    if (pos_2.y < 0 || pos_2.y > data.info_header.bitmap_height)
        return NULL;

    unsigned int crop_width = abs(pos_1.x - pos_2.x);
    unsigned int crop_height = abs(pos_1.y - pos_2.y);

    pixel_32 **crop_data = malloc(crop_height * sizeof(pixel_32 *));

    for (int i = 0; i < crop_height; i++)
        crop_data[i] = malloc(crop_width * sizeof(pixel_32));

    for (int i = min(pos_1.y, pos_2.y); i < max(pos_1.y, pos_2.y); i++)
        for (int j = min(pos_1.x, pos_2.x); j < max(pos_1.x, pos_2.x); j++)
            crop_data[i - min(pos_1.y, pos_2.y)][j - min(pos_1.x, pos_2.x)] = pixel_matrix[i][j];

    *crop_fhd = data;

    crop_fhd->info_header.bitmap_width = crop_width;
    crop_fhd->info_header.bitmap_height = crop_width;

    return crop_data;
}

// 24 bit functions
pixel_24 **imgp_bitmap_init_matrix_24(bitmap_headers headers)
{
    pixel_24 **pixel_matrix = malloc(headers.info_header.bitmap_height * sizeof(pixel_24 *));

    for (int i = 0; i < headers.info_header.bitmap_height; i++)
        pixel_matrix[i] = malloc(headers.info_header.bitmap_width * sizeof(pixel_24));

    return pixel_matrix;
}

void imgp_bitmap_read_24(const char *path, bitmap_headers data, pixel_24** pixel_matrix)
{
    FILE *f = fopen(path, "rb");

    // size of the pixel matrix
    int size = data.info_header.bitmap_width * data.info_header.bitmap_height;

    // jumps to the start position of the pixel matrix
    fseek(f, data.file_header.offset, SEEK_SET);

    for (int i = data.info_header.bitmap_height - 1; i >= 0; i--)
        for (int j = 0; j < data.info_header.bitmap_width; j++)
        {
            // reads and stores the 3 bytes correspoding to each index
            BYTE aux[3];
            fread(aux, 3, 1, f);

            // sets the BGR values
            
            pixel_matrix[i][j].r = aux[0];
            pixel_matrix[i][j].g = aux[1];
            pixel_matrix[i][j].b = aux[2];

            // converts the BGR values to RGB
            imgp_swap_pixel_24_rb_values(&pixel_matrix[i][j]);
        }

    fclose(f);
}

void imgp_bitmap_write_24(const char *path, bitmap_headers data, pixel_24 **pixel_matrix)
{
    bitmap_headers fhd;
    int pixel_matrix_size = 3 * data.info_header.bitmap_width * data.info_header.bitmap_height;

    // file header information
    fhd.file_header.file_identity = 0x4D42;
    fhd.file_header.file_size = sizeof(fhd.file_header) + sizeof(fhd.info_header) + pixel_matrix_size;
    fhd.file_header.reserved_1 = 0;
    fhd.file_header.reserved_2 = 0;
    fhd.file_header.offset = fhd.file_header.file_size - pixel_matrix_size;

    // info header information
    fhd.info_header.info_header_size = 40;
    fhd.info_header.bitmap_width = data.info_header.bitmap_width;
    fhd.info_header.bitmap_height = data.info_header.bitmap_height;
    fhd.info_header.color_planes_number = 1;
    fhd.info_header.bits_per_pixel = 24;
    fhd.info_header.compression_method = 0;
    fhd.info_header.image_size = pixel_matrix_size;
    fhd.info_header.horizontal_resolution = 0;
    fhd.info_header.vertical_resolution = 0;
    fhd.info_header.pallete_color_number = 0;
    fhd.info_header.important_colors_number = 0;

    // swaping RGB to BGR pixels due to file nature
    for (int i = data.info_header.bitmap_height - 1; i >= 0; i--)
        for (int j = 0; j < data.info_header.bitmap_width; j++)
            imgp_swap_pixel_24_rb_values(&pixel_matrix[i][j]);

    // writing to bitmap file
    FILE *f = fopen(path, "wb");

    fwrite(&fhd.file_header, 1, sizeof(fhd.file_header), f);
    fwrite(&fhd.info_header, 1, sizeof(fhd.info_header), f);

    fseek(f, fhd.file_header.offset, SEEK_SET);

    for (int i = data.info_header.bitmap_height - 1; i >= 0; i--)
        for (int j = 0; j < data.info_header.bitmap_width; j++)
            fwrite((BYTE *)(&pixel_matrix[i][j]), 1, 3, f);

    // reswaping (BGR to RGB)
    for (int i = data.info_header.bitmap_height - 1; i >= 0; i--)
        for (int j = 0; j < data.info_header.bitmap_width; j++)
            imgp_swap_pixel_24_rb_values(&pixel_matrix[i][j]);

    fclose(f);
}

pixel_24** imgp_bitmap_rotate_right_24(bitmap_headers data, pixel_24 **pixel_matrix)
{
    pixel_24 **r_img = malloc(data.info_header.bitmap_height * sizeof(pixel_24 *));

    // the new image has reversed sizes (the width of the old image is the height of the new image and same for height)
    for (int i = 0; i < data.info_header.bitmap_height; i++)
        r_img[i] = malloc(data.info_header.bitmap_width * sizeof(pixel_24));

    // transpose
    for (int i = data.info_header.bitmap_height - 1; i >= 0; i--)
        for (int j = 0; j < data.info_header.bitmap_width; j++)
            r_img[i][j] = pixel_matrix[j][i];

    return r_img;
}

void imgp_bitmap_free_pixel_matrix_24(pixel_24 **pixel_matrix, bitmap_headers data)
{
    for (int i = 0; i < data.info_header.bitmap_height; i++)
        free(pixel_matrix[i]);

    free(pixel_matrix);
}

pixel_24 **imgp_bitmap_crop_24(bitmap_headers data, pixel_24 **pixel_matrix, point pos_1, point pos_2, bitmap_headers *crop_fhd)
{
    // error handling
    if (pos_1.x < 0 || pos_1.x > data.info_header.bitmap_width)
        return NULL;

    if (pos_1.y < 0 || pos_1.y > data.info_header.bitmap_height)
        return NULL;

    if (pos_2.x < 0 || pos_2.x > data.info_header.bitmap_width)
        return NULL;

    if (pos_2.y < 0 || pos_2.y > data.info_header.bitmap_height)
        return NULL;

    unsigned int crop_width = abs(pos_1.x - pos_2.x);
    unsigned int crop_height = abs(pos_1.y - pos_2.y);

    pixel_24 **crop_data = malloc(crop_height * sizeof(pixel_24 *));

    for (int i = 0; i < crop_height; i++)
        crop_data[i] = malloc(crop_width * sizeof(pixel_24));

    for (int i = min(pos_1.y, pos_2.y); i < max(pos_1.y, pos_2.y); i++)
        for (int j = min(pos_1.x, pos_2.x); j < max(pos_1.x, pos_2.x); j++)
            crop_data[i - min(pos_1.y, pos_2.y)][j - min(pos_1.x, pos_2.x)] = pixel_matrix[i][j];

    *crop_fhd = data;

    crop_fhd->info_header.bitmap_width = crop_width;
    crop_fhd->info_header.bitmap_height = crop_width;

    return crop_data;
}

int check_bounds(int value)
{
    if(value > 255)
        return 255;
    else if (value < 0)
        return 0;
}

int get_value(BYTE channel, float value)
{
    int aux = channel;
    aux = aux * (1 + value);

    return check_bounds(aux);
}

void modify_pixel_24(pixel_24* pixel, int n_r, int n_g, int n_b)
{
    pixel->r = n_r;
    pixel->g = n_g;
    pixel->b = n_b;
}

void imgp_bitmap_adjust_brightness_24(bitmap_headers data, pixel_24 **pixel_matrix, float value)
{
    if(value < -1.0f || value > 1.0f)
    {
        printf("imgp_bitmap_adjust: Warning, float value should be between -1.0 and 1.0\n");
        printf("The float value will be normalized to -1.0 or 1.0\n");

        if(value < 0)
            value = -1.0f;
        else
            value = 1.0f;
    }

    for (int i = data.info_header.bitmap_height - 1; i >= 0; i--)
        for(int j = 0; j < data.info_header.bitmap_width; j++)
            modify_pixel_24(&pixel_matrix[i][j], get_value(pixel_matrix[i][j].r, value), get_value(pixel_matrix[i][j].g, value),
                get_value(pixel_matrix[i][j].b, value));
}