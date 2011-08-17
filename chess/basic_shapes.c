#include <stdio.h>
#include <stdlib.h>
#include "various.h"
#include "func.h"
/**************************
函数：fb_one_pixel()
功能：在屏幕中打印出一亮点
返回值：0    
**************************/
int fb_one_pixel(int x, int y, u32_t color)
{
    *((u32_t *)fb_v.memo + x + y * fb_v.w) = color;   /* 泛指针 强制类型转化 */
    return 0;
}
/********************************
函数：swap()
功能：将指针a和b所指向的内容互换
返回值：无
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
使用算法：p = 2*dy-dx
功能：在屏幕中打印出一条斜线（斜率非1/2）
返回值：0      
********************************/
int fb_line(int x1, int y1, int x2, int y2, u32_t color)     
{
    int dx = x2 - x1;                                      
    int dy = y2 - y1;
    int inc = ((dx*dy) > 0 ? 1 : -1);                  
    int p = 0;

    if(abs(dx) > abs(dy))             /*判断dx和dy的绝对值 即 随x不断增进 根据算法判断y是否递加*/
    {
        if (dx < 0)                   /* 确保x在x轴使用递加 即 将始末两坐标中x值小的作为起点坐标*/       
        {
        	swap(&x1, &x2);
        	swap(&y1, &y2);
	    	dx = -dx;
		    dy = -dy;
        }
        dy = abs(dy);
        p = 2*dy - dx;                /*画斜线的算法*/
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
    else                             /*随y不断增进 根据算法判断x是否需要递加*/
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
/*************************************
函数：fb_circle()
功能：在屏幕上画出一个实心圆
输入参数：圆的坐标，半径及颜色
使用算法：p = 3-2*r
返回值：0
***************************************/
int fb_circle(int x0, int y0, int r, u32_t color)
{
    int x = 0;                              /*先从圆的最低点开始 即 确定 圆中最低点的横纵坐标*/
    int y = r;
    int p = 3 - 2*r;    
    while(x <= y)                           /* 循环条件 即 满足圆的 1/8之内 其余可按对成以此写出*/
    {
    #if 0
    /*画出由密集点组成的圆圈*/
        fb_one_pixel(x0+x, y0+y, color);
        fb_one_pixel(x0+y, y0+x, color);
        fb_one_pixel(x0+x, y0-y, color);
        fb_one_pixel(x0+y, y0-x, color);

        fb_one_pixel(x0-x, y0+y, color);
        fb_one_pixel(x0-y, y0+x, color);
        fb_one_pixel(x0-y, y0-x, color);
        fb_one_pixel(x0-x, y0-y, color);
    #endif
     /*画出由线组成的实心圆圈*/   
        fb_line(x0+x, y0+y, x0-x, y0+y,color);
        fb_line(x0+y, y0+x, x0-y, y0+x,color);
        fb_line(x0+x, y0-y, x0-x, y0-y,color);
        fb_line(x0+y, y0-x, x0-y, y0-x,color);

        fb_line(x0-x, y0+y, x0+x, y0+y,color);
        fb_line(x0-y, y0+x, x0+y, y0+x,color);
        fb_line(x0-y, y0-x, x0+y, y0-x,color);
        fb_line(x0-x, y0-y, x0+x, y0-y,color);
        if (p < 0)
        {
            p += 4*x + 6;
        }
        else
        {
            p += 4*(x-y) + 10;
            y--;
        }
        x++;

    }
    return 0;
}
