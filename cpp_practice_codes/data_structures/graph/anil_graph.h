/* This is an implementation of a graph class... . */

/* TO DO: */

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

      enum vertex_color_constants {
        WHITE = -3,
        GRAY,
        BLACK
      };

      const int INFINITY = -1;
      
      const int UNDEFINED_SOURCE = -1;

      // Functions:

    public:
      graph() : vertices(nullptr), vertex_color(nullptr),
                vertex_predecessor(nullptr), vertex_distance(nullptr),
                no_of_vertices(0), no_of_edges(0),
                most_recent_source_for_BFS(UNDEFINED_SOURCE) {}
      ~graph();
  };
}

#endif /* ANIL_GRAPH_H */
