#include<stdio.h>
#include "various.h"
#include "func.h"
#define BORD 0x0000fff0
#define T___ 0x00000000
#define X___ 0x00ffffff
#define c_w  10
#define c_h  17
/*************************************
定义 光标的图形
**************************************/
static u32_t currsor_pixel[c_w*c_h] = 
{
    BORD,T___,T___,T___,T___,T___,T___,T___,T___,T___,
    BORD,BORD,T___,T___,T___,T___,T___,T___,T___,T___,
    BORD,X___,BORD,T___,T___,T___,T___,T___,T___,T___,
    BORD,X___,X___,BORD,T___,T___,T___,T___,T___,T___,
    BORD,X___,X___,X___,BORD,T___,T___,T___,T___,T___,
    BORD,X___,X___,X___,X___,BORD,T___,T___,T___,T___,
    BORD,X___,X___,X___,X___,X___,BORD,T___,T___,T___,
    BORD,X___,X___,X___,X___,X___,X___,BORD,T___,T___,
    BORD,X___,X___,X___,X___,X___,X___,X___,BORD,T___,
    BORD,X___,X___,X___,X___,X___,X___,X___,X___,BORD,
    BORD,X___,X___,X___,X___,X___,BORD,BORD,BORD,BORD,
    BORD,X___,X___,BORD,X___,X___,BORD,T___,T___,T___,
    BORD,X___,BORD,T___,BORD,X___,X___,BORD,T___,T___,
    BORD,BORD,T___,T___,BORD,X___,X___,BORD,T___,T___,
    BORD,T___,T___,T___,T___,BORD,X___,X___,BORD,T___,
    T___,T___,T___,T___,T___,BORD,X___,X___,BORD,T___,
    T___,T___,T___,T___,T___,T___,BORD,BORD,T___,T___,
};

u32_t bg[c_h*c_w] = {0};

int draw_cursor(int x, int y)
{
    int i,j;

    save_bg(x, y);
    for (i = 0; i < c_h; i++)
    {
        for (j = 0; j < c_w; j++)
        {
            fb_one_pixel(x+j, y+i, currsor_pixel[j+i*c_w]);
        }
    }
    return 0;
}

int save_bg(int x, int y)
{
    int i,j;

    for (j = 0; j < c_h; j++)
    {
        for (i = 0; i < c_w; i++)
        {
            bg[i+j*c_w] = *((u32_t *)fb_v.memo+x+i+(y+j)*fb_v.w);
        }
    }
    return 0;
}

int restore_bg(int x, int y)
{
    int i,j;

    for (j = 0; j < c_h; j++)
    {
        for (i = 0; i < c_w; i++)
        {
            fb_one_pixel(x+i,y+j,bg[i+j*c_w]);
        }
    }
    return 0;
}
