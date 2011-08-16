#include <stdio.h>
#include "various.h"
#include "func.h"
/**************************
函数：fb_one_pixel()
功能：在屏幕中打印出一亮点
返回值：0   打印出即可 
**************************/
int fb_one_pixel(int x, int y, u32_t color)
{
    *((u32_t *)fb_v.memo + x + y * fb_v.w) = color;   /* 泛指针 强制类型转化 */
    return 0;
}
/********************************
函数：fb_line()
功能：在屏幕中打印出一条斜线（斜率非1/2）
********************************/
int fb_line(int x1, int y1, int x2, int y2, u32_t color)
{
    int dx = x2 - x1;
    int dy = y2 - y1;
    int p = 0;

    p = 2*dy - dx;
    while (x1 <= x2)
    {
    	fb_one_pixel(x1, y1, color);
	x1++;
	if (p < 0)
	{
	    p += 2*dy;
	}
	else
	{
	    y1++;
	    p += 2*(dy - dx);
	}
    }
    return 0;
}
