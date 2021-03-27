
#include"book_management.h"
#include "user.h"
extern char librarian_account[];
extern account logger;
int n = 0;
//saves the database of books in the specified file
//returns 0 if books were stored correctly, or an error code otherwise
int store_books(pbook pointer)
{
	FILE *file;    //文件类型指针 
	file=fopen("bookfile","ab");   //通过追加的方式打开二进制文件bookfile 
	if(file==NULL)
	{
		printf("file can not be opened\n");
	}
	if(fwrite(pointer,M,1,file)!=1)   //将指针pointer所指向的信息输入到二进制文件中 
	{
		printf("something wrong in file writting\n");
	}
	fclose(file);    //关闭文件
}

//loads the database of books from the specified file
//the file must have been generated by a previous call to store_books()
//returns 0 if books were loaded correctly, or an error code otherwise
pbook load_books()
{
	FILE *file;       //文件类型指针 
	int integer=0; 
	pbook bookhead=NULL; 
	pbook pointer2,pointer1,prepointer=NULL; 
	file=fopen("bookfile","ab+");      //以只读的方式打开二进制文件 
	if(file==NULL)
	{
		printf("file can not be opened\n");
	}
	while(!feof(file))        //若文件标志移动到末尾则跳出循环 
	{
	   integer++;
	   pointer1=(pbook)malloc(M); //通过malloc给pbook申请一段空间 
	   fread(pointer1,M,1,file);     //将文件指针file指向的信息输入给pointer指针 
	   if(integer==1)
	    {
	      bookhead=pointer1;
	      pointer2=pointer1;
		}
	    else             //创建一个链表 
	    {
	    	prepointer=pointer2;
	    	pointer2->nextbook=pointer1;
	    	pointer2=pointer1;
		}
    }
    if(prepointer!=NULL)
	{
       prepointer->nextbook=NULL;
	}
    else	//链表未创建成功 
	{
       bookhead=NULL; 
	}
	fclose(file);    //关闭相应文件 
    return bookhead;   //返回链表的头指针 
} 

//adds a book to the ones available to the library
//returns 0 if the book could be added, or an error code otherwise
int add_book(Book book)
{
	do
	{
		system("cls");
		char select;
		pbook pointer1,pointer2=load_books(),_bookhead=load_books();
		unsigned int new_ID;     //ID号 
		char new_name[20];      //书名 
		char author[20];       //作者名 
		unsigned int _year;  //出版时间 
		unsigned int _copy;            //数量 
		pointer1=(pbook)malloc(M);     //给指针p申请空间 
			//用户输入想输入的信息 
			system("cls");
			printf("\t\tPlease enter the book ID:");   //输入ID 
			scanf("%u",&new_ID);
			while(pointer2!=NULL)
			{
				if(pointer2->id==new_ID)
				{
					printf("\n\t\tID already exists, please re-enter:");
					scanf("%u",&new_ID);
					pointer2=_bookhead;
				}
				pointer2=pointer2->nextbook;
			}
			getchar();
			pointer1->id=new_ID;
			printf("\n\t\tPlease enter the title of the book:");   //输入标题 
			scanf("%s",new_name);
			getchar();
			strcpy(pointer1->title,new_name);
			printf("\n\t\tPlease enter author name:");		//输入作者
			scanf("%s",author);
			getchar();
			strcpy(pointer1->authors,author);
			printf("\n\t\tPlease enter the publication time:");		//输入出版时间 
			scanf("%u",&_year);
			pointer1->year=_year;
			printf("\n\t\tPlease enter the number of books:");		////输入数量 
			scanf("%u",&_copy);
			getchar();
			pointer1->copies=_copy;
			store_books(pointer1);
			printf(" in process of saving");
			system("cls");
			printf("\t\t\n---------------------------------\n");
			printf("\t\t\n|                               |\n");
			printf("\t\t\n| Saved successfully! Continue? |\n");		//提示用户是否继续 
			printf("\t\t\n| 1.YES                    2.NO |\n");
			printf("\t\t\n|                               |\n");
			printf("\t\t\n---------------------------------\n");
			while(1)    //为了避免其他按键的干扰所以用死循环 
			{
				select=getch();
				if(select=='1')
				{	
					break;
			 	} 
			 	else if(select=='2')
				 {
			 	administrator_menu();  //回到管理员菜单  
			 	}
			}
		}while(1);
	
} 
//removes a book from the library
//returns 0 if the book could be successfully removed, or an error code otherwise.
int remove_book(Book book)
{
	do
	{
		system("cls");
		FILE *file;
		pbook bookhead,pointer,prepointer=NULL; 
		int intj=0,intx,inti=11;
		char title[20];
		char char1,char2,char3;
		bookhead=load_books();    //得到存书链表表头的地址 
		printf("\t\tPlease enter the book name of the book you want to delete:");
		scanf("%s",title);
		pointer=bookhead;
		while(pointer!=NULL)
		{
			pointer->number=0;
			pointer=pointer->nextbook;
		}
		pointer=bookhead;
		printf("\n\t\t**************************Book overview*****************************\n");
		printf("\t\t--------------------------------------------------------------------\n");
		printf("\t\t     ID        Title        authors         years        copies     \n");
		printf("\t\t--------------------------------------------------------------------\n");
		while(pointer!=NULL)
		{
			if(pointer!=NULL&&strcmp(pointer->title,title)==0)
			{
				intj++;
				printf("\t\t %d %u\t\t%s\t\t%s\t\t%u\t\t%u\n",intj,pointer->id,pointer->title,pointer->authors,pointer->year,pointer->copies);				
				pointer->number=intj;
			}
			pointer=pointer->nextbook;
		}
		if(intj==0)                   //如果intj=0，说明循环内的语句没执行，说明没找到相应图书 
		{ 
			printf("\t\tNo corresponding information found! (press 0 to return, press 1 to search again)\n");
			while(1)               //为了避免其他按键的干扰所以用死循环
			{
				char3=getch();
				if(char3=='0')
				{
					administrator_menu();
					break;
				}
				else if(char3=='1')
				{
					break;
				}
			}
			if(char3=='1')     //当用户输入1时则重新开始循环 
			   continue;
		}
		while(1)
		{
			printf("\t\tPlease enter the number of the book you want to delete:");
			scanf("%d",&intx);
			getchar();
			if(intx>intj||intx==0)
			{
				printf("\n\t\tInput error, please input again!\n");
			}
			else
			{
				break;
			}
		}
		printf("\t\t-------------------------------------------\n");
		printf("\t\t|                                         |\n");
		printf("\t\t|     Are you sure you want to delete?    |\n");
		printf("\t\t| 1. Yes                             2.NO |\n");
		printf("\t\t|                                         |\n");
		printf("\t\t-------------------------------------------\n");
		while(1)
		{
			char1=getch();
			if(char1=='1')
			{
				break;
			} 
			else if(char1=='2')
			{
				administrator_menu();
			}
		}
		pointer=bookhead;
		while(pointer!=NULL&&pointer->number!=intx)
		{
			prepointer=pointer;
			pointer=pointer->nextbook;
		}
		if(pointer!=NULL)
		{
			if(prepointer==NULL)
			{
				bookhead=bookhead->nextbook;
			}
			else
			{
				prepointer->nextbook=pointer->nextbook;
			}
		}
		free(pointer);		//释放内存 
		file=fopen("bookfile","wb");		//打开二进制文件,同时清空其中内容 
		if(file==NULL)
		{
			printf("cannot open file"); 
		}
		if(fwrite(bookhead,M,1,file)!=1)	//存入数据 
		{
			printf("write error!"); 
		}
		fclose(file);
		if(bookhead!=NULL)
		{
			pointer=bookhead->nextbook;
			file=fopen("bookfile","ab");
			if(file==NULL)
			{
				printf("cannot open file");
			}
			while(pointer!=NULL)
			{
				if(fwrite(pointer,M,1,file)!=1)
				{
					printf("write error!");
				}
				pointer=pointer->nextbook;
			}
			fclose(file);
		}
		system("cls");
		printf("\t\tDeleting, please wait\n");
		system("pause");		
		printf("\t\t---------------------------------------------------\n");
		printf("\t\t|                                                 |\n");
		printf("\t\t|  Successfully deleted. Do you want to continue? |\n");
		printf("\t\t| 1. Yes                                     2.No |\n");
		printf("\t\t|                                                 |\n");
		printf("\t\t---------------------------------------------------\n");
		while(1)
		{
			char2=getch();
			if(char2=='1')
			{
				break;
			}
			else if(char2=='2')
			{
				administrator_menu();
			}
		}
	}while(1);
} 

//修改图书相关信息 
void change_book()    
{
	do
	{
		system("cls");
		pbook bookhead=NULL,pointer=NULL;
		int intj=0,intx;
		char char1,char2;
		FILE *file;    //文件类型指针 
		char _title[20];
		unsigned int new_ID;     //id号 
		char new_name[20];      //书的名字 
		char author[20];       //作者的名字 
		unsigned int _year;  //出版的时间 
		unsigned int _copy;         //数量 
		bookhead=load_books();
		pointer=bookhead;
		printf("\t\tPlease enter the title of the book you want to modify:");
		gets(_title); 
		while(pointer!=NULL)    
		{
			pointer->number=0;	//让序号初始为零 
			pointer=pointer->nextbook;
		}
		pointer=bookhead;    //让pointer再次指向表头 
		printf("\n\t\t**********************Book information******************************\n");
		printf("\t\t--------------------------------------------------------------------\n");
		printf("\t\t     ID        Title        authors         years        copies     \n");
		printf("\t\t--------------------------------------------------------------------\n");
		while(pointer!=NULL)
		{
			if(pointer!=NULL&&strcmp(pointer->title,_title)==0)
			{
				intj++;
				printf("\t\t %d %u\t\t%s\t\t%s\t\t%u\t\t%u\n",intj,pointer->id,pointer->title,pointer->authors,pointer->year,pointer->copies);				
				pointer->number=intj;    //给符号条件的书目编号 
			}
			pointer=pointer->nextbook;
		}
		if(intj==0)                   //inj等于零，说明循环内的语句没有执行，没有找到相应书目 
		{ 
			printf("\t\tNo corresponding information found! (press 0 to return, press 1 to search again)\n");
			while(1)               //为了避免其他按键的干扰所以用死循环 
			{
				char1=getch();
				if(char1=='0')
				{
					administrator_menu();
					break;
				}
				else if(char1=='1')
				{
					break;
				}
			}
			if(char1=='1')     //如果用户输入1，那么重新开始循环 
			   continue;
		}
		while(1)
		{
			printf("\t\tPlease enter the number of the book you want to modify:");
			scanf("%d",&intx);
			getchar();
			if(intx>intj||intx==0)     
			{
				printf("\n\t\tInput error, please input again!\n");
			}
			else
			{
				break;
			}
		}
		pointer=bookhead;     //让pointer再次指向表头
		while(pointer!=NULL&&pointer->number!=intx)   //遍历搜索符合条件的书 
		{
			pointer=pointer->nextbook;
		}
		if(pointer!=NULL)    //如果pointer不是NULL		 
		{
			system("cls");
			//输入要修改的信息 
			printf("\n\t\tPlease enter the book registration number:");
			scanf("%u",&new_ID);
			getchar();
			pointer->id=new_ID;
			printf("\n\t\tPlease enter the title of the book:");
			scanf("%s",new_name);
			getchar();
			strcpy(pointer->title,new_name);
			printf("\n\t\tPlease enter author name:");
			scanf("%s",author);
			getchar();
			strcpy(pointer->authors,author);
			printf("\n\t\tPlease enter the publication time:");
			scanf("%u",&_year);
			pointer->year=_year;
			printf("\n\t\tPlease enter the number of books:");
			scanf("%u",&_copy);
			getchar();
			pointer->copies=_copy;
		}
		printf("\t\t----------------------------------\n");
		printf("\t\t|                                |\n");
		printf("\t\t|     Are you sure to modify?    |\n");
		printf("\t\t| 1. Yes                    2. No|\n");
		printf("\t\t|                                |\n");
		printf("\t\t----------------------------------\n");
		while(1)   //利用死循环防止其他按键干扰 
		{
			char2=getch();
			if(char2=='1')
			{
				break;
			} 
			else if(char2=='2')
			{
				administrator_menu();
			}
		}
		system("cls");
		printf("\t\tModifying, please wait\n");
		file=fopen("bookfile","wb");   //通过只写的方式打开二进制文件（bookfile），并且打开时清空文件中原有的内容 
		if(file==NULL)
		{
			printf("\t\tfile can not be opened\n"); 
		}
		if(fwrite(bookhead,M,1,file)!=1)   //向文件指针file指向的文件中输入pointer指针所指向的信息 
		{
			printf("\t\twrite error!\n"); 
		}
		fclose(file);   //关闭此文件 
		if(bookhead!=NULL)   //如果头结点不是NULL 
		{
			pointer=bookhead->nextbook;     //让pointer成为第二个节点的指针 
			file=fopen("bookfile","ab");   //用追加的方式打开bookfile二进制文件 
			if(file==NULL)
			{
				printf("\t\tfile can not be opened\n");
			}
			while(pointer!=NULL)
			{
				if(fwrite(pointer,M,1,file)!=1)//向文件指针file指向的文件中输入pointer指针所指向的信息 
				{
					printf("\t\tsomething wrong in writting!\n");
				}
				pointer=pointer->nextbook;
			}
			fclose(file);  //关闭相应的文件 
		}
		system("cls");
		printf("\t\tModified successfully! About to return to the administrator interface");
		system("pause");
		break;
	}while(1);
}

//finds books with a given title.
//returns a BookArray structure, where the field "array" is a newly allocated array of books, or null if no book with the 
//provided title can be found. The length of the array is also recorded in the returned structure, with 0 in case
//array is the null pointer.
BookArray find_book_by_title (const char *title)
{ 
	system("cls"); 
	int y=0;  
	pbook book_head=NULL,pfind=NULL;
	book_head = load_books();
	BookArray parray;
	char atitle[20];
	printf("Please enter the title of the book you want to query: ");
	scanf("%s", atitle); 
	printf("\nQuerying\n");
	pfind=book_head;
	printf("\t\t**************************Book overview*****************************\n");
	printf("\t\t--------------------------------------------------------------------\n");
	printf("\t\t     ID        Title        authors         years        copies     \n");
	printf("\t\t--------------------------------------------------------------------\n");
	while(pfind!=NULL)
	{
		if(pfind!=NULL&&strcmp(pfind->title,atitle)==0)
		{
			printf("\t\t   %u\t\t%s\t\t%s\t\t%u\t\t%u\n",pfind->id,pfind->title,pfind->authors,pfind->year,pfind->copies);			y=1;
		}
		pfind=pfind->nextbook;
	}
	if(y==0)
	{
		printf("\n\t\tNo corresponding bibliography found\n");
	}
	system("pause");
	search_book();
	return parray;
}
//finds books with the given authors.
//returns a BookArray structure, where the field "array" is a newly allocated array of books, or null if no book with the 
//provided title can be found. The length of the array is also recorded in the returned structure, with 0 in case
//array is the null pointer.
BookArray find_book_by_author (const char *author)
{
	system("cls");
	int y=0; 
	pbook book_head=NULL,pfind=NULL;
	book_head = load_books();
	BookArray parray;
	char authors[20];
	printf("\t\tPlease enter the author of the book you want to inquire about:");
	scanf("%s", authors); 
	printf("\n\t\tIn poccess of Querying\n");
	pfind=book_head;
		printf("\t\t**********************Book information******************************\n");
		printf("\t\t--------------------------------------------------------------------\n");
		printf("\t\t     ID        Title        authors         years        copies     \n");
		printf("\t\t--------------------------------------------------------------------\n");
	while(pfind!=NULL)
	{
		if(pfind!=NULL&&strcmp(pfind->authors,authors)==0)
		{
			printf("\t\t   %u\t\t%s\t\t%s\t\t%u\t\t%u\n",pfind->id,pfind->title,pfind->authors,pfind->year,pfind->copies);			y=1;
			y=1;
		}
		pfind=pfind->nextbook;
	}
	if(y==0)
	{
		printf("\n\t\tNo corresponding bibliography found\n");
	}
	system("pause");
	search_book();
	return parray;
}

//finds books published in the given year.
//returns a BookArray structure, where the field "array" is a newly allocated array of books, or null if no book with the 
//provided title can be found. The length of the array is also recorded in the returned structure, with 0 in case
//array is the null pointer.
BookArray find_book_by_year (unsigned int year)
{
	system("cls");
	int y=0; 
	pbook book_head=NULL,pfind=NULL;
	book_head = load_books();
	BookArray parray;
	unsigned int time;
	printf("\t\tPlease enter the year of the book you want to query:");
	scanf("%u", &time); 
	printf("\n\t\tIn poccess of Querying\n");
	pfind=book_head;
	printf("\t\t**********************Book information******************************\n");
	printf("\t\t--------------------------------------------------------------------\n");
	printf("\t\t     ID        Title        authors         years        copies     \n");
	printf("\t\t--------------------------------------------------------------------\n");
	while(pfind!=NULL)
	{
		if(pfind!=NULL&&pfind->year==time)
		{
			printf("\t\t   %u\t\t%s\t\t%s\t\t%u\t\t%u\n",pfind->id,pfind->title,pfind->authors,pfind->year,pfind->copies);			y=1;
			y=1;
		}
		pfind=pfind->nextbook;
	}
	if(y==0)
	{
		printf("\n\t\tNo corresponding bibliography found\n");
	}
	system("pause");
	search_book();
	return parray;	
}

//通过ID查找图书
void find_number_book()    
{
	system("cls");
	int y=0; 
	pbook book_head=NULL,pfind=NULL;
	book_head = load_books();
	BookArray parray;
	unsigned int ids;
	printf("Please enter the ID of the book you want to query:");
	scanf("%u", &ids); 
	printf("\nIn process of Querying\n");
	pfind=book_head;
	printf("\t\t**********************Book information******************************\n");
	printf("\t\t--------------------------------------------------------------------\n");
	printf("\t\t     ID        Title        authors         years        copies     \n");
	printf("\t\t--------------------------------------------------------------------\n");
	while(pfind!=NULL)
	{
		if(pfind!=NULL&&pfind->id==ids)
		{
			printf("\t\t   %u\t\t%s\t\t%s\t\t%u\t\t%u\n",pfind->id,pfind->title,pfind->authors,pfind->year,pfind->copies);			y=1;
			y=1;
		}
		pfind=pfind->nextbook;
	}
	system("pause"); 
	search_book();
}

//the module of finding book
void search_book()  //查询图书 
{
	do
	{
		const char *title;
		const char *author;
		unsigned int year;
		system("cls");  //清屏 
		printf("\t\t Book Search  \n\n");

		printf("\t\t|     1.Book Title query                  |\n\n");

		printf("\t\t|     2.Author query                      |\n\n");

		printf("\t\t|     3.Year query                        |\n\n");

		printf("\t\t|     4.Return to the previous level      |\n\n");

		printf("\t\t|     0.Return to main menu               |\n\n");
		char char1;
		char1=getch();
		switch(char1)
		{
			case '0':Mainmenu();
			break;
			case '1':find_book_by_title (title);
			break;
			case '2':find_book_by_author(author);
			break;
			case '3':find_book_by_year (year);
			break;
			case '4':
			if(logger!=NULL&&strcmp(logger->register_account,librarian_account)==0)
			{
				administrator_menu();
			}
			else if(logger!=NULL)
			{
				user_menu();
			}
			else{
				Mainmenu();
			} 
			default :break;
		 } 
	}while(1);
}

