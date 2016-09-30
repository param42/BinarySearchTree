
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
	tree.symmetric_walk(out, tree.GetRoot());
	return out;
};

template <typename T>
std::istream & operator >> (std::istream & in, BinarySearchTree<T> & tree)
{
	T value;
	while (in >> value) tree.insert(value);
	return in;
};

template<typename T>
class BinarySearchTree
{
public:
	class  Node{
	public:
		T value_;
		Node * left_;
		Node * right_;
		Node(T value) : value_(value), left_(nullptr), right_(nullptr) {};
		Node*  copy(){
			Node* nNode = new Node(value_);
			if (left_){
				nNode->left_ = left_->copy();
			}
			if (right_){
				nNode->right_ = right_->copy();
			}
			return nNode;
		}

		
		~Node()
		{
			if (this->left_)
				delete this->left_;
			if (this->right_)
				delete this->right_;
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

	BinarySearchTree(BinarySearchTree&& rtree){
		size_ = rtree.size_;
		root_ = rtree.root_;
		rtree.root_ = nullptr;
		rtree.size_ = 0;
	}
	BinarySearchTree(const BinarySearchTree& tree){	
		size_ = tree.size_;
		root_ = tree.root_->copy();
	}

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

	BinarySearchTree<T>& operator = (const BinarySearchTree<T> & tree){//копирования
		
		 if (this == &tree)
        		return *this;

      			root_ = tree.root_->copy();
   			size_ = tree.size_;
    			return *this;	 
	}
	BinarySearchTree<T>& operator = (BinarySearchTree<T> && tree){//оператор присваивания для rvalue  move перемещения
		if (this != &tree){
			size_ =  tree.size_ ;
			root_ =  tree.root_ ;
			tree.size_ = 0;
			tree.root_ = nullptr;
		}
		 
		return *this;
	}
	bool operator == (const BinarySearchTree<T> & tree){
		if (this == &tree) return true;

		return srav(root_,tree.root_);
	}

	bool srav(Node* Fnode, Node* Snode){
	
		if (Fnode == nullptr && Snode == nullptr) return true;
		else 
			if (Fnode != nullptr && Snode != nullptr)
		{
			return( Fnode->value_ == Snode->value_ && srav(Fnode->left_, Snode->left_) && srav(Fnode->right_, Snode->right_));
		}
		else return false;
		
		
	}

	void direct_walk(std::ostream & str, Node *now_node) const
	{
		if (!now_node) { return; }
		str << now_node->value_ << " ";
		direct_walk(str, now_node->left_);
		direct_walk(str, now_node->right_);
	}
	void symmetric_walk(std::ostream & out, Node * node) const
	{
		if (!node)
			return;

		symmetric_walk(out,node->left_);
		out << node->value_ << "  ";
		symmetric_walk(out,node->right_);
	}


};
