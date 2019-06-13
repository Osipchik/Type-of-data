#pragma once

template<typename T>
class Linked_List
{
	template<typename T>
	class Node
	{
	public:
		Node<T>* pNext;
		Node<T>* pPrev;
		T data;
		Node(T data = T(), Node<T>* pNext = nullptr, Node<T>* pPrev = nullptr)
		{
			this->pNext = pNext;
			this->pPrev = pPrev;
			this->data = data;
		}
	};

	int size;
	Node<T>* head;
	Node<T>* tail;

public:
	Linked_List() { size = 0; head = tail = nullptr; }
	~Linked_List() { clear(); }

	void push_back(T data);
	void push_front(T data);
	void insert(int index, T data);

	void pop_front();
	void pop_back();
	void remove(int index);
	void clear();

	int GetSize() { return size; }
	T GetData(int index);
};

template<typename T>
inline void Linked_List<T>::push_back(T data)
{
	if (!head)
	{
		tail = head = new Node<T>(data);
	}
	else
	{
		Node<T>* current = tail;
		tail = new Node<T>(data, nullptr, tail);
		current->pNext = tail;
	}
	size++;
}

template<typename T>
inline void Linked_List<T>::push_front(T data)
{
	if (!head)
	{
		tail = head = new Node<T>(data);
	}
	else
	{
		Node<T>* current = head;
		head = new Node<T>(data, head, nullptr);
		current->pPrev = head;
	}
	size++;
}

template<typename T>
inline void Linked_List<T>::insert(int index, T data)
{
	if (index >= size) return;

	if (index == 0) push_front(data);
	else if (index == size - 1) push_back(data);
	else
	{
		if (index < size / 2)
		{
			Node<T>* next = head;
			while ((index--) - 1) { next = next->pNext; }
			Node<T>* newItem = new Node<T>(data, next->pNext, next);
			next->pNext = newItem;
		}
		else
		{
			Node<T>* previous = tail;
			index = size - index - 1;
			while ((index--) - 1) { previous = previous->pPrev; }
			Node<T>* newItem = new Node<T>(data, previous, previous->pPrev);
			previous->pPrev = newItem;
		}
		size++;
	}
}

template<typename T>
inline void Linked_List<T>::pop_front()
{
	Node<T>* toDelete = head;
	head = head->pNext;
	if(head) head->pPrev = nullptr;
	delete toDelete;
	size--;
}

template<typename T>
inline void Linked_List<T>::pop_back()
{
	Node<T>* toDelete = tail;
	tail = tail->pPrev;
	if (tail) tail->pNext = nullptr;
	delete toDelete;
	size--;
}

template<typename T>
inline void Linked_List<T>::remove(int index)
{
	if (!size) return;
	
	if (index == 0) pop_front();
	else if (index == size - 1) pop_back();
	else
	{
		if (index < (size-1) / 2)
		{
			Node<T>* previous = head;
			while ((index--) - 1) { previous = previous->pNext; }
			Node<T>* toDelete = previous->pNext;
			previous->pNext = toDelete->pNext;
			Node<T>* prev = toDelete->pNext;
			prev->pPrev = toDelete->pPrev;
			delete toDelete;
		}
		else
		{
			Node<T>* next = tail;
			index = size - index - 1;
			while ((index--) - 1) { next = next->pPrev; }
			Node<T>* toDelete = next->pPrev;
			next->pPrev = toDelete->pPrev;
			Node<T>* _next = toDelete->pPrev;
			_next->pNext = toDelete->pNext;
			delete toDelete;
		}
		size--;
	}
}

template<typename T>
inline void Linked_List<T>::clear()
{
	if (!size) return;

	Node<T>* toDelete = head;
	while (head)
	{
		toDelete = head;
		head = head->pNext;
		if(head) head->pPrev = nullptr;
		delete toDelete;
		size--;
	}
}

template<typename T>
inline T Linked_List<T>::GetData(int index)
{
	if (index >= size) return T();

	if (index == 0) return head->data;
	else if (index == size - 1) return tail->data;
	else if (index < size / 2)
	{
		Node<T>* search = head;
		while (search->pNext)
		{
			if (!index) return search->data;
			search = search->pNext;
			index--;
		}
	}
	else
	{
		int count = size-1;
		Node<T>* search = tail;
		while (search->pPrev)
		{
			if (index == count) return search->data;
			search = search->pPrev;
			count--;
		}
	}
}
