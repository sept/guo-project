#ifndef _VAR_H_
#define _VAR_H_
#include "func.h"

extern fbscr_t fb_v;
extern int mx;                    /*在头文件里面声明 为全局变量 外部函数定义后方可使用*/
extern int my;
extern char chess_board[x_num*y_num];
extern char player;
extern u32_t current_color;

#endif
