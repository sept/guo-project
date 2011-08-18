#ifndef FUNC_H
#define FUNC_H

#define st_x 150
#define st_y 40
#define x_num 29
#define y_num 24
#define space 30

#define BLACK 0x00ff0000 
#define WHITE 0x00000ff
typedef unsigned char u8_t;
typedef unsigned int u32_t;

typedef struct  
{
    int w;
    int h;
    int bpp;
    void *memo;
} fbscr_t;

typedef struct  
{
    int dx;
    int dy;
    char button;
} mouse_event;
/*声明*/
int init_data(void);
int fb_one_pixel(int x, int y, u32_t color);
int fb_line(int x1, int y1, int x2, int y2, u32_t color);
int fb_circle(int, int, int, u32_t);
int print_board();
int draw_cursor(int, int);
int save_bg(int , int);
int restore_bg(int, int);
int mouse_doing(void);	
int chess_doing();
#endif
