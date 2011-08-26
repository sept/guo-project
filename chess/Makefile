main:main.o init_op.o basic_shapes.o print_board.o mouse_op.o chess_op.o
	gcc main.o init_op.o basic_shapes.o print_board.o mouse_op.o chess_op.o -o main

main.o:main.c
	gcc main.c -c
init_op.o:init_op.c
	gcc init_op.c -c
basic_shapes.o:basic_shapes.c
	gcc basic_shapes.c -c
print_board.o:print_board.c
	gcc print_board.c -c
mouse_op.o:mouse_op.c
	gcc mouse_op.c -c
chess_op.o:chess_op.c
	gcc chess_op.c -c



#src = main.c init_op.c basic_shapes.c print_board.c mouse_op.c chess_op.c
#para = -o main -Wall 

#main:$(src)
#	gcc $(src) $(para)
.PHONY:clean
clean:
	rm -rf main
	rm -rf *.o
	rm -rf ~*
