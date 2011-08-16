#include<stdio.h>
#include "func.h"
#include "various.h"

int main(int argc, const char *argv[])
{
    int i, j;
    init_data();                              
    for (i = 0; i < 100; i++)                       /*纵坐标*/
    {
        for (j = 0; j < 100; j++)                   /*横坐标*/ 
        {
            fb_one_pixel(500 + j, 300 + i, 0x0000ff00);
        }
    }
    return 0;
}
