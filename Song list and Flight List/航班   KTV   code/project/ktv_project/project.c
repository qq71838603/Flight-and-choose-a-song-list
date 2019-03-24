/** 使用双向循环链表设计KTV点歌系统 **/
/** 1.歌星点歌  2.歌名点名  3.查看已点歌曲  4.置顶 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//设计节点
typedef struct list_node{
	char singer_name[100];
	char song_name[50];
	struct list_node *next;
	struct list_node *prev;
}Node,*PLNode;

PLNode init_head(PLNode head)
{
	//1.为头节点申请堆空间
	head = (PLNode)malloc(sizeof(Node));
	if(head == NULL)
	{
		printf("init_head head is NULL!\n");
		return NULL;
	}
	
	//2.赋值,头节点无效
	head->next = head;
	head->prev = head;
	
	return head;
}

int list_add_tail(PLNode head,const char *singer,const char *song)
{
	//1.为尾插的节点申请内存
	PLNode node = NULL;
	node = (PLNode)malloc(sizeof(Node));
	if(node == NULL)
	{
		printf("list_add_tail node is NULL!\n");
		return -1;
	}
	
	//2.赋值
	strcpy(node->singer_name,singer);
	strcpy(node->song_name,song);
	
	node->prev = head->prev;
	node->next = head;
	head->prev->next = node;
	head->prev = node;
	
	return 0;
}

int show_system_song(PLNode head)
{
	PLNode p = NULL;
	system("clear");
	printf("================系统歌曲========================\n");
	printf("	歌手名字	歌曲名字						\n");
	printf("================================================\n");
	
	for(p=head->next;p!=head;p=p->next)
	{
		printf("	 %s  	%s\n",p->singer_name,p->song_name);
	}
	return 0;
}

PLNode delete_song(PLNode order_head,const char *up_song)
{
	PLNode q = NULL;
	PLNode p = NULL;
	
	for(q=order_head,p=order_head->next;p!=order_head;q=p,p=p->next)
	{
		if(!strcmp(up_song,p->song_name))
		{
			q->next = p->next;
			order_head->prev = p->prev;
			
			p->next = NULL;
			p->prev = NULL;
			
			return p;
		}
	}

	printf("你的已点列表中没有这首歌，不能置顶!\n");
	return NULL;
} 

int list_add_head(PLNode order_head,PLNode tmp)
{
	if(tmp == NULL)
	{
		printf("list_add_head tmp is NULL!\n");
		return -1;
	}

	tmp->next = order_head->next->next;
	order_head->next->next->prev = tmp;
	
	order_head->next->next = tmp;
	tmp->prev = order_head->next;
	
	return 0;
}

int up_song_top(PLNode order_head)
{
	PLNode tmp = NULL;
	char up_song[50];
	printf("请输入需要置顶的歌曲:");
	scanf("%s",up_song);
	
	//找到需要置顶的歌曲，从链表中脱链
	tmp = delete_song(order_head,up_song);
	
	//把这个脱链的节点接入正在播放歌曲的后面
	list_add_head(order_head,tmp);

}

int show_order_song(PLNode order_head)
{
	PLNode p = NULL;
	int operate;
	
	system("clear");
	printf("================已点歌曲========================\n");
	printf("	歌手名字	歌曲名字						\n");
	printf("================================================\n");
	
	for(p=order_head->next;p!=order_head;p=p->next)
	{
		printf(" 	%s  	%s\n",p->singer_name,p->song_name);
	}
	
	printf("================================================\n");
	printf("                1.置顶歌曲                      \n");
	printf("                2.返回                          \n");
	printf("================================================\n");
	printf("请输入您的选项:");
	scanf("%d",&operate);
	
	while(getchar() != '\n');
	
	switch(operate)
	{
		case 1:
			up_song_top(order_head);
		
		case 2:
			break;
		
		default:
			break;
	
	}
	return 0;
}

int show_singer(PLNode head)
{
	PLNode p = NULL;
	PLNode q = NULL;
	printf("======================歌星列表=======================\n");
	p = head->next;
	printf("	%s",p->singer_name);
	
	for(p=head->next->next;p!=head;p=p->next)
	{
		for(q=head->next;q!=p;q=q->next)
		{
			if(!strcmp(q->singer_name,p->singer_name))
			{
				break;
			}
			
			if(q == p->prev)
			{
				printf("		%s",p->singer_name);
			}
		}
	}
	printf("\n");
	return 0;
}

int select_song(PLNode head,PLNode order_head,const char *singer)
{
	PLNode p = NULL;
	char song_buf[50];
	printf("你需要点哪首歌:");
	scanf("%s",song_buf);
	printf("你点了这首歌:%s\n",song_buf);
	
	//1.遍历链表，找到这位歌手对应的这首歌
	for(p=head->next;p!=head;p=p->next)
	{
		//2. 判断这首歌对应的歌手是不是singer
		if(!strcmp(singer,p->singer_name))
		{
			// 3. 你点的歌要与歌手唱的歌的名字一模一样
			if(!strcmp(song_buf,p->song_name))
			{
				//4.尾插已点列表
				list_add_tail(order_head,p->singer_name,p->song_name);
			}
		}
	}
}


int select_song_from_singer(PLNode head,PLNode order_head)
{
	char buf_name[100];
	PLNode p = NULL;
	system("clear");

	//1.把所有的歌星名字都打印出来
	show_singer(head);
	
	//2.要求用户输入歌星名字
	printf("请输入您选择的歌星:");
	scanf("%s",buf_name);
	
	system("clear");
	
	printf("================%s的全部歌曲========================\n",buf_name);
	printf("	歌手名字	歌曲名字						\n");
	
	//3.根据用户输入的歌手名字，进行链表检索
	for(p=head->next;p!=head;p=p->next)
	{
		if(!strcmp(buf_name,p->singer_name))
		{
			printf("	%s	------ 	%s\n",p->singer_name,p->song_name);
		}
	}
	
	//4.用户输入歌曲的名字
	select_song(head,order_head,buf_name);
	
	return 0;
}

int select_song_from_song(PLNode head,PLNode order_head)
{
	//1.要求用户输入歌曲名字
	PLNode p = NULL;
	char buf_song[50];
	printf("请输入歌曲名字:");
	scanf("%s",buf_song);
	printf("你点了这首歌:%s\n",buf_song);
	
	//2.在系统歌曲链表中检索这首歌
	for(p=head->next;p!=head;p=p->next)
	{
		if(!strcmp(buf_song,p->song_name))
		{
			list_add_tail(order_head,p->singer_name,p->song_name);
		}
	}
	
	return 0;
}

int main()
{
	int operate;

	//1.为系统储存歌曲初始化一条空链表
	PLNode head = NULL;
	head = init_head(head);
	
	//2.为已点歌曲初始化一条空链表
	PLNode order_head = NULL;
	order_head = init_head(order_head);
	
	//3.通过尾插法，添加歌曲到链表后面
	list_add_tail(head,"周杰伦","晴天");
	list_add_tail(head,"薛之谦","演员");
	list_add_tail(head,"周杰伦","等你下课");
	list_add_tail(head,"邓紫棋","泡沫");
	list_add_tail(head,"周杰伦","不能说的秘密");
	
	//4.显示主菜单
	while(1)
	{
		printf("==================GEC  KTV=======================\n");
		printf("               1. 查看系统歌曲                   \n");
		printf("               2. 歌星点歌                       \n");
		printf("               3. 歌名点歌                       \n");
		printf("               4. 查看已点列表                   \n");
		printf("               5. 退出                           \n");
		printf("=================================================\n");
		printf("请输入一个选项:");
		scanf("%d",&operate);
		
		switch(operate)
		{
			case 1:
				//遍历系统歌曲
				show_system_song(head);
				break;
				
			case 2:
				select_song_from_singer(head,order_head);
				break;
			
			case 3:
				select_song_from_song(head,order_head);
				break;
			
			case 4:
				show_order_song(order_head);
				break;
			
			case 5:
				break;
			
			default:
				break;
		}
	}
	
	return 0;
}