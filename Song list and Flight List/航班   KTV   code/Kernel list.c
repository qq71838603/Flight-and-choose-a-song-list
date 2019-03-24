#include "myhead.h"
#include "kernel_list.h"

struct flight{
	char number[10];//航班号
	char staddress[10];//起点站
	char arraddress[15];//终点站
	char date[15];//班期
	char type;//机型
	char stime[10];//起飞时间
	int price;//票价
};

typedef struct list_node{

	struct flight info;//数据域
	struct list_head list;

}Node,*PLNode;


PLNode init_head(PLNode head)
{
	head = (PLNode)malloc(sizeof(Node));
	if(head == NULL)
	{
		printf("init_head head is NULL\n");
	}

	INIT_LIST_HEAD(&(head->list));
	
	return head;
}


void menu(PLNode head)
{
	int a;
	do
	{
		printf("\n\n       **************************************************\n");
		printf("       *");printf("\t\t欢迎进入航班查询系统");       printf("\t\t*\n");
		printf("       **************************************************\n");
		printf("       *");printf("********Welcome to flight enquiry system*********\n");
		printf("       *");printf("****************ACCOUNT OPERATE******************\n");
		printf("       *");printf("\t\t1.航班列表    ---》");  printf("\t\t*\n");
		printf("       *");printf("\t\t2.查询航班    ---》");  printf("\t\t*\n");
		printf("       *");printf("\t\t3.快速查询    ---》");  printf("\t\t*\n");
		printf("       *");printf("\t\t4.航班取消    ---》");  printf("\t\t*\n");
		printf("       *");printf("\t\t5.录入航班    ---》");  printf("\t\t*\n");
		printf("       *");printf("\t\t0.退出系统    ---》");        printf("\t\t*\n");
		printf("       **************************************************\n");
    
		printf(" 请选择 : ");
		scanf("%d",&a);

		switch(a)//选择函数
		{
			case 1:printf("\n");system("clear");flight_list(head);break;
			case 2:printf("\n");system("clear");query_flight(head);break;
			case 3:printf("\n");system("clear");quick_query(head);break;
			case 4:printf("\n");system("clear");flight_off(head);break;
			case 5:printf("\n");system("clear");input_flight(head);break;
			case 0:printf("\n");system("clear");exit(0);break;
			default:system("clear");printf("\n请选择 1 到 5或输入0退出.\n");
		} 
   
	}while(a != 0);

}

int quick_query(PLNode head)
{
	char number[10];
	PLNode p =NULL;

	printf("请输入查询的航班号\n");
	scanf("%s",(char*)number);

	printf("********************航班列表***********************************\n");
	printf("航班号   起点站   终点站      班期     机型   起飞时间   票价  \n");

	list_for_each_entry(p,&(head->list),list)
	{
		if(strcmp(p->info.number,number) == 0)
		{
			show_one_node(p);
		}
		
	}
	
	return 0;


}



int show_one_node(PLNode p)
{
	if(p == NULL )
	{
		printf("show_one_node is NULL\n");
		return -1;
	}


	printf("%-10s%-9s-->%-10s%-12s%-6c%-11s%-12d\n",p->info.number,p->info.staddress,p->info.arraddress,p->info.date,p->info.type,p->info.stime,p->info.price);
	return 0;
}



int  query_flight(PLNode head)//查询航班
{
	int a;
	PLNode p =NULL;



	while(1)
	{

		printf("**************************************\n");
		printf("[1]起飞时间 [2]班期  [3]机型  [0]退出\n");
		printf("**************************************\n");
		printf("请输入你的查询方式(如1)\n");
		scanf("%d",&a);

		if(a == 1)
		{
			char stime[10];
			printf("请输入查询的起飞时间(如10.20pm)\n");
			scanf("%s",(char*)stime);
			system("clear");
			printf("********************航班列表***********************************\n");
			printf("航班号   起点站   终点站      班期     机型   起飞时间   票价  \n");
			list_for_each_entry(p,&(head->list),list)
			{
				if(strcmp(p->info.stime,stime) == 0)
				{
					show_one_node(p);
					return 0;
				}
			}
		}

		if(a == 2)
		{
			char date[10];
			printf("请输入查询的起飞时间(如2018.1.24)\n");
			scanf("%s",(char*)date);
			system("clear");
			printf("********************航班列表***********************************\n");
			printf("航班号   起点站   终点站      班期     机型   起飞时间   票价  \n");
			list_for_each_entry(p,&(head->list),list)
			{
				if(strcmp(p->info.date,date) == 0)
				{
					show_one_node(p);
					return 0;
				}
			}
		}

		if(a == 3)
		{
			char b;
			printf("请输入查询的机型(如A)\n");
			printf("********************航班列表***********************************\n");
			printf("航班号   起点站   终点站      班期     机型   起飞时间   票价  \n");	
			do
			{
				list_for_each_entry(p,&(head->list),list)
				{
					if(p->info.type == b)
					{
						show_one_node(p);
						return 0;
					}

				}

			}while((scanf("%c",&b)));			

		}

		if(a == 0)
		{
			break;
		}
		
	}

}


int flight_off(PLNode head)
{
	char pass[10];
	printf("请输入管理密码  输入1退出\n");	
	while(1)
	{
		scanf("%s",(char*)&pass);
		if(strcmp(pass,"1")==0)
		{
			return 0;
		}
		if(strcmp(pass,"123456") != 0)
		{
			printf("密码错误\n");
			printf("请重新输入\n");
		}
		else
		{
			break;
		}
	}


	char number[10];
	printf("请输入需要取消的航班号:\n");
	scanf("%s",(char*)&number);
	PLNode p =NULL;

	list_for_each_entry(p,&(head->list),list)
	{
		if(strcmp(p->info.number,number)==0)
		{
			list_del(&(p->list));
			free(p);
			printf("取消成功\n");
			return 0;
		}
	}
	printf("没有这个航班\n");
	return -1;

}



int flight_list(PLNode head)
{
	PLNode p = NULL;
	p = head;
	system("clear");
	printf("********************航班列表***********************************\n");
	printf("航班号   起点站   终点站      班期     机型   起飞时间   票价  \n");
	show_flight_list(p);


	return 0;
}

int input_flight(PLNode head)
{
	list_add_tail1(head);
	return 0;
}


int list_add_tail1(PLNode head)
{
	char number[10];//航班号
	char staddress[10];//起点站
	char arraddress[15];//终点站
	char date[15];//班期
	char a;//机型
	char stime[10];//起飞时间
	int price;//票价

	char pass[6]={0};

	PLNode node = NULL;
	PLNode p = NULL;

	int i;
	printf("请输入管理密码  输入1退出\n");	
	while(1)
	{	
		scanf("%s",(char*)&pass);
		if(strcmp(pass,"1")==0)
		{
			return 0;
		}
		if(strcmp(pass,"123456") != 0)
		{
			printf("密码错误\n");
			printf("请重新输入\n");
		}
		else
		{
			break;
		}
	}
	

	printf("-----------------正在录入航班-----------------\n");
	node = (PLNode)malloc(sizeof(Node));
	if(node == NULL)
	{
		printf("list_add_tail node is NULL\n");
		return -1;
	}
	printf("请输入航班号:(如A0001)\n");
	scanf("%s",(char*)&number);
	printf("请输入起点站:(如广州)\n");
	scanf("%s",(char*)&staddress);
	printf("请输入终点站:(如赣州)\n");
	scanf("%s",(char*)&arraddress);
	printf("请输入班期:(如2018.1.24)\n");
	scanf("%s",(char*)&date);
	printf("请输入机型:(如A)\n");
	scanf("%c",&a);
	printf("请输入起飞时间:(如12.20pm)\n");
	scanf("%s",(char*)&stime);
	printf("请输入票价:(如1000)\n");
	scanf("%d",&price);


	strcpy(node->info.number,number);
	strcpy(node->info.staddress,staddress);
	strcpy(node->info.arraddress,arraddress);
	strcpy(node->info.date,date);
	node->info.type = a ;
	strcpy(node->info.stime,stime);
	node->info.price=price;


	list_for_each_entry(p,&(head->list),list);
	
	list_add_tail(&(node->list),&(head->list));

	return 0;

}

int list_add_head(PLNode head)
{

	PLNode node = NULL;
	node = (PLNode)malloc(sizeof(Node));

	strcpy(node->info.number,"A0004");
	strcpy(node->info.staddress,"赣州");
	strcpy(node->info.arraddress,"广州");
	strcpy(node->info.date,"2018.1.22");
	node->info.type = 'A' ;
	strcpy(node->info.stime,"7.50am");
	node->info.price=500;

	list_add(&(node->list),&(head->list));



	node = (PLNode)malloc(sizeof(Node));

	strcpy(node->info.number,"A0003");
	strcpy(node->info.staddress,"赣州");
	strcpy(node->info.arraddress,"九江");
	strcpy(node->info.date,"2018.1.23");
	node->info.type = 'A' ;
	strcpy(node->info.stime,"2.30pm");
	node->info.price=800;

	list_add(&(node->list),&(head->list));



	node = (PLNode)malloc(sizeof(Node));

	strcpy(node->info.number,"A0002");
	strcpy(node->info.staddress,"广州");
	strcpy(node->info.arraddress,"赣州");
	strcpy(node->info.date,"2018.1.24");
	node->info.type = 'B' ;
	strcpy(node->info.stime,"6.50pm");
	node->info.price=500;

	list_add(&(node->list),&(head->list));



	node = (PLNode)malloc(sizeof(Node));

	strcpy(node->info.number,"A0001");
	strcpy(node->info.staddress,"九江");
	strcpy(node->info.arraddress,"广州");
	strcpy(node->info.date,"2018.1.24");

	node->info.type = 'C' ;
	strcpy(node->info.stime,"10.20pm");
	node->info.price=1000;

	list_add(&(node->list),&(head->list));


	return 0;
}


int show_flight_list(PLNode head)
{
	PLNode p = NULL;

	
	list_for_each_entry(p,&(head->list),list)
	{
		printf("%-10s%-9s-->%-10s%-12s%-6c%-11s%-12d\n",p->info.number,p->info.staddress,p->info.arraddress,p->info.date,p->info.type,p->info.stime,p->info.price);	
	}
	printf("***************************************************************\n");

	int a;
	printf("按1退出航班列表\n");
	while(a != 1)
	{
		scanf("%d",&a);
	}	
	system("clear");
	return 0;
}


int main(int argc, char const *argv[])
{

	PLNode head = NULL;
	head = init_head(head);//头节点

	list_add_head(head);//头插

	menu(head);

	return 0;
}


