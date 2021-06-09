/* This is the test harness for the binary search tree data structure
   that I built */

/* TO DO: 1) Modify to make it work with:
          #ifdef ANIL_BST_USE_RECURSIVE_VERSIONS
          #elif ANIL_BST_USE_ITERATIVE VERSIONS
          2) Learn how to test the deconstructor!
            2-i) Use a shell program to both run the program and valgrind
            2-ii) What about unit testing a deconstructor? 
*/

#include "anil_binary_search_tree.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
#include <string>
#include <sstream>

// The following enumeration contains the names of the tests conducted in
// this test harness and associates each one with a number to make the code
// more readable / understandable as this method eliminates the need to use
// magic numbers.
enum bst_tests {
  BST_CONSTRUCTOR,
  BST_INSERT,
  BST_SEARCH,
  BST_FIND_MIN,
  BST_FIND_MAX,
  BST_IS_EMPTY,
  BST_PRINT_INORDER,
  BST_GET_NODE_DATA,
  BST_SUCCESSOR,
  BST_PREDECESSOR,
  BST_REMOVE,
  // BST_DECONSTRUCTOR,
  NO_OF_TESTS,
};

// The following array of strings associate enumeration values of tests
// declared in the enumeration 'bst_tests' with their string
// equivalents. For example, 
// 'std::cout<<bst_test_names[BST_CONSTRUCTOR];'
// will print 'BST_CONSTRUCTOR' as expected. This makes
// reporting and logging easier.
static const char* bst_test_names[] = {
  "BST_CONSTRUCTOR",
  "BST_INSERT",
  "BST_SEARCH",
  "BST_FIND_MIN",
  "BST_FIND_MAX",
  "BST_IS_EMPTY",
  "BST_PRINT_INORDER",
  "BST_GET_NODE_DATA",
  "BST_SUCCESSOR",
  "BST_PREDECESSOR",
  "BST_REMOVE",
  // "BST_DECONSTRUCTOR",
  "NO_OF_TESTS",
};

bool run_tests(std::ostream& os, int bst_test, bool verbose) {
  switch(bst_test) {
    case BST_CONSTRUCTOR:
      {
        // Test to construct a binary search tree.
        if (verbose) {
          os << "\nBST_CONSTRUCTOR:" << std::endl <<
            "Starting the construction operation:" <<
            std::endl;
        }
        anil::bst my_bst;
        if (&my_bst == nullptr) {
          if (verbose) {
            os << "Construction unsuccessful!" << std::endl;
          }
          return false;
        } else {
          if (verbose) {
            os << "Construction successful!" << std::endl;
          }
          return true;
        }

        break;
      }
    case BST_INSERT:
      {
        // Test to insert elements:
        anil::bst my_bst;

        // This binary search tree is taken from page 290 of 3rd edition of CLRS.
        std::vector<int> numbers {15, 6, 18, 3, 7, 17, 20, 2, 4, 13, 9};
        std::vector<int> ordered_numbers {2, 3, 4, 6, 7, 9, 13, 15, 17, 18, 20};

        if (verbose) {
          os << "\nBST_INSERT:" << std::endl <<
            "Starting the insert operation:" << std::endl;
        }
        
        for (auto x : numbers) {
          my_bst.insert(x);
          if (verbose) {
            os << x << ' ';
          }
        }
        
        if (verbose) { os << std::endl; }

        for (int i = ordered_numbers.size() - 1; i >= 0; --i) {
          anil::bst_node* node_to_be_removed = my_bst.find_max();
          if (my_bst.get_node_data(node_to_be_removed) != ordered_numbers[i]) { return false; }
          my_bst.remove(node_to_be_removed);
        }

        return true;
        break;
      }
    case BST_SEARCH:
      {
        // Test to search elements:
        anil::bst my_bst;

        // This binary search tree is taken from page 290 of 3rd edition of CLRS.
        std::vector<int> numbers {15, 6, 18, 3, 7, 17, 20, 2, 4, 13, 9};
        int sub_test_success_count (0);

        if (verbose) {
          os << "\nBST_SEARCH:" << std::endl <<
            "Starting the search operation:" << std::endl;
        }
        
        for (auto x : numbers) {
          my_bst.insert(x);
          if (verbose) {
            os << x << ' ';
          }
        }
        
        if (verbose) { os << std::endl; }

        // Sub-test 1
        for (int i = numbers.size() - 1; i >= 0; --i) {
          anil::bst_node* found_node = my_bst.search(numbers[i]);
          if (my_bst.get_node_data(found_node) != numbers[i]) { return false; }
        }

        ++sub_test_success_count;

        // Sub-test 2
        anil::bst_node* found_node = my_bst.search(1);
        if (found_node != nullptr) { return false; }

        ++sub_test_success_count;

        if (sub_test_success_count == 2) {
          return true;
        } else {
          return false;
        }

        break;

      }
    case BST_FIND_MIN:
      {
        // Test to find the minimum elements:
        anil::bst my_bst;

        // This binary search tree is taken from page 290 of 3rd edition of CLRS.
        std::vector<int> numbers {15, 6, 18, 3, 7, 17, 20, 2, 4, 13, 9};
        std::vector<int> ordered_numbers {2, 3, 4, 6, 7, 9, 13, 15, 17, 18, 20};

        if (verbose) {
          os << "\nBST_FIND_MIN:" << std::endl <<
            "Starting the find minimum number operation:" << std::endl;
        }
        
        for (auto x : numbers) {
          my_bst.insert(x);
          if (verbose) {
            os << x << ' ';
          }
        }
        
        if (verbose) { os << std::endl; }

        for (int i = 0; i < ordered_numbers.size(); ++i) {
          anil::bst_node* node_to_be_removed = my_bst.find_min();
          if (my_bst.get_node_data(node_to_be_removed) != ordered_numbers[i]) { return false; }
          my_bst.remove(node_to_be_removed);
        }

        return true;
        break;
      }
    case BST_FIND_MAX:
      {
        // Test to find the maximum elements:
        anil::bst my_bst;

        // This binary search tree is taken from page 290 of 3rd edition of CLRS.
        std::vector<int> numbers {15, 6, 18, 3, 7, 17, 20, 2, 4, 13, 9};
        std::vector<int> ordered_numbers {2, 3, 4, 6, 7, 9, 13, 15, 17, 18, 20};

        if (verbose) {
          os << "\nBST_FIND_MAX:" << std::endl <<
            "Starting the find maximum number operation:" << std::endl;
        }
        
        for (auto x : numbers) {
          my_bst.insert(x);
          if (verbose) {
            os << x << ' ';
          }
        }
        
        if (verbose) { os << std::endl; }

        for (int i = ordered_numbers.size() - 1; i >= 0; --i) {
          anil::bst_node* node_to_be_removed = my_bst.find_max();
          if (my_bst.get_node_data(node_to_be_removed) != ordered_numbers[i]) { return false; }
          my_bst.remove(node_to_be_removed);
        }

        return true;
        break;
      }
    case BST_IS_EMPTY:
      {
        // Test to test is_empty function:
        anil::bst my_bst;

        // This binary search tree is taken from page 290 of 3rd edition of CLRS.
        std::vector<int> numbers {15, 6, 18, 3, 7, 17, 20, 2, 4, 13, 9};
        int sub_test_success_count (0);

        if (verbose) {
          os << "\nBST_IS_EMPTY:" << std::endl <<
            "Starting the insert operation:" << std::endl;
        }
        
        for (auto x : numbers) {
          my_bst.insert(x);
          if (verbose) {
            os << x << ' ';
          }
        }
        
        if (verbose) { os << std::endl; }

        // Sub-test 1
        if (my_bst.is_empty() == true) { return false; }
        ++sub_test_success_count;

        // Sub-test 2
        anil::bst my_empty_bst;
        if (my_empty_bst.is_empty() == false) { return false; }
        ++sub_test_success_count;

        if (sub_test_success_count == 2) {
          return true;
        } else {
          return false;
        }

        break;
      }
    case BST_PRINT_INORDER:
      {
        // Test to print the binary search tree inorder:
        anil::bst my_bst;

        // This binary search tree is taken from page 290 of 3rd edition of CLRS.
        std::vector<int> numbers {15, 6, 18, 3, 7, 17, 20, 2, 4, 13, 9};
        std::string correct_inorder_print ("2, 3, 4, 6, 7, 9, 13, 15, 17, 18, 20, ");
        char inorder_print_output_temp[256];
        std::stringstream inorder_print_stream;

        if (verbose) {
          os << "\nBST_PRINT_INORDER:" << std::endl <<
            "Starting the insert operation:" << std::endl;
        }
        
        for (auto x : numbers) {
          my_bst.insert(x);
          if (verbose) {
            os << x << ' ';
          }
        }
        
        if (verbose) { os << std::endl; }

        my_bst.print_inorder(inorder_print_stream);
        inorder_print_stream.getline(inorder_print_output_temp, 256);
        std::string inorder_print_output(inorder_print_output_temp);
        if (correct_inorder_print.compare(inorder_print_output) != 0) { return false; }

        return true;
        break;
      }
    case BST_GET_NODE_DATA:
      {
        // Test to get node data elements:
        anil::bst my_bst;

        // This binary search tree is taken from page 290 of 3rd edition of CLRS.
        std::vector<int> numbers {15, 6, 18, 3, 7, 17, 20, 2, 4, 13, 9};

        if (verbose) {
          os << "\nBST_GET_NODE_DATA:" << std::endl <<
            "Starting the insert operation:" << std::endl;
        }
        
        for (auto x : numbers) {
          my_bst.insert(x);
          if (verbose) {
            os << x << ' ';
          }
        }
        
        if (verbose) { os << std::endl; }

        anil::bst_node* found_node = my_bst.search(13);
        if (my_bst.get_node_data(found_node) != 13) { return false; }

        return true;
        break;
      }
    case BST_SUCCESSOR:
      {
        // Test to find the successor of an element:
        anil::bst my_bst;

        // This binary search tree is taken from page 290 of 3rd edition of CLRS.
        std::vector<int> numbers {15, 6, 18, 3, 7, 17, 20, 2, 4, 13, 9};
        int sub_test_success_count (0);

        if (verbose) {
          os << "\nBST_SUCCESSOR:" << std::endl <<
            "Starting the insert operation:" << std::endl;
        }
        
        for (auto x : numbers) {
          my_bst.insert(x);
          if (verbose) {
            os << x << ' ';
          }
        }
        
        if (verbose) { os << std::endl; }

        // Sub-test 1
        anil::bst_node* node = my_bst.search(13);
        anil::bst_node* successor_node = my_bst.successor(node);
        if (my_bst.get_node_data(successor_node) != 15) { return false; }
        ++sub_test_success_count;

        // Sub-test 2
        node = my_bst.search(20);
        successor_node = my_bst.successor(node);
        if (successor_node != nullptr) { return false; }
        ++sub_test_success_count;

        if (sub_test_success_count == 2) {
          return true;
        } else {
          return false;
        }

        break;
      }
    case BST_PREDECESSOR:
      {
        // Test to find the predecessor of an element:
        anil::bst my_bst;

        // This binary search tree is taken from page 290 of 3rd edition of CLRS.
        std::vector<int> numbers {15, 6, 18, 3, 7, 17, 20, 2, 4, 13, 9};
        int sub_test_success_count (0);

        if (verbose) {
          os << "\nBST_PREDECESSOR:" << std::endl <<
            "Starting the insert operation:" << std::endl;
        }
        
        for (auto x : numbers) {
          my_bst.insert(x);
          if (verbose) {
            os << x << ' ';
          }
        }
        
        if (verbose) { os << std::endl; }

        // Sub-test 1
        anil::bst_node* node = my_bst.search(15);
        anil::bst_node* predecessor_node = my_bst.predecessor(node);
        if (my_bst.get_node_data(predecessor_node) != 13) { return false; }
        ++sub_test_success_count;

        // Sub-test 2
        node = my_bst.search(2);
        predecessor_node = my_bst.predecessor(node);
        if (predecessor_node != nullptr) { return false; }
        ++sub_test_success_count;

        if (sub_test_success_count == 2) {
          return true;
        } else {
          return false;
        }

        break;
      }
    case BST_REMOVE:
      {
        // Test to remove an element:
        anil::bst my_bst;

        // This binary search tree is taken from page 290 of 3rd edition of CLRS.
        std::vector<int> numbers {15, 6, 18, 3, 7, 17, 20, 2, 4, 13, 9};
        int sub_test_success_count (0);

        if (verbose) {
          os << "\nBST_REMOVE:" << std::endl <<
            "Starting the insert operation:" << std::endl;
        }
        
        for (auto x : numbers) {
          my_bst.insert(x);
          if (verbose) {
            os << x << ' ';
          }
        }
        
        if (verbose) { os << std::endl; }

        // Sub-test 1
        anil::bst_node* node_to_be_removed = my_bst.search(15);
        my_bst.remove(node_to_be_removed);
        if (my_bst.search(15) != nullptr) { return false; }
        ++sub_test_success_count;

        // Sub-test 2
        anil::bst_node* node = my_bst.search(13);
        anil::bst_node* successor_node = my_bst.successor(node);
        if (my_bst.get_node_data(successor_node) != 17) { return false; }
        ++sub_test_success_count;

        if (sub_test_success_count == 2) {
          return true;
        } else {
          return false;
        }

        break;
      }
    // case BST_DECONSTRUCTOR:
    //   {
    //     return false;
    //     break;
    //   }
  }
}

int main (int argc, char **argv) {
  bool verbose = false;

  if (argc > 2 || (argc == 2 and strcmp(argv[1], "-v") != 0)) {
    std::cout << "Usage: ./binary_search_tree [-v]"  << std::endl;
    return 1;
  } else if (argc == 2 and strcmp(argv[1], "-v") == 0) {
    verbose = true;
  }

  std::ofstream log_file ("binary_search_tree_log.txt", std::ios::trunc);
  if (!log_file.is_open()) {
    std::cout << "There was a problem opening 'binary_search_tree_log.txt'" <<
      std::endl;
  }

  int no_of_tests_passed {0};

  for (int i = BST_CONSTRUCTOR; i < NO_OF_TESTS; ++i) {
    bool test_result = run_tests(log_file, i, verbose);
    log_file << "Test " << bst_test_names[i] << ": " <<
      (test_result == true ? "PASSED" : "FAILED") << std::endl;
    if (test_result) { ++no_of_tests_passed; }
  }

  log_file << no_of_tests_passed << "/" << NO_OF_TESTS <<
    " tests were passed." << std::endl;

  log_file.close();

  return 0;
}
