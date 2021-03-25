#include "user.h"
#include <string.h>

//变量域 
extern account logger;
char register_account[30]="",register_password[10]="";
char librarian_account[]={"librarian"};//图书管理员的账号
char librarian_password[]={"librarian"};//图书管理员的密码 
char log_account[30],log_password[10];
Account accounts;

int display_book()   //总览所有图书 
{
	system("cls");
	pbook book_head=load_books(),pdisplay=NULL;
	int total=0;
	book_head=load_books();
	printf("\t\t**********************Book information******************************\n");
	printf("\t\t--------------------------------------------------------------------\n");
	printf("\t\t     ID        Title        authors         years        copies     \n");
	printf("\t\t--------------------------------------------------------------------\n");
	if(book_head==NULL)
	{
		printf("\t\tThere are no books in the library for a while. Please add some^_^\n");
		system("pause");
		return 0;
	}
	pdisplay=book_head;
	while(pdisplay!=NULL)
	{
		printf("\t\t   %u\t\t%s\t\t%s\t\t%u\t\t%u\n",pdisplay->id,pdisplay->title,pdisplay->authors,pdisplay->year,pdisplay->copies);				
		total+=pdisplay->copies;//图书的总数量 
		pdisplay=pdisplay->nextbook;
	}
	printf("\t\tThe total number of books is：%d\n",total);
	system("pause");
	return 0;
}
//借阅模块 
void borrow()
{
	char ny;
	int d=0; 
	FILE *afile,*file;
	pbook book_head,pfind,pointer;
	book_head = load_books();
	unsigned int iD;
	if(logger->Borrow<5) //判断用户借阅书籍数是否已到达上限 
	{
		system("cls");
		while(1)
		{
			printf("\t\tPlease enter the ID of the book you want to borrow:");
			scanf("%u", &iD); 
			printf("\n\t\tIn process of Querying\n");
			pfind=book_head;
			printf("\t\t**********************Book information******************************\n");
			printf("\t\t--------------------------------------------------------------------\n");
			printf("\t\t     ID        Title        authors         years        copies     \n");
			printf("\t\t--------------------------------------------------------------------\n");
			while(pfind!=NULL)
			{
				if(pfind!=NULL&&pfind->id==iD)
				{
					printf("\t\t   %u\t\t%s\t\t%s\t\t%u\t\t%u\n",pfind->id,pfind->title,pfind->authors,pfind->year,pfind->copies);			
					break;  
				}
				pfind=pfind->nextbook;
			}	
			if(pfind==NULL)
			{
				printf("\t\tThis book does not exist in the library, please enter the correct ID\n"); 
				break; 
			}
			else if(pfind->copies>0)
			{
				printf("\t\tDo you need to borrow this book：1. To borrow or 2. Not to borrow\n");
				ny = getch();
				if(ny == '1') //让用户选择是否借阅 
				{
					pfind->copies=pfind->copies-1; 
					logger->borrow[logger->Borrow]=iD;
					logger->Borrow=logger->Borrow+1;
					printf("\t\tBorrow successfully, press any key to return...\n");
					account_saving(*logger);
					file=fopen("bookfile","wb");   //通过只写的方式打开二进制文件（bookfile），并且打开时清空文件中原有的内容  
					if(file==NULL)
					{
						printf("cannot open file"); 
					}
					if(fwrite(book_head,M,1,file)!=1)   //向文件指针file指向的文件中输入pointer指针所指向的信息 
					{
						printf("write error!"); 
					}
						fclose(file);   //关闭当前文件 
					if(book_head!=NULL)   //如果头指针不是NULL 
					{
						pointer=book_head->nextbook;     //让pointer成为第二个节点的指针 
						file=fopen("bookfile","ab");   //用追加的方式打开bookfile二进制文件
						if(file==NULL)
					{
						printf("cannot open file");
					}
					while(pointer!=NULL)
					{
						if(fwrite(pointer,M,1,file)!=1)//向文件指针file指向的文件中输入pointer指针所指向的信息 
					{
						printf("write error!");
					}
						pointer=pointer->nextbook;
					}
						fclose(file);  //关闭文件 
					}
					getch();
					break;
				}
				else 
				{
					if(ny == '2')
					{
					printf("\t\tTo cancel borrowing, press any key to return...\n");
					getch();
					}
					else 
					{
						printf("\t\tInput error, press any key to return...\n");  
						getch();
					}	
					break;
				}
			}
			else 
			{
				printf("The quantity of this book is zero, please borrow other books");
				break; 
			}
		}
	}
	else{
		printf("The number of books you borrowed has reached the upper limit. Please return the borrowed books first"); 
	}
}
//还书模块
void return_book(){
	pbook rebook,rebooks,pointer,rebookss;
	FILE *afile,*file;
	rebook=load_books();
	int i;
	unsigned int return_id; 
	if(logger->Borrow!=0)
	{	
		printf("Books you borrowed:"); 
		printf("\t\t**********************Book information******************************\n");
		printf("\t\t--------------------------------------------------------------------\n");
		printf("\t\t     ID        Title        authors         years        copies     \n");
		printf("\t\t--------------------------------------------------------------------\n");
		for(i=0;i<logger->Borrow;i=i+1)
		{
			while(rebook!=NULL)
			{
				if(rebook!=NULL&&rebook->id==logger->borrow[i])
				{
					printf("\t\t   %u\t\t%s\t\t%s\t\t%u\t\t%u\n",rebook->id,rebook->title,rebook->authors,rebook->year,rebook->copies);			
				}
				rebook=rebook->nextbook;
			}
		}
		printf("\n\t\tPlease enter the ID of the book to be returned:\n");
		scanf("%u",&return_id);
		rebooks=load_books();
		rebookss=rebooks;
		while(rebooks!=NULL)
		{
			if(rebooks!=NULL&&rebooks->id==return_id)
			{
				for(i=0;i<logger->Borrow;i=i+1){
					if(logger->borrow[i]==return_id){
						logger->borrow[i]=0;
						rebooks->copies=rebooks->copies+1;
						logger->Borrow=logger->Borrow-1;
						file=fopen("bookfile","wb");   //通过只写的方式打开二进制文件（bookfile），并且打开时清空文件中原有的内容   
						if(file==NULL)
						{
							printf("cannot open file"); 
						}
						if(fwrite(rebookss,M,1,file)!=1)   //向文件指针file指向的文件中输入pointer指针所指向的信息 
						{
							printf("write error!"); 
						}
						fclose(file);   //关闭当前文件 
						if(rebookss!=NULL)   //如果头指针不是NULL 
						{
							pointer=rebookss->nextbook;     //让pointer指向链表中第二个结点 
							file=fopen("bookfile","ab");   //以追加的方式打开二进制文件 
						if(file==NULL)
						{
							printf("cannot open file");
						}
						while(pointer!=NULL)
						{
							if(fwrite(pointer,M,1,file)!=1)//将pointer指向信息写入file所指向的文件中
						{
							printf("write error!");
						}
							pointer=pointer->nextbook;
						}
							fclose(file);  //关闭文件 
						}
						account_saving(*logger);
						printf("\t\tSuccess in returning books\n");
					}
				}
			}
			rebooks=rebooks->nextbook;
		}
	}
	else{
		printf("\t\tyou did not borrow books\n");
	}
}

//存储账号模块    
void account_saving(Account A)   //将用户注册账号及信息写入文件 
{
	account a = &A;
	FILE *file;    //文件指针 
	file=fopen("account_file","ab");   //以追加的方式打开文件（二进制文件）account_file 
	if(file==NULL)
	{
		printf("file can not be opened");
	}
	if(fwrite(a,sizeof(Account),1,file)!=1)   //将指针a所指向的内容写到二进制文件中 
	{
		printf("something wrong in writing");
	}
	fclose(file);    //关闭文件  
} 
//读取存储账号信息的文件 
account load_account()      //将二进制文件的内容读入到链表中，返回链表头指针 
{
	FILE *file;       //文件指针 
	int i=0;
	account account_head=NULL;
	account a2,a,ar=NULL;
	file=fopen("account_file","a");       //如果mybook文件还不存在，则新建一个
	fclose(file);
 	file=fopen("account_file","ab+");     //用读写的方式打开二进制文件 
	if(file==NULL)
	{
		printf("cannot open file\n");
	}
	while(!feof(file))        //判断读取标志是否已经到达文件的末尾 
	{
	   i++;
	   	a=(account)malloc(sizeof(Account)); //用malloc给a申请一段空间 
	   fread(a,sizeof(Account),1,file);     //将file指向的文件的内容读入指针a中 
	   if(i==1)
	   {
	      account_head=a;
	      a2=a;
	    }
	    else             //创建一个链表 
	    {
	    	ar=a2;
	    	a2->next=a;
	    	a2=a;
		}
    }
    if(ar!=NULL)
       ar->next=NULL;
    else
       account_head=NULL;
    fclose(file);    //关闭文件 
    return account_head;   //返回头指针 
}

//创建账户模块 
void logon()
{
	Account reg_a;
	account pa = load_account();  //返回头指针 
	int x = 0, y = 0;
 	//清空屏幕 
 	system("cls");
	while(1)
 	{
 		//创建用户名
 		printf("\t\tPlease enter the user name [no more than 12 characters]:");
 		scanf("%s",register_account);
  		
 		//判断用户名是否正确 
 		if(strlen(register_account)<=12)		
 		{
 			if(strcmp(register_account,librarian_account)==0){
 				printf("\n\t\tThe user name already exists\n");
 				continue;
			 }
 			while(pa!=NULL){
 				if(strcmp(pa->register_account,register_account)==0){
 					printf("\n\t\tThe user name already exists\n");
 					pa = load_account();
 					y=1;
					break; 
				 }
				 pa = pa->next;
			 }
			if(y==1){
				y=0;
				continue;
			} 
 			while(1)
 			{
    			for (x=0; x<30; ++x)	//将register_account数组中的值赋给reg_a.register_account数组 
    			{
        			reg_a.register_account[x] = register_account[x];
    			}	  				
 				//创建用户密码
 				printf("\n\t\tPlease enter the password [password length is 6 digits]：");
 				scanf("%s",register_password);
  
 				//判断用户密码格式 
 				if(strlen(register_password)==6)
 				{
    				for (x=0; x<10; ++x)	//将register_password数组中的值赋给reg_a.register_password数组 
    				{
        				reg_a.register_password[x] = register_password[x];
    				}		 					
 					printf("\n\n\t\tRegistration is successful. Your user name is %s,The password is %s\n\n",register_account,register_password);
 					break;
 				}
 				else
 				{
 					printf("\n\t\tThe length of the password is %d，Please re-enter\n",strlen(register_password));
 				}
 			}
 			break;
 		}
 		else
 		{
 			printf("\n\t\tThe length of the user name is %d，Please re-enter\n\n",strlen(register_account));
 		}
 	}
	account_saving(reg_a);
}
  
  
//用户登录
account loging()
{
 	int x , y = 0;
 	account log_head = load_account() , current_account = NULL;
 	system("pause");
 	system("cls");
 	printf("\n\n\t\t\tWelcome to the library login system\n\n");
 	//三次登录验证
 	for(x=1;x<=3;x++)
 	{
 		printf("\t\tPlease enter the user name:");
 		scanf("%s",log_account);
 		printf("\n\t\tPlease input a password:");
 		scanf("%s",log_password);
 		if(strcmp(log_account,librarian_account)==0&&strcmp(log_password,librarian_account)==0){
			printf("\t\tLog in as librarian\n"); //以图书管理员的身份登入
			current_account=&accounts;
			strcpy(current_account->register_account,"librarian");
			break; 
 		} 
 		while(log_head!=NULL)
 		{
 			if(strcmp(log_head->register_account,log_account)==0&&strcmp(log_head->register_password,log_password)==0)	
 			{
				printf("\n\n\t\t Login successful\n\n");
				current_account = log_head; 
 				y = 1; 
 				break;
 			}
 		log_head = log_head->next;
 		}
 		if(y==0)
 		{
 			printf("\n\n\t\tLogin failed. Please log in again. You have %d chances\n\n",3-x);
 		}
 		if(y==1)
		{
 			y = 0;
			break;
 		}
 	}
  	return current_account;
}

void terminate()       //终止整个软件 
{
	int i;
	system("cls");
	setxy(20,10);
	printf("-------------------------------------");
	setxy(20,12);
	printf("|   Are you sure you want to exit?  |");
	setxy(20,14);
	printf("| 1. Confirm            2. Cancel   |");
	setxy(20,16);
	printf("-------------------------------------\n");
	while(1)
	{
		scanf("%d",&i);         //让用户输入选择 
		switch(i)
		{
			case 1:
			setxy(20,18);
			printf("The software has been safely exited\n");
			setxy(20,20);
			printf("Thank you for using！\n");
			exit(0);  
			break; //结束整个程序 
			case 2:
			Mainmenu(); //重新进入主菜单 
			break;    
			default :break;
		}
	}
} 

