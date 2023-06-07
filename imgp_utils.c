#include "imgp_utils.h"

void imgp_swap_pixel_32_rb_values(pixel_32* p)
{
    //basic swap sequence
    BYTE aux = p->r;
    p->r = p->b;
    p->b = aux;
}

void imgp_swap_pixel_24_rb_values(pixel_24* p)
{
    //basic swap sequence
    BYTE aux = p->r;
    p->r = p->b;
    p->b = aux;
}