#include<stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student 
{
    int num;
    char name[20];
    struct student *next;
}STU;
/**********************
函数：menu()
功能：打印首页面
**********************/
void menu()
{
    printf("\n");
    printf("请选择操作\n");
    printf("1 : 打印所有信息\n");
    printf("2 : 添加新的信息\n");
    printf("3 : 删除信息\n");
    printf("4 : 保存修改\n");
    printf("5 : 退出系统\n");
    printf("\n");

}
/***********************
函数：print_node()
功能：打印所有结点
返回值：空
***********************/
void print_node(STU *p)
{
    if (p == NULL)
    {
        printf("empty.\n");
        return;
    }
    while(p != NULL) 
    {
        printf("%d  %s\n", p->num, p->name);
        p = p->next;                                   /*移动指针 输出所有的*/
    }
}
/**********************
函数：add_node()
功能：添加新的结点
返回值：head 返回头结点
**********************/
STU *add_node(STU *p)
{
    STU *head = p;
    STU *new = NULL;

    new = malloc(sizeof(STU));                   /*需要添加的结点 先开辟新的空间*/
    if (new == NULL)
    {
        perror("empty");
        exit(0);
    }
    printf("please add a number:\n");
    scanf("%d", &new->num);
    printf("please add the name:\n");
    scanf("%s",new->name);               /*getchar()可接受一个字符,直到按回车才返回,但是第一个字符作为函数的返回值*/  
    getchar();                              /*读入的所有操作 只取一个字符 回车 也是个字符 故在此加*/
    new->next = NULL;                  /*新开辟的空间 一定加上本身指针的指向*/
/*从特殊到一般的情况考虑*/                                            
    if (p == NULL)                                  
    {
        return new;
    }

    if (new->num < head->num)
    {
        new->next = head;
        return new;
    }
/*判断下面两个条件 从左至右*/
    while ((p->next != NULL) && (p->next->num < new->num))      
    {
        new = new->next;                           /*移动指针*/
    }
    new->next = p->next;
    p->next = new;

    return head;
}
/**********************
函数：delete_node()
功能：删除结点
返回值：head 返回头结点
***********************/
#if 1
STU *delete_node(STU *p)
{
    int number = 0;             /*从键盘上获得的参数 存入地址*/
    STU *head = p;              /*固定 头结点*/
    STU *temp = NULL;           /*在找到需删除的结点时  用此指针固定该结点 则可释放该结点*/

    if (p == NULL)
    {
        printf("empty~!\n");
        return head;
    }

    printf("please input a number to delete:\n");
    scanf("%d",&number);
    getchar();                 /*输入的字符送入缓冲区 再从缓冲区读取  注意加getchar()*/

    if (p->num == number)
    {
        head = p->next;
        free(p);
        return head;
    }

    while((p->next != NULL) && (p->next->num != number))
    {
        p = p->next;
    }

    if (p->next == NULL)
    {
        printf("no match.\n");
        return head;
    }
    temp = p->next;
    p->next = p->next->next;
    free(temp);
    return head;
}
#endif


void save_link(STU *p)
{
    FILE *fp = fopen("file.txt", "w");
    if (fp == NULL)
    {
        perror("null");
        exit(0);
    }
    while(p != NULL)
    {
        fprintf(fp, "%d   %s\n", p->num, p->name);
        p = p->next;
    }

    fclose(fp);
}
int main(int argc, const char *argv[])
{
    char choice = 0;
    int flag = 1;
    STU *head = NULL;

    while (flag != 0)
    {   
        menu();
        choice = getchar();
        getchar();
   //     printf("%d\n", choice);
        switch(choice)
        {
            case '1' : print_node(head); break;
            case '2' : head = add_node(head); break;
            case '3' : head = delete_node(head); break;
            case '4' : save_link(head); break;
            case '5' : flag = 0; printf("thank you for using~!\n");; break;
            default : printf("Sorry, no this function~!\n");break;
        }
    }    
    return 0;
}
