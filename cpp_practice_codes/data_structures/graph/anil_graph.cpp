/* This is an implementation of a graph class. In order to standardize the
   result of BFS, this implementation adopts the convention that vertices
   are always processed in sorted order, i.e. by increasing vertex labels.
   In order to store the edges, we use adjacency lists. */

/* TO DO: 1) LEARN HOW TO DO NOTATION FOR GRAPHS AND HOW TO DOCUMENT THEIR RUN TIME
          2) Can graph labelings start from 0 or does it have to start from 1? */

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
 * @brief This function returns the order of a graph (number of vertices
 *        in a graph).
 * @time complexity: O(1)
 * @space complexity: O(1)
 * @author Anil Celik Maral, 2021.07.09  */
int anil::graph::order_of_graph() {
  return this->no_of_vertices;
}

/**
 * @brief This function returns the size of a graph (number edges in a graph).
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

// /**
//  * @brief This function returns the most recent source vertex of a graph that
//  *        is used by BFS. If BFS hasn't been called yet, then this function
//  *        returns UNDEFINED_SOURCE.
//  * @time complexity: O(1)
//  * @space complexity: O(1)
//  * @author Anil Celik Maral, 2021.07.09  */
// int anil::graph::source_vertex() {
//   return this->most_recent_source_for_BFS;
// }

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
  if (child_vertex >= 0) {
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
  if (vertex >= 0) {
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
  if (0 <= vertex && vertex < this->order_of_graph() &&
      this->source_vertex() != INFINITY) {
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
  this->no_of_edges = 0;
}

/**
 * @param vertex_u is the vertex that will be added to the adjacency list of
 *        vertex_v.
 * @param vertex_v is the vertex that will be added to the adjacency list of
 *        vertex_u.
 * @brief This function inserts a new edge joining vertex_u to vertex_v,
 *        i.e. vertex_u is added to the adjacency list of vertex_v, and
 *        vertex_v to the adjacency list of vertex_u. The insertion is made
 *        such that the adjacency lists of both vertex_u and vertex_v are
 *        sorted in an increasing order i.e. vertex with the greatest label
 *        is the last element in a adjacency list.
 * @time complexity: ?
 * @space complexity: ?
 * @precondition: 1 <= vertex_u && vertex_u <= this->order_of_graph() &&
 *                1 <= vertex_v && vertex_v <= this->order_of_graph()
 * @author Anil Celik Maral, 2021.07.12  */
void anil::graph::add_edge(int vertex_u, int vertex_v) {
  if (0 <= vertex_u && vertex_u < this->order_of_graph() &&
      0 <= vertex_v && vertex_v < this->order_of_graph()) {

    // Check if there are any vertices with labels greater than vertex_v in
    // vertex_u's adjacency list.
    for (this->vertices[vertex_u]->move_cursor_front();
         this->vertices[vertex_u]->index() >= 0;
         this->vertices[vertex_u]->move_cursor_next()) {
      if (this->vertices[vertex_u]->cursor_data() > vertex_v) {
        break;  
      }
    }

    // Insertion for when there is a vertex with a greater label than vertex_v.
    if (this->vertices[vertex_u]->index() >= 0) {
      this->vertices[vertex_u]->insert_before_cursor(vertex_v);

    // Insertion for when there isn't a vertex with a greater label than
    // vertex_v or when there are no vertices at all.
    } else {
      this->vertices[vertex_u]->append(vertex_v);
    }

    // Check if there are any vertices with labels greater than vertex_u in
    // vertex_v's adjacency list.
    for (this->vertices[vertex_v]->move_cursor_front();
         this->vertices[vertex_v]->index() >= 0;
         this->vertices[vertex_v]->move_cursor_next()) {
      if (this->vertices[vertex_v]->cursor_data() > vertex_u) {
        break;  
      }
    }

    // Insertion for when there is a vertex with a greater label than vertex_u.
    if (this->vertices[vertex_v]->index() >= 0) {
      this->vertices[vertex_v]->insert_before_cursor(vertex_u);

    // Insertion for when there isn't a vertex with a greater label than
    // vertex_u or when there are no vertices at all.
    } else {
      this->vertices[vertex_v]->append(vertex_u);
    }
    ++this->no_of_edges;
  }
}

/**
 * @param vertex_u is the vertex whose adjacency list vertex_u will be
 *        added to.
 * @param vertex_v is the vertex that will be added to the adjacency list of
 *        vertex_u.
 * @brief This function inserts a new directed edge from vertex_u to vertex_v,
 *        i.e. vertex_v is added to the adjacency list of vertex_u (but not
 *        vertex_u to the adjacency list of vertex_v). The insertion is made
 *        such that the adjacency list of vertex_u is sorted in an increasing
 *        order i.e. vertex with the greatest label is the last element in the
 *        adjacency list.
 * @time complexity: ?
 * @space complexity: ?
 * @precondition: 1 <= vertex_u && vertex_u <= this->order_of_graph() &&
 *                1 <= vertex_v && vertex_v <= this->order_of_graph()
 * @author Anil Celik Maral, 2021.07.12  */
void anil::graph::add_arc(int vertex_u, int vertex_v) {
  if (0 <= vertex_u && vertex_u < this->order_of_graph() &&
      0 <= vertex_v && vertex_v < this->order_of_graph()) {

    // Check if there are any vertices with labels greater than vertex_v in
    // vertex_u's adjacency list.
    for (this->vertices[vertex_u]->move_cursor_front();
         this->vertices[vertex_u]->index() >= 0;
         this->vertices[vertex_u]->move_cursor_next()) {
      if (this->vertices[vertex_u]->cursor_data() > vertex_v) {
        break;  
      }
    }

    // Insertion for when there is a vertex with a greater label than vertex_v.
    if (this->vertices[vertex_u]->index() >= 0) {
      this->vertices[vertex_u]->insert_before_cursor(vertex_v);

    // Insertion for when there isn't a vertex with a greater label than
    // vertex_v or when there are no vertices at all.
    } else {
      this->vertices[vertex_u]->append(vertex_v);
    }
    ++this->no_of_edges;
  }
}

/**
 * @param source_vertex is the vertex that BFS uses as the root of the tree
 *        that it creates while discovering a graph.
 * @brief This function runs the BFS Algorithm on the given graph with source
 *        source_vertex while setting the vertex_color, vertex_distance,
 *        vertex_predecessor and most_recent_source_for_BFS fields of the
 *        graph accordingly.
 * @time complexity: ?
 * @space complexity: ?
 * @credit: The BFS algorithm is taken from page 595 of 3rd edition of CLRS.
 * @author Anil Celik Maral, 2021.07.12  */
void anil::graph::BFS(int source_vertex) {
  for (int i = 0; i < this->no_of_vertices; ++i) {
    if (i != source_vertex) {
      this->vertex_color[i] = WHITE;
      this->vertex_distance[i] = INFINITY;
      this->vertex_predecessor[i] = UNDEFINED_PREDECESSOR;
    }
  }

  this->vertex_color[source_vertex] = GRAY;
  this->vertex_distance[source_vertex] = 0;
  this->vertex_predecessor[source_vertex] = UNDEFINED_PREDECESSOR;
  this->most_recent_source_for_BFS = source_vertex;
  cursor_list priority_queue;
  priority_queue.append(source_vertex);
  while (priority_queue.size()) {
    priority_queue.move_cursor_front();
    int investigated_vertex = priority_queue.cursor_data();
    priority_queue.delete_cursor();
    for (this->vertices[investigated_vertex]->move_cursor_front();
         this->vertices[investigated_vertex]->index() >= 0;
         this->vertices[investigated_vertex]->move_cursor_next()) {
      if (this->vertex_color[this->vertices[investigated_vertex]->cursor_data()] == WHITE) {
        this->vertex_color[this->vertices[investigated_vertex]->cursor_data()] = GRAY;
        this->vertex_distance[this->vertices[investigated_vertex]->cursor_data()] = this->vertex_distance[investigated_vertex] + 1;
        this->vertex_predecessor[this->vertices[investigated_vertex]->cursor_data()] = investigated_vertex;
        priority_queue.append(this->vertices[investigated_vertex]->cursor_data());
      }
    }
    this->vertex_color[investigated_vertex] = BLACK;
  }
}

/**
 * @return an ostream reference so that we can chain this operation.
 * @param out is the reference to the output stream that we are printing this
 *        graph to.
 * @param rhs is the graph whose adjacency list representation we are printing.
 * @brief This function prints the adjacency list representation of this graph
 *        to the output stream specified by out. The printing format is as
 *        following:
 *        vertex-1: vertex-2 vertex-4
 *        vertex-2: vertex-1 vertex-3
 *        vertex-3: vertex-2
 *        vertex-4: vertex-1
 * @time complexity: ?
 * @space complexity: ?
 * @precondition: rhs.is_empty() != false
 * @author Anil Celik Maral, 2021.07.13  */
namespace anil {
  std::ostream& operator<<(std::ostream& out, graph& rhs) {
    if (rhs.is_empty() == false) {
      for (int i = 0; i < rhs.no_of_vertices; ++i) {
        out << i << ':';
        for (rhs.vertices[i]->move_cursor_front();
             rhs.vertices[i]->index() >= 0;
             rhs.vertices[i]->move_cursor_next()) {
          out << ' ' << rhs.vertices[i]->cursor_data();
        }
        out << std::endl;
      }
    }
    return out;
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
    }
    delete[] this->vertex_color;
    delete[] this->vertex_predecessor;
    delete[] this->vertex_distance;
    delete[] this->vertices;
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
