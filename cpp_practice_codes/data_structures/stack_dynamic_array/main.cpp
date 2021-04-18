/* This is the test harness for a stack data structure which utilizes a dynamic
   array*/

/* TO DO: 1) Determine the test cases!
            i) Determine the enumerations!
            ii) Code the "run_tests" function! */

#include "anil.stack_dynamic_array.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>

// The following enumeration contains the names of the tests conducted in
// this test harness and associates each one with a number to make the code
// more readable / understandable as this method eliminates the need to use
// magic numbers.
enum stack_tests {
  STACK_CONSTRUCTOR,
  STACK_PUSH,
  STACK_POP,
  STACK_PEEK,
  STACK_IS_EMPTY,
  STACK_IS_FULL,
  NO_OF_TESTS,
};

// The following array of strings associate enumeration values of tests
// declared in the enumeration 'stack_tests' with their string equivalents.
// For example, 'std::cout << stack_test_names[STACK_CONSTRUCTOR];' will
// print 'STACK_CONSTRUCTOR' as expected. This makes reporting and logging 
// easier.
static const char* stack_test_names[] = {
	"STACK_CONSTRUCTOR",
  "STACK_PUSH",
  "STACK_POP",
  "STACK_PEEK",
  "STACK_IS_EMPTY",
  "STACK_IS_FULL",
  "NO_OF_TESTS",
};

bool run_tests(std::ostream& os, int stack_test, bool verbose) {
  switch(stack_test) {
    case STACK_CONSTRUCTOR:
      {
        // Test to construct a stack.
        if (verbose) {
          os << "\nSTACK_CONSTRUCTOR:" << std::endl <<
            "Starting the construction operation:" <<
            std::endl;
        }
        anil::stack my_stack;
        if (&my_stack == nullptr) {
          if (verbose) {
            os << "\nConstruction unsuccessful!" << std::endl;
          }
          return false;
        } else {
          if (verbose) {
            os << "\nConstruction successful!" << std::endl;
          }
          return true;
        }
        break;
      }
    case STACK_PUSH:
      {
        // Test to insert elements:
        anil::stack my_stack;

        std::vector<int> numbers {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

        if (verbose) {
          os << "\nSTACK_PUSH:" << std::endl <<
            "Starting the push operation:" << std::endl;
        }
        
        for (auto x : numbers) {
          my_stack.push(x);
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
    case STACK_POP:
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
    case STACK_PEEK:
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
    case STACK_IS_EMPTY:
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
    case STACK_IS_FULL:
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
  }
}

int main (int argc, char **argv) {
  bool verbose = false;

  if (argc > 2 || (argc == 2 and strcmp(argv[1], "-v") != 0)) {
    std::cout << "Usage: ./stack_dynamic_array [-v]"  << std::endl;
    return 1;
  } else if (argc == 2 and strcmp(argv[1], "-v") == 0) {
    verbose = true;
  }

  const int number_of_tests = 3;
  std::ofstream log_file ("stack_dynamic_array_log.txt", std::ios::trunc);
  if (!log_file.is_open()) {
    std::cout << "There was a problem opening 'stack_dynamic_array_log.txt'" <<
      std::endl;
  }

  int no_of_tests_passed {0};

  for (int i = STACK_CONSTRUCTOR; i < NO_OF_TESTS; ++i) {
    bool test_result = run_tests(log_file, i, verbose);
    log_file << "Test " << stack_test_names[i] << ": " <<
      (test_result == true ? "PASSED" : "FAILED") << std::endl;
    if (test_result) { ++no_of_tests_passed; }
  }

  log_file << no_of_tests_passed << "/" << NO_OF_TESTS <<
    " tests were passed." << std::endl;

  log_file.close();

  return 0;
}