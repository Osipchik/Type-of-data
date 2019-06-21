#include <stdio.h>
#include <malloc.h>

typedef struct Node
{
    int key;
    int data;
    unsigned char height;

    struct Node *p_left;
    struct Node *p_right;
}node;


node *create_node(int key, int data)
{
    node *item = (node*)malloc(sizeof (node));
    item->key = key;
    item->data = data;
    item->p_left = NULL;
    item->p_right = NULL;
    item->height = 1;
    return item;
}

unsigned char height(node *p_node)
{
    return p_node ? p_node->height : 0;
}

int balance_factor(node *p_node)
{
    return height(p_node->p_right) - height(p_node->p_left);
}

void fix_height(node *p_node)
{
    unsigned char h_left = height(p_node->p_left);
    unsigned char h_right = height(p_node->p_right);
    p_node->height = (h_left > h_right ? h_left : h_right) + 1;
}

node *rotate_right(node *p_node)
{
    node *p_node_left = p_node->p_left;
    p_node->p_left = p_node_left->p_right;
    p_node_left->p_right = p_node;
    fix_height(p_node);
    fix_height(p_node_left);
    return p_node_left;
}

node *rotate_left(node *p_node)
{
    node* p_node_right = p_node->p_right;
    p_node->p_right = p_node_right->p_left;
    p_node_right->p_left = p_node;
    fix_height(p_node);
    fix_height(p_node_right);
    return p_node_right;
}

node *balance(node * p_node)
{
    fix_height(p_node);
    if(balance_factor(p_node) == 2)
    {
        if (balance_factor(p_node->p_right) < 0)
            p_node->p_right = rotate_right(p_node->p_right);
        return rotate_left(p_node);
    }
    if(balance_factor(p_node) == -2)
    {
        if (balance_factor(p_node->p_left) > 0)
            p_node->p_left = rotate_left(p_node->p_left);
        return rotate_right(p_node);
    }
    return p_node;
}

node *insert(int data, int key, node *p_node)
{
    if (!p_node)
        return create_node(key, data);

    if (key < p_node->key)
        p_node->p_left  = insert(data, key, p_node->p_left);
    else
        p_node->p_right = insert(data, key, p_node->p_right);
    return balance(p_node);
}

node *find_min(node *p_node)
{
    return p_node->p_left ? find_min(p_node->p_left) : p_node;
}

node *remove_min(node* p_node)
{
    if (!p_node->p_left)
        return p_node->p_right;
    p_node->p_left = remove_min(p_node->p_left);
    return balance(p_node);
}

node *remove_it(int key, node* p_node)
{
    if (!p_node) return NULL;
    if (key < p_node->key)
        p_node->p_left  = remove_it(key, p_node->p_left);
    else if(key > p_node->key)
        p_node->p_right = remove_it(key, p_node->p_right);
    else //key == p_node->key
    {
        node* p_left  = p_node->p_left;
        node* p_right = p_node->p_right;
        free(p_node);
        if (!p_right) return p_left;
        node* p_min = find_min(p_right);
        p_min->p_right = remove_min(p_right);
    }
    return balance(p_node);
}

int get_data(int key, node* p_node)
{
    if (p_node == NULL) return 0;
    if (key == p_node->key) return p_node->data;
    else if (key < p_node->key) get_data(key, p_node->p_left);
    else if (key > p_node->key) get_data(key, p_node->p_right);
}

node *clear_tree(node *p_root)
{
    while (!p_root)
    {
        p_root = remove_it(p_root->key, p_root);
    }
    return NULL;
}
int main()
{
    node *pRoot = create_node(11, 11);
    pRoot = insert(9, 9, pRoot);
    pRoot = insert(2, 2, pRoot);
    pRoot = insert(5, 5, pRoot);
    pRoot = insert(30, 30, pRoot);
    pRoot = insert(4, 4, pRoot);

    printf("%d", get_data(30, pRoot));

    pRoot = clear_tree(pRoot);
    free(pRoot);

    printf("\n%s", "Ok");
    return 0;
}
