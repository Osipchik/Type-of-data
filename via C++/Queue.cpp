template<typename T>
class Queue
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

    Node *head;
    Node *tail;
    int size;

public:
    Queue();
    ~Queue();

    void push(T data);
    void pop_front();
    T get_front() { return (head) ? head->data : T(); }
    int get_size() { return size; }
};



template<typename T>
Queue<T>::Queue()
{
   head = tail = nullptr;
   size = 0;
}

template<typename T>
Queue<T>::~Queue()
{
    while (head)
    {
        Node *to_delete = head;
        head = head->p_next;
        delete to_delete;
        size--;
    }
}

template<typename T>
void Queue<T>::push(T data)
{
    if(!head)
    {
        head = tail = new Node(data);
    }
    else
    {
        tail->p_next = new Node(data);
        tail = tail->p_next;
    }
    size++;
}

template<typename T>
void Queue<T>::pop_front()
{
    Node *to_delete = head;
    head = head->p_next;
    delete to_delete;
    size--;
}
