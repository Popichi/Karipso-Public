/* This is the test harness for the dynamic, unsorted and
   singly-linked list. */

/* TO DO: 1) Learn how to test the deconstructor!
            1-i) Use a shell program to both run the program and valgrind
            1-ii) What about unit testing a deconstructor? 
*/

#include "anil_singly_linked_list.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>

// The following enumeration contains the names of the tests conducted in
// this test harness and associates each one with a number to make the code
// more readable / understandable as this method eliminates the need to use
// magic numbers.
enum singly_linked_list_tests {
  SINGLY_LINKED_LIST_CONSTRUCTOR,
  SINGLY_LINKED_LIST_INSERT,
  SINGLY_LINKED_LIST_REMOVE,
  SINGLY_LINKED_LIST_SEARCH,
  SINGLY_LINKED_LIST_IS_EMPTY,
  NO_OF_TESTS,
};

// The following array of strings associate enumeration values of tests
// declared in the enumeration 'singly_linked_list_tests' with their string
// equivalents. For example, 
// 'std::cout<<singly_linked_list_test_names[SINGLY_LINKED_LIST_CONSTRUCTOR];'
// will print 'SINGLY_LINKED_LIST_CONSTRUCTOR' as expected. This makes
// reporting and logging easier.
static const char* singly_linked_list_test_names[] = {
  "SINGLY_LINKED_LIST_CONSTRUCTOR",
  "SINGLY_LINKED_LIST_INSERT",
  "SINGLY_LINKED_LIST_REMOVE",
  "SINGLY_LINKED_LIST_SEARCH",
  "SINGLY_LINKED_LIST_IS_EMPTY",
  "NO_OF_TESTS",
};

bool run_tests(std::ostream& os, int singly_linked_list_test, bool verbose) {
  switch(singly_linked_list_test) {
    case SINGLY_LINKED_LIST_CONSTRUCTOR:
      {
        // Test to construct a singly linked list.
        if (verbose) {
          os << "\nSINGLY_LINKED_LIST_CONSTRUCTOR:" << std::endl <<
            "Starting the construction operation:" <<
            std::endl;
        }
        anil::singly_linked_list my_linked_list;
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
    case SINGLY_LINKED_LIST_INSERT:
      {
        // Test to insert elements:
        anil::singly_linked_list my_linked_list;

        std::vector<int> numbers {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

        if (verbose) {
          os << "\nSINGLY_LINKED_LIST_INSERT:" << std::endl <<
            "Starting the insert operation:" << std::endl;
        }
        
        for (auto x : numbers) {
          my_linked_list.insert(x);
          if (verbose) {
            os << x << ' ';
          }
        }
        
        if (verbose) { os << std::endl; }

        for (int i = numbers.size() - 1; i >= 0; --i) {
          anil::node* node_to_be_removed = my_linked_list.search(numbers[i]);
          int removed_element = my_linked_list.remove(node_to_be_removed);
          if (removed_element != numbers[i]) { return false; }
        }

        return true;
        break;
      }
    case SINGLY_LINKED_LIST_REMOVE:
      {
        // Test to remove elements:
        anil::singly_linked_list my_linked_list;

        std::vector<int> numbers {15, 6, 18, 3, 7, 17, 20, 2, 4, 13, 9};
        int sub_test_success_count (0);

        // Sub-test 1
        if (verbose) {
          os << "\nSINGLY_LINKED_LIST_REMOVE, SUB-TEST 1:" << std::endl <<
            "Starting the remove operation:" <<
            std::endl;
        }

        for (auto x : numbers) {
          my_linked_list.insert(x);
          if (verbose) {
            os << x << ' ';
          }
        }

        for (int i = numbers.size() - 1; i >= 0; --i) {
          anil::node* node_to_be_removed = my_linked_list.search(numbers[i]);
          int removed_element = my_linked_list.remove(node_to_be_removed);
          if (removed_element != numbers[i]) { return false; }
        }

        ++sub_test_success_count;

        // Sub-test 2
        if (verbose) {
          os << "\nSINGLY_LINKED_LIST_REMOVE, SUB-TEST 2:" << std::endl <<
            "Starting the remove operation:" << std::endl;
        }
        
        for (auto x : numbers) {
          my_linked_list.insert(x);
          if (verbose) {
            os << x << ' ';
          }
        }
        
        if (verbose) { os << std::endl; }

        // Remove a node in between the head and tail!
        anil::node* node_to_be_removed = my_linked_list.search(2);
        int removed_element = my_linked_list.remove(node_to_be_removed);
        if (removed_element != 2) { return false; }
        anil::node* previous_node = my_linked_list.search(20);
        if (previous_node->next->data != 4) { return false; }

        // Remove the tail!
        node_to_be_removed = my_linked_list.search(9);
        removed_element = my_linked_list.remove(node_to_be_removed);
        if (removed_element != 9) { return false; }
        previous_node = my_linked_list.search(13);
        if (previous_node->next != nullptr) { return false; }

        // Remove the head
        node_to_be_removed = my_linked_list.search(15);
        removed_element = my_linked_list.remove(node_to_be_removed);
        if (removed_element != 15) { return false; }
        anil::node* head = my_linked_list.search(15);
        if (head != nullptr) { return false; }

        ++sub_test_success_count;

        if (sub_test_success_count == 2) {
          return true;
        } else {
          return false;
        }

        break;
      }
    case SINGLY_LINKED_LIST_SEARCH:
      {
        // Test to search elements:
        anil::singly_linked_list my_linked_list;

        std::vector<int> numbers {43, 44, 43, 44, 43, 44, 43, 44, 43, 44, 420};

        for (auto x : numbers) {
          my_linked_list.insert(x);
          if (verbose) {
            os << x << ' ';
          }
        }

        if (verbose) {
          os << "\nSINGLY_LINKED_LIST_SEARCH:" << std::endl <<
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
    case SINGLY_LINKED_LIST_IS_EMPTY:
      {
        // Test to check if is_empty function works correctly:
        anil::singly_linked_list my_linked_list;

        if (verbose) {
          os << "\nSINGLY_LINKED_LIST_IS_EMPTY:" << std::endl <<
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
    std::cout << "Usage: ./singly_linked_list [-v]"  << std::endl;
    return 1;
  } else if (argc == 2 and strcmp(argv[1], "-v") == 0) {
    verbose = true;
  }

  std::ofstream log_file ("singly_linked_list_log.txt", std::ios::trunc);
  if (!log_file.is_open()) {
    std::cout << "There was a problem opening 'singly_linked_list_log.txt'" <<
      std::endl;
  }

  int no_of_tests_passed {0};

  for (int i = SINGLY_LINKED_LIST_CONSTRUCTOR; i < NO_OF_TESTS; ++i) {
    bool test_result = run_tests(log_file, i, verbose);
    log_file << "Test " << singly_linked_list_test_names[i] << ": " <<
      (test_result == true ? "PASSED" : "FAILED") << std::endl;
    if (test_result) { ++no_of_tests_passed; }
  }

  log_file << no_of_tests_passed << "/" << NO_OF_TESTS <<
    " tests were passed." << std::endl;

  log_file.close();

  return 0;
}
