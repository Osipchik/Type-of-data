#pragma once

template<typename T>
class list
{
	class node
	{
	public:
		node* pNext;
		T data;
		node(const T data, node* p_next = nullptr)
		{
			this->data = data;
			this->pNext = p_next;
		}
	};

public:
	list();
	~list();

	void push_back(T data);
	void push_front(T data);
	void insert(int index, T data);

	void remove(int index);
	void pop_front();
	void pop_back();

	int get_data(int index) const;
	int get_size() const;

private:
	int size_;
	node* head_;
};

template<typename T>
list<T>::list()
{
	size_ = 0;
	head_ = nullptr;
}


template<typename T>
list<T>::~list()
{
	while (size_)
	{
		node* to_delete = head_;
		head_ = to_delete->pNext;
		delete to_delete;
		size_--;
	}
}


template<typename T>
void list<T>::push_back(T data)
{
	if (!head_) head_ = new node(data);
	else
	{
		node* temp = head_;
		while (temp->pNext)
		{
			temp = temp->pNext;
		}
		temp->pNext = new node(data);
	}
	size_++;
}


template<typename T>
void list<T>::push_front(T data)
{
	head_ = new node(data, head_);
	size_++;
}

template<typename T>
inline void list<T>::insert(int index, T data)
{
	if (index >= size_) return;
	else if (index == 0) push_front(data);
	else if (index == size_ - 1) push_back(data);
	else
	{
		node* search = head_;
		while(index - 1)
		{
			search = search->pNext;
			index--;
		}
		node* temp = search->pNext;
		search->pNext = new node(data, temp);
		size_++;
	}
}

template<typename T>
inline void list<T>::remove(int index)
{
	if(index >= size_) return;
	else if (index == 0) pop_front();
	else if (index == size_ - 1) pop_back();
	else
	{
		node* search = head_;
		while(index-1)
		{
			search = search->pNext;
			index--;
		}
		node* toDelete = search->pNext;
		node* temp = toDelete->pNext;
		delete toDelete;
		search->pNext = temp;
		size_--;
	}
}

template<typename T>
inline void list<T>::pop_front()
{
	if(size_ == 0) return;

	node* toDelete = head_;
	head_ = head_->pNext;
	delete toDelete;
	size_--;
}

template<typename T>
inline void list<T>::pop_back()
{
	if(size_ == 0) return;

	node* search = head_;
	for(int count = 0; count+1 < size_; count++)
	{
		search = search->pNext;
	}
	node* toDelete = search->pNext;
	delete toDelete;
	search->pNext = nullptr;
	size_--;
}


template<typename T>
int list<T>::get_data(int index) const
{
	if (index >= size_) return 0;

	node* temp = head_;
	while (index)
	{
		temp = temp->pNext;
		index--;
	}
	return temp->data;
}


template<typename T>
int list<T>::get_size() const
{
	return size_;
}


