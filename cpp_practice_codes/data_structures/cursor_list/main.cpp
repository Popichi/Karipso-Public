/* This is the test harness for the cursor list data structure
   that I built */

/* TO DO: 1) Learn how to test the deconstructor!
            1-i) Use a shell program to both run the program and valgrind
            1-ii) What about unit testing a deconstructor? 
*/

#include "anil_cursor_list.h"
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
enum cursor_list_tests {
  CURSOR_LIST_REGULAR_CONSTRUCTOR,
  CURSOR_LIST_COPY_CONSTRUCTOR,
  CURSOR_LIST_IS_EMPTY,
  CURSOR_LIST_SIZE,
  CURSOR_LIST_INDEX,
  CURSOR_LIST_FRONT_DATA,
  CURSOR_LIST_BACK_DATA,
  CURSOR_LIST_CURSOR_DATA,
  CURSOR_LIST_IS_EQUAL_OPERATOR,
  CURSOR_LIST_ASSIGNMENT_OPERATOR,
  CURSOR_LIST_OUTPUT_OPERATOR,
  CURSOR_LIST_CLEAR,
  CURSOR_LIST_MOVE_CURSOR_FRONT,
  CURSOR_LIST_MOVE_CURSOR_BACK,
  CURSOR_LIST_MOVE_CURSOR_PREV,
  CURSOR_LIST_MOVE_CURSOR_NEXT,
  CURSOR_LIST_PREPEND,
  CURSOR_LIST_APPEND,
  CURSOR_LIST_INSERT_BEFORE_CURSOR,
  CURSOR_LIST_INSERT_AFTER_CURSOR,
  CURSOR_LIST_DELETE_FRONT,
  CURSOR_LIST_DELETE_BACK,
  CURSOR_LIST_DELETE_CURSOR,
  //CURSOR_LIST_DELETE_LIST,
  //CURSOR_DECONSTRUCTOR,
  NO_OF_TESTS,
};

// The following array of strings associate enumeration values of tests
// declared in the enumeration 'cursor_list_tests' with their string
// equivalents. For example, 
// 'std::cout<<cursor_list_test_names[CURSOR_LIST_CONSTRUCTOR];'
// will print 'CURSOR_LIST_CONSTRUCTOR' as expected. This makes
// reporting and logging easier.
static const char* cursor_list_test_names[] = {
  "CURSOR_LIST_REGULAR_CONSTRUCTOR",
  "CURSOR_LIST_COPY_CONSTRUCTOR",
  "CURSOR_LIST_IS_EMPTY",
  "CURSOR_LIST_SIZE",
  "CURSOR_LIST_INDEX",
  "CURSOR_LIST_FRONT_DATA",
  "CURSOR_LIST_BACK_DATA",
  "CURSOR_LIST_CURSOR_DATA",
  "CURSOR_LIST_IS_EQUAL_OPERATOR",
  "CURSOR_LIST_ASSIGNMENT_OPERATOR",
  "CURSOR_LIST_OUTPUT_OPERATOR",
  "CURSOR_LIST_CLEAR",
  "CURSOR_LIST_MOVE_CURSOR_FRONT",
  "CURSOR_LIST_MOVE_CURSOR_BACK",
  "CURSOR_LIST_MOVE_CURSOR_PREV",
  "CURSOR_LIST_MOVE_CURSOR_NEXT",
  "CURSOR_LIST_PREPEND",
  "CURSOR_LIST_APPEND",
  "CURSOR_LIST_INSERT_BEFORE_CURSOR",
  "CURSOR_LIST_INSERT_AFTER_CURSOR",
  "CURSOR_LIST_DELETE_FRONT",
  "CURSOR_LIST_DELETE_BACK",
  "CURSOR_LIST_DELETE_CURSOR",
  //CURSOR_LIST_DELETE_LIST,
  //CURSOR_DECONSTRUCTOR,
  "NO_OF_TESTS",
};

bool run_tests(std::ostream& os, int bst_test, bool verbose) {
  switch(bst_test) {
    case CURSOR_LIST_REGULAR_CONSTRUCTOR:
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
        return false;
        break;
      }
    case CURSOR_LIST_COPY_CONSTRUCTOR:
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
        return false;
        break;
      }
    case CURSOR_LIST_IS_EMPTY:
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
        return false;
        break;

      }
    case CURSOR_LIST_SIZE:
      {
        // // Test to find the minimum elements:
        // anil::bst my_bst;

        // // This binary search tree is taken from page 290 of 3rd edition of CLRS.
        // std::vector<int> numbers {15, 6, 18, 3, 7, 17, 20, 2, 4, 13, 9};
        // std::vector<int> ordered_numbers {2, 3, 4, 6, 7, 9, 13, 15, 17, 18, 20};

        // if (verbose) {
        //   os << "\nBST_FIND_MIN:" << std::endl <<
        //     "Starting the find minimum number operation:" << std::endl;
        // }
        
        // for (auto x : numbers) {
        //   my_bst.insert(x);
        //   if (verbose) {
        //     os << x << ' ';
        //   }
        // }
        
        // if (verbose) { os << std::endl; }

        // for (int i = 0; i < ordered_numbers.size(); ++i) {
        //   anil::bst_node* node_to_be_removed = my_bst.find_min();
        //   if (my_bst.get_node_data(node_to_be_removed) != ordered_numbers[i]) { return false; }
        //   my_bst.remove(node_to_be_removed);
        // }

        // return true;
        return false;
        break;
      }
    case CURSOR_LIST_INDEX:
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
        return false;
        break;
      }
    case CURSOR_LIST_FRONT_DATA:
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
        return false;
        break;
      }
    case CURSOR_LIST_BACK_DATA:
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
        return false;
        break;
      }
    case CURSOR_LIST_CURSOR_DATA:
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
        return false;
        break;
      }
    case CURSOR_LIST_IS_EQUAL_OPERATOR:
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
        return false;
        break;
      }
    case CURSOR_LIST_ASSIGNMENT_OPERATOR:
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
        return false;
        break;
      }
    case CURSOR_LIST_OUTPUT_OPERATOR:
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
        return false;
        break;
      }
    case CURSOR_LIST_CLEAR:
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
        return false;
        break;
      }
    case CURSOR_LIST_MOVE_CURSOR_FRONT:
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
        return false;
        break;
      }
    case CURSOR_LIST_MOVE_CURSOR_BACK:
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
        return false;
        break;
      }
    case CURSOR_LIST_MOVE_CURSOR_PREV:
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
        return false;
        break;
      }
    case CURSOR_LIST_MOVE_CURSOR_NEXT:
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
        return false;
        break;
      }
    case CURSOR_LIST_PREPEND:
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
        return false;
        break;
      }
    case CURSOR_LIST_APPEND:
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
        return false;
        break;
      }
    case CURSOR_LIST_INSERT_BEFORE_CURSOR:
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
        return false;
        break;
      }
    case CURSOR_LIST_INSERT_AFTER_CURSOR:
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
        return false;
        break;
      }
    case CURSOR_LIST_DELETE_FRONT:
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
        return false;
        break;
      }
    case CURSOR_LIST_DELETE_BACK:
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
        return false;
        break;
      }
    case CURSOR_LIST_DELETE_CURSOR:
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
        return false;
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
    std::cout << "Usage: ./cursor_list [-v]"  << std::endl;
    return 1;
  } else if (argc == 2 and strcmp(argv[1], "-v") == 0) {
    verbose = true;
  }

  std::ofstream log_file ("cursor_list_log.txt", std::ios::trunc);
  if (!log_file.is_open()) {
    std::cout << "There was a problem opening 'cursor_list_log.txt'" <<
      std::endl;
  }

  int no_of_tests_passed {0};

  for (int i = CURSOR_LIST_REGULAR_CONSTRUCTOR; i < NO_OF_TESTS; ++i) {
    bool test_result = run_tests(log_file, i, verbose);
    log_file << "Test " << cursor_list_test_names[i] << ": " <<
      (test_result == true ? "PASSED" : "FAILED") << std::endl;
    if (test_result) { ++no_of_tests_passed; }
  }

  log_file << no_of_tests_passed << "/" << NO_OF_TESTS <<
    " tests were passed." << std::endl;

  log_file.close();

  return 0;
}
