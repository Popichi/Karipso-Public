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
  GRAPH_ADD_EDGE,
  GRAPH_ADD_ARC,
  GRAPH_DELETE_EDGES,
  GRAPH_SIZE_OF_GRAPH,
  GRAPH_BFS,
  GRAPH_SOURCE_VERTEX,
  GRAPH_PARENT_VERTEX,
  GRAPH_DISTANCE_TO_SOURCE,
  GRAPH_PATH_FROM_SOURCE,
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
  "GRAPH_ADD_EDGE",
  "GRAPH_ADD_ARC",
  "GRAPH_DELETE_EDGES",
  "GRAPH_SIZE_OF_GRAPH",
  "GRAPH_BFS",
  "GRAPH_SOURCE_VERTEX",
  "GRAPH_PARENT_VERTEX",
  "GRAPH_DISTANCE_TO_SOURCE",
  "GRAPH_PATH_FROM_SOURCE",
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
        int sub_test_count (0);

        // Sub-test 1
        if (my_graph.is_empty() != false &&
            my_graph.order_of_graph() != 6 &&
            my_graph.size_of_graph() != 0 &&
            my_graph.source_vertex() != anil::graph::UNDEFINED_SOURCE) {
          return false;
        } else {
          ++sub_test_count;
        }

        for (int i = 0; i < my_graph.order_of_graph(); ++i) {
          if (my_graph.parent_vertex(i) != anil::graph::UNDEFINED_PREDECESSOR
              && my_graph.distance_to_source(i) != anil::graph::INFINITY) {
            return false;
          }
        }
        ++sub_test_count;

        // Sub-test 2
        if (sub_test_count == 2) {
          if (verbose) {
            os << "Construction unsuccessful!" << std::endl;
          }
          return true;
        } else {
          if (verbose) {
            os << "Construction successful!" << std::endl;
          }
          return false;
        }

        return false;
        break;
      }
    case GRAPH_IS_EMPTY:
      {
        // Unit test for is_empty() function.
        if (verbose) {
          os << "\nGRAPH_IS_EMPTY:" << std::endl <<
            "Unit test is_empty():" <<
            std::endl;
        }
        anil::graph my_non_empty_graph(6);
        anil::graph my_empty_graph;
        int sub_test_count(0);

        // Sub-test 1
        if (my_non_empty_graph.is_empty() != false) {
          return false;
        } else {
          ++sub_test_count;
        }

        // Sub-test 2
        if (my_empty_graph.is_empty() != true) {
          return false;
        } else {
          ++sub_test_count;
        }
      
        if (sub_test_count == 2) {
          return true;
        } else {
          return false;
        }

        return false;
        break;
      }
    case GRAPH_ORDER_OF_GRAPH:
      {
        // Unit test for order_of_graph() function.
        if (verbose) {
          os << "\nGRAPH_ORDER_OF_GRAPH:" << std::endl <<
            "Unit test order_of_graph():" <<
            std::endl;
        }
        anil::graph my_non_empty_graph(6);
        anil::graph my_empty_graph;
        int sub_test_count(0);

        // Sub-test 1
        if (my_non_empty_graph.order_of_graph() == 6) {
          ++sub_test_count;
        } else {
          return false;
        }

        // Sub-test 2
        if (my_empty_graph.order_of_graph() == 0) {
          ++sub_test_count;
        } else {
          return false;
        }
      
        if (sub_test_count == 2) {
          return true;
        } else {
          return false;
        }

        return false;
        break;
      }
    case GRAPH_ADD_EDGE:
      {
        // Unit test for order_of_graph() function.
        // In this unit test, the following graph is created;
        // 0: 1 3
        // 1: 0 2
        // 2: 1
        // 3: 0

        if (verbose) {
          os << "\nGRAPH_ADD_EDGE:" << std::endl <<
            "Unit test add_edge():" <<
            std::endl;
        }
        anil::graph my_graph(4);

        my_graph.add_edge(0, 1);
        my_graph.add_edge(0, 3);
        my_graph.add_edge(1, 2);
        std::string correct_graph_output_string ("0: 1 3\n1: 0 2\n2: 1\n3: 0");
        char output_line[256];
        std::stringstream output_stream;

        output_stream << my_graph;
        std::string output_operator_output;
        while (output_stream.getline(output_line, 256)) {
          output_operator_output.append(output_line);
          output_stream.peek();
          if (output_stream.eof() != true) {
            output_operator_output.append("\n");
          }
        }

        if (correct_graph_output_string.compare(output_operator_output) != 0) {
          return false;
        }

        return true;
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
