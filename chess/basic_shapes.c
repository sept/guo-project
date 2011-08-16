#include <stdio.h>
#include "various.h"
#include "func.h"

int fb_one_pixel(int x, int y, u32_t color)
{
    *((u32_t *)fb_v.memo + x + y * fb_v.w) = color;
    return 0;
}
