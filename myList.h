#ifndef QUEUE_H
#define QUEUE_H

template<typename T>
class Node
{
public:
    Node<T> *pNext;
    Node<T> *pPrev;
    T data;

    Node(T data = T(), Node<T> *pNext = nullptr, Node<T> *pPrev = nullptr)
    {
        this->data = data;
        this->pNext = pNext;
        this->pPrev = pPrev;
    }
};

template<typename T>
class myList
{
public:
    myList();
    ~myList();

    void push_back(T data);
    void push_front(T data);
    void pop_front();
    void pop_back();
    void clear();
    int GetSize(){return size;}

    T GetData(int index);
    T GetBack();
    T GetFront();

private:
    Node<T> *head;
    Node<T> *tail;
    int size;
};

#endif // QUEUE_H

template<typename T>
myList<T>::myList()
{
    head = nullptr;
    tail = nullptr;
    size = 0;
}

template<typename T>
myList<T>::~myList()
{
    clear();
}

template<typename T>
void myList<T>::push_back(T data)
{
    if (head == nullptr)
    {
        head = new Node<T>(data);
        tail = head;
    }
    else
    {
        Node<T> *temp = tail;
        tail = new Node<T>(data, nullptr, tail);
        temp->pNext = tail;
    }
    size++;
}

template<typename T>
void myList<T>::push_front(T data)
{
    Node<T> *temp = head;
    head = new Node<T>(data, head);
    temp->pPrev = head;
    size++;
}

template<typename T>
void myList<T>::pop_front()
{
    Node<T> *toDelete = head;
    head = head->pNext;
    if (head) head->pPrev = nullptr;
    delete toDelete;

    size--;
}

template<typename T>
void myList<T>::pop_back()
{
    Node<T> *toDeleteT = tail;
    Node<T> *toDeleteP = tail->pNext;
    tail = tail->pPrev;

}

template<typename T>
void myList<T>::clear()
{
    while(size)
    {
        pop_front();
    }
}

template<typename T>
T myList<T>::GetData(int index)
{
    if (index > size/2)
    {
        int count = size-1;
        Node<T> *search = tail;

        while(search->pPrev != nullptr)
        {
            if (count == index) break;
            search = search->pPrev;
            count--;
        }
        return search->data;
    }
    else
    {
        int count = 0;
        Node<T> *search = head;

        while(search->pNext != nullptr)
        {
            if (count == index) break;
            search = search->pNext;
            count++;
        }
        return search->data;
    }
}

template<typename T>
T myList<T>::GetBack()
{
    return tail->data;
}

template<typename T>
T myList<T>::GetFront()
{
    return head->data;
}
