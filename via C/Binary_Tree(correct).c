typedef struct Node
{
    int key;
    int data;
    unsigned char height;
    struct Node* p_right;
    struct Node* p_left;
}node;

unsigned char height(node* p_node) { return p_node ? p_node->height : 0; }
int balance_factor(node* p_node) { return height(p_node->p_right) - height(p_node->p_left); }

void fix_height(node* p_node)
{
    unsigned char h_right = height(p_node->p_right);
    unsigned char h_left = height(p_node->p_left);
    p_node->height = (h_left > h_right ? h_left : h_right) + 1;
}

node* rotate_right(node* p_node)
{
    node* temp = p_node->p_left;
    p_node->p_left = temp->p_right;
    temp->p_right = p_node;
    fix_height(p_node);
    fix_height(temp);
    return temp;
}

node* rotate_left(node* p_node)
{
    node* temp = p_node->p_right;
    p_node->p_right = temp->p_left;
    temp->p_left = p_node;
    fix_height(p_node);
    fix_height(temp);
    return temp;
}

node* balance(node* p_node)
{
    fix_height(p_node);
    if(balance_factor(p_node)  == 2)
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

node* insert(node* p_node, int key, int data)
{
    if(p_node == NULL)
    {
        node* item = (node*)malloc(sizeof(node));
        item->key = key;
        item->data = data;
        item->height = 1;
        item->p_left = item->p_right = NULL;
        return item;
    }
    if (key > p_node->key) p_node->p_right = insert(p_node->p_right, key, data);
    else p_node->p_left = insert(p_node->p_left, key, data);
    return balance(p_node);
}

int get_data(node* p_node, int key)
{
    if (p_node == NULL) return 0;
    if (key == p_node->key) return p_node->data;
    else if (key > p_node->key) get_data(p_node->p_right, key);
    else if (key < p_node->key) get_data(p_node->p_left, key);
}

node* find_min(node* p_node) { return (p_node->p_left) ? find_min(p_node->p_left) : p_node; }

node* remove_min(node* p_node)
{
    if (p_node->p_left == NULL) return p_node->p_right;
    p_node->p_left = remove_min(p_node->p_left);
    return balance(p_node);
}

node* _remove(node* p_node, int key)
{
    if (p_node == NULL) return NULL;

    if (key > p_node->key) p_node->p_right = _remove(p_node->p_right, key);
    else if (key < p_node->key) p_node->p_left = _remove(p_node->p_left, key);
    else
    {
        node* right = p_node->p_right;
        node* left = p_node->p_left;
        free(p_node);
        if (right == NULL) return left;
        node* min = find_min(right);
        min->p_right = remove_min(right);
        min->p_left = left;
        return balance(min);
    }
    return balance(p_node);
}

node* clear(node* p_node)
{
    if (p_node->p_left) clear(p_node->p_left);
    if (p_node->p_right)clear(p_node->p_right);
    free(p_node);
    return NULL;
}
