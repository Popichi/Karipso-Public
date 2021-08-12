/* This is an implementation of a graph class. In order to standardize the
   result of Breadth-First Search and Depth-First Search, this implementation
   adopts the convention that vertices are always processed in a sorted order
   by increasing vertex labels. In order to store the edges, we use adjacency
   lists. */

/* TO DO: 1) LEARN HOW TO DO NOTATION FOR GRAPHS AND HOW TO DOCUMENT THEIR RUN TIME!
             Then, post your analyses online (stackoverflow etc.) to confirm them.
          2) Can graph labelings start from 0 or does it have to start from 1? */

#ifndef ANIL_GRAPH_H
#define ANIL_GRAPH_H

#include <cstddef>
#include <iostream>
#include "anil_cursor_list.h"

namespace anil {
  class graph {
    private:

      // Data:
      cursor_list** vertices; // An array of cursor_lists whose ith element contains the neighbors of vertex i.
      int* vertex_color;  // An array of int whose ith element is the color (white, gray, black) of vertex i.
      int* vertex_predecessor; // An array of ints whose ith element is the parent of vertex i.
      int* vertex_distance; // An array of ints whose ith element is the distance from the most recent source to vertex i.
      int* vertex_initial_discovery_time; // An array of ints whose ith element is the initial discovery time of vertex i.
      int* vertex_discovery_finish_time; // An array of ints whose ith element is the discovery finish / completion time of vertex i.
      int no_of_vertices; // The number of vertices (called the order of the graph).
      int no_of_edges;  // The number of edges (called the size of the graph).
      int most_recent_source_for_bfs; // The label of the vertex that was most recently used as a source for BFS.
      int vertex_time_counter;

      // Functions:
      void delete_graph();
      void dfs_visit(int vertex, anil::cursor_list& topologically_sorted_vertices);

    public:

      // Data:
      enum vertex_color_constants {
        WHITE = -3,
        GRAY,
        BLACK
      };

      static const int INFINITY = -1;
      static const int UNDEFINED_SOURCE = -1;
      static const int UNDEFINED_PREDECESSOR = -1;
      static const int UNDEFINED_INITIAL_DISCOVERY_TIME = -1;
      static const int UNDEFINED_DISCOVERY_FINISH_TIME = -1;

      // Functions:
      graph() : vertices(nullptr), vertex_color(nullptr),
        vertex_predecessor(nullptr), vertex_distance(nullptr),
        vertex_initial_discovery_time(nullptr),
        vertex_discovery_finish_time(nullptr),
        no_of_vertices(0), no_of_edges(0),
        most_recent_source_for_bfs(UNDEFINED_SOURCE), vertex_time_counter(0) {}
      graph(int no_of_vertices);
      graph(graph& copied_graph);
      bool is_empty();
      int order_of_graph();
      int size_of_graph();
      int source_vertex();
      int parent_vertex(int child_vertex);
      int distance_to_source(int vertex);
      int initial_discovery_time(int vertex); // +
      int discovery_finish_time(int vertex);  // +
      void path_from_source(cursor_list& path_list, int vertex);
      void delete_edges();
      void clear(); // +
      void initialize_graph(int no_of_vertices);
      void add_edge(int vertex_u, int vertex_v);
      void add_arc(int vertex_u, int vertex_v);
      void bfs(int source_vertex);  // Breadth-First Search
      void dfs(anil::cursor_list& list_of_vertices); // Depth-First Side, +
      anil::cursor_list** find_strongly_connected_components(); // +
      anil::graph* transpose();  // +
      graph& operator= (graph& rhs);  // rhs = right hand side, +
      friend std::ostream& operator<<(std::ostream& out, graph& rhs); // rhs = right hand side
      ~graph();
  };
}

#endif /* ANIL_GRAPH_H */
