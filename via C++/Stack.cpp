template<typename T>
class Stack
{
    class Node
    {
    public:
        T data;
        Node *p_next;
        Node(T data = T(), Node *p_next = nullptr)
        {
            this->data = data;
            this->p_next = p_next;
        }
    };

    Node *top;
    int size;

public:
    Stack() { top = nullptr; size = 0; }
    ~Stack();

    void push_back(T data);
    void pop_back();
    int get_size() { return size; }
    T get_top() { return (top) ? top->data : T(); }
};

template<typename T>
Stack<T>::~Stack()
{
    while(top)
    {
        Node *to_delete = top;
        top = to_delete->p_next;
        delete to_delete;
        size--;
    }
}

template<typename T>
void Stack<T>::push_back(T data)
{
    top = new Node(data, top);
    size++;
}

template<typename T>
void Stack<T>::pop_back()
{
    if(!size) return;
    Node *to_delete = top;
    top = to_delete->p_next;
    delete to_delete;
    size--;
}
