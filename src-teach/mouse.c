/*
 *  2010.2.25
 *  mouse.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

#include "common.h"

extern int mouse_open(char *device_name, int *fd);
extern int mouse_parse(const u8_t *buf, mouse_event_t* mevent);
extern int fb_restorecursor(fb_info fb_inf, int x, int y);
extern int fb_drawcursor(fb_info fb_inf, int x, int y);
extern int test_mouse(fb_info fb_inf);

/* **************** end .h */

#define C_WIDTH  10
#define C_HEIGHT 17
#define T___     0XFFFFFFFF
#define BORD     0x0
#define X___     0xFFFF
static unsigned long cursor_pixel[C_WIDTH * C_HEIGHT] = {
	BORD, T___, T___, T___, T___, T___, T___, T___, T___, T___,
	BORD, BORD, T___, T___, T___, T___, T___, T___, T___, T___,
	BORD, X___, BORD, T___, T___, T___, T___, T___, T___, T___,
	BORD, X___, X___, BORD, T___, T___, T___, T___, T___, T___,
	BORD, X___, X___, X___, BORD, T___, T___, T___, T___, T___,
	BORD, X___, X___, X___, X___, BORD, T___, T___, T___, T___,
	BORD, X___, X___, X___, X___, X___, BORD, T___, T___, T___,
	BORD, X___, X___, X___, X___, X___, X___, BORD, T___, T___,
	BORD, X___, X___, X___, X___, X___, X___, X___, BORD, T___,
	BORD, X___, X___, X___, X___, X___, X___, X___, X___, BORD,
	BORD, X___, X___, X___, X___, X___, BORD, BORD, BORD, BORD,
	BORD, X___, X___, BORD, X___, X___, BORD, T___, T___, T___,
	BORD, X___, BORD, T___, BORD, X___, X___, BORD, T___, T___,
	BORD, BORD, T___, T___, BORD, X___, X___, BORD, T___, T___,
	T___, T___, T___, T___, T___, BORD, X___, X___, BORD, T___,
	T___, T___, T___, T___, T___, BORD, X___, X___, BORD, T___,
	T___, T___, T___, T___, T___, T___, BORD, BORD, T___, T___
};
static unsigned long save_cursor[C_WIDTH * C_HEIGHT];

int test_mouse(fb_info fb_inf)
{
	int mfd;
	mouse_open(NULL, &mfd);

	int m_x = fb_inf.w / 2;
	int m_y = fb_inf.h / 2;
	fb_drawcursor(fb_inf, m_x, m_y);

	u8_t buf[8];
	mouse_event_t mevent;
	int mouse = 0;

	while (1)
	{
		int n = read(mfd, buf, 8);
		if (n != -1)
		{
			mouse_parse(buf,&mevent);
			fb_restorecursor(fb_inf, m_x, m_y);
			m_x += mevent.x;
			m_y += mevent.y;

			if (m_x >= (fb_inf.w-C_WIDTH))
			{
				m_x = fb_inf.w-C_WIDTH;
			}
			if(m_y >= (fb_inf.h-C_HEIGHT))
			{
				m_y = fb_inf.h-C_HEIGHT;	
			}
			if(m_x < 0)
			{
				m_x = 0;	
			}
			if(m_y < 0)
			{
				m_y = 0;	
			}
			switch (mevent.button)
			{
				case 0:
					if(mouse == 1)
					{   
						kill(getppid(), SIGSTOP);
						mouse = 0;
					}   
					if (mouse == 2)
					{   
						kill(getppid(), SIGQUIT);
						menu();
						mouse = 0;
					}   
					if (mouse == 3)
					{   
						kill(getppid(),SIGQUIT);
						mouse = 0;
					}   
					break;
				case 1:mouse = 1;break;
				case 2:mouse = 2;break;
				case 3:mouse = 3;break;
				default:break;

			}
			fb_drawcursor(fb_inf, m_x, m_y);
		}
	}

	return 0;
}

int mouse_open(char *device_name, int *fd)
{
	if (NULL == device_name)
		device_name = "/dev/input/mice";

	*fd = open(device_name, O_RDONLY | O_NONBLOCK);
	if(*fd < 0){
		fprintf(stderr, "Open %s:%s\n", device_name, strerror(errno));
		exit(1);
	}

	return 0;
}

int mouse_parse(const u8_t *buf, mouse_event_t* mevent)
{
	switch(buf[0] & 0x7){
		case 1:						/* left */
			mevent->button = 1;
			break;
		case 2:
			mevent->button = 2;		/* right */
			break;
		case 3:
			mevent->button = 3;		/* middle */
			break;
		default:
			mevent->button = 0;
			break;
	}
#if 0
	mevent->x = buf[1];
	mevent->y = buf[2];
#else
	mevent->x =  buf[1] - ((buf[0] & 0x10) ? 256 : 0);
	mevent->y = -buf[2] + ((buf[0] & 0x20) ? 256 : 0); 
#endif
	return 0;
}

/* cursor */

static int fb_pixel_m(fb_info fb_inf, int x, int y, u32_t color)
{
	/* 16 bits */
	u8_t *pos = (u8_t*)fb_inf.fbmem + (fb_inf.w * y + x) * fb_inf.bpp/8;


	switch (fb_inf.bpp){
		case 32:				  /* 32 bits */
			*(pos + 3) = color >> 24;
		case 24:				  /* 24 bits */
			*(pos + 2) = color >> 16;
		case 16:	  		       /* 16 bits */
			*(pos + 1) = color >> 8;
		case 8:			      /* 8 bits */
			*pos = color;
			return 0;
		default:
			return -1;
	}
	return -1;
}

int fb_restorecursor(fb_info fb_inf, int x, int y)
{
	int i, j;
	u32_t color;
	for (j = 0;j<C_HEIGHT;j++)
	{
		for (i = 0;i<C_WIDTH;i++)
		{
			color = save_cursor[i + j * C_WIDTH];
			fb_pixel_m(fb_inf,x+i,y+j,color);
		}
	}

	return 0;
}
static int  fb_savecursor (fb_info fb_inf,int x,int y)
{
	int i,j;
	u32_t color;

	for (j = 0;j<C_HEIGHT;j++)
	{
		for (i = 0;i<C_WIDTH;i++)
		{
			color = *(u32_t*)(fb_inf.fbmem + ((y + j) * fb_inf.w + x + i) * fb_inf.bpp/8);
			save_cursor[i + j * C_WIDTH] = color;
		}
	}
	return 0;
}

int  fb_drawcursor(fb_info fb_inf, int x, int y)
{
	int i,j;
	unsigned int color;

	fb_savecursor (fb_inf,x,y);

	for (j = 0;j<C_HEIGHT;j++)
	{
		for (i = 0;i<C_WIDTH;i++)
		{
			color = cursor_pixel[i + j * C_WIDTH];
			if (color != T___)
				fb_pixel_m(fb_inf,x+i,y+j,color);
		}
	}
	return 0;
}

