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
int fb_one_pixel(int , int , u32_t );
	
#endif
