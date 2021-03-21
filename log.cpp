//��¼ϵͳ�ĵ�һ���汾
 
#include "stdio.h"
#include <conio.h>
#include "string.h"
#include "windows.h"

struct reg_Account              //ע���ߵ��˺� 
{ 
	char register_account[30];
 	struct reg_Account *next;   //ָ���� 
};

struct reg_Password              //ע���ߵ����� 
{ 
	char register_password[10];
 	struct reg_Password *next;   //ָ���� 
};

typedef struct reg_Account Account;
typedef Account *account;
typedef struct reg_Password Password;
typedef Password *password;


//������ 
char register_account[30]="",register_password[10]="";
char log_account[30],log_password[10];
char t;

void account_saving(Account A)   //���û�ע���˺�д���ļ� 
{
	account a = &A;
	FILE *file;    //�ļ�ָ�� 
	file=fopen("account_file","ab");   //��׷�ӵķ�ʽ���ļ����������ļ���account_file 
	if(file==NULL)
	{
		printf("file can not be opened");
	}
	if(fwrite(a,sizeof(Account),1,file)!=1)   //��ָ��a��ָ�������д���������ļ��� 
	{
		printf("something wrong in writing");
	}
	fclose(file);    //�ر��ļ�  
} 

void password_saving(Password P)   //���û�ע������д���ļ� 
{
	password p = &P;
	FILE *file;    //�ļ�ָ�� 
	file=fopen("password_file","ab");   //��׷�ӵķ�ʽ���ļ����������ļ���password_file 
	if(file==NULL)
	{
		printf("file can not be opened");
	}
	if(fwrite(p,sizeof(Password),1,file)!=1)   //��ָ��p��ָ�������д���������ļ��� 
	{
		printf("something wrong in writing");
	}
	fclose(file);    //�ر��ļ�  
} 

account load_account()      //���������ļ������ݶ��뵽�����У���������ͷָ�� 
{
	FILE *file;       //�ļ�ָ�� 
	int i=0;
	account account_head=NULL;
	account a2,a,ar=NULL;
	file=fopen("account_file","a");       //���mybook�ļ��������ڣ����½�һ��
	fclose(file);
 	file=fopen("account_file","ab+");     //�ö�д�ķ�ʽ�򿪶������ļ� 
	if(file==NULL)
	{
		printf("cannot open file\n");
	}
	while(!feof(file))        //�ж϶�ȡ��־�Ƿ��Ѿ������ļ���ĩβ 
	{
	   i++;
	   	a=(account)malloc(sizeof(Account)); //��malloc��a����һ�οռ� 
	   fread(a,sizeof(Account),1,file);     //��fileָ����ļ������ݶ���ָ��a�� 
	   if(i==1)
	   {
	      account_head=a;
	      a2=a;
	    }
	    else             //�������� 
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
    fclose(file);    //�ر��ļ� 
    return account_head;   //����ͷָ�� 
}

//�û�ע��ϵͳ 
void logon()
{
	Account reg_a;
	Password reg_p;
	account pa = load_account();
 	//�����Ļ 
 	system("cls");
	while(1)
 	{
 		//�����û���
 		printf("\t\t�������û���[���ܴ���12���ַ�]��");
 		scanf("%s",register_account);
  		
 		//�ж��û���
 		if(strlen(register_account)<=12)		
 		{
 			while(pa!=NULL){
 				if(strcmp(pa->register_account,register_account)==0){
 					printf("\t\t�û����Ѵ���");
 					continue; 
				 }	
			 } 
 			while(1)
 			{
 				//��������
 				printf("\n\t\t����������[���볤��Ϊ��λ]��");
 				scanf("%s",register_password);
  
 				//�ж�����
 				if(strlen(register_password)==6)
 				{
 					printf("\n\n\t\tע��ɹ��������û�����%s,������%s\n\n",register_account,register_password);
 					break;
 				}
 				else
 				{
 					printf("\n\t\t����ĳ���Ϊ%d������������\n",strlen(register_password));
 				}
 			}
 			break;
 		}
 		else
 		{
 			printf("\n\t\t�û����ĳ���Ϊ%d������������\n\n",strlen(register_account));
 		}
 	}
	account_saving(reg_a);
	password_saving(reg_p);
}
  
//�ж��Ƿ�ע��
int judge()
{
 if(strcmp(register_account,"")==0&&strcmp(register_password,"")==0)
 {
 printf("\n\n\t\t����δע�ᣬ����ע�ᣡ\n\n");
 return 0;
 }
 else
 {
 return 1;
 }
}
  
//�û���¼
void dl()
{
 int i;
 system("pause");
 system("cls");
  
 printf("\n\n\t\t\t��ӭʹ����ѶQQ��¼ϵͳ\n\n");
 //���ε�¼��֤
 for(i=1;i<=4;i++)
 {
 printf("\t\t�������û���:");
 scanf("%s",log_account);
 printf("\n\t\t�������� ��:");
 scanf("%s",log_password);
 if(strcmp(register_account,log_account)==0&&strcmp(register_password,log_password)==0)
 {
 printf("\n\n\t\t��¼�ɹ�����ӭʹ����ѶQQϵͳ\n\n");
 break;
 }
 else
 {
 printf("\n\n\t\t��¼ʧ�ܣ������µ�¼��������%d�λ���\n\n",4-i);
 }
  
 }
  
}
int main()//��ѶQQע���½ϵͳ
{
 //�������
 int id;
 while(1)
 {
 system("cls");
 system("pause");
 //�������
 printf("\n\n\t\t\t��ѶQQ����ϵͳ\n\n");
  
 printf("\t\t\t1:ע��\n");
 printf("\t\t\t2:��¼\n");
 printf("\t\t\t0:�˳�\n\n");
  
 //���빦�ܱ��
 printf("\t\t��ѡ���ܱ�ţ�");
 scanf("%d",&id);
  
 //�ж�
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
 printf("\n\t\t������Ĺ��ܱ���������������룡\n");
 }
  
 }
  return 0;
}
 

