#pragma once

#include <vector>

template<typename T1, typename T2>
class AVL_Tree
{
	class node
	{
	public:
		T1 data;
		T2 key;
		node* p_right;
		node* p_left;
		unsigned char height;
		node(T1 data, T2 key)
		{
			this->data = data;
			this->key = key;
			p_left = p_right = nullptr;
			height = 1;
		}
	};
	node* p_root = nullptr;

	unsigned char height(node* p_node) { return (p_node) ? p_node->height : 0; }
	int balance_factor(node* p_node) { return height(p_node->p_right) - height(p_node->p_left); }
	void fix_height(node* p_node);

	auto* rotate_right(node* p_node); //node*
	auto* rotate_left(node* p_node); //node*
	auto* balance(node* p_node); //node*

	auto insert(node* p_node, T1 data, T2 key) -> auto*; //node*

	T1 get_data(node* p_node, T2 key);

	node* find_min(node* p_node) { return (p_node->p_left) ? find_min(p_node->p_left) : p_node; }
	auto* remove_min(node* p_node);
	auto* remove(node* p_node, T2 key);
	node* clear(node* p_node);

	void get_NLR(node* p_node, std::vector<T2> &vec);

public:
	~AVL_Tree() { p_root ? clear(p_root) : nullptr; }

	void insert(T1 data, T2 key) { p_root = insert(p_root, data, key); }
	void remove(T2 key) { p_root = p_root ? remove(p_root, key) : nullptr; }
	void clear() { p_root = p_root ? clear(p_root) : nullptr; }
	T1 get_data(T2 key) { return p_root ? get_data(p_root, key) : T1(); }
	T1 get_root() { return p_root ? p_root->data : T1(); }
	void get_NLR(std::vector<T2> &vec) { get_NLR(p_root, vec); }
};

template<typename T1, typename T2>
inline void AVL_Tree<T1, T2>::fix_height(node* p_node)
{
	unsigned char h_left = height(p_node->p_left);
	unsigned char h_right = height(p_node->p_right);
	p_node->height = (h_left > h_right ? h_left : h_right) + 1;
}

template<typename T1, typename T2>
inline auto* AVL_Tree<T1, T2>::rotate_right(node* p_node)
{
	node* p_left = p_node->p_left;
	p_node->p_left = p_left->p_right;
	p_left->p_right = p_node;
	fix_height(p_node);
	fix_height(p_left);
	return p_left;
}

template<typename T1, typename T2>
inline auto* AVL_Tree<T1, T2>::rotate_left(node* p_node)
{
	node* p_right = p_node->p_right;
	p_node->p_right = p_right->p_left;
	p_right->p_left = p_node;
	fix_height(p_node);
	fix_height(p_right);
	return p_right;
}

template<typename T1, typename T2>
inline auto* AVL_Tree<T1, T2>::balance(node* p_node)
{
	fix_height(p_node);
	if (balance_factor(p_node) == 2)
	{
		if(balance_factor(p_node->p_right) < 0)
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

template<typename T1, typename T2>
inline auto* AVL_Tree<T1, T2>::insert(node* p_node, T1 data, T2 key)
{
	if (p_node == nullptr) return new node(data, key);

	if (key < p_node->key) p_node->p_left = insert(p_node->p_left, data, key);
	else p_node->p_right = insert(p_node->p_right, data, key);

	return balance(p_node);
}

template<typename T1, typename T2>
inline T1 AVL_Tree<T1, T2>::get_data(node* p_node, T2 key)
{
	if (p_node == nullptr) return T2();
	if (key == p_node->key) return p_node->data;
	else if (key > p_node->key) get_data(p_node->p_right, key);
	else if (key < p_node->key) get_data(p_node->p_left, key);
}

template<typename T1, typename T2>
inline auto* AVL_Tree<T1, T2>::remove_min(node* p_node)
{
	if (!p_node->p_left) return p_node->p_right;
	p_node->p_left = remove_min(p_node->p_left);
	return balance(p_node);
}

template<typename T1, typename T2>
inline auto* AVL_Tree<T1, T2>::remove(node* p_node, T2 key)
{
	if (!p_node)
	{
		node* temp = nullptr;
		return temp;
	}
	
	if (key > p_node->key) p_node->p_right = remove(p_node->p_right, key);
	else if (key < p_node->key) p_node->p_left = remove(p_node->p_left, key);
	else // key == p_node->key
	{
		node* left = p_node->p_left;
		node* right = p_node->p_right;
		delete p_node;

		if (!right) return left;
		node* min = find_min(right);
		min->p_right = remove_min(right);
		min->p_left = left;
		return balance(min);
	}
	return balance(p_node);
}

template<typename T1, typename T2>
inline typename AVL_Tree<T1, T2>::node* AVL_Tree<T1, T2>::clear(node* p_node)
{
	if (p_node->p_left) p_node->p_left = clear(p_node->p_left);
	if (p_node->p_right) p_node->p_right = clear(p_node->p_right);
	delete p_node;
	return nullptr;
}

template<typename T1, typename T2>
inline void AVL_Tree<T1, T2>::get_NLR(node* p_node, std::vector<T2> &vec)
{
	if(!p_node) return;

	vec.push_back(p_node->data);
	get_NLR(p_node->p_left, vec);
	get_NLR(p_node->p_right, vec);
}
