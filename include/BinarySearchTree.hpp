#ifndef MAIN_BINARYSEARCHTREE_HPP
#define MAIN_BINARYSEARCHTREE_HPP


#include <iostream>
#include <fstream>
#include <memory>
template <typename T>
class BinarySearchTree;

template <typename T> auto operator >> (std::istream& input, BinarySearchTree<T>& tree) -> std::istream;
template <typename T> auto operator << (std::ofstream& fileout, const BinarySearchTree<T>& tree) -> std::ofstream&;
template <typename T> auto operator >> (std::ifstream& in, BinarySearchTree<T>& tree) -> std::ifstream&;
template <typename T> auto operator << (std::ostream& out, const BinarySearchTree<T>& tree) -> std::ostream&;


template <typename T>
class BinarySearchTree {
public:
    class Node{
    public:
        std::shared_ptr<Node> left_;
        std::shared_ptr<Node> right_;
        std::shared_ptr<Node> parent_;
        T value_;
        Node() :  left_(nullptr), right_(nullptr), parent_(nullptr){}
        Node(T value) : value_(value), left_(nullptr), right_(nullptr), parent_(nullptr){}
        Node(T value,std::shared_ptr<Node> Parent) : value_(value), left_(nullptr), right_(nullptr), parent_(Parent){}
        ~Node(){
           left_= nullptr;
           right_= nullptr;
        }

        std::shared_ptr<Node> copy(){
            std::shared_ptr<Node> nNode=std::make_shared<Node>(value_);
            if(left_)
                nNode->left_=left_->copy();
            if(right_)
                nNode->right_=right_->copy();
            return nNode;
        }
    };


    size_t size_;
    std::shared_ptr<Node> root_;

    BinarySearchTree() : root_(nullptr), size_(0){};
    BinarySearchTree(const std::initializer_list<T>& list);
    BinarySearchTree(BinarySearchTree&& rvalue) {
        size_ = rvalue.size_;
        root_ = rvalue.root_;

        rvalue.root_ = nullptr;
    }

    BinarySearchTree(const BinarySearchTree& tree){
        size_=tree.size_;

        root_=tree.root_->copy();
    }

    std::shared_ptr<Node> ReturnRoot() const noexcept {return root_;}
    ~BinarySearchTree();

    auto size() const noexcept -> size_t;
    auto insert(const T& value) noexcept -> bool;
    auto find(const T& value) const noexcept -> const std::shared_ptr<T>;
    auto remove(const T& value) noexcept ->bool;

    void direct(std::shared_ptr<Node> root, std::ostream& out) const ;
    void symmetric(std::shared_ptr<Node> root, std::ostream& out) const;
    auto equal(std::shared_ptr<Node> firstTree, std::shared_ptr<Node> secondTree) const -> bool;

    auto operator = (const BinarySearchTree<T>& tree) -> BinarySearchTree<T>&; //копирование
    auto operator = (BinarySearchTree<T>&& tree) -> BinarySearchTree<T>&;      //перемещение
    auto operator == (const BinarySearchTree& tree) -> bool;

    friend auto operator >> <> (std::istream& input, BinarySearchTree<T>& tree) -> std::istream;
    friend auto operator << <> (std::ofstream& fileout, const BinarySearchTree<T>& tree) -> std::ofstream&;
    friend auto operator >> <> (std::ifstream& in, BinarySearchTree<T>& tree) -> std::ifstream&;
    friend auto operator << <> (std::ostream& out, const BinarySearchTree<T>& tree) -> std::ostream&;

    void Remove(std::shared_ptr<Node> node, int value)
    {

        if (node == nullptr)
            return;

        if (value < node->value_)
            return Remove(node->left_, value);
        else if (value > node->value_)
            return Remove(node->right_, value);
        else  {
            if (node->left_ == nullptr && node->right_ == nullptr) {
                if (node->parent_->left_ == node)
                    node->parent_->left_ = nullptr;
                else
                    node->parent_->right_ = nullptr;
                node=nullptr;
            }
            else {
                std::shared_ptr<Node> newnode=nullptr;//
                if (node->left_ != nullptr) {
                    newnode = Rightmost(node->left_);
                }
                else
                    newnode = Leftmost(node->right_);

                if (node->parent_->left_ == node){

                    newnode->right_ = node->right_;
                    node->parent_->left_ = newnode;

                }
                else{
                    newnode->left_ = node->left_;
                    node->parent_->right_ = newnode;
                }

                node=nullptr;

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
    std::shared_ptr<Node> Rightmost(std::shared_ptr<Node> node) {
        if (node == nullptr)
            return nullptr;
        if (node->right_ != nullptr) {
            return Rightmost(node->right_);
        }
        return node;
    }

};

template<typename T>
BinarySearchTree<T>::BinarySearchTree(const std::initializer_list<T>& list): BinarySearchTree() {
    for (auto& el : list) { insert(el);}
}

template<typename T>
auto BinarySearchTree<T>::size() const noexcept -> size_t {
    return size_;
}

template<typename T>
auto BinarySearchTree<T>::insert(const T& value) noexcept -> bool{
//    std::shared_ptr<Node> node(root_);
//    std::shared_ptr<Node> my_node(nullptr);
    if (root_== nullptr) {
        root_ = std::make_shared<Node>(value);
        size_++;
        return true;
    }

    std::shared_ptr<Node> node=root_, parent=nullptr;
    while(node){
        parent=node;
        if (value < parent->value_)
            node = parent->left_;
        else if (value > parent->value_)
            node = parent->right_;
        else
            return false;
    }

    if (value < parent->value_)
        parent->left_ = std::make_shared<Node>(value,parent);
    else
        parent->right_ = std::make_shared<Node>(value,parent);
    size_ ++;
    return true;

}

template<typename T>
auto BinarySearchTree<T>::find(const T& value) const noexcept -> const std::shared_ptr<T>{
    auto node=root_;
    while(node){
        if(value< node->value_)
            node = node->left_;
        else if (value> node->value_)
            node = node->right_;
        else
            return std::make_shared<T>(node->value_);

    }
    return nullptr;
}

template<typename T>
void BinarySearchTree<T>::direct(const std::shared_ptr<Node> node, std::ostream& out) const{
    if(!node)
        return;
    out << node->value_<<" ";
    direct(node->left_, out);
    direct(node->right_, out);
}


template<typename T>
void BinarySearchTree<T>::symmetric(const std::shared_ptr<Node> node, std::ostream& out) const
{
    if (!node)
        return;

    symmetric(node->right_, out);
    out << node->value_ << "  ";
    symmetric(node->left_, out);
}

template<typename T>
std::ostream& operator << (std::ostream& out, const BinarySearchTree<T>& tree) {
    //tree.symmetric(tree.ReturnRoot(), out);
    tree.direct(tree.ReturnRoot(), out);
    return out;
}

template<typename T>
std::ofstream& operator << (std::ofstream& fileout, const BinarySearchTree<T>& tree) {
    tree.direct(tree.ReturnRoot(), fileout);
    return fileout;
}

template<typename T>
std::istream& operator >> (std::istream& input, BinarySearchTree<T>& tree) {

    T value;
    while(input >> value)
        tree.insert(value);
    return input;
}

template<typename T>
BinarySearchTree<T>::~BinarySearchTree() {
    if (root_){
        root_= nullptr;
        size_ = 0;
    }
}

template<typename T>
auto BinarySearchTree<T>::equal(const std::shared_ptr<Node> fNode, const std::shared_ptr<Node> sNode) const -> bool{
    if (fNode)
        return sNode && fNode->value_ == sNode->value_
               && equal(fNode->left_, sNode->left_) && equal(fNode->right_, sNode->right_);
    else
        return !sNode;
}

template<typename T>
auto BinarySearchTree<T>::operator=(const BinarySearchTree<T> & tree) -> BinarySearchTree<T>&{
    if (this == &tree)
        return *this;
    delete root_;
    this->root_=tree.root_->copy();
    this->size_=tree.size_;
    return *this;
}

template <typename T>
auto BinarySearchTree<T>::operator=(BinarySearchTree<T> && tree) -> BinarySearchTree<T>&{

    if (this == &tree)
        return *this;
    delete root_;
    this->size_= tree.size_;
    this->root_ = tree.root_;
    tree.size_ = 0;
    tree.root_= nullptr;

    return *this;
}

template<typename T>
auto BinarySearchTree<T>::operator == (const BinarySearchTree<T>& tree) -> bool{
    if (this == &tree)
        return true;

    return equal(root_, tree.root_);
}




#endif //MAIN_BINARYSEARCHTREE_HPP
