#include <stdio.h>
#include <malloc.h>

typedef struct Node
{
    int data;
    struct Node *p_next;
    struct Node *p_prew;
}node;

typedef struct Lincked_list
{
    node *head;
    node *tail;
    int size;
}LinckeList;


void createLinckedList(LinckeList *pList)
{
    pList->head = NULL;
    pList->tail = NULL;
    pList->size = 0;
}

void push_front(LinckeList *pList, int data)
{
    if(pList->head == NULL)
    {
        pList->head = (node*)malloc(sizeof (node));
        pList->head->p_next = NULL;
        pList->head->p_prew = NULL;
        pList->tail = pList->head;

        pList->head->data = data;
    }
    else
    {
        node *item = (node*)malloc(sizeof (node));
        item->data = data;
        item->p_prew = NULL;
        item->p_next = pList->head;
        pList->head->p_prew = item;
        pList->head = item;
    }
    pList->size++;
}

void push_back(LinckeList *pList, int data)
{
    if(pList->head == NULL)
    {
        pList->head = (node*)malloc(sizeof(node));
        pList->head->p_next = NULL;
        pList->head->p_prew = NULL;
        pList->head->data = data;
        pList->tail = pList->head;
    }
    else
    {
        node *item = (node*)malloc(sizeof (node));
        item->data = data;
        item->p_next = NULL;
        item->p_prew = pList->tail;
        pList->tail->p_next = item;
        pList->tail = item;
    }
    pList->size++;
}

void insert(int index, LinckeList *pList, int data)
{
    int size = pList->size;
    if(index == 0) push_front(pList, data);
    else if(index == size) push_back(pList, data);
    else if(index < size && index > 0)
    {
       if(index < (size - 1) / 2)
       {
           node *search = pList->head;
           while(index-1)
           {
               search = search->p_next;
               index--;
           }
           node *item = (node*)malloc(sizeof (node));
           item->data = data;
           item->p_next = search->p_next;
           item->p_prew = search;
           search->p_next->p_prew = item;
           search->p_next = item;
       }
       else
       {
           index = size - index - 1;
           node *search = pList->tail;
           while(index)
           {
               search = search->p_prew;
               index--;
           }
           node *item = (node*)malloc(sizeof (node));
           item->data = data;
           item->p_prew = search->p_prew;
           item->p_next = search;
           search->p_prew->p_next = item;
           search->p_prew = item;
       }
       pList->size++;
    }
}

void pop_front(LinckeList *pList)
{
    if(pList->size)
    {
        node *toDelete = pList->head;
        pList->head = pList->head->p_next;
        pList->head->p_prew = NULL;
        free(toDelete);
        pList->size--;
    }
}

void pop_back(LinckeList *pList)
{
    if(pList->size)
    {
        node *toDelete = pList->tail;
        pList->tail = pList->tail->p_prew;
        pList->tail->p_next = NULL;
        free(toDelete);
        pList->size--;
    }
}

void remove_item(int index, LinckeList *pList)
{
    int size = pList->size;
    if(index == 0) pop_front(pList);
    else if(index == size - 1) pop_back(pList);
    else if(index < size && index > 0)
    {
        if(index < (size - 1) / 2)
        {
            node *search = pList->head;
            while(index-1)
            {
                search = search->p_next;
                index--;
            }
            node *toDelete = search->p_next;
            search->p_next = toDelete->p_next;
            toDelete->p_next->p_prew = search;
            free(toDelete);
        }
        else
        {
            index = size - index - 1;
            node *search = pList->tail;
            while(index-1)
            {
                search = search->p_prew;
                index--;
            }
            node *toDelete = search->p_prew;
            search->p_prew = toDelete->p_prew;
            toDelete->p_prew->p_next = search;
            free(toDelete);
        }
        pList->size--;
    }
}

void clear(LinckeList *plist)
{
    int size = plist->size;
    while(size)
    {
        pop_front(plist);
        size--;
    }
}

int get_data(int index, LinckeList *pList)
{
    int size = pList->size;
    if(index < size && index >= 0)
    {
        if(index < (size - 1) / 2)
        {
            node *item = pList->head;
            while(index)
            {
                item = item->p_next;
                index--;
            }
            return item->data;
        }
        else
        {
            index = size - index - 1;
            node *item = pList->tail;
            while(index)
            {
                item = item->p_prew;
                index--;
            }
            return item->data;
        }
    }
    return 0;
}




int main()
{
    LinckeList *list = (LinckeList*)malloc(sizeof (LinckeList));
    createLinckedList(list);

    push_back(list, 0);
    push_back(list, 1);
    push_back(list, 2);
    push_back(list, 3);
    push_back(list, 4);
    push_back(list, 5);
    push_back(list, 6);
    push_back(list, 7);

    //insert(8, list, 10);

    //remove_item(5, list);

    printf("size = %d\n\n", list->size);
    for(int i = 0; i < list->size; i++)
    {
        printf("%d\n", get_data(i, list));
    }

    printf("\nasd");
    return 0;
}
