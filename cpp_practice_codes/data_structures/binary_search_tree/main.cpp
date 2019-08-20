/* This is the test harness for the binary search tree data structure
   that I built */

/* TO DO: 1) Modify to make it work with:
     #ifdef ANIL_BST_USE_RECURSIVE_VERSIONS
     #elif ANIL_BST_USE_ITERATIVE VERSIONS */

#include "anil_binary_search_tree.h"
#include <iostream>
#include <vector>
#include <fstream>

int main() {

  const int number_of_tests = 3;
  std::ofstream my_file ("bst_test_user.txt", std::ios::trunc);
  if (!my_file.is_open()) {
    std::cout << "There was a problem opening 'bst_test_user.txt'" <<
      std::endl;
  }

  // Binary search tree from page 290 of 3rd edition of CLRS
  std::vector<int> list_one {15, 6, 18, 3, 7, 17, 20, 2, 4, 13, 9};
  anil::bst my_bst;
 
  // TEST ONE (Insert Recursively):
  my_file << "TEST ONE (Insert Recursively):" << std::endl <<
    "Starting insert operation(Insert Recursively):" << std::endl;
  //my_file << "Starting insert operation(Insert Iteratively):" << std::endl;
  for (auto x : list_one) {
    my_bst.insert_recursively(x);
    my_file << x << ' ';
  }
  my_file << std::endl;

  my_file << "Current binary search tree in preorder:" << std::endl;
  my_bst.print_inorder(my_file);
  my_file << std::endl;

  // TEST TWO (Search Recursively and remove):
  my_file << "\nTEST TWO (Search Recursively):\n" << "Number to be searched: 7" << std::endl;
  anil::bst_node* found_node = my_bst.search_recursively(7);
  my_bst.print_node_info(my_file, found_node);
  
  // TEST THREE (Remove):
  my_file << "\nTEST THREE (Remove):\n" << "Number to be removed: 7" << std::endl;
  my_bst.remove(found_node);
  my_file << "Current binary search tree in preorder:" << std::endl;
  my_bst.print_inorder(my_file);
  my_file << std::endl;

  //bst_node* predecessor(bst_node* node);

  my_file.close();
}