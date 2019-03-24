#include "myhead.h"

typedef struct list_node{

	char song_name[50];
	char singer_name[50];
	struct list_node*next;
	struct list_node*prev;

}Node,*PLNode;

typedef struct music_list{

	char song_name[50];
	char singer_name[50];
	struct music_list*next;
	struct music_list*prev;

}Node1,*PLNode1;



PLNode init_head(PLNode head)//系统歌曲链表头
{
	head = (PLNode)malloc(sizeof(Node));
	if(head == NULL)
	{
		printf("init_head head is NULL\n");
	}

	head->next = head;
	head->prev = head;

	return head;
}

PLNode1 init_head1(PLNode1 head_music)//列表歌曲链表头
{
	head_music = (PLNode1)malloc(sizeof(Node1));
	if(head_music == NULL)
	{
		printf("init_head head_music is NULL\n");
	}

	head_music->next = head_music;
	head_music->prev = head_music;

	return head_music;
}

void menu()//主菜单
{
	int a;

	PLNode head = NULL;
	PLNode1 head_music = NULL;
	head = init_head(head);
	head_music = init_head1(head_music);

	list_add_head(head);

	do
	{
		printf("\n\n       **************************************************\n");
		printf("       *");printf("\t\t欢迎进入KTV点歌系统");       printf("\t\t*\n");
		printf("       **************************************************\n");
		printf("       *");printf("*********************GEC KTV*********************\n");
		printf("       *");printf("*********************主界面**********************\n");
		printf("       **************************************************\n");
		printf("       *");printf("\t\t1.查看系统所有歌曲---》");  printf("\t\t*\n");
		printf("       *");printf("\t\t2.歌星点歌        ---》");  printf("\t\t*\n");
		printf("       *");printf("\t\t3.歌名点歌        ---》");  printf("\t\t*\n");
		printf("       *");printf("\t\t4.查看已点列表    ---》");  printf("\t\t*\n");
		printf("       *");printf("\t\t5.录入歌曲        ---》");  printf("\t\t*\n");
		printf("       *");printf("\t\t6.退出系统        ---》");  printf("\t\t*\n");
		printf("       **************************************************\n");
    
		printf(" 请选择 : ");
		scanf("%d",&a);

		switch(a)//选择函数
		{
			case 1:printf("\n");system("clear");system_music(head);break;
			case 2:printf("\n");system("clear");singer_name_music(head,head_music);break;
			case 3:printf("\n");system("clear");song_music(head,head_music);break;
			case 4:printf("\n");system("clear");music_list(head_music);break;
			case 5:printf("\n");system("clear");add_music(head);break;
			case 6:printf("\n");system("clear");exit(0);
			default:system("clear");printf("\n请选择 1 到 4或输入5退出.\n");
		}
   
	}while(a != 6);
}

//通过歌曲名字点歌
int song_music(PLNode head,PLNode1 head_music)
{
	char song_name[50];
	PLNode p = NULL;
	PLNode1 z = NULL;

	printf("------------------歌曲列表----------------------------\n");
	for(p=head->next;p != head;p=p->next)
	{
		printf("%s\t",p->song_name);

	}
	printf("\n------------------------------------------------------\n");
	printf("请输入歌曲名字\n");
	scanf("%s",(char*)song_name);

	for(p=head->next;p != head;p=p->next)
	{
		if(strcmp(p->song_name,song_name) == 0)
		{
			break;
		}

	}
	if(p == head)
	{
		printf("没有这首歌!\n");
		return -1;
	}

	for(p=head->next;p != head;p=p->next)
	{
		if(strcmp(p->song_name,song_name) == 0)
		{
			for(z=head_music->next;z != head_music;z=z->next )
			{
				if(strcmp(z->song_name,song_name)==0)
				{
					printf("已经在列表中点了这首歌，不能重复点\n");
					return -1;
				}
			}
			list_add_tail(head_music,p->singer_name,p->song_name);
		}
	}
	return 0;
}

//通过歌手名字点歌
int singer_name_music(PLNode head,PLNode1 head_music)
{
	printf("---------------歌手列表-------------\n");
	PLNode p = NULL;
	PLNode q = NULL; 

	p = head->next;
	printf("\t%s\t",p->singer_name);

	for(p=head->next->next;p != head ;p = p->next)
	{
		for(q = head->next;q != p;q = q->next)
		{
			if(strcmp(q->singer_name,p->singer_name) == 0)
			{
				break;
			}

			if(q == p->prev)
			{
				printf("%s\t",p->singer_name);
			}
		}
	}



	/*
	char *a[5] = {"周杰伦","薛之谦","周杰伦","邓紫棋","周杰伦"};  //42651
	int i,j;
	
	printf("\t%s\t",(char*)a[0]);
	
	for(i=1;i<5;i++)//被对比的数
	{		
		for(j=0;j<i;j++)//去跟i对比的数
		{
			if(a[j] == a[i])
				break;
			if(j == i-1)//一直对比到这个数的上一个数为止
				printf("%s\t",(char*)a[i]);	
		}	
	}*/
	
	PLNode l = NULL;

	printf("\n");
	printf("------------------------------------\n" );
	char singer_name1[50];
	printf("请输入歌手名字\n");
	scanf("%s",(char*)singer_name1);
	for(l=head->next;l != head;l=l->next)
	{
		if(strcmp(l->singer_name,singer_name1)==0)
		{
			break;
		}
	}	


		if(l == head)
		{
			printf("没有这个歌手!\n");
			return -1;
		}


	system("clear");

	printf("*******************歌手的全部歌曲为***************\n");
	printf("**************************************************\n");
	PLNode t = NULL;
	for(t=head->next;t != head; t=t->next)
	{
		if(strcmp(t->singer_name,singer_name1) ==0)
		{
			show_one_node(t);
		}
	}

	char song_name1[50];
	PLNode n = NULL;

	PLNode1 z = NULL;

	printf("**************************************************\n");
	printf("请选择需要点的歌曲\n");
	scanf("%s",(char*)song_name1);

	//遍历链表 找到歌手对应的这首歌
	for(n=head->next;n != head; n=n->next)
	{	//判断这首歌对应的歌手是不是singer
		if(strcmp(singer_name1,n->singer_name) == 0)
		{	//点的歌是否与歌手唱的一致
			if(strcmp(n->song_name,song_name1)==0)
			{	//是否已经点过这首歌
				for(z=head_music->next;z != head_music;z=z->next )
				{	
					if(strcmp(z->song_name,song_name1)==0)
					{
						printf("已经在列表中点了这首歌，不能重复点\n");
						return -1;
					}
				}
				list_add_tail(head_music,n->singer_name,n->song_name);	
			}
		}
		
	}
	return 0;
}


int list_add_tail(PLNode1 head_music,char singer_name[],char song_name[])
{
	//尾插入点歌列表
	PLNode1 node = NULL;
	PLNode1 p = NULL;
	//分配节点
	node = (PLNode1)malloc(sizeof(Node1));

	if(node == NULL)
	{
		printf("list_add_tail node is NULL\n");
		return -1;
	}
	//传递数据
	strcpy(node->singer_name , singer_name);
	strcpy(node->song_name , song_name);
	//尾插
	p=head_music->next;
	while(1)
	{
		if(p->next == head_music)
		{
			break;
		}
		p = p->next;
	}
	
	p->next = node;
	node->next = head_music;
	node->prev = p;
	

	return 0;
}




int show_one_node(PLNode t)//通过遍历列表所传过来的参数显示节点数据
{
	if(t == NULL)
	{
		printf("show_one_node is NULL\n");
		return -1;
	}

	printf("          %-10s       -------     %-10s\n",t->singer_name,t->song_name );
	return 0;
}

int add_music(PLNode head)
{
	char singer_name[50];
	char song_name[50];
	if(head == NULL)
	{
		printf("add_music head is NULL\n");
		return -1;
	}
	printf("请输入录入的歌名\n");
	scanf("%s",(char*)song_name);
	printf("请输入录入的歌星\n");
	scanf("%s",(char*)singer_name);

	list_add_head2(head,singer_name,song_name);

	printf("录入成功!\n");

	return 0;
}


int list_add_head2(PLNode head,char singer_name[],char song_name[])
{
	PLNode node = NULL;

	node = (PLNode)malloc(sizeof(Node));

	if(node == NULL)
	{
		printf("list_add_head node is NULL\n");
		return -1;
	}

	strcpy(node->singer_name,singer_name);
	strcpy(node->song_name,song_name);

	node->next = head->next;
	if(head->next != NULL)
		head->next->prev = node;

	node->prev = head;
	head->next = node;
	return 0;
}


int list_add_head(PLNode head)//系统列表的头插
{
	PLNode node = NULL;
	//分配节点
	node = (PLNode)malloc(sizeof(Node));	

	strcpy(node->song_name,"不能说的秘密");
	strcpy(node->singer_name,"周杰伦");

	//头插
	node->next = head->next;
	if(head->next != NULL)
		head->next->prev = node;

	node->prev = head;
	head->next = node;

	node = (PLNode)malloc(sizeof(Node));

	strcpy(node->song_name,"爱你");
	strcpy(node->singer_name,"邓紫棋");

	node->next = head->next;
	if(head->next != NULL)
		head->next->prev = node;

	node->prev = head;
	head->next = node;

	node = (PLNode)malloc(sizeof(Node));

	strcpy(node->song_name,"晴天");
	strcpy(node->singer_name,"周杰伦");

	node->next = head->next;
	if(head->next != NULL)
		head->next->prev = node;

	node->prev = head;
	head->next = node;
	
	node = (PLNode)malloc(sizeof(Node));

	strcpy(node->song_name,"绅士");
	strcpy(node->singer_name,"薛之谦");

	node->next = head->next;
	if(head->next != NULL)
		head->next->prev = node;

	node->prev = head;
	head->next = node;

	node = (PLNode)malloc(sizeof(Node));

	strcpy(node->song_name,"告白气球");
	strcpy(node->singer_name,"周杰伦");

	node->next = head->next;
	if(head->next != NULL)
		head->next->prev = node;

	node->prev = head;
	head->next = node;

	return 0;
}




int list_add_head1(PLNode1 head_music,PLNode1 tmp)
{
	if(tmp == NULL)
	{
		printf("list_add_head is NULL\n");
		return -1;
	}

	tmp->next = head_music->next->next;
	head_music->next->next->next->prev = tmp;

	head_music->next->next = tmp;
	tmp->prev = head_music->next;

	return 0;

}

PLNode1 delete_song(PLNode1 head_music,const char*up_song)
{
	PLNode1 q = NULL;
	PLNode1 p = NULL;

	for(q=head_music,p=head_music->next; p != head_music;q = p ,p = p->next)
	{
		if(strcmp(up_song,p->song_name) == 0)
		{
			q->next = p->next;
			p->next->prev = p->prev;

			p->next = NULL;
			p->prev = NULL;

			return p;
		}
	}


	printf("你点的列表中没有这首歌! \n");
	return NULL;
}

int up_song_top(PLNode1 head_music)
{
	PLNode1 tmp = NULL;
	char up_song[50];
	printf("请输入需要置顶的歌曲:\n");
	scanf("%s",up_song);


	//找到需要置顶的歌曲  从链表中脱链
	tmp = delete_song(head_music,up_song);
	//把这个脱链的节点接入正在播放歌曲的后面
	if(tmp != NULL)
	{
		list_add_head1(head_music,tmp);
	}

	return 0;
}


int music_list(PLNode1 head_music)//已点歌曲列表
{
	PLNode1 p = NULL;
	
	printf("**********************已点歌曲*********************************\n");
	printf("          歌手名                       歌曲名  \n");
	for(p=head_music->next;p != head_music;p=p->next)//遍历已点歌曲列表
	{
		printf("          %-8s       ---------        %-8s\n",p->singer_name,p->song_name);	
	}
	printf("***************************************************************\n");
	printf("***************************************************************\n");
	printf("                       1.置顶歌曲\n");
	printf("                       2.删除歌曲\n");
	printf("                       3.返回\n");
	printf("***************************************************************\n");
	int a;

	printf("请选择:\n");
	scanf("%d",&a);

	while(getchar() != '\n');

	if(a == 3)
	{
		system("clear");
		return 0;
	}
	else if (a == 1)
	{	
		up_song_top(head_music);
	}
	else if (a == 2)
	{
		char song_name[50];
		PLNode1 m = NULL;
		PLNode1 n = NULL;

		printf("请输入需要删除的歌曲:\n");
		scanf("%s",(char*)song_name);
		for(n=head_music->next; n != head_music; n=n->next)
		{
			if(!strcmp(n->song_name,song_name) == 0)
			{
				break;	
			}
			if(n == head_music)
			{
				printf("列表中没有这首歌\n");
				return -1;
			}
		}

			 
		m=delete_song(head_music,song_name);
		free(m);
		

	}


	return 0;
}


int system_music(PLNode head)//显示系统歌曲
{
	PLNode p = NULL;
	
	printf("********************系统歌曲***********************************\n");
	printf("          歌手名                    歌曲名  \n");
	for(p=head->next;p != head;p=p->next)//遍历链表
	{
		printf("          %-10s       -------     %-10s\n",p->singer_name,p->song_name);	
	}
	printf("***************************************************************\n");

	int a;
	printf("输入任意键退出歌曲列表\n");
	scanf("%d",&a);
	while(getchar() != '\n');
	
	system("clear");

	return 0;
}



int main(int argc, char const *argv[])
{

	menu();//主菜单

	return 0;
}