#include<stdio.h>
#include "func.h"
#include "various.h"
/**************************************************************
函数：check()
功能：判断一个交点上的四个方向上是否有四个连续点与起始点颜色一样
输入参数：棋盘中一个点的横纵坐标
返回值：0       没有符合连续五点相连成同一颜色
        winner  符合连续五点相连并是相同颜色
****************************************************************/
int check(int x, int y)
{
    int i,j;                             
    int counter = 0;                       /*每个方向连续上数四个点 及颜色*/
    int who = chess_board[x+y*x_num];      /*记录每次扫描的点 根据坐标确定位置*/

    if (who == 0)                         /*判断没有点 返回 即进行下次扫描*/
    {
        return 0;
    }
    for (i = 1; i < 5; i++)        /*沿x轴的方向*/
    {
        if (chess_board[x+i+y*x_num] == who)
        {
            counter++;
        }
        else
            break;
    }
    if (counter == 4)
    {
        return who;
    }

    counter = 0;                 /*判断之前清零*/
    for (i = 1,j = -1; i < 5; i++,j--)    /*沿右上方向*/
    {
        if (chess_board[x+i+(y+j)*x_num] == who)
        {
            counter++;
        }
        else
            break;
    }
    if (counter == 4)
    {
        return who;
    }

    counter = 0;
    for (j = 1; j < 5; j++)                    /*沿y轴的方向*/
    {
        if (chess_board[x+(y+j)*x_num] == who)
        {
            counter++;
        }
        else
            break;
    }
    if (counter == 4)
    {
        return who;
    }

    counter = 0;
    for (i = 1,j = 1; i < 5; i++,j++)             /*沿右下的方向*/
    {
        if (chess_board[x+i+(y+j)*x_num] == who)
        {
            counter++;
        }
        else
            break;
    }
    if (counter == 4)
    {
        return who;
    }
    return 0;
}
/*************************************************
函数：chess_put()
功能：从第一个点开始扫描所有的点 完成check()函数
输入参数：
返回值：0       扫描所有点之后未发现相连五点成一色
        winner  发现相连五点成一色
*************************************************/
int chess_put(int x, int y)
{
    int i,j;
    int winner = 0;
    chess_board[x+y*x_num] = player;

    for (i = 0; i < y_num; i++)
    {
        for (j = 0; j < x_num; j++)
        {
            if ((winner = check(j, i)) > 0)
            {
                return winner;
            }
        }
    }
    return 0;
}
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
    int winner = 0;
    fb_circle(cx, cy, 10, current_color);            /*画圆*/
    winner = chess_put((cx-st_x)/space, (cy-st_y)/space);
    if (winner > 0)
    {
        return winner;
    }
    if (current_color == WHITE)
    {
        current_color = BLACK;
        player = 1;
    }
    else
    {
        current_color = WHITE;
        player = 2;
    }
    return 0;
}
