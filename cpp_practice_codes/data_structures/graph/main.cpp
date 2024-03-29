/* This is the test harness for the cursor list data structure
   that I built */

/* TO DO: 1) Learn how to test the deconstructor!
            1-i) Use a shell program to both run the program and valgrind
            1-ii) What about unit testing a deconstructor?
          2) Include a loop for test in the unit test of BFS()!
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
  GRAPH_COPY_CONSTRUCTOR,
  GRAPH_IS_EMPTY,
  GRAPH_ORDER_OF_GRAPH,
  GRAPH_ADD_EDGE,
  GRAPH_ADD_ARC,
  GRAPH_DELETE_EDGES,
  GRAPH_CLEAR,
  GRAPH_INITIALIZE_GRAPH,
  GRAPH_SIZE_OF_GRAPH,
  GRAPH_BFS,
  GRAPH_TRANSPOSE,
  GRAPH_DFS,
  GRAPH_FIND_STRONGLY_CONNECTED_COMPONENTS,
  GRAPH_SOURCE_VERTEX,
  GRAPH_PARENT_VERTEX,
  GRAPH_DISTANCE_TO_SOURCE,
  GRAPH_PATH_FROM_SOURCE,
  GRAPH_INITIAL_DISCOVERY_TIME,
  GRAPH_DISCOVERY_FINISH_TIME,
  GRAPH_OUTPUT_OPERATOR,
  GRAPH_ASSIGNMENT_OPERATOR,
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
  "GRAPH_COPY_CONSTRUCTOR",
  "GRAPH_IS_EMPTY",
  "GRAPH_ORDER_OF_GRAPH",
  "GRAPH_ADD_EDGE",
  "GRAPH_ADD_ARC",
  "GRAPH_DELETE_EDGES",
  "GRAPH_CLEAR",
  "GRAPH_INITIALIZE_GRAPH",
  "GRAPH_SIZE_OF_GRAPH",
  "GRAPH_BFS",
  "GRAPH_TRANSPOSE",
  "GRAPH_DFS",
  "GRAPH_FIND_STRONGLY_CONNECTED_COMPONENTS",
  "GRAPH_SOURCE_VERTEX",
  "GRAPH_PARENT_VERTEX",
  "GRAPH_DISTANCE_TO_SOURCE",
  "GRAPH_PATH_FROM_SOURCE",
  "GRAPH_INITIAL_DISCOVERY_TIME",
  "GRAPH_DISCOVERY_FINISH_TIME",
  "GRAPH_OUTPUT_OPERATOR",
  "GRAPH_ASSIGNMENT_OPERATOR",
  //GRAPH_DELETE_GRAPH,
  //GRAPH_DECONSTRUCTOR,
  "NO_OF_TESTS",
};

bool run_tests(std::ostream& os, int bst_test, bool verbose) {
  switch(bst_test) {
    case GRAPH_CONSTRUCTOR:
      {
        // Unit test for the graph(int no_of_vertices) function.
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
    case GRAPH_COPY_CONSTRUCTOR:
      {
        // Unit test for the copy constructor.
        if (verbose) {
          os << "\nGRAPH_COPY_CONSTRUCTOR:" << std::endl <<
            "Unit test graph(graph& copied_graph):" <<
            std::endl;
        }
        anil::graph my_graph(7);

        my_graph.add_edge(0, 1);
        my_graph.add_edge(0, 2);
        my_graph.add_edge(1, 2);
        my_graph.add_edge(1, 3);
        my_graph.add_edge(2, 3);
        my_graph.add_edge(3, 5);
        my_graph.add_edge(4, 6);
        my_graph.add_edge(5, 6);
        anil::graph my_copy_graph = my_graph;
        
        char output_line[256];
        std::stringstream output_stream;
        std::string correct_graph_output_string ("0: 1 2\n1: 0 2 3\n2: 0 1 3\n3: 1 2 5\n4: 6\n5: 3 6\n6: 4 5");

        output_stream << my_copy_graph;
        std::string output_operator_output;
        while (output_stream.getline(output_line, 256)) {
          output_operator_output.append(output_line);
          output_stream.peek();
          if (output_stream.eof() != true) {
            output_operator_output.append("\n");
          }
        }

        if (correct_graph_output_string.compare(output_operator_output) == 0) {
          return true;
        } else {
          return false;
        }

        break;
      }
    case GRAPH_IS_EMPTY:
      {
        // Unit test for the is_empty() function.
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
        // Unit test for the order_of_graph() function.
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
        // Unit test for the add_edge() function.
        // In this unit test, the following graph is created:
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
    case GRAPH_ADD_ARC:
      {
        // Unit test for add_arc() function.
        // In this unit test, the following directed graph is created:
        // 0: 1 2 3
        // 1: 2
        // 2: 3
        // 3:

        if (verbose) {
          os << "\nGRAPH_ADD_ARC:" << std::endl <<
            "Unit test add_arc():" <<
            std::endl;
        }
        anil::graph my_directed_graph(4);

        my_directed_graph.add_arc(0, 1);
        my_directed_graph.add_arc(0, 2);
        my_directed_graph.add_arc(0, 3);
        my_directed_graph.add_arc(1, 2);
        my_directed_graph.add_arc(2, 3);
        std::string correct_graph_output_string ("0: 1 2 3\n1: 2\n2: 3\n3:");
        char output_line[256];
        std::stringstream output_stream;

        output_stream << my_directed_graph;
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
    case GRAPH_DELETE_EDGES:
      {
        // Unit test for delete_edges() function.
        // In this unit test, the following graph is created:
        // 0: 1 3
        // 1: 0 2
        // 2: 1
        // 3: 0

        if (verbose) {
          os << "\nGRAPH_DELETE_EDGES:" << std::endl <<
            "Unit test delete_edges():" <<
            std::endl;
        }
        anil::graph my_graph(4);
        int sub_test_count(0);

        my_graph.add_edge(0, 1);
        my_graph.add_edge(0, 3);
        my_graph.add_edge(1, 2);

        // Sub-test 1
        if (my_graph.order_of_graph() == 4 && my_graph.size_of_graph() == 3) {
          ++sub_test_count;
        } else {
          return false;
        }

        // Sub-test 2
        my_graph.delete_edges();
        if (my_graph.order_of_graph() == 4 && my_graph.size_of_graph() == 0) {
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
    case GRAPH_CLEAR:
      {
        // Unit test for the clear() function.
        // In this unit test, the following graph is created:
        // 0: 1 3
        // 1: 0 2
        // 2: 1
        // 3: 0

        if (verbose) {
          os << "\nGRAPH_CLEAR:" << std::endl <<
            "Unit test clear():" <<
            std::endl;
        }
        anil::graph my_graph(4);
        int sub_test_count(0);

        my_graph.add_edge(0, 1);
        my_graph.add_edge(0, 3);
        my_graph.add_edge(1, 2);

        // Sub-test 1
        if (my_graph.order_of_graph() == 4 && my_graph.size_of_graph() == 3) {
          ++sub_test_count;
        } else {
          return false;
        }

        // Sub-test 2
        my_graph.clear();
        if (my_graph.order_of_graph() == 0 && my_graph.size_of_graph() == 0) {
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
    case GRAPH_INITIALIZE_GRAPH:
      {
        // Unit test for the initialize_graph() function.
        // In this unit test, the following graph is created:
        // 0: 1 3
        // 1: 0 2
        // 2: 1
        // 3: 0

        if (verbose) {
          os << "\nGRAPH_INITIALIZE_GRAPH:" << std::endl <<
            "Unit test initialize_graph():" <<
            std::endl;
        }
        anil::graph my_graph;
        int sub_test_count(0);

        // Sub-test 1
        if (my_graph.order_of_graph() == 0 && my_graph.size_of_graph() == 0) {
          ++sub_test_count;
        } else {
          return false;
        }

        // Sub-test 2
        my_graph.initialize_graph(4);
        my_graph.add_edge(0, 1);
        my_graph.add_edge(0, 3);
        my_graph.add_edge(1, 2);
        if (my_graph.order_of_graph() == 4 && my_graph.size_of_graph() == 3) {
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
    case GRAPH_SIZE_OF_GRAPH:
      {
        // Unit test for size_of_graph() function. This unit test is exactly
        // the same as the unit test of GRAPH_DELETE_EDGES
        // In this unit test, the following graph is created:
        // 0: 1 3
        // 1: 0 2
        // 2: 1
        // 3: 0

        if (verbose) {
          os << "\nGRAPH_SIZE_OF_GRAPH:" << std::endl <<
            "Unit test size_of_graph():" <<
            std::endl;
        }
        anil::graph my_graph(4);
        int sub_test_count(0);

        my_graph.add_edge(0, 1);
        my_graph.add_edge(0, 3);
        my_graph.add_edge(1, 2);

        // Sub-test 1
        if (my_graph.order_of_graph() == 4 && my_graph.size_of_graph() == 3) {
          ++sub_test_count;
        } else {
          return false;
        }

        // Sub-test 2
        my_graph.delete_edges();
        if (my_graph.order_of_graph() == 4 && my_graph.size_of_graph() == 0) {
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
    case GRAPH_BFS:
      {
        // Unit test for BFS() function.
        // In this unit test, the following graph is created:
        // 0: 1 2
        // 1: 0 2 3
        // 2: 0 1 3
        // 3: 1 2 5
        // 4: 6
        // 5: 3 6
        // 6: 4 5

        if (verbose) {
          os << "\nGRAPH_BFS:" << std::endl <<
            "Unit test BFS():" <<
            std::endl;
        }
        anil::graph my_graph(7);
        int sub_test_count(0);

        my_graph.add_edge(0, 1);
        my_graph.add_edge(0, 2);
        my_graph.add_edge(1, 2);
        my_graph.add_edge(1, 3);
        my_graph.add_edge(2, 3);
        my_graph.add_edge(3, 5);
        my_graph.add_edge(4, 6);
        my_graph.add_edge(5, 6);
        char output_line[256];
        std::stringstream output_stream;

        // Sub-test 1
        std::string correct_graph_output_string ("0: 1 2\n1: 0 2 3\n2: 0 1 3\n3: 1 2 5\n4: 6\n5: 3 6\n6: 4 5");

        output_stream << my_graph;
        std::string output_operator_output;
        while (output_stream.getline(output_line, 256)) {
          output_operator_output.append(output_line);
          output_stream.peek();
          if (output_stream.eof() != true) {
            output_operator_output.append("\n");
          }
        }

        if (correct_graph_output_string.compare(output_operator_output) == 0) {
          ++sub_test_count;
        }

        std::string distance_output;
        std::string path_output;
        anil::cursor_list path_from_source_list;
        std::string path_from_source_string;

        // Sub-test 2
        std::string zero_to_five_path_correct_distance_output ("The distance from 0 to 5 is 3");
        std::string zero_to_five_path_correct_path_output ("A shortest 0-5 path is: 0 1 3 5");
        output_stream.str(""); // Empty the string stream
        output_stream.clear(); // Clear the state of the string stream
        my_graph.bfs(0);
        distance_output = "The distance from " + std::to_string(my_graph.source_vertex()) + " to 5 is " + std::to_string(my_graph.distance_to_source(5));
        my_graph.path_from_source(path_from_source_list, 5);
        output_stream << path_from_source_list;
        output_stream.getline(output_line, 256);
        path_from_source_string.append(output_line);
        path_output = "A shortest " + std::to_string(my_graph.source_vertex()) + "-5 " + "path is: " + path_from_source_string;
        if (zero_to_five_path_correct_distance_output.compare(distance_output) == 0 &&
            zero_to_five_path_correct_path_output.compare(path_output) == 0) {
          ++sub_test_count;
        }
        
        // Sub-test 3
        std::string two_to_two_path_correct_distance_output ("The distance from 2 to 2 is 0");
        std::string two_to_two_path_correct_path_output ("A shortest 2-2 path is: 2");
        distance_output.clear();
        path_output.clear();
        path_from_source_string.clear();
        output_stream.str(""); // Clear to string stream
        output_stream.clear(); // Clear the state of the string stream
        path_from_source_list.clear();
        my_graph.bfs(2);
        distance_output = "The distance from " + std::to_string(my_graph.source_vertex()) + " to 2 is " + std::to_string(my_graph.distance_to_source(2));
        my_graph.path_from_source(path_from_source_list, 2);
        output_stream << path_from_source_list;
        output_stream.getline(output_line, 256);
        path_from_source_string.append(output_line);
        path_output = "A shortest " + std::to_string(my_graph.source_vertex()) + "-2 " + "path is: " + path_from_source_string;
        if (two_to_two_path_correct_distance_output.compare(distance_output) == 0 &&
            two_to_two_path_correct_path_output.compare(path_output) == 0) {
          ++sub_test_count;
        }

        // Sub-test 4
        std::string one_to_four_path_correct_distance_output ("The distance from 1 to 4 is 4");
        std::string one_to_four_path_correct_path_output ("A shortest 1-4 path is: 1 3 5 6 4");
        distance_output.clear();
        path_output.clear();
        path_from_source_string.clear();
        output_stream.str(""); // Clear to string stream
        output_stream.clear(); // Clear the state of the string stream
        path_from_source_list.clear();
        my_graph.bfs(1);
        distance_output = "The distance from " + std::to_string(my_graph.source_vertex()) + " to 4 is " + std::to_string(my_graph.distance_to_source(4));
        my_graph.path_from_source(path_from_source_list, 4);
        output_stream << path_from_source_list;
        output_stream.getline(output_line, 256);
        path_from_source_string.append(output_line);
        path_output = "A shortest " + std::to_string(my_graph.source_vertex()) + "-4 " + "path is: " + path_from_source_string;
        if (one_to_four_path_correct_distance_output.compare(distance_output) == 0 &&
            one_to_four_path_correct_path_output.compare(path_output) == 0) {
          ++sub_test_count;
        }

        if (sub_test_count == 4) {
          return true;
        } else {
          return false;
        }

        break;
      }
    case GRAPH_TRANSPOSE:
      {
        // Unit test for transpose() function.
        // In this unit test, the following directed graph is created:
        // 0: 1
        // 1: 2 4 5
        // 2: 3 6
        // 3: 2 7
        // 4: 0 5
        // 5: 6
        // 6: 5 7
        // 7: 7

        // The transposed graph will be as following:
        // 0: 4
        // 1: 0
        // 2: 1 3
        // 3: 2
        // 4: 1
        // 5: 1 4 6
        // 6: 2 5
        // 7: 3 6 7

        if (verbose) {
          os << "\nGRAPH_TRANSPOSE:" << std::endl <<
            "Unit test transpose():" <<
            std::endl;
        }
        anil::graph my_directed_graph(8);

        my_directed_graph.add_arc(0, 1);
        my_directed_graph.add_arc(1, 2);
        my_directed_graph.add_arc(1, 4);
        my_directed_graph.add_arc(1, 5);
        my_directed_graph.add_arc(2, 3);
        my_directed_graph.add_arc(2, 6);
        my_directed_graph.add_arc(3, 2);
        my_directed_graph.add_arc(3, 7);
        my_directed_graph.add_arc(4, 0);
        my_directed_graph.add_arc(4, 5);
        my_directed_graph.add_arc(5, 6);
        my_directed_graph.add_arc(6, 5);
        my_directed_graph.add_arc(6, 7);
        my_directed_graph.add_arc(7, 7);

        std::string correct_graph_output_string ("0: 4\n1: 0\n2: 1 3\n3: 2\n4: 1\n5: 1 4 6\n6: 2 5\n7: 3 6 7");
        char output_line[256];
        std::stringstream output_stream;

        anil::graph* my_transposed_directed_graph = my_directed_graph.transpose();

        output_stream << *my_transposed_directed_graph;
        std::string output_operator_output;
        while (output_stream.getline(output_line, 256)) {
          output_operator_output.append(output_line);
          output_stream.peek();
          if (output_stream.eof() != true) {
            output_operator_output.append("\n");
          }
        }

        delete my_transposed_directed_graph;

        if (correct_graph_output_string.compare(output_operator_output) == 0) {
          return true;
        } else {
          return false;
        }

        break;
      }
    case GRAPH_DFS:
      {
        // Unit test for dfs() function.
        // In this unit test, the following directed graph is created:
        // 0: 1
        // 1: 2 4 5
        // 2: 3 6
        // 3: 2 7
        // 4: 0 5
        // 5: 6
        // 6: 5 7
        // 7: 7

        // The transposed graph will be as following:
        // 0: 4
        // 1: 0
        // 2: 1 3
        // 3: 2
        // 4: 1
        // 5: 1 4 6
        // 6: 2 5
        // 7: 3 6 7

        // The strongly connected components for this graph are:
        // Component 1: 0 4 1
        // Component 2: 2 3
        // Component 3: 6 5
        // Component 4: 7

        if (verbose) {
          os << "\nGRAPH_DFS:" << std::endl <<
            "Unit test dfs():" <<
            std::endl;
        }
        anil::graph my_directed_graph(8);
        int sub_test_count(0);

        my_directed_graph.add_arc(0, 1);
        my_directed_graph.add_arc(1, 2);
        my_directed_graph.add_arc(1, 4);
        my_directed_graph.add_arc(1, 5);
        my_directed_graph.add_arc(2, 3);
        my_directed_graph.add_arc(2, 6);
        my_directed_graph.add_arc(3, 2);
        my_directed_graph.add_arc(3, 7);
        my_directed_graph.add_arc(4, 0);
        my_directed_graph.add_arc(4, 5);
        my_directed_graph.add_arc(5, 6);
        my_directed_graph.add_arc(6, 5);
        my_directed_graph.add_arc(6, 7);
        my_directed_graph.add_arc(7, 7);

        std::string correct_graph_output_string ("0: 4\n1: 0\n2: 1 3\n3: 2\n4: 1\n5: 1 4 6\n6: 2 5\n7: 3 6 7");
        char output_line[256];
        std::stringstream output_stream;

        anil::graph* my_transposed_directed_graph = my_directed_graph.transpose();

        output_stream << *my_transposed_directed_graph;
        std::string output_operator_output;
        while (output_stream.getline(output_line, 256)) {
          output_operator_output.append(output_line);
          output_stream.peek();
          if (output_stream.eof() != true) {
            output_operator_output.append("\n");
          }
        }

        if (correct_graph_output_string.compare(output_operator_output) == 0) {
          ++sub_test_count;
        }

        delete my_transposed_directed_graph;

        // Sub-test 2

        // We create a list that contains the proper processing order for the
        // vertices of the graph. For example, the correct processing ordering
        // for a graph of order 5 would be; vertex-0, vertex-1, vertex-2, vertex-3
        // vertex-4. So, the list would contain the numbers 0, 1, 2, 3 and 4.
        anil::cursor_list list_of_vertices;
        for (int i = 0; i < my_directed_graph.order_of_graph(); ++i) {
          list_of_vertices.append(i);
        }

        // First call to dfs() is to compute the finishing times for each
        // vertex. After this call, the list 'list_of_vertices' will contain the
        // list of vertices of the graph in decreasing finish times. So, the list
        // of vertices will be topologically sorted.
        my_directed_graph.dfs(list_of_vertices);

        // Correct dfs() output.
        std::string topologically_sorted_vertices ("0 1 4 2 6 5 3 7");
        
        output_stream.str(""); // Empty the string stream
        output_stream.clear(); // Clear the state of the string stream
        output_operator_output = "";
        output_stream << list_of_vertices;
        output_stream.getline(output_line, 256);
        output_operator_output.append(output_line);
        if (topologically_sorted_vertices.compare(output_operator_output) == 0) {
          ++sub_test_count;
        }

        if (sub_test_count == 2) {
          return true;
        } else {
          return false;
        }

        break;
      }
    case GRAPH_FIND_STRONGLY_CONNECTED_COMPONENTS:
      {
        // Unit test for find_strongly_connected_components() function.
        // In this unit test, the following directed graph is created:
        // 0: 1
        // 1: 2 4 5
        // 2: 3 6
        // 3: 2 7
        // 4: 0 5
        // 5: 6
        // 6: 5 7
        // 7: 7

        // The transposed graph will be as following:
        // 0: 4
        // 1: 0
        // 2: 1 3
        // 3: 2
        // 4: 1
        // 5: 1 4 6
        // 6: 2 5
        // 7: 3 6 7

        // The strongly connected components for this graph are:
        // Component 1: 0 4 1
        // Component 2: 2 3
        // Component 3: 6 5
        // Component 4: 7

        if (verbose) {
          os << "\nGRAPH_FIND_STRONGLY_CONNECTED_COMPONENTS:" << std::endl <<
            "Unit test find_strongly_connected_components():" <<
            std::endl;
        }
        anil::graph my_directed_graph(8);
        my_directed_graph.add_arc(0, 1);
        my_directed_graph.add_arc(1, 2);
        my_directed_graph.add_arc(1, 4);
        my_directed_graph.add_arc(1, 5);
        my_directed_graph.add_arc(2, 3);
        my_directed_graph.add_arc(2, 6);
        my_directed_graph.add_arc(3, 2);
        my_directed_graph.add_arc(3, 7);
        my_directed_graph.add_arc(4, 0);
        my_directed_graph.add_arc(4, 5);
        my_directed_graph.add_arc(5, 6);
        my_directed_graph.add_arc(6, 5);
        my_directed_graph.add_arc(6, 7);
        my_directed_graph.add_arc(7, 7);

        std::string correct_strongly_connected_components_output[4] {"0 4 1",
                                                                     "2 3",
                                                                     "6 5",
                                                                     "7"};
        char output_line[256];
        std::stringstream output_stream;
        std::string a_strongly_connected_component;

        std::vector<anil::cursor_list> strongly_connected_components = my_directed_graph.find_strongly_connected_components();

        for (int i = 0; i < 4; ++i) {
          output_stream.str(""); // Empty the string stream
          output_stream.clear(); // Clear the state of the string stream
          a_strongly_connected_component = "";
          output_stream << strongly_connected_components[i];
          output_stream.getline(output_line, 256);
          a_strongly_connected_component.append(output_line);
          if (correct_strongly_connected_components_output[i].compare(a_strongly_connected_component) != 0) {
            return false;
          }
        }

        return true;
        break;
      }
    case GRAPH_SOURCE_VERTEX:
      {
        // Unit test for source_vertex() function.
        // In this unit test, the following graph is created:
        // 0: 1 3
        // 1: 0 2
        // 2: 1
        // 3: 0

        if (verbose) {
          os << "\nGRAPH_SOURCE_VERTEX:" << std::endl <<
            "Unit test source_vertex():" <<
            std::endl;
        }
        anil::graph my_graph(4);
        int sub_test_count(0);

        my_graph.add_edge(0, 1);
        my_graph.add_edge(0, 3);
        my_graph.add_edge(1, 2);

        // Sub-test 1
        my_graph.bfs(3);
        if (my_graph.source_vertex() == 3) {
          ++sub_test_count;
        } else {
          return false;
        }

        // Sub-test 2
        my_graph.bfs(0);
        if (my_graph.source_vertex() == 0) {
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
    case GRAPH_PARENT_VERTEX:
      {
        // Unit test for parent_vertex() function.
        // In this unit test, the following graph is created:
        // 0: 1 3
        // 1: 0 2
        // 2: 1
        // 3: 0

        if (verbose) {
          os << "\nGRAPH_PARENT_VERTEX:" << std::endl <<
            "Unit test parent_vertex():" <<
            std::endl;
        }
        anil::graph my_graph(4);
        int sub_test_count(0);

        my_graph.add_edge(0, 1);
        my_graph.add_edge(0, 3);
        my_graph.add_edge(1, 2);

        // Sub-test 1
        my_graph.bfs(3);
        if (my_graph.parent_vertex(2) == 1) {
          ++sub_test_count;
        } else {
          return false;
        }

        // Sub-test 2
        my_graph.bfs(0);
        if (my_graph.parent_vertex(3) == 0) {
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
    case GRAPH_DISTANCE_TO_SOURCE:
      {
        // Unit test for distance_to_source() function.
        // In this unit test, the following graph is created:
        // 0: 1 3
        // 1: 0 2
        // 2: 1
        // 3: 0

        if (verbose) {
          os << "\nGRAPH_DISTANCE_TO_SOURCE:" << std::endl <<
            "Unit test distance_to_source():" <<
            std::endl;
        }
        anil::graph my_graph(4);
        int sub_test_count(0);

        my_graph.add_edge(0, 1);
        my_graph.add_edge(0, 3);
        my_graph.add_edge(1, 2);

        // Sub-test 1
        my_graph.bfs(3);
        if (my_graph.distance_to_source(2) == 3) {
          ++sub_test_count;
        } else {
          return false;
        }

        // Sub-test 2
        my_graph.bfs(0);
        if (my_graph.distance_to_source(3) == 1) {
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
    case GRAPH_PATH_FROM_SOURCE:
      {
        // Unit test for path_from_source() function.
        // In this unit test, the following graph is created:
        // 0: 1 2
        // 1: 0 2 3
        // 2: 0 1 3
        // 3: 1 2 5
        // 4: 6
        // 5: 3 6
        // 6: 4 5

        if (verbose) {
          os << "\nGRAPH_PATH_FROM_SOURCE:" << std::endl <<
            "Unit test path_from_source():" <<
            std::endl;
        }
        anil::graph my_graph(7);

        my_graph.add_edge(0, 1);
        my_graph.add_edge(0, 2);
        my_graph.add_edge(1, 2);
        my_graph.add_edge(1, 3);
        my_graph.add_edge(2, 3);
        my_graph.add_edge(3, 5);
        my_graph.add_edge(4, 6);
        my_graph.add_edge(5, 6);

        char output_line[256];
        std::stringstream output_stream;
        std::string path_output;
        anil::cursor_list path_from_source_list;
        std::string path_from_source_string;

        std::string zero_to_five_path_correct_path_output ("A shortest 0-5 path is: 0 1 3 5");
        my_graph.bfs(0);
        my_graph.path_from_source(path_from_source_list, 5);
        output_stream << path_from_source_list;
        output_stream.getline(output_line, 256);
        path_from_source_string.append(output_line);
        path_output = "A shortest " + std::to_string(my_graph.source_vertex()) + "-5 " + "path is: " + path_from_source_string;
        if (zero_to_five_path_correct_path_output.compare(path_output) == 0) {
          return true;
        } else {
          return false;
        }

        break;
      }
    case GRAPH_INITIAL_DISCOVERY_TIME:
      {
        // Unit test for initial_discovery_time() function.
        // In this unit test, the following directed graph is created:
        // 0: 1
        // 1: 2 4 5
        // 2: 3 6
        // 3: 2 7
        // 4: 0 5
        // 5: 6
        // 6: 5 7
        // 7: 7

        // The transposed graph will be as following:
        // 0: 4
        // 1: 0
        // 2: 1 3
        // 3: 2
        // 4: 1
        // 5: 1 4 6
        // 6: 2 5
        // 7: 3 6 7

        // The strongly connected components for this graph are:
        // Component 1: 0 4 1
        // Component 2: 2 3
        // Component 3: 6 5
        // Component 4: 7

        // The initial discovery times and discovery finish times for each
        // vertex in the original graph are as follows:
        // 0: 1 / 16
        // 1: 2 / 15
        // 2: 3 / 12
        // 3: 4 / 7
        // 4: 13 / 14
        // 5: 9 / 10
        // 6: 8 / 11
        // 7: 5 / 6

        // The initial discovery times and discovery finish times for each
        // vertex in the transposed graph are as follows:
        // 0: 1 / 6
        // 1: 3 / 4
        // 2: 6 / 9
        // 3: 7 / 8
        // 4: 2 / 5
        // 5: 11 / 12
        // 6: 10 / 13
        // 7: 14 / 15

        if (verbose) {
          os << "\nGRAPH_INITIAL_DISCOVERY_TIME:" << std::endl <<
            "Unit test initial_discovery_time():" <<
            std::endl;
        }
        anil::graph my_directed_graph(8);
        int sub_test_count(0);

        my_directed_graph.add_arc(0, 1);
        my_directed_graph.add_arc(1, 2);
        my_directed_graph.add_arc(1, 4);
        my_directed_graph.add_arc(1, 5);
        my_directed_graph.add_arc(2, 3);
        my_directed_graph.add_arc(2, 6);
        my_directed_graph.add_arc(3, 2);
        my_directed_graph.add_arc(3, 7);
        my_directed_graph.add_arc(4, 0);
        my_directed_graph.add_arc(4, 5);
        my_directed_graph.add_arc(5, 6);
        my_directed_graph.add_arc(6, 5);
        my_directed_graph.add_arc(6, 7);
        my_directed_graph.add_arc(7, 7);

        std::string correct_graph_output_string ("0: 4\n1: 0\n2: 1 3\n3: 2\n4: 1\n5: 1 4 6\n6: 2 5\n7: 3 6 7");
        char output_line[256];
        std::stringstream output_stream;

        anil::graph* my_transposed_directed_graph = my_directed_graph.transpose();

        output_stream << *my_transposed_directed_graph;
        std::string output_operator_output;
        while (output_stream.getline(output_line, 256)) {
          output_operator_output.append(output_line);
          output_stream.peek();
          if (output_stream.eof() != true) {
            output_operator_output.append("\n");
          }
        }

        if (correct_graph_output_string.compare(output_operator_output) == 0) {
          ++sub_test_count;
        }

        // Sub-test 2

        // We create a list that contains the proper processing order for the
        // vertices of the graph. For example, the correct processing ordering
        // for a graph of order 5 would be; vertex-0, vertex-1, vertex-2, vertex-3
        // vertex-4. So, the list would contain the numbers 0, 1, 2, 3 and 4.
        anil::cursor_list list_of_vertices;
        for (int i = 0; i < my_directed_graph.order_of_graph(); ++i) {
          list_of_vertices.append(i);
        }

        // First call to dfs() is to compute the finishing times for each
        // vertex. After this call, the list 'list_of_vertices' will contain the
        // list of vertices of the graph in decreasing finish times. So, the list
        // of vertices will be topologically sorted.
        my_directed_graph.dfs(list_of_vertices);

        if (my_directed_graph.initial_discovery_time(3) == 4) {
          ++sub_test_count;
        } else {
          return false;
        }

        // Sub-test 3
        if (my_directed_graph.initial_discovery_time(5) == 9) {
          ++sub_test_count;
        } else {
          return false;
        }

        delete my_transposed_directed_graph;

        if (sub_test_count == 3) {
          return true;
        } else {
          return false;
        }

        break;
      }
    case GRAPH_DISCOVERY_FINISH_TIME:
      {
        // Unit test for discovery_finish_time() function.
        // In this unit test, the following directed graph is created:
        // 0: 1
        // 1: 2 4 5
        // 2: 3 6
        // 3: 2 7
        // 4: 0 5
        // 5: 6
        // 6: 5 7
        // 7: 7

        // The transposed graph will be as following:
        // 0: 4
        // 1: 0
        // 2: 1 3
        // 3: 2
        // 4: 1
        // 5: 1 4 6
        // 6: 2 5
        // 7: 3 6 7

        // The strongly connected components for this graph are:
        // Component 1: 0 4 1
        // Component 2: 2 3
        // Component 3: 6 5
        // Component 4: 7

        // The initial discovery times and discovery finish times for each
        // vertex in the original graph are as follows:
        // 0: 1 / 16
        // 1: 2 / 15
        // 2: 3 / 12
        // 3: 4 / 7
        // 4: 13 / 14
        // 5: 9 / 10
        // 6: 8 / 11
        // 7: 5 / 6

        // The initial discovery times and discovery finish times for each
        // vertex in the transposed graph are as follows:
        // 0: 1 / 6
        // 1: 3 / 4
        // 2: 6 / 9
        // 3: 7 / 8
        // 4: 2 / 5
        // 5: 11 / 12
        // 6: 10 / 13
        // 7: 14 / 15

        if (verbose) {
          os << "\nGRAPH_DISCOVERY_FINISH_TIME:" << std::endl <<
            "Unit test discovery_finish_time():" <<
            std::endl;
        }
        anil::graph my_directed_graph(8);
        int sub_test_count(0);

        my_directed_graph.add_arc(0, 1);
        my_directed_graph.add_arc(1, 2);
        my_directed_graph.add_arc(1, 4);
        my_directed_graph.add_arc(1, 5);
        my_directed_graph.add_arc(2, 3);
        my_directed_graph.add_arc(2, 6);
        my_directed_graph.add_arc(3, 2);
        my_directed_graph.add_arc(3, 7);
        my_directed_graph.add_arc(4, 0);
        my_directed_graph.add_arc(4, 5);
        my_directed_graph.add_arc(5, 6);
        my_directed_graph.add_arc(6, 5);
        my_directed_graph.add_arc(6, 7);
        my_directed_graph.add_arc(7, 7);

        std::string correct_graph_output_string ("0: 4\n1: 0\n2: 1 3\n3: 2\n4: 1\n5: 1 4 6\n6: 2 5\n7: 3 6 7");
        char output_line[256];
        std::stringstream output_stream;

        anil::graph* my_transposed_directed_graph = my_directed_graph.transpose();

        output_stream << *my_transposed_directed_graph;
        std::string output_operator_output;
        while (output_stream.getline(output_line, 256)) {
          output_operator_output.append(output_line);
          output_stream.peek();
          if (output_stream.eof() != true) {
            output_operator_output.append("\n");
          }
        }

        if (correct_graph_output_string.compare(output_operator_output) == 0) {
          ++sub_test_count;
        }

        // Sub-test 2

        // We create a list that contains the proper processing order for the
        // vertices of the graph. For example, the correct processing ordering
        // for a graph of order 5 would be; vertex-0, vertex-1, vertex-2, vertex-3
        // vertex-4. So, the list would contain the numbers 0, 1, 2, 3 and 4.
        anil::cursor_list list_of_vertices;
        for (int i = 0; i < my_directed_graph.order_of_graph(); ++i) {
          list_of_vertices.append(i);
        }

        // First call to dfs() is to compute the finishing times for each
        // vertex. After this call, the list 'list_of_vertices' will contain the
        // list of vertices of the graph in decreasing finish times. So, the list
        // of vertices will be topologically sorted.
        my_directed_graph.dfs(list_of_vertices);

        if (my_directed_graph.discovery_finish_time(2) == 12) {
          ++sub_test_count;
        } else {
          return false;
        }

        // Sub-test 3
        if (my_directed_graph.discovery_finish_time(7) == 6) {
          ++sub_test_count;
        } else {
          return false;
        }

        delete my_transposed_directed_graph;

        if (sub_test_count == 3) {
          return true;
        } else {
          return false;
        }

        break;
      }
    case GRAPH_OUTPUT_OPERATOR:
      {
        // Unit test for operator<<() function.
        // In this unit test, the following graph is created:
        // 0: 1 2
        // 1: 0 2 3
        // 2: 0 1 3
        // 3: 1 2 5
        // 4: 6
        // 5: 3 6
        // 6: 4 5

        if (verbose) {
          os << "\nGRAPH_OUTPUT_OPERATOR:" << std::endl <<
            "Unit test operator<<():" <<
            std::endl;
        }
        anil::graph my_graph(7);

        my_graph.add_edge(0, 1);
        my_graph.add_edge(0, 2);
        my_graph.add_edge(1, 2);
        my_graph.add_edge(1, 3);
        my_graph.add_edge(2, 3);
        my_graph.add_edge(3, 5);
        my_graph.add_edge(4, 6);
        my_graph.add_edge(5, 6);
        char output_line[256];
        std::stringstream output_stream;

        // Sub-test 1
        std::string correct_graph_output_string ("0: 1 2\n1: 0 2 3\n2: 0 1 3\n3: 1 2 5\n4: 6\n5: 3 6\n6: 4 5");

        output_stream << my_graph;
        std::string output_operator_output;
        while (output_stream.getline(output_line, 256)) {
          output_operator_output.append(output_line);
          output_stream.peek();
          if (output_stream.eof() != true) {
            output_operator_output.append("\n");
          }
        }

        if (correct_graph_output_string.compare(output_operator_output) == 0) {
          return true;
        } else {
          return false;
        }

        break;
      }
    case GRAPH_ASSIGNMENT_OPERATOR:
      {
        // Unit test for the assignment operator.
        if (verbose) {
          os << "\nGRAPH_ASSIGNMENT_OPERATOR:" << std::endl <<
            "Unit test for operator= ():" <<
            std::endl;
        }
        anil::graph my_graph(7);
        anil::graph my_copy_graph;

        my_graph.add_edge(0, 1);
        my_graph.add_edge(0, 2);
        my_graph.add_edge(1, 2);
        my_graph.add_edge(1, 3);
        my_graph.add_edge(2, 3);
        my_graph.add_edge(3, 5);
        my_graph.add_edge(4, 6);
        my_graph.add_edge(5, 6);
        my_copy_graph = my_graph;
        
        char output_line[256];
        std::stringstream output_stream;
        std::string correct_graph_output_string ("0: 1 2\n1: 0 2 3\n2: 0 1 3\n3: 1 2 5\n4: 6\n5: 3 6\n6: 4 5");

        output_stream << my_copy_graph;
        std::string output_operator_output;
        while (output_stream.getline(output_line, 256)) {
          output_operator_output.append(output_line);
          output_stream.peek();
          if (output_stream.eof() != true) {
            output_operator_output.append("\n");
          }
        }

        if (correct_graph_output_string.compare(output_operator_output) == 0) {
          return true;
        } else {
          return false;
        }

        break;
      }
    // case GRAPH_DECONSTRUCTOR:
    //   {s
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
