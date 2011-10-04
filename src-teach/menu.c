#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <pthread.h>
#include "common.h"

int display_menu(char *, fb_info);

/*主界面 函数*/
void menu(fb_info fb_inf)
{
	display_menu("1.jpg", fb_inf);
	
	if (init_ft("mao.ttf", 0) != 0)
	{
	    fprintf(stderr, "Error initial font\n");
	    return;
	}
	
	display_string("播放", fb_inf.w/8, fb_inf.h/5, fb_inf, 0xFF0000);
	display_string("预览", fb_inf.w/8, fb_inf.h*2/5, fb_inf, 0xFF0000);
	display_string("音乐", fb_inf.w/8, fb_inf.h*3/5, fb_inf, 0xFF0000);
	display_string("退出", fb_inf.w/8, fb_inf.h*4/5, fb_inf, 0xFF0000);

		display_string("上一页",fb_inf.w/2,98*fb_inf.h/100,fb_inf, 0x00ff0000);
		display_string("下一页",3*fb_inf.w/4,98*fb_inf.h/100,fb_inf, 0x00ff0000);
}
