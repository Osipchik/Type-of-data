template<typename T>
class list
{
	class node
	{
	public:
		T data;
		node* p_next;
		node(T data = T(), node* p_next = nullptr)
		{
			this->data = data;
			this->p_next = p_next;
		}
	};

	int size;
	node* head;

public:
	list() { size = 0; head = nullptr; }
	~list();

	void push_front(T data);
	void push_back(T data);
	void insert(T data, int index);

	void pop_front();
	void pop_back();
	void pop(int index);
	void clear();

	T get_front();
	T get_back();
	T get_data(int index);
	int get_size() { return size; }
};

template<typename T>
inline list<T>::~list()
{
	clear();
}

template<typename T>
inline void list<T>::push_front(T data)
{
	head = new node(data, head);
	size++;
}

template<typename T>
inline void list<T>::push_back(T data)
{
	if (!head)
	{
		head = new node(data);
	}
	else
	{
		node* temp = head;
		while (temp->p_next)
		{
			temp = temp->p_next;
		}
		temp->p_next = new node(data);
	}
	size++;
}

template<typename T>
inline void list<T>::insert(T data, int index)
{
	if (!head || index > size || index < 0) return;
	if (index == 0) push_back(data);
	else
	{
		node* search = head;
		while (--index)
		{
			search = search->p_next;
		}
		search->p_next = new node(data, search->p_next);
		size++;
	}
}

template<typename T>
inline void list<T>::pop_front()
{
	if (head)
	{
		node* to_delete = head;
		head = head->p_next;
		delete to_delete;
		size--;
	}
}

template<typename T>
inline void list<T>::pop_back()
{
	node* search = head;
	while (search->p_next->p_next)
	{
		search = search->p_next;
	}
	node* to_delete = search->p_next->p_next;
	search->p_next = nullptr;
	delete to_delete;
	size--;
}

template<typename T>
inline void list<T>::pop(int index)
{
	if (!head || index > size || index < 0) return;
	if (index == 0) pop_front();
	else
	{
		node* search = head;
		while (--index)
		{
			search = search->p_next;
		}
		node* to_delete = search->p_next;
		search->p_next = to_delete->p_next;
		delete to_delete;
		size--;
	}
}

template<typename T>
inline void list<T>::clear()
{
	if (!head) return;

	while (head)
	{
		node* to_delete = head;
		head = head->p_next;
		delete to_delete;
		size--;
	}
}

template<typename T>
inline T list<T>::get_front()
{
	return (head) ? head->data : T();
}

template<typename T>
inline T list<T>::get_back()
{
	if (!head) return T();

	node* search = head;
	while (search->p_next)
	{
		search = search->p_next;
	}
	return search->data;
}

template<typename T>
inline T list<T>::get_data(int index)
{
	if (!head || index >= size || index < 0) return T();
	node* search = head;
	while (index--)
	{
		search = search->p_next;
	}
	return search->data;
}
