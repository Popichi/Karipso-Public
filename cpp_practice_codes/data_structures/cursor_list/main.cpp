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
  CURSOR_LIST_DELETE_LIST,
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
  "CURSOR_LIST_DELETE_LIST",
  //CURSOR_DECONSTRUCTOR,
  "NO_OF_TESTS",
};

bool run_tests(std::ostream& os, int bst_test, bool verbose) {
  switch(bst_test) {
    case CURSOR_LIST_REGULAR_CONSTRUCTOR:
      {
        // Test to construct a cursor list.
        if (verbose) {
          os << "\nCURSOR_LIST_REGULAR_CONSTRUCTOR:" << std::endl <<
            "Starting the construction operation:" <<
            std::endl;
        }
        anil::cursor_list my_cursor_list;
        if (my_cursor_list.index() != -1 && my_cursor_list.size() != 0 &&
            my_cursor_list.is_empty() != true) {
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
        return false;
        break;
      }
    case CURSOR_LIST_COPY_CONSTRUCTOR:
      {
        // Test to construct a cursor list by using the copy constructor.
        if (verbose) {
          os << "\nCURSOR_LIST_COPY_CONSTRUCTOR:" << std::endl <<
            "Starting the construction operation:" <<
            std::endl;
        }
        anil::cursor_list my_cursor_list;
        my_cursor_list.append(1);
        anil::cursor_list my_copied_cursor_list = my_cursor_list;
        if (my_copied_cursor_list.index() != -1 &&
            my_copied_cursor_list.size() != 1 &&
            my_copied_cursor_list.front_data() != 1 &&
            my_copied_cursor_list.back_data() != 1) {
          if (verbose) {
            os << "Copy construction unsuccessful!" << std::endl;
          }
          return false;
        } else {
          if (verbose) {
            os << "Copy construction successful!" << std::endl;
          }
          return true;
        }
        
        return false;
        break;
      }
    case CURSOR_LIST_IS_EMPTY:
      { 
        // Test to test is_empty() function.
        if (verbose) {
          os << "\nCURSOR_LIST_IS_EMPTY:" << std::endl <<
            "Starting the is_empty() operation:" <<
            std::endl;
        }
        anil::cursor_list my_cursor_list;
        if (my_cursor_list.is_empty() != true) {
          if (verbose) {
            os << "CURSOR_LIST_IS_EMPTY check unsuccessful!" << std::endl;
          }
          return false;
        } else {
          if (verbose) {
            os << "CURSOR_LIST_IS_EMPTY check successful!" << std::endl;
          }
          return true;
        }
        return false;
        break;
      }
    case CURSOR_LIST_SIZE:
      {
        // Test to test size() function.
        if (verbose) {
          os << "\nCURSOR_LIST_SIZE:" << std::endl <<
            "Starting the is_empty() operation:" <<
            std::endl;
        }
        anil::cursor_list my_cursor_list;
        if (my_cursor_list.size() != 0) {
          return false;
        }

        my_cursor_list.append(1);
        my_cursor_list.append(2);
        if (my_cursor_list.size() != 2) {
          return false;
        }

        return true;
        break;
      }
    case CURSOR_LIST_INDEX:
      {
        // Test to test index() function.
        if (verbose) {
          os << "\nCURSOR_LIST_INDEX:" << std::endl <<
            "Starting the index() operation:" <<
            std::endl;
        }
        anil::cursor_list my_cursor_list;

        my_cursor_list.append(1);
        my_cursor_list.append(2);
        my_cursor_list.append(3);
        my_cursor_list.append(4);
        my_cursor_list.append(5);
        if (my_cursor_list.index() != -1) {
          return false;
        }

        my_cursor_list.move_cursor_front();
        my_cursor_list.move_cursor_next();
        my_cursor_list.move_cursor_next();
        if (my_cursor_list.index() != 2) {
          return false;
        }

        return true;
        break;
      }
    case CURSOR_LIST_FRONT_DATA:
      {
        // Test to test front_data() function.
        if (verbose) {
          os << "\nCURSOR_LIST_FRONT_DATA:" << std::endl <<
            "Starting the front_data() operation:" <<
            std::endl;
        }
        anil::cursor_list my_cursor_list;

        my_cursor_list.append(1);
        my_cursor_list.append(2);
        my_cursor_list.append(3);
        my_cursor_list.append(4);
        my_cursor_list.append(5);
        if (my_cursor_list.front_data() != 1) {
          return false;
        }

        return true;
        break;
      }
    case CURSOR_LIST_BACK_DATA:
      {
        // Test to test back_data() function.
        if (verbose) {
          os << "\nCURSOR_LIST_BACK_DATA:" << std::endl <<
            "Starting the back_data() operation:" <<
            std::endl;
        }
        anil::cursor_list my_cursor_list;

        my_cursor_list.append(1);
        my_cursor_list.append(2);
        my_cursor_list.append(3);
        my_cursor_list.append(4);
        my_cursor_list.append(5);
        if (my_cursor_list.back_data() != 5) {
          return false;
        }

        return true;
        break;
      }
    case CURSOR_LIST_CURSOR_DATA:
      {
        // Test to test cursor_data() function.
        if (verbose) {
          os << "\nCURSOR_LIST_CURSOR_DATA:" << std::endl <<
            "Starting the cursor_data() operation:" <<
            std::endl;
        }
        anil::cursor_list my_cursor_list;

        my_cursor_list.append(1);
        my_cursor_list.append(2);
        my_cursor_list.append(3);
        my_cursor_list.append(4);
        my_cursor_list.append(5);
        my_cursor_list.move_cursor_back();
        if (my_cursor_list.cursor_data() != 5) {
          return false;
        }

        my_cursor_list.move_cursor_front();
        if (my_cursor_list.cursor_data() != 1) {
          return false;
        }

        my_cursor_list.move_cursor_next();
        my_cursor_list.move_cursor_next();
        if (my_cursor_list.cursor_data() != 3) {
          return false;
        }

        return true;
        break;
      }
    case CURSOR_LIST_IS_EQUAL_OPERATOR:
      {
        // Test to test == function.
        if (verbose) {
          os << "\nCURSOR_LIST_IS_EQUAL_OPERATOR:" << std::endl <<
            "Starting the == operation:" <<
            std::endl;
        }
        anil::cursor_list my_cursor_list;
        int sub_test_count (0);

        my_cursor_list.append(1);
        my_cursor_list.append(2);
        my_cursor_list.append(3);
        my_cursor_list.append(4);
        my_cursor_list.append(5);

        anil::cursor_list my_copied_cursor_list = my_cursor_list;
        if (my_cursor_list == my_copied_cursor_list) {
          ++sub_test_count;
        }

        anil::cursor_list empty_cursor_list;
        if (empty_cursor_list == my_cursor_list) {
          return false;
        } else {
          ++sub_test_count;
        }

        if (sub_test_count == 2) {
          return true;
        } else {
          return false;
        }
        break;
      }
    case CURSOR_LIST_ASSIGNMENT_OPERATOR:
      {
        // Test to test the assignment operator function.
        if (verbose) {
          os << "\nCURSOR_LIST_ASSIGNMENT_OPERATOR:" << std::endl <<
            "Starting the assignment operator operation:" <<
            std::endl;
        }
        anil::cursor_list my_cursor_list;
        int sub_test_count (0);

        my_cursor_list.append(1);
        my_cursor_list.append(2);
        my_cursor_list.append(3);
        my_cursor_list.append(4);
        my_cursor_list.append(5);

        anil::cursor_list my_copied_cursor_list = my_cursor_list;
        if (my_cursor_list == my_copied_cursor_list) {
          ++sub_test_count;
        }

        anil::cursor_list other_copied_cursor_list;
        other_copied_cursor_list = my_cursor_list;
        if (other_copied_cursor_list == my_cursor_list) {
          ++sub_test_count;
        }

        if (sub_test_count == 2) {
          return true;
        } else {
          return false;
        }
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
        // Test to test the clear function.
        if (verbose) {
          os << "\nCURSOR_LIST_CLEAR:" << std::endl <<
            "Starting the clear operation:" <<
            std::endl;
        }
        anil::cursor_list my_cursor_list;
        int sub_test_count (0);

        my_cursor_list.append(1);
        my_cursor_list.append(2);
        my_cursor_list.append(3);
        my_cursor_list.append(4);
        my_cursor_list.append(5);

        if (my_cursor_list.size() == 0 && my_cursor_list.is_empty() == true) {
          return false;
        } else {
          ++sub_test_count;
        }

        my_cursor_list.clear();
        if (my_cursor_list.size() == 0 && my_cursor_list.is_empty() == true) {
          ++sub_test_count;
        } else {
          return false;
        }

        if (sub_test_count == 2) {
          return true;
        } else {
          return false;
        }
        break;
      }
    case CURSOR_LIST_MOVE_CURSOR_FRONT:
      {
        // Test to move the cursor to underline the front node.
        if (verbose) {
          os << "\nCURSOR_LIST_MOVE_CURSOR_FRONT:" << std::endl <<
            "Starting the move cursor front operation:" <<
            std::endl;
        }
        anil::cursor_list my_cursor_list;
        int sub_test_count (0);

        my_cursor_list.append(1);
        my_cursor_list.append(2);
        my_cursor_list.append(3);
        my_cursor_list.append(4);
        my_cursor_list.append(5);

        if (my_cursor_list.index() != -1) {
          return false;
        } else {
          ++sub_test_count;
        }

        my_cursor_list.move_cursor_front();
        if (my_cursor_list.index() == 0 && my_cursor_list.cursor_data() == 1) {
          ++sub_test_count;
        } else {
          return false;
        }

        if (sub_test_count == 2) {
          return true;
        } else {
          return false;
        }
        break;
      }
    case CURSOR_LIST_MOVE_CURSOR_BACK:
      {
        // Test to move the cursor to underline the back node.
        if (verbose) {
          os << "\nCURSOR_LIST_MOVE_CURSOR_BACK:" << std::endl <<
            "Starting the move cursor back operation:" <<
            std::endl;
        }
        anil::cursor_list my_cursor_list;
        int sub_test_count (0);

        my_cursor_list.append(1);
        my_cursor_list.append(2);
        my_cursor_list.append(3);
        my_cursor_list.append(4);
        my_cursor_list.append(5);

        if (my_cursor_list.index() != -1) {
          return false;
        } else {
          ++sub_test_count;
        }

        my_cursor_list.move_cursor_back();
        if (my_cursor_list.index() == 4 && my_cursor_list.cursor_data() == 5) {
          ++sub_test_count;
        } else {
          return false;
        }

        if (sub_test_count == 2) {
          return true;
        } else {
          return false;
        }
        break;
      }
    case CURSOR_LIST_MOVE_CURSOR_PREV:
      {
        // Test to move the cursor to underline the previous node.
        if (verbose) {
          os << "\nCURSOR_LIST_MOVE_CURSOR_PREV:" << std::endl <<
            "Starting the move cursor prev operation:" <<
            std::endl;
        }
        anil::cursor_list my_cursor_list;
        int sub_test_count (0);

        my_cursor_list.append(1);
        my_cursor_list.append(2);
        my_cursor_list.append(3);
        my_cursor_list.append(4);
        my_cursor_list.append(5);
        my_cursor_list.move_cursor_front();

        if (my_cursor_list.cursor_data() != 1) {
          return false;
        } else {
          ++sub_test_count;
        }

        my_cursor_list.move_cursor_prev();
        if (my_cursor_list.index() != -1) {
          return false;
        } else {
          ++sub_test_count;
        }

        my_cursor_list.move_cursor_back();
        my_cursor_list.move_cursor_prev();
        my_cursor_list.move_cursor_prev();
        if (my_cursor_list.index() == 2 && my_cursor_list.cursor_data() == 3) {
          ++sub_test_count;
        } else {
          return false;
        }

        if (sub_test_count == 3) {
          return true;
        } else {
          return false;
        }
        break;
      }
    case CURSOR_LIST_MOVE_CURSOR_NEXT:
      {
        // Test to move the cursor to underline the next node.
        if (verbose) {
          os << "\nCURSOR_LIST_MOVE_CURSOR_NEXT:" << std::endl <<
            "Starting the move cursor next operation:" <<
            std::endl;
        }
        anil::cursor_list my_cursor_list;
        int sub_test_count (0);

        my_cursor_list.append(1);
        my_cursor_list.append(2);
        my_cursor_list.append(3);
        my_cursor_list.append(4);
        my_cursor_list.append(5);
        my_cursor_list.move_cursor_back();

        if (my_cursor_list.cursor_data() != 5) {
          return false;
        } else {
          ++sub_test_count;
        }

        my_cursor_list.move_cursor_next();
        if (my_cursor_list.index() != -1) {
          return false;
        } else {
          ++sub_test_count;
        }

        my_cursor_list.move_cursor_front();
        my_cursor_list.move_cursor_next();
        my_cursor_list.move_cursor_next();
        if (my_cursor_list.index() == 2 && my_cursor_list.cursor_data() == 3) {
          ++sub_test_count;
        } else {
          return false;
        }

        if (sub_test_count == 3) {
          return true;
        } else {
          return false;
        }
        break;
      }
    case CURSOR_LIST_PREPEND:
      {
        // Test to prepend new nodes to the cursor list.
        if (verbose) {
          os << "\nCURSOR_LIST_PREPEND:" << std::endl <<
            "Starting the prepend operation:" <<
            std::endl;
        }
        anil::cursor_list my_cursor_list;
        int sub_test_count (0);

        my_cursor_list.append(1);
        my_cursor_list.append(2);
        my_cursor_list.append(3);
        my_cursor_list.append(4);
        my_cursor_list.append(5);
        my_cursor_list.prepend(6);

        if (my_cursor_list.front_data() == 6) {
          ++sub_test_count;
        } else {
          return false;
        }

        my_cursor_list.prepend(7);
        if (my_cursor_list.front_data() == 7) {
          ++sub_test_count;
        } else {
          return false;
        }

        anil::cursor_list my_prepended_cursor_list;
        my_prepended_cursor_list.prepend(1);
        my_prepended_cursor_list.prepend(2);
        my_prepended_cursor_list.prepend(3);
        my_prepended_cursor_list.prepend(4);
        my_prepended_cursor_list.prepend(5);

        if (my_prepended_cursor_list.front_data() == 5 &&
            my_prepended_cursor_list.back_data() == 1) {
          ++sub_test_count;
        } else {
          return false;
        }

        if (sub_test_count == 3) {
          return true;
        } else {
          return false;
        }
        break;
      }
    case CURSOR_LIST_APPEND:
      {
        // Test to append new nodes to the cursor list.
        if (verbose) {
          os << "\nCURSOR_LIST_APPEND:" << std::endl <<
            "Starting the append operation:" <<
            std::endl;
        }
        anil::cursor_list my_cursor_list;
        int sub_test_count (0);

        my_cursor_list.prepend(1);
        my_cursor_list.prepend(2);
        my_cursor_list.prepend(3);
        my_cursor_list.prepend(4);
        my_cursor_list.prepend(5);
        my_cursor_list.append(6);

        if (my_cursor_list.front_data() == 5) {
          ++sub_test_count;
        } else {
          return false;
        }

        my_cursor_list.append(7);
        if (my_cursor_list.back_data() == 7) {
          ++sub_test_count;
        } else {
          return false;
        }

        anil::cursor_list my_appended_cursor_list;
        my_appended_cursor_list.append(1);
        my_appended_cursor_list.append(2);
        my_appended_cursor_list.append(3);
        my_appended_cursor_list.append(4);
        my_appended_cursor_list.append(5);

        if (my_appended_cursor_list.front_data() == 1 &&
            my_appended_cursor_list.back_data() == 5) {
          ++sub_test_count;
        } else {
          return false;
        }

        if (sub_test_count == 3) {
          return true;
        } else {
          return false;
        }
        break;
      }
    case CURSOR_LIST_INSERT_BEFORE_CURSOR:
      {
        // Test to insert new nodes before the cursor.
        if (verbose) {
          os << "\nCURSOR_LIST_INSERT_BEFORE_CURSOR:" << std::endl <<
            "Starting the insert before the cursor operation:" <<
            std::endl;
        }
        anil::cursor_list my_cursor_list;
        int sub_test_count (0);

        my_cursor_list.append(1);
        my_cursor_list.append(2);
        my_cursor_list.append(3);
        my_cursor_list.append(4);
        my_cursor_list.append(5);
        my_cursor_list.append(6);
        my_cursor_list.move_cursor_back();
        my_cursor_list.move_cursor_prev();
        my_cursor_list.insert_before_cursor(7);

        if (my_cursor_list.cursor_data() == 5) {
          ++sub_test_count;
        } else {
          return false;
        }

        my_cursor_list.move_cursor_prev();
        if (my_cursor_list.cursor_data() == 7) {
          ++sub_test_count;
        } else {
          return false;
        }

        my_cursor_list.move_cursor_front();
        my_cursor_list.insert_before_cursor(8);

        if (my_cursor_list.front_data() == 8 && my_cursor_list.cursor_data() == 1) {
          ++sub_test_count;
        } else {
          return false;
        }

        if (sub_test_count == 3) {
          return true;
        } else {
          return false;
        }
        break;
      }
    case CURSOR_LIST_INSERT_AFTER_CURSOR:
      {
        // Test to insert new nodes after the cursor.
        if (verbose) {
          os << "\nCURSOR_LIST_INSERT_AFTER_CURSOR:" << std::endl <<
            "Starting the insert after the cursor operation:" <<
            std::endl;
        }
        anil::cursor_list my_cursor_list;
        int sub_test_count (0);

        my_cursor_list.append(1);
        my_cursor_list.append(2);
        my_cursor_list.append(3);
        my_cursor_list.append(4);
        my_cursor_list.append(5);
        my_cursor_list.append(6);
        my_cursor_list.move_cursor_front();
        my_cursor_list.move_cursor_next();
        my_cursor_list.insert_after_cursor(7);

        if (my_cursor_list.cursor_data() == 2) {
          ++sub_test_count;
        } else {
          return false;
        }

        my_cursor_list.move_cursor_next();
        if (my_cursor_list.cursor_data() == 7) {
          ++sub_test_count;
        } else {
          return false;
        }

        my_cursor_list.move_cursor_back();
        my_cursor_list.insert_after_cursor(8);

        if (my_cursor_list.back_data() == 8 && my_cursor_list.cursor_data() == 6) {
          ++sub_test_count;
        } else {
          return false;
        }

        if (sub_test_count == 3) {
          return true;
        } else {
          return false;
        }
        break;
      }
    case CURSOR_LIST_DELETE_FRONT:
      {
        // Test to delete the front node of the cursor list.
        if (verbose) {
          os << "\nCURSOR_LIST_DELETE_FRONT:" << std::endl <<
            "Starting the delete front operation:" <<
            std::endl;
        }
        anil::cursor_list my_cursor_list;
        int sub_test_count (0);

        my_cursor_list.append(1);
        my_cursor_list.append(2);
        my_cursor_list.append(3);
        my_cursor_list.append(4);
        my_cursor_list.append(5);
        my_cursor_list.append(6);

        if (my_cursor_list.front_data() == 1) {
          ++sub_test_count;
        } else {
          return false;
        }

        my_cursor_list.delete_front();
        if (my_cursor_list.front_data() == 2) {
          ++sub_test_count;
        } else {
          return false;
        }

        my_cursor_list.delete_front();
        if (my_cursor_list.front_data() == 3) {
          ++sub_test_count;
        } else {
          return false;
        }

        if (sub_test_count == 3) {
          return true;
        } else {
          return false;
        }
        break;
      }
    case CURSOR_LIST_DELETE_BACK:
      {
        // Test to delete the back node of the cursor list.
        if (verbose) {
          os << "\nCURSOR_LIST_DELETE_BACK:" << std::endl <<
            "Starting the delete back operation:" <<
            std::endl;
        }
        anil::cursor_list my_cursor_list;
        int sub_test_count (0);

        my_cursor_list.append(1);
        my_cursor_list.append(2);
        my_cursor_list.append(3);
        my_cursor_list.append(4);
        my_cursor_list.append(5);
        my_cursor_list.append(6);

        if (my_cursor_list.back_data() == 6) {
          ++sub_test_count;
        } else {
          return false;
        }

        my_cursor_list.delete_back();
        if (my_cursor_list.back_data() == 5) {
          ++sub_test_count;
        } else {
          return false;
        }

        my_cursor_list.delete_back();
        if (my_cursor_list.back_data() == 4) {
          ++sub_test_count;
        } else {
          return false;
        }

        if (sub_test_count == 3) {
          return true;
        } else {
          return false;
        }
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
    default:
      {
        return false;
        break;
      }
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
