/* This is the test harness for the binary search tree data structure
   that I built */

/* TO DO: 1) Modify to make it work with:
     #ifdef ANIL_BST_USE_RECURSIVE_VERSIONS
     #elif ANIL_BST_USE_ITERATIVE VERSIONS */

#include "anil_binary_search_tree.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>

// The following enumeration contains the names of the tests conducted in
// this test harness and associates each one with a number to makes the code
// more readable/understandable as this method eliminates the need to use
// magic numbers.
enum bst_tests {
  BST_CONSTRUCTOR,
  BST_INSERT_RECURSIVELY,
  BST_INSERT_ITERATIVELY,
  BST_PRINT_INORDER,
  BST_PRINT_NODE_INFO,
  BST_SEARCH_RECURSIVELY,
  BST_SEARCH_ITERATIVELY,
  BST_FIND_MIN_RECURSIVELY,
  BST_FIND_MIN_ITERATIVELY,
  BST_FIND_MAX_RECURSIVELY,
  BST_FIND_MAX_ITERATIVELY,
  BST_DATA,
  BST_SUCCESSOR,
  BST_PREDECESSOR,
  BST_REMOVE,
  BST_DESTRUCTOR,
  NO_OF_TESTS,
};

// The following array of strings associate enumeration values of tests
// declared in the enumeration 'bst_tests' with their string equivalents.
// For example, 'std::cout << bst_test_names[BST_CONSTRUCTOR];' will
// print 'BST_CONSTRUCTOR' as expected. This makes reporting and logging 
// easier.
static const char* bst_test_names[] = {
	"BST_CONSTRUCTOR",
  "BST_INSERT_RECURSIVELY",
  "BST_INSERT_ITERATIVELY",
  "BST_PRINT_INORDER",
  "BST_PRINT_NODE_INFO",
  "BST_SEARCH_RECURSIVELY",
  "BST_SEARCH_ITERATIVELY",
  "BST_FIND_MIN_RECURSIVELY",
  "BST_FIND_MIN_ITERATIVELY",
  "BST_FIND_MAX_RECURSIVELY",
  "BST_FIND_MAX_ITERATIVELY",
  "BST_DATA",
  "BST_SUCCESSOR",
  "BST_PREDECESSOR",
  "BST_REMOVE",
  "BST_DESTRUCTOR",
  "NO_OF_TESTS",
};

bool run_bst_tests(std::ostream& os, int bst_test, bool verbose) {
  switch(bst_test) {

  // // TEST TWO (Search Recursively and remove):
  // my_file << "\nTEST TWO (Search Recursively):\n" << "Number to be searched: 7" << std::endl;
  // anil::bst_node* found_node = my_bst.search_recursively(7);
  // my_bst.print_node_info(my_file, found_node);
  
  // // TEST THREE (Remove):
  // my_file << "\nTEST THREE (Remove):\n" << "Number to be removed: 7" << std::endl;
  // my_bst.remove(found_node);
  // my_file << "Current binary search tree in preorder:" << std::endl;
  // my_bst.print_inorder(my_file);
  // my_file << std::endl;

  //bst_node* predecessor(bst_node* node);
  // Model you scripts for testing using Isaak's scripts at https://github.com/legendddhgf/cmps101-pt.f17.grading
    case BST_CONSTRUCTOR:
      {
        // Test to construct a binary search tree.
        if (verbose) {
          os << "\nBST_CONSTRUCTOR:" << std::endl <<
            "Starting the construction operation(BST_INSERT_RECURSIVELY):" <<
            std::endl;
        }
        anil::bst my_bst;
        if (&my_bst == nullptr) {
          return false;
        } else {
          return true;
        }
        break;
      }
    case BST_INSERT_RECURSIVELY:
      {
        // Test to insert recursively:
        anil::bst my_bst;

        // list_one represents the same elements from page 290 of CLRS 3rd
        // edition.
        std::vector<int> list_one {15, 6, 18, 3, 7, 17, 20, 2, 4, 13, 9};
        std::vector<int> correct_bst_order {2, 3, 4, 6, 7, 9, 13, 15, 17, 18,
                                            20};
        if (verbose) {
          os << "\nBST_INSERT_RECURSIVELY:" << std::endl <<
            "Starting the insert operation(BST_INSERT_RECURSIVELY):" <<
            std::endl;
        }
        
        for (auto x : list_one) {
          my_bst.insert_recursively(x);
          if (verbose) {
            os << x << ' ';
          }
        }

        if (verbose) {
          os << std::endl;
          os << "Current binary search tree inorder:" << std::endl;
          my_bst.print_inorder(os);
          os << "\n" << std::endl;
        }

        for (auto x : correct_bst_order) {
          anil::bst_node* node = my_bst.find_min_recursively();
          if (x != my_bst.data(node)) { return false; }
          my_bst.remove(node);
        }
        return true;
        break;
      }
    case BST_INSERT_ITERATIVELY:
      {
        // Test to insert iteratively:
        anil::bst my_bst;

        // list_one represents the same elements from page 290 of CLRS 3rd
        // edition.
        std::vector<int> list_one {15, 6, 18, 3, 7, 17, 20, 2, 4, 13, 9};
        std::vector<int> correct_bst_order {2, 3, 4, 6, 7, 9, 13, 15, 17, 18,
                                            20};
        if (verbose) {
          os << "\nBST_INSERT_ITERATIVELY:" << std::endl <<
            "Starting the insert operation(BST_INSERT_ITERATIVELY):" <<
            std::endl;
        }

        for (auto x : list_one) {
          anil::bst_node* node = my_bst.insert_iteratively(x);
          if (verbose) {
            os << x << ' ';
          }
        }

        if (verbose) {
          os << std::endl;
          os << "Current binary search tree inorder:" << std::endl;
          my_bst.print_inorder(os);
          os << "\n" << std::endl;
        }

        for (auto x : correct_bst_order) {
          anil::bst_node* node = my_bst.find_min_iteratively();
          if (x != my_bst.data(node)) { return false; }
          my_bst.remove(node);
        }
        return true;
        break;
      }
    case BST_PRINT_INORDER:
      {
        return false;
        break;
      }
    case BST_PRINT_NODE_INFO:
      {
        return false;
        break;
      }
    case BST_SEARCH_RECURSIVELY:
      {
        return false;
        break;
      }
    case BST_SEARCH_ITERATIVELY:
      {
        return false;
        break;
      }
    case BST_FIND_MIN_RECURSIVELY:
      {
        return false;
        break;
      }
    case BST_FIND_MIN_ITERATIVELY:
      {
        return false;
        break;
      }
    case BST_FIND_MAX_RECURSIVELY:
      {
        return false;
        break;
      }
    case BST_FIND_MAX_ITERATIVELY:
      {
        return false;
        break;
      }
    case BST_DATA:
      {
        return false;
        break;
      }
    case BST_SUCCESSOR:
      {
        return false;
        break;
      }
    case BST_PREDECESSOR:
      {
        return false;
        break;
      }
    case BST_REMOVE:
      {
        return false;
        break;
      }
    case BST_DESTRUCTOR:
      {
        return false;
        break;
      }
    case NO_OF_TESTS:
      {
        return false;
        break;
      }
  }
}

int main (int argc, char **argv) {
  bool verbose = false;

  if (argc > 2 || (argc == 2 and strcmp(argv[1], "-v") != 0)) {
    std::cout << "Usage: ./bisetr [-v]"  << std::endl;
    return 1;
  } else if (argc == 2 and strcmp(argv[1], "-v") == 0) {
    verbose = true;
  }

  const int number_of_tests = 3;
  std::ofstream log_file ("bst_test_user.txt", std::ios::trunc);
  if (!log_file.is_open()) {
    std::cout << "There was a problem opening 'bst_test_user.txt'" <<
      std::endl;
  }

  int no_of_tests_passed {0};

  for (int i = BST_CONSTRUCTOR; i < NO_OF_TESTS; ++i) {
    bool test_result = run_bst_tests(log_file, i, verbose);
    log_file << "Test " << bst_test_names[i] << ": " <<
      (test_result == true ? "PASSED" : "FAILED") << std::endl;
    if (test_result) { ++no_of_tests_passed; }
  }

  log_file << no_of_tests_passed << "/" << NO_OF_TESTS <<
    " tests were passed." << std::endl;

  log_file.close();

  return 0;
}