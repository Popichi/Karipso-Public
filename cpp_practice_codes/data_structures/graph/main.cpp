/* This is the test harness for the cursor list data structure
   that I built */

/* TO DO: 1) Learn how to test the deconstructor!
            1-i) Use a shell program to both run the program and valgrind
            1-ii) What about unit testing a deconstructor? 
*/

#include "anil_graph.h"
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
enum graph_tests {
  GRAPH_CONSTRUCTOR,
  GRAPH_IS_EMPTY,
  GRAPH_ORDER_OF_GRAPH,
  GRAPH_SIZE_OF_GRAPH,
  GRAPH_SOURCE_VERTEX,
  GRAPH_PARENT_VERTEX,
  GRAPH_DISTANCE_TO_SOURCE,
  GRAPH_PATH_FROM_SOURCE,
  GRAPH_DELETE_EDGES,
  GRAPH_ADD_EDGE,
  GRAPH_ADD_ARC,
  GRAPH_BFS,
  GRAPH_OUTPUT_OPERATOR,
  //GRAPH_DELETE_GRAPH,
  //GRAPH_DECONSTRUCTOR,
  NO_OF_TESTS,
};

// The following array of strings associate enumeration values of tests
// declared in the enumeration 'graph_tests' with their string
// equivalents. For example, 
// 'std::cout<<graph_test_names[GRAPH_CONSTRUCTOR];'
// will print 'GRAPH_CONSTRUCTOR' as expected. This makes
// reporting and logging easier.
static const char* graph_test_names[] = {
  "GRAPH_CONSTRUCTOR",
  "GRAPH_IS_EMPTY",
  "GRAPH_ORDER_OF_GRAPH",
  "GRAPH_SIZE_OF_GRAPH",
  "GRAPH_SOURCE_VERTEX",
  "GRAPH_PARENT_VERTEX",
  "GRAPH_DISTANCE_TO_SOURCE",
  "GRAPH_PATH_FROM_SOURCE",
  "GRAPH_DELETE_EDGES",
  "GRAPH_ADD_EDGE",
  "GRAPH_ADD_ARC",
  "GRAPH_BFS",
  "GRAPH_OUTPUT_OPERATOR",
  //GRAPH_DELETE_GRAPH,
  //GRAPH_DECONSTRUCTOR,
  "NO_OF_TESTS",
};

bool run_tests(std::ostream& os, int bst_test, bool verbose) {
  switch(bst_test) {
    case GRAPH_CONSTRUCTOR:
      {
        // Test to construct a graph.
        if (verbose) {
          os << "\nGRAPH_CONSTRUCTOR:" << std::endl <<
            "Starting the construction operation:" <<
            std::endl;
        }
        anil::graph my_graph(6);
        if (my_graph.order_of_graph() != 6 &&
            my_graph.size_of_graph() != 0 &&
            my_graph.source_vertex() != anil::graph::UNDEFINED_SOURCE) {
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
    case GRAPH_IS_EMPTY:
      {
        // Test to delete the cursor node of the cursor list.
        if (verbose) {
          os << "\nCURSOR_LIST_DELETE_CURSOR:" << std::endl <<
            "Starting the delete cursor operation:" <<
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
        my_cursor_list.delete_cursor();
        if (my_cursor_list.back_data() == 5 && my_cursor_list.index() == -1) {
          ++sub_test_count;
        } else {
          return false;
        }

        my_cursor_list.move_cursor_front();
        my_cursor_list.delete_cursor();
        if (my_cursor_list.front_data() == 2) {
          ++sub_test_count;
        } else {
          return false;
        }

        my_cursor_list.move_cursor_front();
        my_cursor_list.move_cursor_next();
        my_cursor_list.move_cursor_next();
        my_cursor_list.delete_cursor(); // delete 4
        my_cursor_list.move_cursor_front();
        my_cursor_list.move_cursor_next();
        if (my_cursor_list.front_data() == 2 &&
            my_cursor_list.cursor_data() == 3 &&
            my_cursor_list.back_data() == 5) {
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
    // case GRAPH_DECONSTRUCTOR:
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
    std::cout << "Usage: ./graph [-v]"  << std::endl;
    return 1;
  } else if (argc == 2 and strcmp(argv[1], "-v") == 0) {
    verbose = true;
  }

  std::ofstream log_file ("graph_log.txt", std::ios::trunc);
  if (!log_file.is_open()) {
    std::cout << "There was a problem opening 'graph_log.txt'" <<
      std::endl;
  }

  int no_of_tests_passed {0};

  for (int i = GRAPH_CONSTRUCTOR; i < NO_OF_TESTS; ++i) {
    bool test_result = run_tests(log_file, i, verbose);
    log_file << "Test " << graph_test_names[i] << ": " <<
      (test_result == true ? "PASSED" : "FAILED") << std::endl;
    if (test_result) { ++no_of_tests_passed; }
  }

  log_file << no_of_tests_passed << "/" << NO_OF_TESTS <<
    " tests were passed." << std::endl;

  log_file.close();

  return 0;
}
