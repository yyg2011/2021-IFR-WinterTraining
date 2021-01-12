#include <stdio.h> 
#include <stdlib.h>
#include "linked-list.h" 

int insert0,insert1;

list * creat_list(list * head)//�������� 
{
    head=(list*)malloc(sizeof(list));
    head->prior=NULL;
    head->next=NULL;
    head->data=1;
    list * name=head;
    insert_node(head,2);
    return head;
}

list * insert_node(list *head,int num)//����ָ���ڵ� 
{
    list *new_data=NULL;//�������
    list *current_data=NULL;
    current_data=head;
    new_data=(list*)malloc(sizeof(list));//�½��ڵ�
    new_data->data=num;
    while(new_data->data>current_data->data&&current_data->next!=NULL) current_data=current_data->next;//�����Ҳ���λ�� 
    if (new_data->data==current_data->data)	return head; //���������ͬ������һ��
    if (new_data->data>current_data->data)//����β������
    {
        current_data->next=new_data;
        new_data->prior=current_data;
        new_data->next=NULL;
    }
    else
    {
        if (head==current_data)//����ͷ������ 
        {
            new_data->next=current_data;
            current_data->prior=new_data;
            head=new_data;
        } 
        else//�����м���� 
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

list * delete_node(list *head,int num)//ɾ��ָ���ڵ� 
{
	list *delete_data=NULL;
    delete_data=head;
	while(num!=delete_data->data&&delete_data->next!=NULL)
    {
        delete_data=delete_data->next;
    }
    if (num!=delete_data->data) error();//����Ҳ����Ļ��ͱ��� 
    else
    {
        if(delete_data==head)//����ͷ��ɾ�� 
        {
            head=delete_data->next;
            head->prior=NULL;
            free(delete_data);
        }
        else if(delete_data->next==NULL) //����β��ɾ�� 
        {
            delete_data->prior->next=NULL;
            free(delete_data);
        }
        else //�����м�ɾ�� 
        {
            delete_data->next->prior=delete_data->prior;
            delete_data->prior->next=delete_data->next;
            free(delete_data);
        }
	}
	//success(); 
    return head; 
}

list * merge_list(list *head1,list *head2)//�ϲ����� 
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

void safe_flush(FILE *fp)//���scanf���� 
{
 int ch;
 while((ch=fgetc(fp))!=EOF&&ch!='\n');     
}

void success()//�ɹ���Ϣ��ʾ 
{
	system("cls");
	printf("|======�ɹ�======|\n");
	printf("|�ѳɹ�ִ�иò���|\n");
	printf("|================|\n");
	system("pause");
	system("cls");
} 

void error()//������Ϣ��ʾ 
{
	system("cls");
	printf("|======����======|\n");
	printf("|���������Ϣ����|\n");
	printf("|================|\n");
	system("pause");
	system("cls");
} 

void print(list *head)//��ӡ���� 
{
	list *temp=head;
	//system("pause");
	printf("%d <-> ",temp->data);
    while(temp->next!=NULL)//һֱ��ȡ�ڵ����� 
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
		printf("������1-����ڵ� 2-ɾ���ڵ� 3-���ڶ�������ϲ�����һ��\n");
		printf("���������ֲ���Enter��");
		scanf("%d",&insert0); 
		if(insert0==1)
		{
			printf("\n������������Ҫ��Ӧ�����������Ͳ�������ݣ�ʹ�ÿո����\n");
			printf("���������ֲ���Enter��");
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
			printf("\n������������Ҫ��Ӧ������������ɾ�������ݣ�ʹ�ÿո����\n");
			printf("���������ֲ���Enter��");
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

