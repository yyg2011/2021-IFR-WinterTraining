typedef struct list
{
    struct list * prior;
    int data;
    struct list * next; 
}list;

list * creat_list(list * head);
list * insert_node(list *head,int num);
list * delete_node(list *head,int num);
list * merge_list(list *head1,list *head2);
void safe_flush(FILE *fp);
void success();
void error();
void print(list *head);
int main();

