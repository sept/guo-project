#include<stdio.h>
#include "func.h"
#include "various.h"

int main(int argc, const char *argv[])
{
    init_data();                              
#if 0
    int i, j;
    for (i = 0; i < 100; i++)                       /*纵坐标*/
    {
        for (j = 0; j < 100; j++)                   /*横坐标*/ 
        {
            fb_one_pixel(500 + j, 300 + i, 0x0000ff00);
        }
    }
#endif
    fb_line(0, 0, fb_v.w-1, fb_v.h-1, 0x0000ff00);
    
    return 0;
}
