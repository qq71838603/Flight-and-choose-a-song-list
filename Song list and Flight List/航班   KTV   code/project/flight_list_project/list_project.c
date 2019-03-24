#include "kernel_list.h"
#include "project.h"

struct flight{
	char number[10];//航班号
	char staddress[10];//起点站
	char arraddress[15];//终点站
	char date[15];//班期
	char type;//机型
	char stime[10];//起飞时间
	int price;//票价
};

struct list_node{
	struct flight info;
	struct list_head list;
};

struct list_node *init_list_head()
{
	struct list_node *Node = NULL;
	
	Node = (struct list_node *)malloc(sizeof(struct list_node));
	if(Node == NULL)
		goto Err;
	
	INIT_LIST_HEAD(&(Node->list));
	
	return Node;
	
Err:
	return NULL;
}

int tail_insert_node(struct list_node*head
							,char *number
							,char *staddress
							,char *arraddress
							,char *date
							,char type
							,char *stime
							,float price)
{
	struct list_node *Node = NULL;
	
	Node = (struct list_node *)malloc(sizeof(struct list_node));
	
	strcpy(Node->info.number,number);
	strcpy(Node->info.staddress,staddress);
	strcpy(Node->info.arraddress,arraddress);
	strcpy(Node->info.date,date);
	Node->info.type = type;
	strcpy(Node->info.stime,stime);
	Node->info.price = price;
	
	list_add_tail(&(Node->list),&(head->list));
	return 0;
}

int Show_list_data(struct list_node *head)
{
	struct list_node *p = NULL;
	system("clear");
	printf("**********************************************************\n");
	printf("航班号  起点站   终点站    班期    机型   起飞时间   票价\n");
	//遍历链表
	list_for_each_entry(p,&(head->list),list)
	{
		 
		printf("%s   %s --> %s   %s   %c    %s    %d\n",p->info.number
											       ,p->info.staddress
								                   ,p->info.arraddress
									               ,p->info.date
								                   ,p->info.type
								                   ,p->info.stime
								                   ,p->info.price);	
		
	}
	printf("**********************************************************\n");
	return 0;
}

int Show_flight(struct list_node *p)
{
	if(p == NULL)
		goto Err;
	
	
	printf("%s   %s --> %s   %s   %c    %s    %d\n",p->info.number
											       ,p->info.staddress
								                   ,p->info.arraddress
									               ,p->info.date
								                   ,p->info.type
								                   ,p->info.stime
								                   ,p->info.price);
	return 0;
Err:
	return -1;
}

struct list_node *Quick_check_number(struct list_node *head)
{
	struct list_node *p = NULL;
	
	char number[10];
	printf("提示：请输入查询的航班号(A0001):");
	scanf("%s",number);
	//printf("number:%s\n",number);
	
	system("clear");
	printf("航班号  起点站   终点站    班期    机型   起飞时间   票价\n");
	
	//记住后面没有分号;
	list_for_each_entry(p,&(head->list),list)
	{
		if(strcmp(p->info.number,number) == 0)
		{
			//printf("Found the flight is %s\n",p->info.number);
			//go OK;
			Show_flight(p);	
		}	
	}

//OK:
    //Show_flight(p);
	//printf(" check not this flight!\n");
	return p;
}


struct list_node *Find_flight_stime(struct list_node *head,char *stime)
{
	struct list_node *p = NULL;
	system("clear");
	printf("航班号  起点站   终点站    班期    机型   起飞时间   票价\n");
	
	//记住后面没有分号;
	list_for_each_entry(p,&(head->list),list)
	{
		if(strcmp(p->info.stime,stime) == 0)
		{
			//printf("Found the flight is %s\n",p->info.number);
			//当前p指向的节点就是匹配到特征值的节点
			Show_flight(p);	
		}	
	}
	
	//printf(" check not this flight!\n");
	return p;
}

struct list_node *Find_flight_date(struct list_node *head,char *date)
{
	struct list_node *p = NULL;
	system("clear");
	printf("航班号  起点站   终点站    班期    机型   起飞时间   票价\n");
	
	//记住后面没有分号;
	list_for_each_entry(p,&(head->list),list)
	{
		if(strcmp(p->info.date,date) == 0)
		{
			//printf("Found the flight is %s\n",p->info.number);
			
			Show_flight(p);	
		}	
	}
	
	//printf(" check not this flight!\n");
	return p;
}

struct list_node *Find_flight_type(struct list_node *head,char c)
{
	struct list_node *p = NULL;
	system("clear");
	printf("航班号  起点站   终点站    班期    机型   起飞时间   票价\n");
	
	
	//记住后面没有分号;
	list_for_each_entry(p,&(head->list),list)
	{
		if(p->info.type == c)
		{
			//printf("Found the flight is %s\n",p->info.number);
			
			Show_flight(p);	
		}	
	}
	
	//printf(" check not this flight!\n");
	return p;
}

void Select_check_way(struct list_node *head)
{
	int choice;
	char stime[10];
	char date[15];
	char type;
	
	while(1)
	{	
		printf("==========================================================\n");
		printf("            [1]起飞时间 [2]班期 [3]机型 [4] 退出\n");
		printf("==========================================================\n");
		printf("提示：请输入你的查询方式(如：2):");
		scanf("%d",&choice);
	
		switch(choice)
		{
		    //宏定义
			case Stime:
				printf("请输入查询的起飞时间(如13:50am)：");
				scanf("%s",stime);
				Find_flight_stime(head,stime);	
				break;	
			case Date:
				printf("请输入查询的班期(如2010.12.13)：");
				scanf("%s",date);
				Find_flight_date(head,date);
				break;
			case Type:
				printf("请输入查询的类型(如：B)：");		
				//在scanf前面加一个空格，就可以避免吃了回车键
				scanf(" %c",&type);		
				Find_flight_type(head,type);
				break;
			case Quit:
				goto OK;
			default:
				printf("警告：请输入正确的号码！\n");
				break;
		}	
	}
	
OK:
	return;
}

int Delete_flight(struct list_node *head)
{
	struct list_node *p = NULL;

	char number[10];
	printf("提示：请输入取消的航班号(A0004):");
	scanf("%s",number);
	
	list_for_each_entry(p,&(head->list),list)
	{
		if(strcmp(p->info.number,number) == 0)
		{
			//printf("找到需要删除的航班号为 %s\n",p->info.number);
			goto OK;
		}
	}
	
	printf("not found flight %s\n",number);
	return -1;
	
OK:
	list_del(&(p->list));
	free(p);
	return 0;
	
	
	
}

int Quit_system(struct list_node *head)
{
	struct list_node *p,*q;
	
	list_for_each_entry_safe(p,q,&(head->list),list)
	{
		list_del(&(p->list));
		free(p);
	}
	
	list_del(&(head->list));
	free(head);
	return 0;
}

int su_login()
{
	int flags = 5;
	char password[10];//你输入的密码！
	
	while(1)
	{
		printf("提示：请输入管理员的密码(输入quit返回菜单)：");
		scanf("%s",password);
	
		if(strcmp(password,"123456") == 0)
		{
			printf("提示：密码正确！登录成功！\n");
			return flags;	
		}
		
		else if(strcmp(password,"quit") == 0)
		{
			break;	
		}
		
		else if(strcmp(password,"123456") != 0)
		{
			printf("提示：密码错误!\n");
			continue;
		}
	}
}

void input_data(struct list_node *head)
{
	char number[10];//航班号
	char staddress[10];//起点站
	char arraddress[15];//终点站
	char date[15];//班期
	char type;//机型
	char stime[10];//起飞时间
	int price;//票价
	
	printf("请输入航班号(如B0008)：");
	scanf("%s",number);
	printf("请输入起点站(如guangzhou)：");
	scanf("%s",staddress);
	printf("请输入终点站(如shanghai):");
	scanf("%s",arraddress);
	printf("请输入班期(如2017.07.05):");
	scanf("%s",date);
	printf("请输入机型(如D):");
	scanf(" %c",&type);
	printf("请输入起飞时间(如13:50am)：");
	scanf("%s",stime);
	printf("请输入票价(如2300)：");
	scanf("%d",&price);
	
	tail_insert_node(head,number,staddress,arraddress,date,type,stime,price);
}


int main()
{
	int choice;
	int pwd_ret;
	struct list_node * head = NULL;
	
	system("clear");
	
	//1.初始化链表头
	head = init_list_head();
	
	//2.尾插若干个节点
	tail_insert_node(head,"A0001","武冈","纽约","2017.06.09",'A',"13:50pm",900);
	tail_insert_node(head,"A0002","怀化","日本","2017.06.09",'B',"14:30am",3700);
	tail_insert_node(head,"A0003","凤凰","印度","2017.06.10",'A',"09:18am",2500);
	tail_insert_node(head,"A0004","义乌","伦敦","2017.06.08",'C',"11:30am",1500);
	tail_insert_node(head,"A0005","岳阳","埃及","2017.06.10",'C',"15:00am",1600);
	tail_insert_node(head,"A0006","杭州","伦敦","2017.06.09",'C',"20:14am",2800);
	tail_insert_node(head,"A0007","广州","泰国","2017.06.11",'C',"14:30am",2300);
	tail_insert_node(head,"A0008","衡阳","巴黎","2017.06.13",'C',"22:14am",2900);
	
	printf("====================================================================\n");
	printf("                 欢迎进入航班查询系统  \n");
	
	while(1)
	{
		printf("====================================================================\n");
		printf("   [1]航班列表[2]查询航班[3]快速查询[4]航班取消[5]录入航班[0]退出\n");
		printf("====================================================================\n");
		printf("请输入您的选项(如:1)：");
		scanf("%d",&choice);
		
		switch(choice)
		{
			case 1:  //print  遍历整条链表		
				Show_list_data(head);
				break;
				
			case 2:  //Find   打印与特征值相匹配的节点的所有信息 
				Select_check_way(head);				
				break;
				
			case 3:  //Quick_check  航班号是唯一的，只要找到相匹配的节点，马上跳出遍历
				Quick_check_number(head);
				break;
				
			case 4:  //Delete
				pwd_ret = su_login();
				if(pwd_ret == LOGIN_TRUE)
					Delete_flight(head);
				break;
				
			case 5: //input
				input_data(head);
				break;
				
			case 0:  //Quit
			    Quit_system(head);
				goto QUIT;
				break;				
		}	
	}
	
QUIT:
	printf("再见!Mr.关，欢迎再次登录\n");
	return 0;
}