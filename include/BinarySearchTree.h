#ifndef BINARYSEARCHTREE_BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_BINARYSEARCHTREE_H
#include <iostream>
#include <cstddef>
#include <fstream>
template<typename T>
class BinarySearchTree;


template <typename T>
std::ofstream & operator << (std::ofstream & out, const BinarySearchTree<T> & tree)
{
	tree.direct_walk(out, tree.GetRoot());
	return out;
};

template <typename T>
std::ostream & operator << (std::ostream & out, const BinarySearchTree<T> & tree)
{
	tree.direct_walk(out, tree.GetRoot());
	return out;
};

template <typename T>
std::istream & operator >> (std::istream & in, BinarySearchTree<T> & tree)
{
	T value;
        while (in >> value)
        	tree.insert(value);
        return in;
};

template<typename T>
class BinarySearchTree
{
public:
	struct  Node{
		T value_; 
		Node * left_;
		Node * right_;
		Node(T value) : value_(value), left_(nullptr), right_(nullptr) {};
			~Node()
			{
				delete left_;
				delete right_;
			}
	};
	
	Node* root_; 
	size_t size_;

	BinarySearchTree()
	{
		size_ = 0;
		root_ = nullptr;
	};
	BinarySearchTree(const std::initializer_list<T> & list)
	{
		size_ = 0;
		root_ = nullptr;
		for (auto it : list)
		{
			insert(it);
		};

	};
	
	Node* GetRoot() const
	{
		return root_;
	}
	~BinarySearchTree()
	{
		delete root_;
	};


	size_t size() 
	{
		return size_;
	};


	bool insert(const T & value)
	{

		Node* this_node = root_;
		Node* my_node = nullptr;
		if (root_ == nullptr)
		{
			root_ = new Node(value);
			size_++;
			return true;
		}
		while (this_node)
		{
			my_node = this_node;
			if (value == my_node->value_)
			{
				return false;
			}
			else if (value < my_node->value_)
			{
				this_node = my_node->left_;
			}
			else if (value > my_node->value_)
			{
				this_node = my_node->right_;
			}
		}
		if (value < my_node->value_)
		{
			my_node->left_ = new Node(value);
		}
		else
		{
			my_node->right_ = new Node(value);
		};
		size_++;
		return true;
	};

	const T * find(const T & value) const
	{
		Node *this_node = root_;
		if (size_ == 0)
		{
			return nullptr;
		};
		while (this_node)
		{
			if (value < this_node->value_)
			{
				this_node = this_node->left_;
			}
			else if (value > this_node->value_)
			{
				this_node = this_node->right_;
			}
			else if (value == this_node->value_)
			{
				return &this_node->value_;
			}
		}
		return nullptr;
	};

	void direct_walk(std::ostream & str, Node *now_node) const //Прямой обход 
	{
		if (!now_node) { return; }
		str << now_node->value_ << " ";
		direct_walk(str, now_node->left_);
		direct_walk(str, now_node->right_);
	}
};
#endif //BINARYSEARCHTREE_BINARYSEARCHTREE_H
