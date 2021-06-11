/* This is the test harness for the trie data structure
   that I built */

/* TO DO: 1) Learn how to test the deconstructor!
            1-i) Use a shell program to both run the program and valgrind
            1-ii) What about unit testing a deconstructor? 
*/

#include "anil_trie.h"
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
enum trie_tests {
  TRIE_CONSTRUCTOR,
  TRIE_INSERT,
  TRIE_SEARCH,
  TRIE_STARTS_WITH,
  NO_OF_TESTS,
};

// The following array of strings associate enumeration values of tests
// declared in the enumeration 'trie_tests' with their string
// equivalents. For example, 
// 'std::cout<<trie_test_names[TRIE_CONSTRUCTOR];'
// will print 'TRIE_CONSTRUCTOR' as expected. This makes
// reporting and logging easier.
static const char* trie_test_names[] = {
  "TRIE_CONSTRUCTOR",
  "TRIE_INSERT",
  "TRIE_SEARCH",
  "TRIE_STARTS_WITH",
  "NO_OF_TESTS",
};

bool run_tests(std::ostream& os, int trie_test, bool verbose) {
  switch(trie_test) {
    case TRIE_CONSTRUCTOR:
      {
        // // Test to construct a binary search tree.
        // if (verbose) {
        //   os << "\nBST_CONSTRUCTOR:" << std::endl <<
        //     "Starting the construction operation:" <<
        //     std::endl;
        // }
        // anil::bst my_bst;
        // if (&my_bst == nullptr) {
        //   if (verbose) {
        //     os << "Construction unsuccessful!" << std::endl;
        //   }
        //   return false;
        // } else {
        //   if (verbose) {
        //     os << "Construction successful!" << std::endl;
        //   }
        //   return true;
        // }

        // break;
        return false;
      }
    case TRIE_INSERT:
      {
        // // Test to construct a binary search tree.
        // if (verbose) {
        //   os << "\nBST_CONSTRUCTOR:" << std::endl <<
        //     "Starting the construction operation:" <<
        //     std::endl;
        // }
        // anil::bst my_bst;
        // if (&my_bst == nullptr) {
        //   if (verbose) {
        //     os << "Construction unsuccessful!" << std::endl;
        //   }
        //   return false;
        // } else {
        //   if (verbose) {
        //     os << "Construction successful!" << std::endl;
        //   }
        //   return true;
        // }

        // break;
        return false;
      }
    case TRIE_SEARCH:
      {
        // // Test to insert elements:
        // anil::bst my_bst;

        // // This binary search tree is taken from page 290 of 3rd edition of CLRS.
        // std::vector<int> numbers {15, 6, 18, 3, 7, 17, 20, 2, 4, 13, 9};
        // std::vector<int> ordered_numbers {2, 3, 4, 6, 7, 9, 13, 15, 17, 18, 20};

        // if (verbose) {
        //   os << "\nBST_INSERT:" << std::endl <<
        //     "Starting the insert operation:" << std::endl;
        // }
        
        // for (auto x : numbers) {
        //   my_bst.insert(x);
        //   if (verbose) {
        //     os << x << ' ';
        //   }
        // }
        
        // if (verbose) { os << std::endl; }

        // for (int i = ordered_numbers.size() - 1; i >= 0; --i) {
        //   anil::bst_node* node_to_be_removed = my_bst.find_max();
        //   if (my_bst.get_node_data(node_to_be_removed) != ordered_numbers[i]) { return false; }
        //   my_bst.remove(node_to_be_removed);
        // }

        // return true;
        // break;
        return false;
      }
    case TRIE_STARTS_WITH:
      {
        // // Test to search elements:
        // anil::bst my_bst;

        // // This binary search tree is taken from page 290 of 3rd edition of CLRS.
        // std::vector<int> numbers {15, 6, 18, 3, 7, 17, 20, 2, 4, 13, 9};
        // int sub_test_success_count (0);

        // if (verbose) {
        //   os << "\nBST_SEARCH:" << std::endl <<
        //     "Starting the search operation:" << std::endl;
        // }
        
        // for (auto x : numbers) {
        //   my_bst.insert(x);
        //   if (verbose) {
        //     os << x << ' ';
        //   }
        // }
        
        // if (verbose) { os << std::endl; }

        // // Sub-test 1
        // for (int i = numbers.size() - 1; i >= 0; --i) {
        //   anil::bst_node* found_node = my_bst.search(numbers[i]);
        //   if (my_bst.get_node_data(found_node) != numbers[i]) { return false; }
        // }

        // ++sub_test_success_count;

        // // Sub-test 2
        // anil::bst_node* found_node = my_bst.search(1);
        // if (found_node != nullptr) { return false; }

        // ++sub_test_success_count;

        // if (sub_test_success_count == 2) {
        //   return true;
        // } else {
        //   return false;
        // }

        // break;
        return false;
      }
    // case TRIE_DECONSTRUCTOR:
    //   {
    //     return false;
    //     break;
    //   }
  }
}

int main (int argc, char **argv) {
  bool verbose = false;

  if (argc > 2 || (argc == 2 and strcmp(argv[1], "-v") != 0)) {
    std::cout << "Usage: ./trie [-v]"  << std::endl;
    return 1;
  } else if (argc == 2 and strcmp(argv[1], "-v") == 0) {
    verbose = true;
  }

  std::ofstream log_file ("trie_log.txt", std::ios::trunc);
  if (!log_file.is_open()) {
    std::cout << "There was a problem opening 'trie_log.txt'" <<
      std::endl;
  }

  int no_of_tests_passed {0};

  for (int i = TRIE_CONSTRUCTOR; i < NO_OF_TESTS; ++i) {
    bool test_result = run_tests(log_file, i, verbose);
    log_file << "Test " << trie_test_names[i] << ": " <<
      (test_result == true ? "PASSED" : "FAILED") << std::endl;
    if (test_result) { ++no_of_tests_passed; }
  }

  log_file << no_of_tests_passed << "/" << NO_OF_TESTS <<
    " tests were passed." << std::endl;

  log_file.close();

  return 0;
}
