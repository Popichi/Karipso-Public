/* This is the test harness for the binary search tree data structure
   that I built */

#include "anil_binary_search_tree.h"
#include <iostream>
#include <vector>

int main() {

    // Binary search tree from page 290 of 3rd edition of CLRS
    std::vector<int> list_one {15, 6, 18, 3, 7, 17, 20, 2, 4, 13, 9};
    anil::bst my_bst;

    std::cout << "Starting insert operation:" << std::endl;
    for (auto x : list_one) {
        my_bst.insert_recursively(x);
        std::cout << x << ' ';
    }
    std::cout << std::endl;

    std::cout << "Current binary search tree in preorder:" << std::endl;
    my_bst.print_inorder();
    std::cout << std::endl;

    my_bst.remove(my_bst.search_recursively(7));
    //anil::bst_node* node = my_bst.search_recursively(7);
    //std::cout << "Removed node: " << node->data << std::endl;

    std::cout << "Current binary search tree in preorder:" << std::endl;
    my_bst.print_inorder();
    std::cout << std::endl;

    std::cout << "Program works!" << std::endl;
}