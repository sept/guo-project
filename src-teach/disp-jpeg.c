/********************************************************************
文    件:    display-jpep.c
功    能:    显示图片特效
函数列表:
日    期:
*********************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include "common.h"

/********************************************************************
函    数:        display_four
功    能:        实现中间两根线分别拉伸则出现四块
传入参数:        filename : 要显示的图片的名字
                 fb_info  : 图片显示的缓存区
传出参数:        fb_info  : 图片显示的信息
返    回:
修改记录:
********************************************************************/
int display_four(char *filename, fb_info fb_inf)
{
    fb_info jpeg_inf;
    
    /*get the information of the picture*/
    u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
    u8_t * scale_buf = scale24(buf24, fb_inf, jpeg_inf);
    u32_t *buf32 = rgb24to32(scale_buf, fb_inf);

    int i = 0;
    int j = 0;
    
    for (i = fb_inf.h/2; i > 0; i--)
    {
        for (j = 0; j < fb_inf.w; j++)
        {
	    fb_pixel(fb_inf, j, i, buf32[j + i * fb_inf.w]);
	    fb_pixel(fb_inf,j,fb_inf.h-i-1,buf32[j+(fb_inf.h-i-1)*(fb_inf.w)]);
	}
	
	usleep(900);
    }

    free(buf24);
    free(scale_buf);
    free(buf32);
    return 0;
}

/********************************************************************
函    数:        display_line
功    能:        按线显示图片    
传入参数:        filename : 要显示的图片的名字
                 fb_info  : 图片显示的缓存区
传出参数:        fb_info  : 图片显示的信息
返    回:
修改记录:
********************************************************************/
int display_line(char *filename, fb_info fb_inf)
{
    fb_info jpeg_inf;
	
    /*提取图片信息*/
    u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
    u8_t * scale_buf = scale24(buf24, fb_inf, jpeg_inf);
    u32_t *buf32 = rgb24to32(scale_buf, fb_inf);

    int i = 0;
    int j = 0;
    
    for(i = 0; i < fb_inf.h/2; ++i)
    {
        for (j = 0; j < fb_inf.w; ++j)
        {    
	    /*检测鼠标动作的函数*/
            if (back_main(buf24, scale_buf, buf32, fb_inf) == 1)
            {
                 return 0;
            }

            fb_pixel(fb_inf, j, i, buf32[j + i * fb_inf.w]);
	    fb_pixel(fb_inf,j,fb_inf.h-i-1,buf32[j+(fb_inf.h-i-1)*(fb_inf.w)]);
        }

        usleep(900);
    }

    free(buf24);
    free(scale_buf);
    free(buf32);
   
    return 0;
}

/********************************************************************
函    数:        display_circle
功    能:        按圆显示图片    
传入参数:        filename : 要显示的图片的名字
                 fb_info  : 图片显示的缓存区
传出参数:        fb_info  : 图片显示的信息
返    回:
修改记录:
********************************************************************/
int display_circle(char *filename, fb_info fb_inf)
{
    fb_info jpeg_inf;
	
    u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
    u8_t * scale_buf = scale24(buf24, fb_inf, jpeg_inf);
    u32_t *buf32 = rgb24to32(scale_buf, fb_inf);

    int i = 0;
    int j = 0;
    int r = 0;
    long long a,b; 	
    int x = fb_inf.w/2;
    int y = fb_inf.h/2;

    for(r = 0;r < 5*fb_inf.w/8;r++)
    {
        for(i = 0;i<fb_inf.h;i++)
        {
            for(j = 0;j < fb_inf.w; j++)	
            {
                a = (j - x) * (j - x) + (i - y) * (i - y);
                b = r * r;
		
                if (abs(a - b) < 4 * r)
		{
                    if (back_main(buf24, scale_buf, buf32, fb_inf) == 1)
                    {
		        return 0;
		    }

                    fb_pixel(fb_inf,j,i,buf32[j + i * fb_inf.w]);
                 }
	    }
	}
    }
	
    free(buf24);
    free(scale_buf);
    free(buf32);
	
    return 0;
}

/********************************************************************
函    数:        display_scale
功    能:        图片的缩放    
传入参数:        filename : 要显示的图片的名字
		 jpeg_w   : 图片的长
		 jpeg_h   : 图片的宽
		 jpeg_x   : 图片所在的坐标 
		 jpeg_y   : 
                 fb_info  : 图片显示的缓存区
传出参数:        fb_info  : 图片显示的信息
返    回:
修改记录:
********************************************************************/
int display_scale(char *filename,int jpeg_w,int jpeg_h,int jpeg_x,int jpeg_y,fb_info fb_inf)
{
	if(jpeg_w >= fb_inf.w || jpeg_h >= fb_inf.h||jpeg_w < 0|| jpeg_h < 0)
	{
		fprintf(stderr, "the jpeg_w or jpeg_h is error!\n");
		return -1;
	}
	if(jpeg_x >= fb_inf.w || jpeg_y >= fb_inf.h || jpeg_x < 0 || jpeg_y < 0)
	{
		fprintf(stderr, "the jpeg_x or jpeg_y is error!\n");
		return -1;
	}
	fb_info jpeg_inf;

	fb_info fb_inff;
	fb_inff.h = jpeg_h;
	fb_inff.w = jpeg_w;
	fb_inff.bpp = fb_inf.bpp;
	fb_inf.fbmem = fb_inf.fbmem;

	u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
	u8_t *scale_buf = scale24(buf24, fb_inff, jpeg_inf);
	u32_t *buf32 = rgb24to32(scale_buf, fb_inff);
	
	int i ,j;

	for (i = 0; i < fb_inff.h; ++i)
	{
		for (j = 0 ;j < fb_inff.w; ++j)	
		{
                    if (back_main(buf24, scale_buf, buf32, fb_inf) == 1)
                    {
		        return 0;
		    }
		    fb_pixel(fb_inf,j+jpeg_x,i+jpeg_y,buf32[j + i*fb_inff.w]);
		}
	}

	free(buf24);
	free(scale_buf);
	free(buf32);

	return 0;
}

/*********************************************************
函    名：
功    能：
传入参数：
传出参数：
返    回:
特殊说明:
*********************************************************/
int display_scale_pull(char *filename, fb_info fb_inf)
{
    int i = 0;
    int j = 0;
    int ii;
    int x,y;
    x = fb_inf.w/50;
    y = fb_inf.h/50;

   for(ii = 0; ii < 30; ii++)
    {
    	i += x;
	j += y;		

    	if (j >= fb_inf.h/2) j = fb_inf.h/2;
	if (i >= fb_inf.w/2) i = fb_inf.w/2;

        display_scale(filename, fb_inf.w/2 + i-1, fb_inf.h/2 + j-1, 0, 0, fb_inf); 
    }

    return 0;
}

/********************************************************************
函    数:        display_jpeg
功    能:        显示图片    
传入参数:        filename : 要显示的图片的名字
                 fb_info  : 图片显示的缓存区
传出参数:        fb_info  : 图片显示的信息
返    回:
修改记录:
********************************************************************/
int display_jpeg(char *filename, fb_info fb_inf)
{
    fb_info jpeg_inf;
	
    u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
    u8_t * scale_buf = scale24(buf24, fb_inf, jpeg_inf);
    u32_t *buf32 = rgb24to32(scale_buf, fb_inf);

    int i = 0;
    int j = 0;
    for (i = fb_inf.h-1; i > 0 ; i--)
    {
        for (j = 0; j < fb_inf.w ; j++)
	{
	    if (back_main(buf24, scale_buf, buf32, fb_inf) == 1)
            {
                return 0;
            }

            fb_pixel(fb_inf, j, i, buf32[j + i * fb_inf.w]);
        }
    }

    free(buf24);
    free(scale_buf);
    free(buf32);
	
    return 0;
}

/********************************************************************
函    数:        display_circle
功    能:        按圆显示    
传入参数:        filename : 要显示的图片的名字
                 fb_info  : 图片显示的缓存区
传出参数:        fb_info  : 图片显示的信息
返    回:
修改记录:
********************************************************************/
int display_menu(char *filename, fb_info fb_inf)
{

    fb_info jpeg_inf;
	
    u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
    u8_t * scale_buf = scale24(buf24, fb_inf, jpeg_inf);
    u32_t *buf32 = rgb24to32(scale_buf, fb_inf);

    int i = 0;
    int j = 0;

    for (i = fb_inf.h-1; i > 0 ; i--)
    {
        for (j = 0; j < fb_inf.w ; j++)
	{
            fb_pixel(fb_inf, j, i, buf32[j + i * fb_inf.w]);
        }
    }

    free(buf24);
    free(scale_buf);
    free(buf32);
	
    return 0;
}

/********************************************************************
函    数:        display_rand
功    能:        随机出现点    
传入参数:        filename : 要显示的图片的名字
                 fb_info  : 图片显示的缓存区
传出参数:        fb_info  : 图片显示的信息
返    回:
修改记录:
********************************************************************/
int display_rand(char *filename, fb_info fb_inf)
{
    fb_info jpeg_inf;
    
    u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
    u8_t * scale_buf = scale24(buf24, fb_inf, jpeg_inf);
    u32_t *buf32 = rgb24to32(scale_buf, fb_inf);
    
    int i = 0;
    int j = 0;
    int m = fb_inf.w * (fb_inf.h-1) * fb_inf.bpp;

    while (m--)
    {
        i = rand() % fb_inf.w;
        j = rand()%fb_inf.h;
                
        if (back_main(buf24, scale_buf, buf32, fb_inf) == 1)
	{
            return 0;
	}
		
	fb_pixel(fb_inf, i, j, buf32[i + j * fb_inf.w]);
    }

    free(buf24);
    free(scale_buf);
    free(buf32);
	
    return 0;
}

/********************************************************************
函    数:        display_rand_line
功    能:        随机按线显示图片    
传入参数:        filename : 要显示的图片的名字
                 fb_info  : 图片显示的缓存区
传出参数:        fb_info  : 图片显示的信息
返    回:
修改记录:
********************************************************************/
int display_rand_line(char *filename, fb_info fb_inf)
{
    fb_info jpeg_inf;
    
    u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
    u8_t * scale_buf = scale24(buf24, fb_inf, jpeg_inf);
    u32_t *buf32 = rgb24to32(scale_buf, fb_inf);

    int j = 0;
    int i = 0;
    
    int m = fb_inf.w * 8;

    while (m--)
    {
        i = rand() % fb_inf.h;
        
	for (j = 0; j < fb_inf.w; j++)
        {
	    if (back_main(buf24, scale_buf, buf32, fb_inf) == 1)
            {
		 return 0;
            }

            fb_pixel(fb_inf, j, i, buf32[j + i * fb_inf.w]);
        }
    }

    free(buf24);
    free(scale_buf);
    free(buf32);
	
    return 0;
}

/********************************************************************
函    数:        back_main
功    能:        检测鼠标动作    
传入参数:        buf24     : 
                 scale_buf : 
		 buf32     :  
传出参数:        fb_info   : 图片信息
返    回:
修改记录:
********************************************************************/
int back_main(u8_t *buf24, u8_t *scale_buf, u32_t *buf32, fb_info fb_inf)
{    
    while (dis_flag % 2 == 0 && start == 1)
    {
        display_string("开始", 100, 100, fb_inf, 0xFF0000);

	if (restar_flag == 1)
        {   
	    /*显示主界面*/
            menu(fb_inf);
             
	    /*在检测到鼠标停止以后释放函数中申请的内存防止内存泄漏*/
	    free(buf24);
	    free(scale_buf);
	    free(buf32);
	    
	    return 1;
         }
    }

    if (restar_flag == 1)
    {
         menu(fb_inf);
	 
	 free(buf24);
	 free(scale_buf);
	 free(buf32);
         
	 return 1;
    }

    return 0;
}
