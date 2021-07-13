/* This is an implementation of a graph class. In order to standardize the
   result of BFS, this implementation adopts the convention that vertices
   are always processed in sorted order, i.e. by increasing vertex labels.
   In order to store the edges, we use adjacency lists. */

/* TO DO: 1) LEARN HOW TO DO NOTATION FOR GRAPHS AND HOW TO DOCUMENT THEIR RUN TIME*/

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
      int no_of_vertices; // The number of vertices (called the order of the graph).
      int no_of_edges;  // The number of edges (called the size of the graph).
      int most_recent_source_for_BFS; // The label of the vertex that was most recently used as a source for BFS.

      // Functions:
      void delete_graph();

    public:

      // Data:
      enum vertex_color_constants {
        WHITE = -3,
        GRAY,
        BLACK
      };

      const int INFINITY = -1;
      const int UNDEFINED_SOURCE = -1;
      const int UNDEFINED_PREDECESSOR = -1;

      // Functions:
      graph(int no_of_vertices);
      bool is_empty();
      int order_of_graph();
      int size_of_graph();
      int source_vertex();
      int parent_vertex(int child_vertex);
      int distance_to_source(int vertex);
      void path_from_source(cursor_list& path_list, int vertex);
      void delete_edges();
      void add_edge(int vertex_u, int vertex_v);
      void add_arc(int vertex_u, int vertex_v);
      void BFS(int source_vertex);
      friend std::ostream& operator<<(std::ostream& out, graph& rhs); // rhs = right hand side
      ~graph();
  };
}

#endif /* ANIL_GRAPH_H */
