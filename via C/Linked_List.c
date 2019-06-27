#include <stdio.h>
#include <malloc.h>

typedef struct Node
{
    int data;
    struct Node* p_next;
    struct Node* p_prev;
}node;

typedef struct Linked_List
{
    int size;
    node* head;
    node* tail;
}linked_list;

linked_list* create_list(void)
{
    linked_list* list = (linked_list*)malloc(sizeof(linked_list));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

void create_first(linked_list* list, int data)
{
    node* item = (node*)malloc(sizeof(node));
    item->data = data;
    item->p_next = NULL;
    item->p_prev = NULL;
    list->head = list->tail = item;
    list->size++;
}

void push_front(linked_list* list, int data)
{
    if (list->head == NULL)
    {
        create_first(list, data);
    }
    else
    {
        node* item = (node*)malloc(sizeof(node));
        item->data = data;
        item->p_next = list->head;
        item->p_prev = NULL;
        list->head->p_prev = item;
        list->head = item;
        list->size++;
    }
}

void push_back(linked_list* list, int data)
{
    if (list->tail == NULL)
    {
        create_first(list, data);
    }
    else
    {
        node* item = (node*)malloc(sizeof(node));
        item->data = data;
        item->p_next = NULL;
        item->p_prev = list->tail;
        list->tail->p_next = item;
        list->tail = item;
        list->size++;
    }
}

void insert(linked_list* list, int data, int index)
{
    if (index > list->size || index < 0) return;

    if (!list->head || index == 0)
    {
        push_front(list, data);
    }
    else if (index == list->size)
    {
        push_back(list, data);
    }
    else
    {
        if (index < (list->size / 2))
        {
            node* search = list->head;
            while (--index)
            {
                search = search->p_next;
            }
            node* item = (node*)malloc(sizeof(node));
            item->data = data;
            item->p_next = search->p_next;
            item->p_prev = search;
            search->p_next = item;
            search->p_next->p_prev = item;
        }
        else
        {
            index = list->size - index;
            node* search = list->tail;
            while (--index)
            {
                search = search->p_prev;
            }
            node* item = (node*)malloc(sizeof(node));
            item->data = data;
            item->p_next = search;
            item->p_prev = search->p_prev;
            search->p_prev->p_next = item;
            search->p_prev = item;
        }
        list->size++;
    }
}

void pop_front(linked_list* list)
{
    if(!list->head) return;

    node* to_delete = list->head;
    list->head = to_delete->p_next;
    list->head->p_prev = NULL;
    free(to_delete);
    list->size--;
}

void pop_back(linked_list* list)
{
    if(!list->tail) return;

    node* to_delete = list->tail;
    list->tail = to_delete->p_prev;
    list->tail->p_next = NULL;
    free(to_delete);
    list->size--;
}

void remove_(linked_list* list, int index)
{
    if(!list->head || index >= list->size || index < 0) return;

    if (index == 0)
    {
        pop_front(list);
    }
    else if (index == list->size - 1)
    {
        pop_back(list);
    }
    else
    {
        if (index < (list->size / 2))
        {
            node* search = list->head;
            while (--index)
            {
                search = search->p_next;
            }
            node* to_delete = search->p_next;
            search->p_next = to_delete->p_next;
            search->p_next->p_prev = search;
            free(to_delete);
        }
        else
        {
            index = list->size - index - 1;
            node* search = list->tail;
            while (--index)
            {
                search = search->p_prev;
            }
            node* to_delete = search->p_prev;
            search->p_prev = to_delete->p_prev;
            search->p_prev->p_next = search;
            free(to_delete);
        }
        list->size--;
    }
}

linked_list* clear(linked_list* list)
{
    while(list->size - 1)
    {
        pop_front(list);
    }
    free(list->head);
    list->head = list->tail = NULL;
    return NULL;
}

int get_data(linked_list* list, int index)
{
    if(!list->head || index >= list->size || index < 0) return 0;

    if (index == 0)
    {
        return list->head->data;
    }
    else if (index == list->size - 1)
    {
        return list->tail->data;
    }
    else
    {
        if (index < (list->size / 2))
        {
            node* search = list->head;
            while (index--)
            {
                search = search->p_next;
            }
            return search->data;
        }
        else
        {
            index = list->size - index - 1;
            node* search = list->tail;
            while (index--)
            {
                search = search->p_prev;
            }
            return search->data;
        }
    }
}

int main()
{
    linked_list* list = create_list();

    push_back(list, 1);
    push_back(list, 2);
    push_back(list, 3);
    push_back(list, 4);
    push_back(list, 5);
    push_back(list, 6);
    push_back(list, 7);
    push_back(list, 8);
    push_back(list, 9);
    push_back(list, 10);
    push_back(list, 11);
    push_back(list, 12);
    push_back(list, 13);

    push_front(list, 0);

    //remove_(list, 9);
    insert(list, 999, 9);

    for(int i = 0; i < list->size; i++)
    {
        printf("\n%d", get_data(list, i));
    }

    list = clear(list);
    free(list);
    return 0;
}
