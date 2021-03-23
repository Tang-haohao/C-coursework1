#include "user.h"
#include"interface.h"
#include"book_management.h"

#include <stdio.h>
#include <conio.h>
#include<windows.h>
#include <stdlib.h>

extern char librarian_account[];
account logger;
//�ù�괦���ض�λ�� 
void setxy(int a,int b) 
{
    COORD coordinate;//Coord����һ���ṹ�壬������windows.h�� 
    coordinate.X=a-1;
    coordinate.Y=b-1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coordinate);
}
//�õ��������y��λ�� 
int ylocation()
{
    CONSOLE_SCREEN_BUFFER_INFO screen_buffer;//CONSOLE_SCREEN_BUFFER_INFO�ṹ���������̨��Ļ����������Ϣ
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &screen_buffer);// GetConsoleScreenBufferInfo �������Ի�ȡ����̨��Ļ��������Ϣ
    return (screen_buffer.dwCursorPosition.Y+1);
}
//�õ��������x��λ�� 
int xlocation()
{
    CONSOLE_SCREEN_BUFFER_INFO screen_buffer;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &screen_buffer);
    return (screen_buffer.dwCursorPosition.X+1);
}
//������ 
void Mainmenu()
{
	FILE *afile;
	logger = NULL; 
    do
	{	
		store_books(afile);
		load_books(afile);
		system("pause");
		system("cls");
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
    	printf(" 3 Administrator login");//Administrator account: librarian password: librarian
    	setxy(20,12);
    	printf(" 4 Search for books");
    	setxy(20,13);
    	printf(" 5 Display all books");
    	setxy(20,14);
    	printf(" 0 Terminate program");
    	setxy(20,15);
    	printf("************************************************");
    	setxy(20,16);
    	printf("���������ѡ��(0-5):[ ]");
    	a=xlocation();
    	b=ylocation();
    	setxy(a-2,b);
    	scanf("%d",&Num);
		switch(Num)
		{
			case 1:logger = loging();
			if(logger!=NULL)
			{
				user_menu();
			}
			break;
			case 2:logon();
			break;
			case 3:logger = loging();
			if(logger!=NULL&&strcmp(logger->register_account,librarian_account)==0)
			{
				administrator_menu();
			}
			else if(logger!=NULL)
			{
				printf("\n\t\t�Բ��𣬼�⵽���Ƿǹ���Ա�˺ţ������µ�¼\n");	
			}
			break;
			case 4:search_book();
			break; 
			case 5:display_book();
			break;
			case 0:terminate();
			break;
			default :break;
		}
	}while(1);
}

//�û����� 
void user_menu()  
{
	FILE *afile;
	do
	{
		system("pause");
		system("cls");  //���� 
		printf("\n\n\t\t      User        Interface         \n\n");

		printf("\t\t|     1.Search for books         |\n\n");

		printf("\t\t|     2.Borrow books             |\n\n");

		printf("\t\t|     3.return books             |\n\n");

		printf("\t\t|     0.Return to main menu      |\n\n");
		int i =6;
		scanf("%d",&i);
		switch(i)
		{
			case 0:Mainmenu();
			break;
			case 1:search_book();
			break;
			case 2:borrow();
			break;
			case 3:return_book();
			break;
			default :break;
		 } 
	}while(1);
}

//����Ա���� 
void administrator_menu() 
{
	FILE *afile;
	Book book1;
	do
	{
		system("pause");
		system("cls");  //���� 
		printf("\t\t      ͼ�����ϵͳ       \n\n");

		printf("\t\t|     1.����鼮        |\n\n");

		printf("\t\t|     2.ɾ���鼮        |\n\n");

		printf("\t\t|     3.��ѯ�鼮        |\n\n");

		printf("\t\t|     4.�޸��鼮        |\n\n");

		printf("\t\t|     0.�������˵�      |\n\n");
		int i =6;
		scanf("%d",&i);
		switch(i)
		{
			case 0:Mainmenu();
			break;
			case 1:add_book(book1);
			break;
			case 2:remove_book(book1);
			break;
			case 3:search_book();
			break;
			case 4:amend_book();
			break;
			default :break;
		 } 
	}while(1);
}

