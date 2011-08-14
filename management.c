#include<stdio.h>

typedef struct student 
{
    int num;
    char name[20];
    struct student *next;
}STU;

int main(int argc, const char *argv[])
{
    char choice = 0;
    int flag = 1;

    while (flag != 0)
    {   
        menu();
        choice = getchar();
        switch(choice)
        {
            case 1 : print_node(); break;
            case 2 : add_node(); break;
            case 3 : delete_node(); break;
            case 4 : break;
            case 5 : flage = 0; break;
            default : break;
        }
    }    
    return 0;
}
