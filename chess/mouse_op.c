#include<stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "various.h"
#include "func.h"
#define BORD 0x00f0f000
#define T___ 0x00000000
#define X___ 0x00ffffff
#define c_w  10
#define c_h  17
/*************************************
定义无符号整形的数组
用于 打印出光标的图形
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
/****************************************
定义一个无符号整形数组
用于存放光标所占的屏幕区域
以便用于光标的移动之后 前位置的光标消失
*****************************************/
u32_t bg[c_h*c_w] = {0};
/*****************************************
函数：draw_cursor()
功能：画出光标的形状及其坐标
输入参数：打印光标处的横纵坐标
返回值：0
*****************************************/
int draw_cursor(int x, int y)
{
    int i,j;                                   /*定义 相对屏幕原坐标的偏移量*/

    save_bg(x, y);                             /*先保存该处坐标的区域*/
    for (i = 0; i < c_h; i++)                  /*打印外循环的为纵坐标*/
    {
        for (j = 0; j < c_w; j++)              /*横坐标*/
        {
            fb_one_pixel(x+j, y+i, currsor_pixel[j+i*c_w]);
      /*根据定义光标数组的大小 按点及相应的颜色打印出光标及其所在的位置*/
        }
    }
    return 0;
}
/*********************************************
函数：save_bg()
功能：保存与光标区域大小相等的区域
输入参数：打印区域所在的横纵坐标
*********************************************/
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
/***********************************
函数:restore_bg();
功能：恢复save_bg()中保存的区域
输入参数：打印区域的横纵坐标
***********************************/
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
int get_mouse_info(int fd, mouse_event *p)
{
	char buf[8];
	int n = 0;
	n = read(fd, buf, 3);
	if(n > 0)
	{
		p->dx = buf[1];
		p->dy = -buf[2];
		p->button = (buf[0] & 0x07);
	}
	
	return n;
}

int mouse_doing(void)
{
	int fd = 0;
	mouse_event m_e;

	fd = open("/dev/input/mice", O_RDWR|O_NONBLOCK);
	if(fd == -1)
	{
		perror("mice");
		exit(0);
	}

	mx = fb_v.w/2;
	my = fb_v.h/2;

	draw_cursor(mx, my);

	while(1)
	{
		if(get_mouse_info(fd, &m_e) > 0)
		{
			restore_bg(mx, my);
			mx += m_e.dx;
			my += m_e.dy;
			draw_cursor(mx, my);
		}
    }
	return 0;
}
