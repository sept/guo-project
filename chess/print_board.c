#include<stdio.h>
#include "func.h"

/*************************************
函数：print_board()
功能：打印出五子棋棋盘形式的线
及打出较棋盘大的方框设为底盘 
要求：每格边长为space长度的正方形；
      在图形左边空出一截；
      不能超出屏幕的长度。
输入参数：无
返回值：0
*************************************/
int print_board()
{
    int i,j;
/*打印底边框及颜色*/
    for (i = st_y-20; i < (y_num+1)*space;i++)
    {
        for (j = st_x-50; j < (x_num+5)*space; j++)
        {
            fb_one_pixel(j, i, YELLOW);
        }
    }
/*打印棋盘图形*/
    for (i = 0; i < y_num ; i++)            /*打印出横线*/
    {
        fb_line(st_x, st_y+i*space, st_x+space*(x_num-1), st_y+i*space, 0xffffff);
    }
    for (i = 0; i < x_num; i++)             /*打印出纵线*/
    {
        fb_line(st_x+i*space, st_y, st_x+i*space, st_y+space*(y_num - 1), 0xffffff);
    }
    return 0;
}
