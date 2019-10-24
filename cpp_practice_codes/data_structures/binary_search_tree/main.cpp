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
  "NO_OF_TESTS",
};

bool run_bst_tests(std::ostream& os, int bst_test, bool verbose) {
  switch(bst_test) {
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
          my_bst.insert_iteratively(x);
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
    case BST_SEARCH_RECURSIVELY:
      {
        // Test to search recursively:
        anil::bst my_bst;

        // list_one represents the same elements from page 295 of CLRS 3rd
        // edition.
        std::vector<int> list_one {12, 5, 18, 2, 9, 15, 19, 13, 17};
        std::string correct_bst_order {2, 5, 9, 12, 13, 15, 17, 18, 19};

        if (verbose) {
          os << "\nBST_SEARCH_RECURSIVELY:" << std::endl <<
            "Starting the insert operation(BST_SEARCH_RECURSIVELY):" <<
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

        anil::bst_node* node = my_bst.search_recursively(2);
        if (my_bst.data(node) != 2) { return false; }
        
        node = my_bst.search_recursively(18);
        if (my_bst.data(node) != 18) { return false; }

        node = my_bst.search_recursively(17);
        if (my_bst.data(node) != 17) { return false; }

        return true;
        break;
      }
    case BST_SEARCH_ITERATIVELY:
      {
        // Test to search iteratively:
        anil::bst my_bst;

        // list_one represents the same elements from page 295 of CLRS 3rd
        // edition.
        std::vector<int> list_one {12, 5, 18, 2, 9, 15, 19, 13, 17};
        std::string correct_bst_order {2, 5, 9, 12, 13, 15, 17, 18, 19};

        if (verbose) {
          os << "\nBST_SEARCH_ITERATIVELY:" << std::endl <<
            "Starting the insert operation(BST_SEARCH_ITERATIVELY):" <<
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

        anil::bst_node* node = my_bst.search_iteratively(2);
        if (my_bst.data(node) != 2) { return false; }
        
        node = my_bst.search_iteratively(18);
        if (my_bst.data(node) != 18) { return false; }

        node = my_bst.search_iteratively(17);
        if (my_bst.data(node) != 17) { return false; }

        node = my_bst.search_iteratively(12);
        if (my_bst.data(node) != 12) { return false; }

        return true;
        break;
      }
    case BST_FIND_MIN_RECURSIVELY:
      {
        // Test to find the minimum value recursively:
        anil::bst my_bst;

        // list_one represents the same elements from page 295 of CLRS 3rd
        // edition.
        std::vector<int> list_one {12, 5, 18, 2, 9, 15, 19, 13, 17};

        if (verbose) {
          os << "\nBST_FIND_MIN_RECURSIVELY:" << std::endl <<
            "Starting the insert operation(BST_FIND_MIN_RECURSIVELY):" <<
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

        anil::bst_node* node = my_bst.find_min_recursively();
        if (my_bst.data(node) != 2) { return false; }
        
        my_bst.remove(node);
        node = my_bst.find_min_recursively();
        if (my_bst.data(node) != 5) { return false; }

        return true;
        break;
      }
    case BST_FIND_MIN_ITERATIVELY:
      {
        // Test to find the minimum value iteratively:
        anil::bst my_bst;

        // list_one represents the same elements from page 295 of CLRS 3rd
        // edition.
        std::vector<int> list_one {12, 5, 18, 2, 9, 15, 19, 13, 17};

        if (verbose) {
          os << "\nBST_FIND_MIN_ITERATIVELY:" << std::endl <<
            "Starting the insert operation(BST_FIND_MIN_ITERATIVELY):" <<
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

        anil::bst_node* node = my_bst.find_min_iteratively();
        if (my_bst.data(node) != 2) { return false; }
        
        my_bst.remove(node);
        node = my_bst.find_min_iteratively();
        if (my_bst.data(node) != 5) { return false; }

        return true;
        break;
      }
    case BST_FIND_MAX_RECURSIVELY:
      {
        // Test to find the maximum value recursively:
        anil::bst my_bst;

        // list_one represents the same elements from page 295 of CLRS 3rd
        // edition.
        std::vector<int> list_one {12, 5, 18, 2, 9, 15, 19, 13, 17};

        if (verbose) {
          os << "\nBST_FIND_MAX_RECURSIVELY:" << std::endl <<
            "Starting the insert operation(BST_FIND_MAX_RECURSIVELY):" <<
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

        anil::bst_node* node = my_bst.find_max_recursively();
        if (my_bst.data(node) != 19) { return false; }
        
        my_bst.remove(node);
        node = my_bst.find_max_recursively();
        if (my_bst.data(node) != 18) { return false; }

        return true;
        break;
      }
    case BST_FIND_MAX_ITERATIVELY:
      {
        // Test to find the maximum value iteratively:
        anil::bst my_bst;

        // list_one represents the same elements from page 295 of CLRS 3rd
        // edition.
        std::vector<int> list_one {12, 5, 18, 2, 9, 15, 19, 13, 17};

        if (verbose) {
          os << "\nBST_FIND_MAX_ITERATIVELY:" << std::endl <<
            "Starting the insert operation(BST_FIND_MAX_ITERATIVELY):" <<
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

        anil::bst_node* node = my_bst.find_max_iteratively();
        if (my_bst.data(node) != 19) { return false; }
        
        my_bst.remove(node);
        node = my_bst.find_max_iteratively();
        if (my_bst.data(node) != 18) { return false; }

        return true;
        break;
      }
    case BST_DATA:
      {
        // Test to get the data in a node:
        anil::bst my_bst;

        // list_one represents the same elements from page 295 of CLRS 3rd
        // edition.
        std::vector<int> list_one {12, 5, 18, 2, 9, 15, 19, 13, 17};

        if (verbose) {
          os << "\nBST_DATA:" << std::endl <<
            "Starting the insert operation(BST_DATA):" <<
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

        anil::bst_node* node = my_bst.find_max_iteratively();
        if (my_bst.data(node) != 19) { return false; }

        return true;
        break;
      }
    case BST_SUCCESSOR:
      {
        // Test to get the successor of a node:
        anil::bst my_bst;

        // list_one represents the same elements from page 295 of CLRS 3rd
        // edition.
        std::vector<int> list_one {12, 5, 18, 2, 9, 15, 19, 13, 17};

        if (verbose) {
          os << "\nBST_SUCCESSOR:" << std::endl <<
            "Starting the insert operation(BST_SUCCESSOR):" <<
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

        anil::bst_node* node = my_bst.find_min_iteratively();
        anil::bst_node* successor_node = my_bst.successor(node);
        if (my_bst.data(successor_node) != 5) { return false; }

        return true;
        break;
      }
    case BST_PREDECESSOR:
      {
        // Test to get the predecessor of a node:
        anil::bst my_bst;

        // list_one represents the same elements from page 295 of CLRS 3rd
        // edition.
        std::vector<int> list_one {12, 5, 18, 2, 9, 15, 19, 13, 17};

        if (verbose) {
          os << "\nBST_PREDECESSOR:" << std::endl <<
            "Starting the insert operation(BST_PREDECESSOR):" <<
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

        anil::bst_node* node = my_bst.find_max_iteratively();
        anil::bst_node* successor_node = my_bst.predecessor(node);
        if (my_bst.data(successor_node) != 18) { return false; }

        return true;
        break;
      }
    case BST_REMOVE:
      {
        // Test to remove a node from the binary search tree:
        anil::bst my_bst;

        // list_one represents the same elements from page 295 of CLRS 3rd
        // edition.
        std::vector<int> list_one {12, 5, 18, 2, 9, 15, 19, 13, 17};

        if (verbose) {
          os << "\nBST_REMOVE:" << std::endl <<
            "Starting the insert operation(BST_REMOVE):" <<
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

        anil::bst_node* node = my_bst.find_max_iteratively();
        anil::bst_node* successor_node = my_bst.predecessor(node);
        my_bst.remove(successor_node);
        successor_node = my_bst.predecessor(node);
        if (my_bst.data(successor_node) != 17) { return false; }

        return true;
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