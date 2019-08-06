/* This is the test harness for the binary search tree data structure
   that I built */

#include "anil_binary_search_tree.h"
#include <iostream>

int main() {
    anil::linked_list my_linked_list;

    std::cout << "Starting insert operation:" << std::endl;
    for (int i = 1; i < 11; ++i) {
        my_linked_list.insert(i);
        std::cout << i << ' ';
    }
    std::cout << std::endl;

    std::cout << "Starting remove operation:" << std::endl;
    for (int i = 1; i < 11; ++i) {
        anil::node* temp = my_linked_list.search(i);
        std::cout << temp->data << ' ';
        my_linked_list.remove(temp);
    }
    std::cout << std::endl;

    std::cout << "Program works!" << std::endl;
}