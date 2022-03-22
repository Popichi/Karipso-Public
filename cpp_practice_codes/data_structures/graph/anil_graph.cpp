/* This is an implementation of a graph class. In order to standardize the
   result of Breadth-First Search (BFS) and Depth-First Search (DFS), this
   implementation adopts the convention that vertices are always processed
   in a sorted order by increasing vertex labels. In order to store the
   edges, we use adjacency lists. */

/* TO DO: 1) LEARN HOW TO DO NOTATION FOR GRAPHS AND HOW TO DOCUMENT THEIR RUN TIME!
             Then, post your analyses online (stackoverflow etc.) to confirm them.
          2) Can graph labelings start from 0 or does it have to start from 1?
          3) Verify the time and space complexities marked by "???" */

#include "anil_graph.h"

/**
 * @param number_of_vertices is the number of vertices in the graph.
 * @brief This constructor creates a new graph that has vertices which equal
 *        to the number_of_vertices parameter. This new graph has no edges
 *        defined.
 * @time complexity: O(V) because the main for loop repeats for |V|.
 * @space complexity: "For both directed and undirected graphs, the 
 *                    adjacency-list representation has the desirable property 
 *                    that the amount of memory it requires is O(V + E)". 
 *                    (CLRS, 3rd Edition, Page 590) However, since initially a 
 *                    graph contains no edges this boils down to O(V). 
 *                    Although we store other information such as the color of 
 *                    each vertex, these arrays are V in length and O(2V), 
 *                    O(3V) ... O(XV) are all equal to O(V).
 * @precondition: number_of_vertices >= 1
 * @author Anil Celik Maral, 2021.07.09
 * @update Anil Celik Maral, 2021.08.06
 * @update Anil Celik Maral, 2021.12.05  */
anil::graph::graph(int number_of_vertices) {
  this->no_of_vertices = number_of_vertices;
  this->no_of_edges = 0;
  this->most_recent_source_for_bfs = UNDEFINED_SOURCE;
  this->vertex_time_counter = 0;
  this->vertices = new cursor_list*[number_of_vertices];
  this->vertex_color = new int[number_of_vertices];
  this->vertex_predecessor = new int[number_of_vertices];
  this->vertex_distance = new int[number_of_vertices];
  this->vertex_initial_discovery_time = new int[number_of_vertices];
  this->vertex_discovery_finish_time = new int[number_of_vertices];  
  for (int i = 0; i < number_of_vertices; ++i) {
    this->vertices[i] = new cursor_list;
    this->vertex_color[i] = WHITE;
    this->vertex_predecessor[i] = UNDEFINED_PREDECESSOR;
    this->vertex_distance[i] = INFINITY;
    this->vertex_initial_discovery_time[i] = UNDEFINED_INITIAL_DISCOVERY_TIME;
    this->vertex_discovery_finish_time[i] = UNDEFINED_DISCOVERY_FINISH_TIME;
  }
}

/**
 * @param copied_graph is the graph that will be copied / assigned onto a new
 *        graph.
 * @brief This copy constructor copies the graph and all of its contents
 *        referenced by the parameter copied_graph onto a new graph. After
 *        the copying, these graph are identical.
 * @time complexity: O(V + E) because the main for loop repeats for |V| and 
 *                   the second for loop traverses the adjacency list of Vi 
 *                   which means, in total, it traverses the adjacency list 
 *                   of each vertex and this sums up to |E|.???
 * @space complexity: "For both directed and undirected graphs, the 
 *                    adjacency-list representation has the desirable property 
 *                    that the amount of memory it requires is O(V + E)". 
 *                    (CLRS, 3rd Edition, Page 590) We store the vertices and 
 *                    their adjacency lists. Although we store other 
 *                    information such as the color of each vertex, these 
 *                    arrays are V in length and O(2V), O(3V) ... O(XV) are 
 *                    all equal to O(V).???
 * @precondition: copied_graph.is_empty() == false
 * @author Anil Celik Maral, 2021.08.09
 * @update Anil Celik Maral, 2021.12.05  */
anil::graph::graph(graph& copied_graph) {
  if (copied_graph.is_empty() == false) {
    this->no_of_vertices = copied_graph.no_of_vertices;
    this->no_of_edges = copied_graph.no_of_edges;
    this->most_recent_source_for_bfs = copied_graph.most_recent_source_for_bfs;
    this->vertex_time_counter = copied_graph.vertex_time_counter;
    this->vertices = new cursor_list*[copied_graph.no_of_vertices];
    this->vertex_color = new int[copied_graph.no_of_vertices];
    this->vertex_predecessor = new int[copied_graph.no_of_vertices];
    this->vertex_distance = new int[copied_graph.no_of_vertices];
    this->vertex_initial_discovery_time = new int[copied_graph.no_of_vertices];
    this->vertex_discovery_finish_time = new int[copied_graph.no_of_vertices]; 
    for (int i = 0; i < copied_graph.no_of_vertices; ++i) {
      this->vertices[i] = new cursor_list;
      copied_graph.vertices[i]->save_cursor_state();
      for (copied_graph.vertices[i]->move_cursor_front();
          copied_graph.vertices[i]->index() >= 0;
          copied_graph.vertices[i]->move_cursor_next()) {
        this->vertices[i]->append(copied_graph.vertices[i]->cursor_data());
      }
      copied_graph.vertices[i]->restore_cursor_state();

      this->vertex_color[i] = copied_graph.vertex_color[i];
      this->vertex_predecessor[i] = copied_graph.vertex_predecessor[i];
      this->vertex_distance[i] = copied_graph.vertex_distance[i];
      this->vertex_initial_discovery_time[i] =
        copied_graph.vertex_initial_discovery_time[i];
      this->vertex_discovery_finish_time[i] =
        copied_graph.vertex_discovery_finish_time[i];
    }
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
 *        is used by bfs(). If bfs() hasn't been called yet, then this function
 *        returns UNDEFINED_SOURCE.
 * @time complexity: O(1)
 * @space complexity: O(1)
 * @author Anil Celik Maral, 2021.07.09  */
int anil::graph::source_vertex() {
  return this->most_recent_source_for_bfs;
}

/**
 * @param child_vertex is the vertex whose parent we are looking for.
 * @brief If bfs() has been called before, this function returns the parent of
 *        the vertex child_vertex in the tree created by bfs(). Otherwise,
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
 * @brief If bfs() has been called before, and there is a path from source to
 *        the specified vertex, then this function returns the distance
 *        from the source to the specified vertex. If bfs() hasn't been called
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
 * @param vertex is the vertex whose initial discovery time
 *        - that was set during DFS - we are checking.
 * @brief If dfs() has been called before, this function returns the initial
 *        discovery time of the specified vertex discovered by the DFS
 *        algorithm. If dfs() hasn't been called before function returns
 *        UNDEFINED_INITIAL_DISCOVERY_TIME.
 * @time complexity: O(1)
 * @space complexity: O(1)
 * @precondition: vertex >= 1
 * @author Anil Celik Maral, 2021.08.03  */
int anil::graph::initial_discovery_time(int vertex) {
  if (vertex >= 0) {
    return this->vertex_initial_discovery_time[vertex];
  }
}

/**
 * @param vertex is the vertex whose discovery finish / completion time
 *        - that was set during DFS - we are checking.
 * @brief If dfs() has been called before, this function returns the discovery
 *        finish time of the specified vertex whose discovery was completed by
 *        the DFS algorithm. If dfs() hasn't been called before function
 *        returns UNDEFINED_DISCOVERY_FINISH_TIME.
 * @time complexity: O(1)
 * @space complexity: O(1)
 * @precondition: vertex >= 1
 * @author Anil Celik Maral, 2021.08.03  */
int anil::graph::discovery_finish_time(int vertex) {
  if (vertex >= 0) {
    return this->vertex_discovery_finish_time[vertex];
  }
}

/**
 * @param vertex is the vertex we check to see if there is a path from the 
 *        most recent BFS source to it.
 * @brief If bfs() has been called before and there is a path from source to
 *        the specified vertex, then this function returns the list of 
 *        vertices, which includes the source vertex and the vertex that we 
 *        are trying to reach, that needs to be traced in order to get to the 
 *        vertex we are trying to reach. If bfs() hasn't been called before or 
 *        there is no path from source to the vertex, then this function 
 *        appends a single element with the value INFINITY to the list and 
 *        returns this single element list.
 * @time complexity: In the worst case scenario, we must traverse all of the 
 *                   vertices to go from the source to the specified vertex. 
 *                   This happens when to go from the source to specified 
 *                   vertex, you must first visit all of the other vertices.
 *                   Therefore, the worst case run time for this algorithm is
 *                   O(V).???
 * @space complexity: In the worst case scenario, we must traverse all of the 
 *                    vertices to go from the source to the specified vertex. 
 *                    This happens when to go from the source to specified 
 *                    vertex, you must first visit all of the other vertices. 
 *                    Therefore, memory required in the worst case of this 
 *                    algorithm is O(V).???
 * @precondition: 0 <= vertex && vertex <= this->order_of_graph() &&
 *                this->source_vertex() != INFINITY
 * @author Anil Celik Maral, 2021.07.12
 * @update Anil Celik Maral, 2022.03.22  */
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
 * @return void
 * @brief This function deletes every vertex and edge in the graph one by one
 *        and resets the graph to its uninitialized state (similar to a graph
 *        created by using the constructor graph()).
 * @time complexity: ?
 * @space complexity: ?
 * @precondition: this->is_empty() == false
 * @author Anil Celik Maral, 2021.08.06  */
void anil::graph::clear() {
  if (this->is_empty() == false) {
    for (int i = 0; i < no_of_vertices; ++i) {
      delete this->vertices[i];
    }
    delete[] this->vertex_color;
    delete[] this->vertex_predecessor;
    delete[] this->vertex_distance;
    delete[] this->vertex_initial_discovery_time;
    delete[] this->vertex_discovery_finish_time;
    delete[] this->vertices;
    this->no_of_vertices = 0;
    this->no_of_edges = 0;
    this->most_recent_source_for_bfs = UNDEFINED_SOURCE;
    this->vertex_time_counter = 0;
  }
}

/**
 * @param number_of_vertices is the number of vertices in the graph.
 * @brief This function initializes an empty graph. The state of the
 *        graph after a call to this function is similar to that of
 *        a graph which was created by using the constructor
 *        grap(int no_of_vertices).
 * @time complexity: ?
 * @space complexity: ?
 * @precondition: number_of_vertices >= 1 && this->is_empty() == true
 * @author Anil Celik Maral, 2021.08.06 */
void anil::graph::initialize_graph(int number_of_vertices) {
  if (number_of_vertices >= 1 && this->is_empty() == true) {
    this->no_of_vertices = number_of_vertices;
    this->no_of_edges = 0;
    this->most_recent_source_for_bfs = UNDEFINED_SOURCE;
    this->vertex_time_counter = 0;
    this->vertices = new cursor_list*[number_of_vertices];
    this->vertex_color = new int[number_of_vertices];
    this->vertex_predecessor = new int[number_of_vertices];
    this->vertex_distance = new int[number_of_vertices];
    this->vertex_initial_discovery_time = new int[number_of_vertices];
    this->vertex_discovery_finish_time = new int[number_of_vertices]; 
    for (int i = 0; i < number_of_vertices; ++i) {
      this->vertices[i] = new cursor_list;
      this->vertex_color[i] = WHITE;
      this->vertex_predecessor[i] = UNDEFINED_PREDECESSOR;
      this->vertex_distance[i] = INFINITY;
      this->vertex_initial_discovery_time[i] =
        UNDEFINED_INITIAL_DISCOVERY_TIME;
      this->vertex_discovery_finish_time[i] = UNDEFINED_DISCOVERY_FINISH_TIME;
    }
  }
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
 * @param source_vertex is the vertex that bfs() uses as the root of the tree
 *        that it creates while discovering a graph.
 * @brief This function runs the bfs() algorithm on the given graph with source
 *        source_vertex while setting the vertex_color, vertex_distance,
 *        vertex_predecessor and most_recent_source_for_bfs fields of the
 *        graph accordingly.
 * @time complexity: O(V + E)
 *                   "Before proving the various properties of breadth-first
 *                   search, we take on the somewhat easier job of analyzing
 *                   its running time on an input graph G = (V, E). We use
 *                   aggregate analysis, as we saw in Section 17.1. After
 *                   initialization, breadth-first search never whitens a
 *                   vertex, and thus the test in line 13 ensures that each
 *                   vertex is enqueued at most once, and hence dequeued at
 *                   most once. The operations of enqueuing and dequeuing take
 *                   O(1) time, and so the total time devoted to queue
 *                   operations is O(V). Because the procedure scans the
 *                   adjacency list of each vertex only when the vertex is
 *                   dequeued, it scans each adjacency list at most once. Since
 *                   the sum of the lengths of all the adjacency lists is
 *                   THETA(E), the total time spent in scanning adjacency lists
 *                   is O(E). The overhead for initialization is O(V), and thus
 *                   the total running time of the BFS procedure is O(V + E).
 *                   Thus, breadth-first search runs in time linear in the size
 *                   of the adjacency-list representation of G."
 *                   (CLRS, 3rd Edition, Page 597)
 * @space complexity: ?
 * @credit: The BFS algorithm is taken from page 595 of 3rd edition of CLRS.
 * @author Anil Celik Maral, 2021.07.12  */
void anil::graph::bfs(int source_vertex) {
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
  this->most_recent_source_for_bfs = source_vertex;
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
 * @param list_of_vertices is the list that contains the vertices in the order
 *        in which they will be processed in the main loop of this function
 *        i.e. during the depth-first search. When the DFS is completed, this
 *        parameter will store the topologically sorted vertices i.e. in order
 *        of decreasing finish times. Therefore, this parameter can be
 *        considered both an input and output.
 * @brief This function performs the depth-first search algorithm on the given
 *        graph. The vertices of the given graph are processed in the order
 *        given by the parameter list_of_vertices.
 * @time complexity: ?
 * @space complexity: ?
 * @credit: The DFS algorithm is taken from page 604 of 3rd edition of CLRS.
 * @precondition: list_of_vertices.size() == this->order_of_graph() 
 * @author Anil Celik Maral, 2021.08.05 */
void anil::graph::dfs(anil::cursor_list& list_of_vertices) {
  if(list_of_vertices.size() == this->order_of_graph()) {
    for (int i = 0; i < this->no_of_vertices; ++i) {
      this->vertex_color[i] = WHITE;
      this->vertex_predecessor[i] = UNDEFINED_PREDECESSOR;
    }

    vertex_time_counter = 0;
    anil::cursor_list topologically_sorted_vertices;

    for (list_of_vertices.move_cursor_front(); list_of_vertices.index() >= 0;
         list_of_vertices.move_cursor_next()) {
      if (this->vertex_color[list_of_vertices.cursor_data()] == WHITE) {
        dfs_visit(list_of_vertices.cursor_data(),
                  topologically_sorted_vertices);
      }
    }

    list_of_vertices.clear();
    for (topologically_sorted_vertices.move_cursor_front();
         topologically_sorted_vertices.index() >= 0;
         topologically_sorted_vertices.move_cursor_next()) {
      list_of_vertices.append(topologically_sorted_vertices.cursor_data());
    }
  }
  return;
}

/**
 * @param vertex is the vertex who and whose adjacency list we will visit.
 * @param topologically_sorted_vertices is the list that is created to
 *        topologically sort the vertices. Topological sorting is done by
 *        splicing the vertex, who and whose adjacency list we have visited,
 *        onto the front of the list.
 * @brief This is the private function used by the DFS algorithm. It sets the
 *        initial discovery and discovery finish times of the vertices.
 *        Additionally, it visits the adjacency list of the vertex in a
 *        depth-first search fashion.
 * @time complexity: ?
 * @space complexity: ?
 * @credit: The DFS Visit algorithm is taken from page 604 of 3rd edition of
 *          CLRS.
 * @author Anil Celik Maral, 2021.08.05 */
void anil::graph::dfs_visit(int vertex,
                            anil::cursor_list& topologically_sorted_vertices) {
  this->vertex_color[vertex] = GRAY;
  this->vertex_initial_discovery_time[vertex] = ++vertex_time_counter;
  for (this->vertices[vertex]->move_cursor_front();
       this->vertices[vertex]->index() >= 0;
       this->vertices[vertex]->move_cursor_next()) {
    if (this->vertex_color[this->vertices[vertex]->cursor_data()] == WHITE) {
      this->vertex_predecessor[this->vertices[vertex]->cursor_data()] = vertex;
      dfs_visit(this->vertices[vertex]->cursor_data(),
                topologically_sorted_vertices);
    }
  }
  this->vertex_color[vertex] = BLACK;
  this->vertex_discovery_finish_time[vertex] = ++vertex_time_counter;
  topologically_sorted_vertices.prepend(vertex);
  return;
}

/**
 * @brief This function does the necessary operations to find the strongly 
 *        connected components of a directed graph. If they exist, the
 *        strongly connected components of the graph are stored in an array
 *        of lists. The convention for storing the strongly connected component
 *        is as following; the dfs tree (strongly connected component) with the
 *        root which has the smaller vertex label comes first. So, the
 *        strongly connected components are order in an ascending manner in
 *        regard to their first element / root.
 * @time complexity: ?
 * @space complexity: ?
 * @credit: The algorithm for finding the strongly connected components is
 *          taken from page 617 of 3rd edition of CLRS. 
 * @author Anil Celik Maral, 2021.08.17 */
std::vector<anil::cursor_list> anil::graph::find_strongly_connected_components() {

  // We create a list that contains the proper processing order for the
  // vertices of the graph. For example, the correct processing ordering
  // for a graph of order 5 would be; vertex-0, vertex-1, vertex-2, vertex-3
  // vertex-4. So, the list would contain the numbers 0, 1, 2, 3 and 4.
  anil::cursor_list list_of_vertices;
  for (int i = 0; i < this->no_of_vertices; ++i) {
    list_of_vertices.append(i);
  }

  // First call to dfs() is to compute the finishing times for each
  // vertex. After this call, the list 'list_of_vertices' will contain the
  // list of vertices of the graph in decreasing finish times. So, the list
  // of vertices will be topologically sorted.
  this->dfs(list_of_vertices);

  anil::graph* transposed_directed_graph = this->transpose();

  // After this call to dfs(), the list 'list_of_vertices' contains the
  // vertices of the graph's strongly connected components. The way to
  // properly seperate each strongly connected component is to use the fact
  // that the first element (root of a dfs tree) of each strongly connected
  // component doesn't have a parent (nullptr). 
  transposed_directed_graph->dfs(list_of_vertices);

  // We process the list of vertices in reverse order to save each strongly
  // connected component as a seperate list in an array of lists. The reason
  // behind the reverse processing order is due to the fact the strongly
  // connected component with the root that has the greatest vertex label
  // comes first in the list of vertices. Since the vertices in an
  // adjacency list is stored using and ascending order, we do the same for the
  // strongly connected components. The strongly connected component with the
  // root that has the smallest vertex label comes first in array of lists
  // named 'strongly_connected_components'. Ane example format is as following:
  // Component 1: 0 4 1
  // Component 2: 2 3
  // Component 3: 6 5
  // Component 4: 7

  // Vector of cursor lists
  std::vector<anil::cursor_list> strongly_connected_components;
  
  int strongly_connected_component_counter(0);
  for (list_of_vertices.move_cursor_back(); list_of_vertices.index() >= 0;
       list_of_vertices.move_cursor_prev()) {
    if (transposed_directed_graph->vertex_predecessor[list_of_vertices.cursor_data()] == UNDEFINED_PREDECESSOR) {

      // The encounter to the last dfs tree root shouldn't trigger a call to
      // create another list.
      if (list_of_vertices.index() != 0) {
        anil::cursor_list strongly_connected_component_list;
        strongly_connected_components.push_back(strongly_connected_component_list);
        strongly_connected_components[strongly_connected_component_counter].prepend(list_of_vertices.cursor_data());
        ++strongly_connected_component_counter;
      } else if (list_of_vertices.index() == 0) {
        strongly_connected_components[strongly_connected_component_counter].prepend(list_of_vertices.cursor_data());
      }

    // If we are at the first vertex of the first strongly connected component,
    // then create a new list to store this strongly connected component.
    // We do this for the first strongly connected component because
    // we are dynamically allocating memory and for the first strongly
    // connected component, there isn't an element of a previous strongly
    // connected component such as
    // this->vertex_predecessor[list_of_vertices.cursor_data()] == nullptr we
    // can check to catch the start of a newly strongly connected component.
    } else if (list_of_vertices.index() == list_of_vertices.size() - 1) {
      anil::cursor_list strongly_connected_component_list;
      strongly_connected_components.push_back(strongly_connected_component_list);
    }

    if (transposed_directed_graph->vertex_predecessor[list_of_vertices.cursor_data()] != UNDEFINED_PREDECESSOR) {
      strongly_connected_components[strongly_connected_component_counter].prepend(list_of_vertices.cursor_data());
    }
  }

  delete transposed_directed_graph;

  return strongly_connected_components;
}

/**
 * @param graph_to_be_transposed is the graph whose transpose will be returned.
 *        This graph remains unchanged.
 * @return transpose of the input graph graph_to_be_transposed is returned.
 * @brief This functions a reference to a new graph representing the transpose
 *        of graph_to_be_transposed. The digraph graph_to_be_transposed^T is
 *        obtained by reversing the directions on all edges of
 *        graph_to_be_transposed.
 * @time complexity: ?
 * @space complexity: ?
 * @author Anil Celik Maral, 2021.08.06  */
anil::graph* anil::graph::transpose() {
  anil::graph* transposed_graph = new graph(this->no_of_vertices);
  for (int i = 0; i < this->no_of_vertices; ++i) {
    for (this->vertices[i]->move_cursor_front();
         this->vertices[i]->index() >= 0;
         this->vertices[i]->move_cursor_next()) {
      transposed_graph->add_arc(this->vertices[i]->cursor_data(), i);
    }
  }
  return transposed_graph;
}

/**
 * @param rhs (right hand side) is the graph that will be
 *        copied / assigned onto a new graph.
 * @return ??
 * @brief The assignment operator copies the graph and all of its contents
 *        referenced by the parameter rhs onto a graph. This means a deep
 *        copy assignment is done. As a result, the previous graph that is
 *        pointed by 'this' will be deleted. The function has a check for
 *        self-assignment. At the end of the assignment, the copied / assigned
 *        and the lhs (left hand side) graph are identical.
 * @time complexity: ?
 * @space complexity: ?
 * @precondition: rhs.is_empty() == false
 * @author Anil Celik Maral, 2021.08.09  */
anil::graph& anil::graph::operator= (anil::graph& rhs) {
  // Self-assignment check
  if (this == &rhs) {
    return *this;
  }

  if (rhs.is_empty() == false) {
    // If the lhs graph is not empty, clear it
    if (this->is_empty() != false) {
      this->clear();
    }

    // Copy everything in rhs to this.
    this->no_of_vertices = rhs.no_of_vertices;
    this->no_of_edges = rhs.no_of_edges;
    this->most_recent_source_for_bfs = rhs.most_recent_source_for_bfs;
    this->vertex_time_counter = rhs.vertex_time_counter;
    this->vertices = new cursor_list*[rhs.no_of_vertices];
    this->vertex_color = new int[rhs.no_of_vertices];
    this->vertex_predecessor = new int[rhs.no_of_vertices];
    this->vertex_distance = new int[rhs.no_of_vertices];
    this->vertex_initial_discovery_time = new int[rhs.no_of_vertices];
    this->vertex_discovery_finish_time = new int[rhs.no_of_vertices];
    for (int i = 0; i < rhs.no_of_vertices; ++i) {
      this->vertices[i] = new cursor_list;
      rhs.vertices[i]->save_cursor_state();
      for (rhs.vertices[i]->move_cursor_front();
           rhs.vertices[i]->index() >= 0;
           rhs.vertices[i]->move_cursor_next()) {
        this->vertices[i]->append(rhs.vertices[i]->cursor_data());
      }
      rhs.vertices[i]->restore_cursor_state();
      this->vertex_color[i] = rhs.vertex_color[i];
      this->vertex_predecessor[i] = rhs.vertex_predecessor[i];
      this->vertex_distance[i] = rhs.vertex_distance[i];
      this->vertex_initial_discovery_time[i] =
        rhs.vertex_initial_discovery_time[i];
      this->vertex_discovery_finish_time[i] =
        rhs.vertex_discovery_finish_time[i];
    }
  }

  // Return the existing object so that we can chain this operator
  return *this;
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
 * @time complexity: ?
 * @space complexity: ?
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
    delete[] this->vertex_initial_discovery_time;
    delete[] this->vertex_discovery_finish_time;
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
