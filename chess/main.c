#include<stdio.h>
#include <unistd.h>
#include "func.h"
#include "various.h"

int main(int argc, const char *argv[])
{
    init_data();                              
    print_board();
    mouse_doing();
//    save_bg(500, 300);
//    draw_cursor(500, 300);
//    sleep(1);
//    restore_bg(500, 300);
//    draw_cursor(600, 500);
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
//    fb_line(0, 0, fb_v.w-1, fb_v.h-1, 0x00ff0000);   
//    fb_line(fb_v.w-1, 0, 0, fb_v.h-1, 0x00ff0000);
//    fb_line(300, fb_v.h-1, 500, 0, 0x0000ff00);
//    fb_line(0, 0, fb_v.w-1, 0, 0x00ffffff);
//    fb_line(0, 0, 0, fb_v.h-1, 0x00ffffff);
//    fb_line(fb_v.w-1, fb_v.h-1, fb_v.w-1, 0, 0x00ffffff);
//    fb_line(fb_v.w-1, fb_v.h-1, 0, fb_v.h-1, 0x00ffffff);
//      fb_circle(500, 300, 300, 0x00ff0000);
#if 1
    int i;
    for (i = 0; i < fb_v.w; i++)
    {
        fb_line(0, 0+i*30, fb_v.w-1, 0+i*30, 0x00ffffff);
    }

    printf("location:\n");
    scanf("%d",&i);

    fb_circle(st_x+i*space, st_y+i*space, 10, 0x0000ff00);
#endif
    return 0;
}
