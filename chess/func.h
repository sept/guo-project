#ifndef FUNC_H
#define FUNC_H

typedef unsigned char u8_t;
typedef unsigned int u32_t;

typedef struct  
{
    int w;
    int h;
    int bpp;
    void *memo;
} fbscr_t;

int init_data(void);
int fb_one_pixel(int x, int y, u32_t color);
int fb_line(int x1, int y1, int x2, int y2, u32_t color);
	
#endif
