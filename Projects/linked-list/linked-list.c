#include <stdio.h> 
#include <stdlib.h>
#include "linked-list.h" 

int insert0,insert1;

list * creat_list(list * head)//创建链表 
{
    head=(list*)malloc(sizeof(list));
    head->prior=NULL;
    head->next=NULL;
    head->data=1;
    list * name=head;
    insert_node(head,2);
    return head;
}

list * insert_node(list *head,int num)//插入指定节点 
{
    list *new_data=NULL;//定义变量
    list *current_data=NULL;
    current_data=head;
    new_data=(list*)malloc(sizeof(list));//新建节点
    new_data->data=num;
    while(new_data->data>current_data->data&&current_data->next!=NULL) current_data=current_data->next;//挨个找插入位置 
    if (new_data->data==current_data->data)	return head; //如果二者相同仅保留一个
    if (new_data->data>current_data->data)//若在尾部插入
    {
        current_data->next=new_data;
        new_data->prior=current_data;
        new_data->next=NULL;
    }
    else
    {
        if (head==current_data)//若在头部插入 
        {
            new_data->next=current_data;
            current_data->prior=new_data;
            head=new_data;
        } 
        else//若在中间插入 
        {
            current_data->prior->next=new_data;
            new_data->next=current_data;
            new_data->prior=current_data->prior;
            current_data->prior=new_data;
        }        
    }
    //success(); 
    return head; 
}

list * delete_node(list *head,int num)//删除指定节点 
{
	list *delete_data=NULL;
    delete_data=head;
	while(num!=delete_data->data&&delete_data->next!=NULL)
    {
        delete_data=delete_data->next;
    }
    if (num!=delete_data->data) error();//如果找不到的话就报错 
    else
    {
        if(delete_data==head)//若在头部删除 
        {
            head=delete_data->next;
            head->prior=NULL;
            free(delete_data);
        }
        else if(delete_data->next==NULL) //若在尾部删除 
        {
            delete_data->prior->next=NULL;
            free(delete_data);
        }
        else //若在中间删除 
        {
            delete_data->next->prior=delete_data->prior;
            delete_data->prior->next=delete_data->next;
            free(delete_data);
        }
	}
	//success(); 
    return head; 
}

list * merge_list(list *head1,list *head2)//合并链表 
{
	list *merge_data=NULL;
	merge_data=head2;
	insert_node(head1,merge_data->data);
	while(merge_data->next!=NULL) 
	{
		merge_data=merge_data->next;
		insert_node(head1,merge_data->data);
	}
	success(); 
}

void safe_flush(FILE *fp)//清除scanf缓存 
{
 int ch;
 while((ch=fgetc(fp))!=EOF&&ch!='\n');     
}

void success()//成功信息显示 
{
	system("cls");
	printf("|======成功======|\n");
	printf("|已成功执行该操作|\n");
	printf("|================|\n");
	system("pause");
	system("cls");
} 

void error()//错误信息显示 
{
	system("cls");
	printf("|======错误======|\n");
	printf("|你输入的信息有误|\n");
	printf("|================|\n");
	system("pause");
	system("cls");
} 

void print(list *head)//打印链表 
{
	list *temp=head;
	//system("pause");
	printf("%d <-> ",temp->data);
    while(temp->next!=NULL)//一直读取节点数据 
	{
		temp=temp->next;
        if (temp->next==NULL) 
		{
            printf("%d\n",temp->data);
        }
		else
		{
            printf("%d <-> ",temp->data);
        }
    }
}

int main()
{
	list *head1=NULL;
	list *head2=NULL;
	head1=creat_list(head1);
	head2=creat_list(head2);
	while(1)
	{
		print(head1); 
		print(head2); 
		printf("操作：1-插入节点 2-删除节点 3-将第二行链表合并到第一行\n");
		printf("请输入数字并按Enter：");
		scanf("%d",&insert0); 
		if(insert0==1)
		{
			printf("\n操作：请输入要对应操作的行数和插入的数据，使用空格隔开\n");
			printf("请输入数字并按Enter：");
			scanf("%d %d",&insert0,&insert1); 
			if (insert0==1)
			{
				insert_node(head1,insert1);
				success();
			}
			else if (insert0==2)
			{
				insert_node(head2,insert1);
				success();
			} 
			else error();
			safe_flush(stdin);
		}
		else if(insert0==2)
		{
			printf("\n操作：请输入要对应操作的行数和删除的数据，使用空格隔开\n");
			printf("请输入数字并按Enter：");
			scanf("%d %d",&insert0,&insert1); 
			if (insert0==1)
			{
				delete_node(head1,insert1);
				success();
			}
			else if (insert0==2)
			{
				delete_node(head2,insert1);
				success();
			} 
			else error();
			safe_flush(stdin);
		}
		else if(insert0==3)
		{
			merge_list(head1,head2);
			safe_flush(stdin);
		}
		else
		{
			error();
			safe_flush(stdin);
		}
	}
}

