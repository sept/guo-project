CFLAGS = -Wall -g
CC = gcc

src = $(wildcard *.c)
	#代替所有.c文件
obj = $(patsubst %.c, %.o, $(src))
	#提取所有.c文件 将.c文件 都编译成.o文件
main:$(obj)
	$(CC) $^ -o $@
%.o:%.c
	$(CC) $(CFLAGS) $^ -c

#"$^" 表示：所有依赖文件
#“$<” 表示：第一个依赖文件
#“$@” 表示：目标文件
#“%.c  %.o” 表示 当前目录下所有.c 和 .o 文件



#main:main.o init_op.o basic_shapes.o print_board.o mouse_op.o chess_op.o
#	gcc main.o init_op.o basic_shapes.o print_board.o mouse_op.o chess_op.o -o main
#main.o:main.c
#	gcc main.c -c
#init_op.o:init_op.c
#	gcc init_op.c -c
#basic_shapes.o:basic_shapes.c
#	gcc basic_shapes.c -c
#print_board.o:print_board.c
#	gcc print_board.c -c
#mouse_op.o:mouse_op.c
#	gcc mouse_op.c -c
#chess_op.o:chess_op.c
#	gcc chess_op.c -c




#src = main.c init_op.c basic_shapes.c print_board.c mouse_op.c chess_op.c
#para = -o main -Wall 

#main:$(src)
#	gcc $(src) $(para)
.PHONY:clean
clean:
	rm -rf main
	rm -rf *.o
	rm -rf ~*
