#include "user.h"
#include <string.h>

//������ 
extern account logger;
char register_account[30]="",register_password[10]="";
char librarian_account[]={"librarian"};//ͼ�����Ա���˺�
char librarian_password[]={"librarian"};//ͼ�����Ա������ 
char log_account[30],log_password[10];
Account accounts;

int display_book()   //��������ͼ�� 
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
		total+=pdisplay->copies;//ͼ��������� 
		pdisplay=pdisplay->nextbook;
	}
	printf("\t\tThe total number of books is��%d\n",total);
	system("pause");
	return 0;
}
//����ģ�� 
void borrow()
{
	char ny;
	int d=0; 
	FILE *afile,*file;
	pbook book_head,pfind,pointer;
	book_head = load_books();
	unsigned int iD;
	if(logger->Borrow<5) //�ж��û������鼮���Ƿ��ѵ������� 
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
				printf("\t\tDo you need to borrow this book��1. To borrow or 2. Not to borrow\n");
				ny = getch();
				if(ny == '1') //���û�ѡ���Ƿ���� 
				{
					pfind->copies=pfind->copies-1; 
					logger->borrow[logger->Borrow]=iD;
					logger->Borrow=logger->Borrow+1;
					printf("\t\tBorrow successfully, press any key to return...\n");
					account_saving(*logger);
					file=fopen("bookfile","wb");   //ͨ��ֻд�ķ�ʽ�򿪶������ļ���bookfile�������Ҵ�ʱ����ļ���ԭ�е�����  
					if(file==NULL)
					{
						printf("cannot open file"); 
					}
					if(fwrite(book_head,M,1,file)!=1)   //���ļ�ָ��fileָ����ļ�������pointerָ����ָ�����Ϣ 
					{
						printf("write error!"); 
					}
						fclose(file);   //�رյ�ǰ�ļ� 
					if(book_head!=NULL)   //���ͷָ�벻��NULL 
					{
						pointer=book_head->nextbook;     //��pointer��Ϊ�ڶ����ڵ��ָ�� 
						file=fopen("bookfile","ab");   //��׷�ӵķ�ʽ��bookfile�������ļ�
						if(file==NULL)
					{
						printf("cannot open file");
					}
					while(pointer!=NULL)
					{
						if(fwrite(pointer,M,1,file)!=1)//���ļ�ָ��fileָ����ļ�������pointerָ����ָ�����Ϣ 
					{
						printf("write error!");
					}
						pointer=pointer->nextbook;
					}
						fclose(file);  //�ر��ļ� 
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
//����ģ��
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
						file=fopen("bookfile","wb");   //ͨ��ֻд�ķ�ʽ�򿪶������ļ���bookfile�������Ҵ�ʱ����ļ���ԭ�е�����   
						if(file==NULL)
						{
							printf("cannot open file"); 
						}
						if(fwrite(rebookss,M,1,file)!=1)   //���ļ�ָ��fileָ����ļ�������pointerָ����ָ�����Ϣ 
						{
							printf("write error!"); 
						}
						fclose(file);   //�رյ�ǰ�ļ� 
						if(rebookss!=NULL)   //���ͷָ�벻��NULL 
						{
							pointer=rebookss->nextbook;     //��pointerָ�������еڶ������ 
							file=fopen("bookfile","ab");   //��׷�ӵķ�ʽ�򿪶������ļ� 
						if(file==NULL)
						{
							printf("cannot open file");
						}
						while(pointer!=NULL)
						{
							if(fwrite(pointer,M,1,file)!=1)//��pointerָ����Ϣд��file��ָ����ļ���
						{
							printf("write error!");
						}
							pointer=pointer->nextbook;
						}
							fclose(file);  //�ر��ļ� 
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

//�洢�˺�ģ��    
void account_saving(Account A)   //���û�ע���˺ż���Ϣд���ļ� 
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
//��ȡ�洢�˺���Ϣ���ļ� 
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
	    else             //����һ������ 
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

//�����˻�ģ�� 
void logon()
{
	Account reg_a;
	account pa = load_account();  //����ͷָ�� 
	int x = 0, y = 0;
 	//�����Ļ 
 	system("cls");
	while(1)
 	{
 		//�����û���
 		printf("\t\tPlease enter the user name [no more than 12 characters]:");
 		scanf("%s",register_account);
  		
 		//�ж��û����Ƿ���ȷ 
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
    			for (x=0; x<30; ++x)	//��register_account�����е�ֵ����reg_a.register_account���� 
    			{
        			reg_a.register_account[x] = register_account[x];
    			}	  				
 				//�����û�����
 				printf("\n\t\tPlease enter the password [password length is 6 digits]��");
 				scanf("%s",register_password);
  
 				//�ж��û������ʽ 
 				if(strlen(register_password)==6)
 				{
    				for (x=0; x<10; ++x)	//��register_password�����е�ֵ����reg_a.register_password���� 
    				{
        				reg_a.register_password[x] = register_password[x];
    				}		 					
 					printf("\n\n\t\tRegistration is successful. Your user name is %s,The password is %s\n\n",register_account,register_password);
 					break;
 				}
 				else
 				{
 					printf("\n\t\tThe length of the password is %d��Please re-enter\n",strlen(register_password));
 				}
 			}
 			break;
 		}
 		else
 		{
 			printf("\n\t\tThe length of the user name is %d��Please re-enter\n\n",strlen(register_account));
 		}
 	}
	account_saving(reg_a);
}
  
  
//�û���¼
account loging()
{
 	int x , y = 0;
 	account log_head = load_account() , current_account = NULL;
 	system("pause");
 	system("cls");
 	printf("\n\n\t\t\tWelcome to the library login system\n\n");
 	//���ε�¼��֤
 	for(x=1;x<=3;x++)
 	{
 		printf("\t\tPlease enter the user name:");
 		scanf("%s",log_account);
 		printf("\n\t\tPlease input a password:");
 		scanf("%s",log_password);
 		if(strcmp(log_account,librarian_account)==0&&strcmp(log_password,librarian_account)==0){
			printf("\t\tLog in as librarian\n"); //��ͼ�����Ա����ݵ���
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

void terminate()       //��ֹ������� 
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
		scanf("%d",&i);         //���û�����ѡ�� 
		switch(i)
		{
			case 1:
			setxy(20,18);
			printf("The software has been safely exited\n");
			setxy(20,20);
			printf("Thank you for using��\n");
			exit(0);  
			break; //������������ 
			case 2:
			Mainmenu(); //���½������˵� 
			break;    
			default :break;
		}
	}
} 

