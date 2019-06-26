#include <malloc.h>

typedef struct Node
{
    int data;
    struct Node *p_next;
}node;

typedef struct Stack
{
    int size;
    node *top;
}stack;

stack *create_stack(void)
{
    stack *Stack = (stack*)malloc(sizeof (stack));
    Stack->size = 0;
    Stack->top = NULL;
    return Stack;
}

void push_top(stack *Stack, int data)
{
    Stack->size++;
    node *item = (node*)malloc(sizeof (node));
    item->data = data;
    item->p_next = Stack->top;
    Stack->top = item;
}

void pop_top(stack *Stack)
{
    if(!Stack->top) return;
     node *to_delete = Stack->top;
     Stack->top = Stack->top->p_next;
     free(to_delete);
     Stack->size--;
}

stack *clear_stack(stack *Stack)
{
    while (Stack->size)
    {
        node *to_delete = Stack->top;
        Stack->top = Stack->top->p_next;
        free(to_delete);
        Stack->size--;
    }
    return NULL;
}
