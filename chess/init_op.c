#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include "func.h"

fbscr_t fb_v;
/***************************
函数：init_data()
功能：初始化
*****************************/
int init_data()
{
    int fd = 0;

    struct fb_var_screeninfo fb_var;

    fd = open("/dev/fb0", O_RDWR);
    if (fd < 0)
    {
    	perror("open fb0");
	exit(0);
    }

    if (ioctl(fd, FBIOGET_VSCREENINFO, &fb_var) < 0)
    {
    	perror("ioctl");
	exit(0);
    }
//    printf("w = %d\t h = %d\t dpp = %d\n", fb_var.xres, fb_var.yres, fb_var.bits_per_pixel);
    fb_v.w = fb_var.xres;
    fb_v.h = fb_var.yres;
    fb_v.bpp = fb_var.bits_per_pixel;

    fb_v.memo = mmap(NULL, fb_v.w*fb_v.h*fb_v.bpp/8, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);

    if (fb_v.memo == MAP_FAILED)
    {
    	perror("map");
	exit(0);
    }
    memset(fb_v.memo, 0, fb_v.w*fb_v.h*fb_v.bpp/8);       /*清屏*/

   /* int i ;
    u32_t *p = fb_v.memo;
    for (i = 0; i < fb_v.w; i++)
    {
        p[i] = 0x0000ff00;
    }
  
    for (i = 0; i < fb_v.h; i++)
    {
    	p[i*fb_v.w] = 0x00ff0000;
    }*/
  return 0;
}
