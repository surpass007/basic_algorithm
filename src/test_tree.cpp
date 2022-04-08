#include <iostream>

#include "tree.h"

using namespace std;

int main() {
    
    BST<int> bst;
    int a = 20;
    int b = 15;
    bst.Insert(a);
    bst.Delete(b);
    return 0;
}