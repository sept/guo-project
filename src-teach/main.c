#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <pthread.h>
#include "common.h"

mouse_event_t mevent;
int main(int argc, char *argv[]) 
{
	if (argc < 2)
		argv[1] = "test.jpg";
	fb_info fb_inf;
	if (init_fb(&fb_inf) < 0)
	{
		fprintf(stderr, "Error initial framebuffer\n");
		return 1;
	}
	pid_t pid;

	menu();
	pid = fork();
	if (pid > 0)
	{
//		pause();
		while (1)	
		{
			display_circle("2.jpg", fb_inf);
			if (init_ft("mao.ttf", 0) != 0){
				fprintf(stderr, "Error initial font\n")	;
				return 1;
			}
			display_string("幻灯片", 32, 400, fb_inf, 0xFF0000);
			sleep(1);

			display_rand("3.jpg", fb_inf);
			if (init_ft("mao.ttf", 0) != 0){
				fprintf(stderr, "Error initial font\n")	;
				return 1;
			}
			display_string("幻灯片", 32, 400, fb_inf, 0xFF0000);
			sleep(1);

			display_line("4.jpg", fb_inf);
			if (init_ft("mao.ttf", 0) != 0){
				fprintf(stderr, "Error initial font\n")	;
				return 1;
			}
			display_string("幻灯片", 32, 400, fb_inf, 0xFF0000);
			sleep(1);

			display_rand_line("5.jpg", fb_inf);
			if (init_ft("mao.ttf", 0) != 0){
				fprintf(stderr, "Error initial font\n")	;
				return 1;
			}
			display_string("幻灯片", 32, 400, fb_inf, 0xFF0000);
			sleep(1);
		}
	}
	else if (pid == 0)
	{
		test_mouse(fb_inf);
	}
	else
	{
		perror("fork failed");	
		exit(-1);
	}

	munmap(fb_inf.fbmem, fb_inf.w * fb_inf.h * fb_inf.bpp / 8);

	return 0;
}
