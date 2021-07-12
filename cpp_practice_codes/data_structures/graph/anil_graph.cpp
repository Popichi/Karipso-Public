/* This is an implementation of a graph class... */

/* TO DO: 1) LEARN HOW TO DO NOTATION FOR GRAPHS AND HOW TO DOCUMENT THEIR RUN TIME*/

#include "anil_graph.h"

/**
 * @param number_of_vertices is the number of vertices in the graph.
 * @brief This constructor creates a new graph that has vertices which equal
 *        to the number_of_vertices parameter. This new graph has no edges
 *        defined.
 * @time complexity: O(n), where n is the number of vertices in the graph.
 *                   All of the vertices are visited once during the initialization.
 * @space complexity: O(n), where n is the number of vertices in the graph.
 * @precondition: number_of_vertices >= 1
 * @author Anil Celik Maral, 2021.07.09  */
anil::graph::graph(int number_of_vertices) {
  this->no_of_vertices = number_of_vertices;
  this->no_of_edges = 0;
  this->most_recent_source_for_BFS = UNDEFINED_SOURCE;
  this->vertices = new cursor_list*[number_of_vertices];
  this->vertex_color = new int[number_of_vertices];
  this->vertex_predecessor = new int[number_of_vertices];
  this->vertex_distance = new int[number_of_vertices];
  for (int i = 0; i < number_of_vertices; ++i) {
    this->vertices[i] = new cursor_list;
    this->vertex_color[i] = WHITE;
    this->vertex_predecessor[i] = UNDEFINED_PREDECESSOR;
    this->vertex_distance[i] = INFINITY;
  }
}

/**
 * @return true if the graph is empty and false if not.
 * @brief This function checks if a graph is empty or not.
 * @time complexity: O(1)
 * @space complexity: O(1)
 * @author Anil Celik Maral, 2021.07.09  */
bool anil::graph::is_empty() {
  return this->no_of_vertices == 0;
}

/**
 * @brief This function returns the order of a graph.
 * @time complexity: O(1)
 * @space complexity: O(1)
 * @author Anil Celik Maral, 2021.07.09  */
int anil::graph::order_of_graph() {
  return this->no_of_vertices;
}

/**
 * @brief This function returns the size of a graph.
 * @time complexity: O(1)
 * @space complexity: O(1)
 * @author Anil Celik Maral, 2021.07.09  */
int anil::graph::size_of_graph() {
  return this->no_of_edges;
}

/**
 * @brief This function returns the most recent source vertex of a graph that
 *        is used by BFS. If BFS hasn't been called yet, then this function
 *        returns UNDEFINED_SOURCE.
 * @time complexity: O(1)
 * @space complexity: O(1)
 * @author Anil Celik Maral, 2021.07.09  */
int anil::graph::source_vertex() {
  return this->most_recent_source_for_BFS;
}

/**
 * @brief This function returns the most recent source vertex of a graph that
 *        is used by BFS. If BFS hasn't been called yet, then this function
 *        returns UNDEFINED_SOURCE.
 * @time complexity: O(1)
 * @space complexity: O(1)
 * @author Anil Celik Maral, 2021.07.09  */
int anil::graph::source_vertex() {
  return this->most_recent_source_for_BFS;
}

/**
 * @param child_vertex is the vertex whose parent we are looking for.
 * @brief If BFS has been called before, this function returns the parent of
 *        the vertex child_vertex in the tree created by BFS. Otherwise,
 *        it will return UNDEFINED_PREDECESSOR.
 * @time complexity: O(1)
 * @space complexity: O(1)
 * @precondition: child_vertex >= 1
 * @author Anil Celik Maral, 2021.07.09  */
int anil::graph::parent_vertex(int child_vertex) {
  if (child_vertex >= 1) {
    return this->vertex_predecessor[child_vertex];
  }
}

/**
 * @param vertex is the vertex whose distance to the most recent BFS source we
 *        are checking.
 * @brief If BFS has been called before and there is a path from source to
 *        the specified vertex, then this function returns the distance
 *        from the source to the specified vertex. If BFS hasn't been called
 *        before or there is no path from source to the vertex, then this
 *        function returns INFINITY.
 * @time complexity: O(1)
 * @space complexity: O(1)
 * @precondition: vertex >= 1
 * @author Anil Celik Maral, 2021.07.09  */
int anil::graph::distance_to_source(int vertex) {
  if (vertex >= 1) {
    return this->vertex_distance[vertex];
  }
}

/**
 * @param vertex is the vertex whose distance to the most recent BFS source we
 *        are checking.
 * @brief If BFS has been called before and there is a path from source to
 *        the specified vertex, then this function returns the distance
 *        from the source to the specified vertex. If BFS hasn't been called
 *        before or there is no path from source to the vertex, then this
 *        function returns INFINITY.
 * @time complexity: O(1)
 * @space complexity: O(1)
 * @precondition: 1 <= vertex && vertex <= this->order_of_graph() &&
 *                this->source_vertex() != INFINITY
 * @author Anil Celik Maral, 2021.07.12  */
void anil::graph::path_from_source(cursor_list& path_list, int vertex) {
  if (1 <= vertex && vertex <= this->order_of_graph() && this->source_vertex() != INFINITY) {
    if (vertex == this->source_vertex()) {
      path_list.append(this->source_vertex());
    } else if (this->vertex_predecessor[vertex] == UNDEFINED_PREDECESSOR) {
      path_list.append(INFINITY);
    } else {
      this->path_from_source(path_list, this->vertex_predecessor[vertex]);
      path_list.append(vertex);
    }
  }
}

/**
 * @brief This function deletes all of the edges of this graph and restores
 *        it to its original (no edge) state.
 * @time complexity: ?
 * @space complexity: ?
 * @precondition: 1 <= vertex && vertex <= this->order_of_graph() &&
 *                this->source_vertex() != INFINITY
 * @author Anil Celik Maral, 2021.07.12  */
void anil::graph::delete_edges() {
  for (int i = 0; i < this->no_of_vertices; ++i) {
    for (this->vertices[i]->move_cursor_front();
         this->vertices[i]->index() >= 0;
         this->vertices[i]->move_cursor_front()) {
      this->vertices[i]->delete_cursor();
    }
  }
}

/**
 * @param vertex_u is the vertex that will be added to the adjacency list of
 *        vertex_v.
 * @param vertex_v is the vertex that will be added to the adjacency list of
 *        vertex_u.
 * @brief This function deletes all of the edges of this graph and restores
 *        it to its original (no edge) state.
 * @time complexity: ?
 * @space complexity: ?
 * @precondition: 1 <= vertex_u && vertex_u <= this->order_of_graph() &&
 *                1 <= vertex_v && vertex_v <= this->order_of_graph()
 * @author Anil Celik Maral, 2021.07.12  */
void anil::graph::add_edge(int vertex_u, int vertex_v) {
  if (1 <= vertex_u && vertex_u <= this->order_of_graph() &&
      1 <= vertex_v && vertex_v <= this->order_of_graph()) {
    // placeholder
  }
}

/**
 * @return void
 * @brief This function deletes every vertex and edge in the graph one by one.
 *        This is a private function.
 * @time complexity: O(n), LEARN HOW TO DO NOTATION FOR GRAPHS AND HOW TO DOCUMENT THEIR RUN TIME.
 * @space complexity: O(1)
 * @precondition: this->is_empty() == false
 * @author Anil Celik Maral, 2021.07.09  */
void anil::graph::delete_graph() {
  if (this->is_empty() == false) {
    for (int i = 0; i < no_of_vertices; ++i) {
      delete this->vertices[i];
      delete this->vertex_color;
      delete this->vertex_predecessor;
      delete this->vertex_distance;
    }
    delete this->vertices;
  }
}

/**
 * @return void
 * @brief This function deletes an entire graph by triggering a
 *        call to delete_graph(), which then iteratively deletes vertex
 *        and edge in the graph.
 * @author Anil Celik Maral, 2021.07.09  */
anil::graph::~graph() {
  delete_graph();
}
