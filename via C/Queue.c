#include <malloc.h>

typedef struct Node
{
    int data;
    struct Node *p_next;
}node;

typedef struct Queue
{
    int size;
    node *head;
    node *tail;
}queue;


queue *create_queue(void)
{
    queue *Queue = (queue*)malloc(sizeof (queue));
    Queue->head = NULL;
    Queue->tail = NULL;
    Queue->size = 0;
    return Queue;
}

void push(queue *Queue, int data)
{
    node *item = (node*)malloc(sizeof (node));
    item->data = data;
    item->p_next = NULL;
    Queue->size++;
    if(!Queue->head)
    {
        Queue->head = Queue->tail = item;
    }
    else
    {
        Queue->tail->p_next = item;
        Queue->tail = Queue->tail->p_next;
    }
}

void pop_front(queue *Queue)
{
    if(!Queue->size) return;

    node *to_delete = Queue->head;
    Queue->head = Queue->head->p_next;
    free(to_delete);
    Queue->size--;
}
