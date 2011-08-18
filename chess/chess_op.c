#include<stdio.h>
#include "func.h"
#include "various.h"
/*************************************************
函数：chess_doing()
功能：在棋盘图形内确定光标的位置在空格内最近的交点
      使得每次点击鼠标画出的圆圈在标准棋盘图形交点处
传入参数：void
返回值：0
**************************************************/
int chess_doing()
{
    int rx = (mx-st_x)%space;                   /*在所属空格内计算出它离上下两线的距离*/
    int ry = (my-st_y)%space;                   /*或所属空格内小的坐标*/ 

    int cx = mx - rx;                           /*计算出交点的坐标*/ 
    int cy = my - ry;
 /*首先规定光标移动的范围*/
    if ((mx < st_x) || (mx > (st_x + (x_num- 1)*space)))
    {
        printf("error.\n");
        return 0;
    }
    if ((my < st_y) || (my > (st_y + (y_num - 1)*space)))
    {
        printf("error.\n");
        return 0;
    }
  /*判断出离最近的交点 确定该交点即为打印圆的圆点*/
    if (rx > space/2)
    {
        cx += space;
    }
    if (ry > space/2)
    {
        cy += space;
    }

    fb_circle(cx, cy, 10, 0x00ff0000);            /*画圆*/
    return 0;
}
