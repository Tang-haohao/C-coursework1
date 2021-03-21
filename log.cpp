//登录系统的第一个版本
 
#include "stdio.h"
#include <conio.h>
#include "string.h"
#include "windows.h"

struct reg_Account              //注册者的账号 
{ 
	char register_account[30];
 	struct reg_Account *next;   //指针域 
};

struct reg_Password              //注册者的密码 
{ 
	char register_password[10];
 	struct reg_Password *next;   //指针域 
};

typedef struct reg_Account Account;
typedef Account *account;
typedef struct reg_Password Password;
typedef Password *password;


//变量域 
char register_account[30]="",register_password[10]="";
char log_account[30],log_password[10];
char t;

void account_saving(Account A)   //将用户注册账号写入文件 
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

void password_saving(Password P)   //将用户注册密码写入文件 
{
	password p = &P;
	FILE *file;    //文件指针 
	file=fopen("password_file","ab");   //以追加的方式打开文件（二进制文件）password_file 
	if(file==NULL)
	{
		printf("file can not be opened");
	}
	if(fwrite(p,sizeof(Password),1,file)!=1)   //将指针p所指向的内容写到二进制文件中 
	{
		printf("something wrong in writing");
	}
	fclose(file);    //关闭文件  
} 

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
	    else             //创建链表 
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

//用户注册系统 
void logon()
{
	Account reg_a;
	Password reg_p;
	account pa = load_account();
 	//清空屏幕 
 	system("cls");
	while(1)
 	{
 		//创建用户名
 		printf("\t\t请输入用户名[不能大于12个字符]：");
 		scanf("%s",register_account);
  		
 		//判断用户名
 		if(strlen(register_account)<=12)		
 		{
 			while(pa!=NULL){
 				if(strcmp(pa->register_account,register_account)==0){
 					printf("\t\t用户名已存在");
 					continue; 
				 }	
			 } 
 			while(1)
 			{
 				//输入密码
 				printf("\n\t\t请输入密码[密码长度为六位]：");
 				scanf("%s",register_password);
  
 				//判断密码
 				if(strlen(register_password)==6)
 				{
 					printf("\n\n\t\t注册成功，您的用户名是%s,密码是%s\n\n",register_account,register_password);
 					break;
 				}
 				else
 				{
 					printf("\n\t\t密码的长度为%d，请重新输入\n",strlen(register_password));
 				}
 			}
 			break;
 		}
 		else
 		{
 			printf("\n\t\t用户名的长度为%d，请重新输入\n\n",strlen(register_account));
 		}
 	}
	account_saving(reg_a);
	password_saving(reg_p);
}
  
//判断是否注册
int judge()
{
 if(strcmp(register_account,"")==0&&strcmp(register_password,"")==0)
 {
 printf("\n\n\t\t您尚未注册，请先注册！\n\n");
 return 0;
 }
 else
 {
 return 1;
 }
}
  
//用户登录
void dl()
{
 int i;
 system("pause");
 system("cls");
  
 printf("\n\n\t\t\t欢迎使用腾讯QQ登录系统\n\n");
 //三次登录验证
 for(i=1;i<=4;i++)
 {
 printf("\t\t请输入用户名:");
 scanf("%s",log_account);
 printf("\n\t\t请输入密 码:");
 scanf("%s",log_password);
 if(strcmp(register_account,log_account)==0&&strcmp(register_password,log_password)==0)
 {
 printf("\n\n\t\t登录成功，欢迎使用腾讯QQ系统\n\n");
 break;
 }
 else
 {
 printf("\n\n\t\t登录失败，请重新登录，您还有%d次机会\n\n",4-i);
 }
  
 }
  
}
int main()//腾讯QQ注册登陆系统
{
 //定义变量
 int id;
 while(1)
 {
 system("cls");
 system("pause");
 //输出界面
 printf("\n\n\t\t\t腾讯QQ管理系统\n\n");
  
 printf("\t\t\t1:注册\n");
 printf("\t\t\t2:登录\n");
 printf("\t\t\t0:退出\n\n");
  
 //输入功能编号
 printf("\t\t请选择功能编号：");
 scanf("%d",&id);
  
 //判断
 switch(id)
 {
 case 1:logon();break;
 case 2:
 if(judge()==1)
 {
 dl();
 }
 break;
 case 0:exit(1);break;
 default:
 printf("\n\t\t您输入的功能编号有误，请重新输入！\n");
 }
  
 }
  return 0;
}
 

