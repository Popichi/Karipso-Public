/* This is the test harness for the binary search tree data structure
   that I built */

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

  // TEST ONE:
  my_file << "Starting insert operation:" << std::endl;
  for (auto x : list_one) {
    my_bst.insert_recursively(x);
    my_file << x << ' ';
  }
  my_file << std::endl;

  my_file << "Current binary search tree in preorder:" << std::endl;
  my_bst.print_inorder(my_file);
  my_file << std::endl;


  my_bst.remove(my_bst.search_recursively(7));

  my_file << "Current binary search tree in preorder:" << std::endl;
  my_bst.print_inorder(my_file);
  my_file << std::endl;

  my_file << "Program works!" << std::endl;

  my_file.close();
}