#ifndef SRC_TREE_H_
#define SRC_TREE_H_

template<typename T>
class Node {
    public:
        Node<T>(T& value) : val_(value), left_(NULL), right_(NULL) {}

    private:
        T val_;
        Node<T>* left_;
        Node<T>* right_;
};

template<typename Type>
class BST {
    public:
        int Insert(const Type& v);

        int Delete(const Type& v);

        ~BST() { std::cout << "~BST" << std::endl; }
};

#endif // SRC_TREE_H_