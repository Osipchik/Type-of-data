#include <stdio.h>
#include <malloc.h>

typedef struct Node
{
    int data;
    struct Node *p_next;
}node;

typedef struct list
{
    node *head;
    int size;
}List;

void create_list(List *list)
{
    list->head = NULL;
    list->size = 0;
}

void push_front(List *list, int data)
{
    if(list->head == NULL)
    {
        list->head = (node*)malloc(sizeof (node));
        list->head->data = data;
        list->head->p_next = NULL;
        list->size++;
    }
    else
    {
        node* item = (node*)malloc(sizeof (node));
        item->data = data;
        item->p_next = list->head;
        list->head = item;
        list->size++;
    }
}

void push_back(List *list, int data)
{
    if(list == NULL)
    {
        list->head = (node*)malloc(sizeof (node));
        list->head->data = data;
        list->head->p_next = NULL;
        list->size++;
    }
    else
    {
        node *item = list->head;
        while(item->p_next)
        {
            item = item->p_next;
        }
        node *new_item = (node*)malloc(sizeof (node));
        new_item->data = data;
        new_item->p_next = NULL;
        item->p_next = new_item;
        list->size++;
    }
}

void insert(int index, List *list, int data)
{
    if(index > list->size || index < 0) return;

    if(index == 0) push_front(list, data);
    else if(index == list->size) push_back(list, data);
    else
    {
        node *item = list->head;
        while(index-1)
        {
            item = item->p_next;
            index--;
        }
        node *new_item = (node*)malloc(sizeof (node));
        new_item->data = data;
        new_item->p_next = item->p_next;
        item->p_next = new_item;
        list->size++;
    }
}

void pop_front(List *list)
{
    if(list->size == 0) return;

    node *to_delete = list->head;
    list->head = to_delete->p_next;
    free(to_delete);
    list->size--;
}

void pop_back(List *list)
{
    int size = list->size;
    if(size == 0) return;

    node *temp = list->head;
    while(size-1)
    {
        temp = temp->p_next;
        size--;
    }
    node *to_delete = temp->p_next;
    free(to_delete);
    temp->p_next = NULL;
    list->size--;
}

void remove_item(List *list, int index)
{
    if(list->size == 0) return;

    if(index == 0) pop_front(list);
    else if(index == list->size - 1) pop_back(list);
    else
    {
        node *temp = list->head;
        while(index-1)
        {
           temp = temp->p_next;
           index--;
        }
        node *to_delete = temp->p_next;
        node *p_next = to_delete->p_next;
        free(to_delete);
        temp->p_next = p_next;
        list->size--;
    }
}

void clear(List *list)
{
    while(list->head)
    {
        node *to_delete = list->head;
        list->head = to_delete->p_next;
        free(to_delete);
    }
    list->size = 0;
}

int get_data(List *list, int index)
{
    if(index > list->size) return 0;

    node *temp = list->head;
    while(index)
    {
        temp = temp->p_next;
        index--;
    }
    return temp->data;
}

int main()
{
    List *list = (List*)malloc(sizeof (List));
    create_list(list);
    push_front(list, 1);
    push_back(list, 2);
    push_back(list, 3);
    push_back(list, 4);
    push_back(list, 5);
    push_back(list, 6);
    push_front(list, 0);

    insert(7, list, 10);


    printf("size = %d\n", list->size);

    for(int i = 0; i < list->size; i++)
    {
        printf("%d\n", get_data(list, i));
    }

    clear(list);
    free(list);

    return 0;
}
