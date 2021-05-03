/* This is the test harness for the static, unsorted and
   doubly-linked list. */

/* TO DO: 1) 
          3) Learn how to test the deconstructor! */

#include "anil_doubly_linked_list.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>

// The following enumeration contains the names of the tests conducted in
// this test harness and associates each one with a number to make the code
// more readable / understandable as this method eliminates the need to use
// magic numbers.
enum doubly_linked_list_tests {
  DOUBLY_LINKED_LIST_CONSTRUCTOR,
  DOUBLY_LINKED_LIST_INSERT,
  DOUBLY_LINKED_LIST_REMOVE,
  DOUBLY_LINKED_LIST_SEARCH,
  DOUBLY_LINKED_LIST_IS_EMPTY,
  NO_OF_TESTS,
};

// The following array of strings associate enumeration values of tests
// declared in the enumeration 'doubly_linked_list_tests' with their string
// equivalents. For example, 
// 'std::cout<<doubly_linked_list_test_names[DOUBLY_LINKED_LIST_CONSTRUCTOR];'
// will print 'DOUBLY_LINKED_LIST_CONSTRUCTOR' as expected. This makes
// reporting and logging easier.
static const char* doubly_linked_list_test_names[] = {
  "DOUBLY_LINKED_LIST_CONSTRUCTOR",
  "DOUBLY_LINKED_LIST_INSERT",
  "DOUBLY_LINKED_LIST_REMOVE",
  "DOUBLY_LINKED_LIST_SEARCH",
  "DOUBLY_LINKED_LIST_IS_EMPTY",
  "NO_OF_TESTS",
};

bool run_tests(std::ostream& os, int doubly_linked_list_test, bool verbose) {
  switch(doubly_linked_list_test) {
    case DOUBLY_LINKED_LIST_CONSTRUCTOR:
      {
        // Test to construct a doubly linked list.
        if (verbose) {
          os << "\nDOUBLY_LINKED_LIST_CONSTRUCTOR:" << std::endl <<
            "Starting the construction operation:" <<
            std::endl;
        }
        anil::linked_list my_linked_list;
        if (&my_linked_list == nullptr) {
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
    case DOUBLY_LINKED_LIST_INSERT:
      {
        // Test to insert elements:
        anil::linked_list my_linked_list;

        std::vector<int> numbers {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

        if (verbose) {
          os << "\nDOUBLY_LINKED_LIST_INSERT:" << std::endl <<
            "Starting the insert operation:" << std::endl;
        }
        
        for (auto x : numbers) {
          my_linked_list.insert(x);
          if (verbose) {
            os << x << ' ';
          }
        }
        
        if (verbose) { os << std::endl; }

        for (int i = numbers.size() - 1; i > 0; --i) {
          anil::node* node_to_be_removed = my_linked_list.search(numbers[i]);
          int removed_element = my_linked_list.remove(node_to_be_removed);
          if (removed_element != numbers[i]) { return false; }
        }

        return true;
        break;
      }
    case DOUBLY_LINKED_LIST_REMOVE:
      {
        // Test to remove elements:
        anil::linked_list my_linked_list;

        std::vector<int> numbers {15, 6, 18, 3, 7, 17, 20, 2, 4, 13, 9};

        for (auto x : numbers) {
          my_linked_list.insert(x);
          if (verbose) {
            os << x << ' ';
          }
        }

        if (verbose) {
          os << "\nDOUBLY_LINKED_LIST_REMOVE:" << std::endl <<
            "Starting the remove operation:" <<
            std::endl;
        }

        for (int i = numbers.size() - 1; i > 0; --i) {
          anil::node* node_to_be_removed = my_linked_list.search(numbers[i]);
          int removed_element = my_linked_list.remove(node_to_be_removed);
          if (removed_element != numbers[i]) { return false; }
        }

        return true;
        break;
      }
    case DOUBLY_LINKED_LIST_SEARCH:
      {
        // Test to search elements:
        anil::linked_list my_linked_list;

        std::vector<int> numbers {43, 44, 43, 44, 43, 44, 43, 44, 43, 44, 420};

        for (auto x : numbers) {
          my_linked_list.insert(x);
          if (verbose) {
            os << x << ' ';
          }
        }

        if (verbose) {
          os << "\nDOUBLY_LINKED_LIST_SEARCH:" << std::endl <<
            "Starting the search operation:" <<
            std::endl;
        }

        for (int i = numbers.size() - 1; i > 0; --i) {
          anil::node* node_to_be_removed = my_linked_list.search(numbers[i]);
          int removed_element = my_linked_list.remove(node_to_be_removed);
          if (removed_element != numbers[i]) { return false; }
        }

        return true;
        break;
      }
    case DOUBLY_LINKED_LIST_IS_EMPTY:
      {
        // Test to check if is_empty function works correctly:
        anil::linked_list my_linked_list;

        if (verbose) {
          os << "\nDOUBLY_LINKED_LIST_IS_EMPTY:" << std::endl <<
            "Starting the is_empty operation:" <<
            std::endl;
        }

        if(my_linked_list.is_empty() != true) { return false; }

        return true;
        break;
      }
  }
}

int main (int argc, char **argv) {
  bool verbose = false;

  if (argc > 2 || (argc == 2 and strcmp(argv[1], "-v") != 0)) {
    std::cout << "Usage: ./doubly_linked_list [-v]"  << std::endl;
    return 1;
  } else if (argc == 2 and strcmp(argv[1], "-v") == 0) {
    verbose = true;
  }

  std::ofstream log_file ("doubly_linked_list_log.txt", std::ios::trunc);
  if (!log_file.is_open()) {
    std::cout << "There was a problem opening 'doubly_linked_list_log.txt'" <<
      std::endl;
  }

  int no_of_tests_passed {0};

  for (int i = DOUBLY_LINKED_LIST_CONSTRUCTOR; i < NO_OF_TESTS; ++i) {
    bool test_result = run_tests(log_file, i, verbose);
    log_file << "Test " << doubly_linked_list_test_names[i] << ": " <<
      (test_result == true ? "PASSED" : "FAILED") << std::endl;
    if (test_result) { ++no_of_tests_passed; }
  }

  log_file << no_of_tests_passed << "/" << NO_OF_TESTS <<
    " tests were passed." << std::endl;

  log_file.close();

  return 0;
}