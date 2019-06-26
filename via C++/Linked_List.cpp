#pragma once

template<typename T>
class linked_list
{
	class node
	{
	public:
		T data;
		node* p_next;
		node* p_prev;
		node(T data = T(), node *p_next = nullptr, node* p_prev = nullptr)
		{
			this->data = data;
			this->p_next = p_next;
			this->p_prev = p_prev;
		}
	};

	int size;
	node* head;
	node* tail;

public:
	linked_list();
	~linked_list();

	void push_front(T data);
	void push_back(T data);
	void insert(T data, int index);

	void pop_front();
	void pop_back();
	void remove(int index);

	T get_data(int index);
	T get_front() { return (head) ? head->data : T(); }
	T get_back() { return (tail) ? tail->data : T(); }
	int get_size() { return size; }
};

template<typename T>
inline linked_list<T>::linked_list()
{
	size = 0;
	head = tail = nullptr;
}

template<typename T>
inline linked_list<T>::~linked_list()
{
	while(head)
	{
		pop_front();
	}
}

template<typename T>
inline void linked_list<T>::push_front(T data)
{
	if(!head)
	{
		head = tail = new node(data);
	}
	else
	{
		node* temp = head;
		head = new node(data, head);
		temp->p_prev = head;
	}
	size++;
}

template<typename T>
inline void linked_list<T>::push_back(T data)
{
	if(!tail)
	{
		tail = head = new node(data);
	}
	else
	{
		node* temp = tail;
		tail = new node(data, nullptr, tail);
		temp->p_next = tail;
	}
	size++;
}

template<typename T>
inline void linked_list<T>::insert(T data, int index)
{
	if(!head || index > size || index < 0) return;

	if (index == 0) push_front(data);
	else if (index == size) push_back(data);
	else
	{
		if(index < (size / 2))
		{
			node* search = head;
			while (--index)
			{
				search = search->p_next;
			}
			node* temp = search->p_next;
			search->p_next = new node(data, search->p_next, search);
			temp->p_prev = search->p_next;
		}
		else
		{
			index = size - index + 1;
			node* search = tail;
			while (--index)
			{
				search = search->p_prev;
			}
			node* temp = search->p_prev;
			search->p_prev = new node(data, search, search->p_prev);
			temp->p_next = search->p_prev;
		}
		size++;
	}
}

template<typename T>
inline void linked_list<T>::pop_front()
{
	if(!head) return;

	node* to_delete = head;
	head = head->p_next;
	head->p_prev = nullptr;
	delete to_delete;
	size--;
}

template<typename T>
inline void linked_list<T>::pop_back()
{
	if(!tail) return;

	node* to_delete = tail;
	tail = tail->p_prev;
	tail->p_next = nullptr;
	delete to_delete;
	size--;
}

template<typename T>
inline void linked_list<T>::remove(int index)
{
	if(!head || index == size || index < 0) return;

	if (index == 0) pop_front();
	else if (index == size - 1) pop_back();
	else
	{
		if(index < size / 2)
		{
			node* temp = head;
			while(--index)
			{
				temp = temp->p_next;
			}
			node* to_delete = temp->p_next;
			temp->p_next = to_delete->p_next;
			temp->p_next->p_prev = temp;
		}
		else
		{
			index = size - index - 1;
			node* temp = tail;
			while(--index)
			{
				temp = temp->p_prev;
			}
			node* to_delete = temp->p_prev;
			temp->p_prev = to_delete->p_prev;
			temp->p_prev->p_next = temp;
		}
		size--;
	}
}

template<typename T>
inline T linked_list<T>::get_data(int index)
{
	if (!head || index >= size || index < 0) return T();

	if (index == 0) get_front();
	else if (index == size - 1) get_back();
	else
	{
		if (index < (size / 2))
		{
			node* search = head;
			while (index--)
			{
				search = search->p_next;
			}
			return search->data;
		}
		else
		{
			index = size - index - 1;
			node* search = tail;
			while (index--)
			{
				search = search->p_prev;
			}
			return search->data;
		}
	}
}
