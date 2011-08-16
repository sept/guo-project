#include <stdio.h>
#include <stdlib.h>
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
函数：swap()
功能：将指针a和b所指向的内容互换
********************************/
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
/********************************
函数：fb_line()
传入参数：起始和终点坐标 及颜色
      dy,dx 表示出斜率
      判断斜率正或负
功能：在屏幕中打印出一条斜线（斜率非1/2）
返回值：0      
********************************/
int fb_line(int x1, int y1, int x2, int y2, u32_t color)     
{
    int dx = x2 - x1;                                      
    int dy = y2 - y1;
    int inc = ((dx*dy) > 0 ? 1 : -1);                  
    int p = 0;

    if(abs(dx) > abs(dy))                     /*判断dx和dy的绝对值 即斜率的正负*/
    {
        if (dx < 0)                          
        {
        	swap(&x1, &x2);
        	swap(&y1, &y2);
		dx = -dx;
		dy = -dy;
        }
        dy = abs(dy);
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
		y1 += inc;
		p += 2*(dy - dx);
	    }
         }
    }
    else
    {
        if (dy < 0)
        {
        	swap(&x1, &x2);
        	swap(&y1, &y2);
		dx = -dx;
		dy = -dy;
        }
        dx = abs(dx);
        p = 2*dx - dy;
        while (y1 <= y2)
        {
	    fb_one_pixel(x1, y1, color);
	    y1++;
	    if (p < 0)
	    {
		p += 2*dx;
	    }
	    else
	    {
		x1 += inc;
		p += 2*(dx - dy);
	    }
         }
    
    }
	 
    return 0;
}
