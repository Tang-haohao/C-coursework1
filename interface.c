#include<stdio.h>
#include<windows.h>
#include <conio.h>
#include <stdlib.h>
#include"book_management.h"
#include"interface.h"

//让光标处在特定位置 
void setxy(int a,int b) 
{
    COORD coordinate;//Coord是在一个结构体，定义在windows.h里 
    coordinate.X=a-1;
    coordinate.Y=b-1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coordinate);
}
//得到光标坐标y的位置 
int ylocation()
{
    CONSOLE_SCREEN_BUFFER_INFO screen_buffer;//CONSOLE_SCREEN_BUFFER_INFO结构体包含控制台屏幕缓冲区的信息
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &screen_buffer);// GetConsoleScreenBufferInfo 函数可以获取控制台屏幕缓冲区信息
    return (screen_buffer.dwCursorPosition.Y+1);
}
//得到光标坐标x的位置 
int xlocation()
{
    CONSOLE_SCREEN_BUFFER_INFO screen_buffer;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &screen_buffer);
    return (screen_buffer.dwCursorPosition.X+1);
}
//主界面 
void Mainmenu()
{
    do
	{
		int a, b;
    	int Num;
    	setxy(31,5);
    	printf("Library management system");
    	setxy(20,8);
    	printf("*********************Main Menu*********************");
    	setxy(20,9);
    	printf(" 1 General user login ");
    	setxy(20,10);
    	printf(" 2 General user registration ");
    	setxy(20,11);
    	printf(" 3 Administrator login");//Administrator account: Administrator password: Administrator
    	setxy(20,12);
    	printf(" 5 Search for books");
    	setxy(20,13);
    	printf(" 6 Display all books");
    	setxy(20,14);
    	printf("************************************************");
    	setxy(20,15);
    	printf("请输入你的选择(0-5):[ ]");
    	a=xlocation();
    	b=ylocation();
    	setxy(a-2,b);
    	scanf("%d",&Num);
		switch(Num)
		{
			case '1':break;
			case '2':break;
			case '3':break;
			case '4':break;
			case '5':break; 
			case '6':break;
			default :break;
		}
	}while(1);
}


