#include <iostream>
#include <fstream>
#include <limits>
#include <memory>



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
	class  Node {
	public:
		T value_;


		std::shared_ptr<Node> left_;
		std::shared_ptr<Node> right_;
		std::shared_ptr<Node> parent_;
		Node() : left_(nullptr), right_(nullptr), parent_(nullptr) {}

		Node(T value) : value_(value), left_(nullptr), right_(nullptr), parent_(nullptr) {};

		Node(T value, std::shared_ptr<Node>parenttt) : value_(value), left_(nullptr), right_(nullptr), parent_(parenttt) {};

		std::shared_ptr<Node> copy() {


			std::shared_ptr<Node> nNode = std::make_shared<Node>(value_);
			//auto nNode = std::make_shared<Node>(value_);
			//Node* nNode = new Node(value_);
			//std::shared_ptr<int> x_ptr(new int(42));
			if (left_) {
				nNode->left_ = left_->copy();
			}
			if (right_) {
				nNode->right_ = right_->copy();
			}
			return nNode;
		}


		~Node()
		{
		 
			left_ = nullptr;
			right_ = nullptr;
			parent_ = nullptr;
		}

	};
	std::shared_ptr<Node> root_;
	/*Node* root_;*/
	size_t size_;

	BinarySearchTree() : root_(nullptr), size_(0) {};

	BinarySearchTree(const std::initializer_list<T> & list)
	{
		size_ = 0;
		root_ = nullptr;
		for (auto it : list)
		{
			insert(it);
		};

	};

	BinarySearchTree(BinarySearchTree&& rtree) {
		size_ = rtree.size_;
		root_ = rtree.root_;
		rtree.root_ = nullptr;
		rtree.size_ = 0;
	}
	BinarySearchTree(const BinarySearchTree& tree) {
		size_ = tree.size_;
		root_ = tree.root_->copy();
	}

	std::shared_ptr<Node> GetRoot() const
	{
		return root_;
	}


	~BinarySearchTree()
	{
		//delete root_;
	};


	size_t size()
	{
		return size_;
	};


	bool insert(const T & value)
	{

		/*Node* this_node = root_;
		Node* my_node = nullptr;*/

		std::shared_ptr<Node> this_node(root_);
		std::shared_ptr<Node> my_node(nullptr);


		if (!root_)
		{

			root_ = std::make_shared<Node>(value);
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
			my_node->left_ = std::make_shared<Node>(value, my_node);
		}
		else
		{
			my_node->right_ = std::make_shared<Node>(value, my_node);
		};
		size_++;
		return true;
	};

	const std::shared_ptr<T> find(const T & value) const
	{
		//Node *this_node = root_;
		auto this_node = root_;
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
				return std::make_shared<T>(this_node->value_);
			}
		}
		return nullptr;
	};

	BinarySearchTree<T>& operator = (const BinarySearchTree<T> & tree) {//присваивания
		root_ = nullptr;
		this->root_ = tree.root_->copy();
		this->size_ = tree.size_;
		return *this;// ?
	}
	BinarySearchTree<T>& operator = (BinarySearchTree<T> && tree) {//оператор присваивания для rvalue  move перемещения
		if (this != &tree) {
			size_ = std::move(tree.size_);
			root_ = std::move(tree.root_);
			tree.size_ = 0;
			tree.root_ = nullptr;
		}

		return *this;
	}
	bool operator == (const BinarySearchTree<T> & tree) {
	
		if (this == &tree) return true;

		return srav(root_, tree.root_);
	}

	bool srav(std::shared_ptr<Node> Fnode, std::shared_ptr<Node> Snode) {
		if (Fnode!=nullptr && Snode !=nullptr) {
			return (Fnode->value_ == Snode->value_ && srav(Fnode->left_, Snode->left_) && srav(Fnode->right_, Snode->right_));
		}
		if ((Fnode != nullptr && Snode == nullptr) || (Fnode == nullptr && Snode != nullptr)) {
			return false;
		}
		return true;
	}



	void remove(std::shared_ptr<Node> node, int value)
	{

		if (node == nullptr)
			return;

		if (value < node->value_)
			return remove(node->left_, value);
		else if (value > node->value_)
			return remove(node->right_, value);
		else {

			if (node == root_) {
				std::shared_ptr<Node> newnode=Leftmost(node->right_);
				
				if (Leftmost(node->right_) == node->right_) {
					newnode->right_ = node->right_->right_;
				}
				else {//b
					newnode->right_ = node->right_;
					Leftmost(node->right_)->parent_->left_ = nullptr;
				}
				root_ = newnode;
				newnode->parent_ = nullptr;
				node = nullptr;
				return;
			}

			if (node->left_ == nullptr && node->right_ == nullptr) {
				if (node->parent_->left_ == node)
					node->parent_->left_ = nullptr;
				else
					node->parent_->right_ = nullptr;
				node = nullptr;//2
			}
			else {
				std::shared_ptr<Node> newnode;
				if (node->left_ && node->right_)
				{
					newnode = Leftmost(node->right_);
					Leftmost(node->right_)->parent_->left_ = Leftmost(node->right_)->right_;
					newnode->parent_ = node->parent_;
					
					if (newnode == node->right_) {
						newnode->right_ = node->right_->right_;
					}
					else {//b
						newnode->right_ = node->right_;
						 
					}
					newnode->left_ = node->left_;


					if (node != root_) {

						if (node->parent_->right_ = node) {
							newnode->parent_->right_ = newnode;
						}
						else {
							newnode->parent_->left_ = newnode;
						}
					}
					else {
						root_ = newnode;
					}
					

				}
				else
				{	//node->right_ || node->left_   

					if (node->right_) {
						node->parent_->left_ = node->right_;
					}
					if (node->left_) {
						node->parent_->right_ = node->left_;
					}

				}
				node = nullptr;
				
			}
		}
	}
	std::shared_ptr<Node> Leftmost(std::shared_ptr<Node> node) {
		if (node == nullptr)
			return nullptr;
		if (node->left_ != nullptr) {
			return Leftmost(node->left_);
		}
		return node;
	}
 




	void direct_walk(std::ostream & str, std::shared_ptr<Node> node) const
	{
		if (!node) { return; }
		str << node->value_ << " ";
		direct_walk(str, node->left_);
		direct_walk(str, node->right_);
	}
	void symmetric_walk(std::ostream & out, std::shared_ptr<Node> node) const
	{
		if (!node)
			return;

		symmetric_walk(out, node->left_);
		out << node->value_ << "  ";
		symmetric_walk(out, node->right_);
	}


};
