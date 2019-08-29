/*###############################################
# Name: Anil Celik Maral
# Cruz ID: amaral
# amaral@ucsc.edu
# Student ID: 1454995
# CMPS101, Programming Assignment-4(pa)
# Date: 11/18/17
###############################################*/

# include "Graph.h"

/*** Constructors-Destructors ***/

// Returns a new Graph that has n vertices and no edges. Precondition: n >= 1.
// Actually the Graph is created with (n + 1) vertices and no edges so that each list
// corresponds to the correct vertex in the mathematical representation.
Graph newGraph(int n)
{
    if(n < 1)
    {
        printf("Graph Error: newGraph() called on with an invalid size n must be >= 1.\n");
        exit(1);
    }
    Graph graph = NULL;
    graph = malloc(sizeof(GraphObj));
    if(graph != NULL)
    {
        graph->noOfVertices = n;
        graph->noOfEdges = 0;
        graph->mostRecentSourceBFS = NIL;
        graph->vertices = (List*)calloc((n + 1), sizeof(List));
        graph->color = (int*)calloc((n + 1), sizeof(int));
        graph->predecessor = (int*)calloc((n + 1), sizeof(int));
        graph->distance = (int*)calloc((n + 1), sizeof(int));
        for(int i = 0; i < n + 1; i++) 
        {
            graph->vertices[i] = newList();
            graph->color[i] = WHITE;
            graph->predecessor[i] = NIL;
            graph->distance[i] = INF;
        }
        return graph;
    }
    return NULL;
}


// Function freeGraph() frees all dynamic memory associated with the Graph
// *pG, then sets the handle *pG to NULL. Precondition pG != NULL.
void freeGraph(Graph* pG)
{
    if(pG != NULL && *pG != NULL)
    {
        for(int i = 0; i < (*pG)->noOfVertices + 1; i++)
        {
            freeList(&((*pG)->vertices[i]));
        }
        free((*pG)->color);
        free((*pG)->predecessor);
        free((*pG)->distance);
        free((*pG)->vertices);
        free(*pG);
        *pG = NULL;
    }
    else
    {
        printf("Graph Error: freeGraph() called on an empty Graph.\n");
        exit(1);
    }
    return;
}


/*** Access functions ***/

// Returns the number of vertices (called the order of the graph) of the graph G.
// Precondition: G != NULL.
int getOrder(Graph G)
{
    if(G != NULL)
    {
        return G->noOfVertices;
    }
    else
    {
        printf("Graph Error: getOrder() is called on a non-existing graph.\n");
        exit(1);
    }
}


// Returns the number of edges (called the size of the graph) of the graph G.
// Precondition: G != NULL.
int getSize(Graph G)
{
    if(G != NULL)
    {
        return G->noOfEdges;
    }
    else
    {
        printf("Graph Error: getSize() is called on a non-existing graph.\n");
        exit(1);
    }
}

// getSource() returns the source vertex most recently used in function BFS(), or NIL if
// BFS() has not yet been called.
// Precondition: G != NULL.
int getSource(Graph G)
{
    if(G != NULL)
    {
        return G->mostRecentSourceBFS;
    }
    else
    {
        printf("Graph Error: getSource() is called on a non-existing graph.\n");
        exit(1);
    }
}

// Function getParent() will return the parent of vertex u in the BreadthFirst
// tree created by BFS(), or NIL if BFS() has not yet been called.
int getParent(Graph G, int u)
{
    if(G != NULL && u >= 1)
    {
        return G->predecessor[u];
    }
    else
    {
        printf("Graph Error: getParent() is called on a non-existing graph or invalid vertex.\n");
        exit(1);
    }
}

// Function getDist() returns the distance from the most recent BFS source to vertex u, or INF if
// BFS() has not yet been called. 
int getDist(Graph G, int u)
{
    if(G != NULL && u >= 1)
    {
        return G->distance[u];
    }
    else
    {
        printf("Graph Error: getDist() is called on a non-existing graph or invalid vertex.\n");
        exit(1);
    }
}


// Function getPath() appends to the List L the vertices of a shortest path in G from source to u,
// or appends to L the value NIL if no such path exists. getPath() has the precondition
// getSource(G)!= NIL, so BFS() must be called before getPath().
// Precondition: 1 <= u <= getOrder(G).
void getPath(List L, Graph G, int u)
{
    if(G != NULL && L != NULL && ( 1 <= u && u <= getOrder(G)) && getSource(G)!= NIL) 
    {
        if(u == getSource(G))
        {
            append(L, getSource(G));
        }
        else if(G->predecessor[u] == NIL)
        {
            append(L, NIL);
        }
        else
        {
            getPath(L, G, G->predecessor[u]);
            append(L, u);
        }
    }
    else
    {
        printf("Graph Error: getPath() is called on a non-existing graph, invalid vertex,"
               " a non-existing List or BFS hasn't been called before calling getPath().\n");
        exit(1);
    }
    return;
}


/*** Manipulation procedures ***/

// Function makeNull() deletes all edges of G, restoring it to its original
// (no edge) state.
void makeNull(Graph G)
{
    if(G != NULL)
    {
        for(int i = 0; i < G->noOfVertices + 1; i++)
        {
            moveFront(G->vertices[i]);
            while(index(G->vertices[i]) >= 0)
            {
                delete(G->vertices[i]);
                moveFront(G->vertices[i]);
            }
        }
    }
    else
    {
        printf("Graph Error: makeNull() is called on a non-existing graph.\n");
        exit(1);
    }
    return;
}

// addEdge() inserts a new edge joining u to v, i.e. u is added to the adjacency List of v, and v
// to the adjacency List of u.
void addEdge(Graph G, int u, int v)
{
    if(G != NULL && ( 1 <= u && u <= getOrder(G)) && ( 1 <= v && v <= getOrder(G)))
    {
        int possibleNeighbor = -5;
        bool thereIsAGreaterVertexThanV = false;
        for(moveFront(G->vertices[u]); index(G->vertices[u]) >= 0; moveNext(G->vertices[u]))
        {
            possibleNeighbor = get(G->vertices[u]);
            if(possibleNeighbor > v)
            {
                thereIsAGreaterVertexThanV = true;
                break;
            }
        }
        // I can do this coz I break the loop as soon as I reach the vertex with the greater
        // vertex.So, I insert right before that element in the list pointed by G->vertices[u].
        // cursor is at the node with the greater vertex.
        if(thereIsAGreaterVertexThanV == true)
        {
            insertBefore(G->vertices[u], v);
            G->noOfEdges += 1;
        }
        // Now I know, there is no vertex greater than v. There is either no non-zero elements
        // or all of them are vertices less than v. Either way, I don't care.
        // We just append the new vertex to the adjacency list.
        else // if(thereIsAGreaterVertexThanV == false)
        {
            append(G->vertices[u], v);
            G->noOfEdges += 1;
        }
        
        // Now we add u to the adjacency list of v.
        possibleNeighbor = -5;
        bool thereIsAGreaterVertexThanU = false;
        for(moveFront(G->vertices[v]); index(G->vertices[v]) >= 0; moveNext(G->vertices[v]))
        {
            possibleNeighbor = get(G->vertices[v]);
            if(possibleNeighbor > u)
            {
                thereIsAGreaterVertexThanU = true;
                break;
            }
        }
        // I can do this coz I break the loop as soon as I reach the vertex with the greater
        // vertex.So, I insert right before that element in the list pointed by G->vertices[v].
        // cursor is at the node with the greater vertex.
        if(thereIsAGreaterVertexThanU == true)
        {
            insertBefore(G->vertices[v], u);
        }
        // Now I know, there is no vertex greater than u. There is either no non-zero elements
        // or all of them are vertices less than u. Either way, I don't care.
        // We just append the new vertex to the adjacency list.
        else // if(thereIsAGreaterVertexThanU == false)
        {
            append(G->vertices[v], u);
        }
    }
    else
    {
        printf("Graph Error: addEdge() is called on a non-existing graph or with invalid vertices"
               " u and/or v.\n");
        exit(1);
    }
    return;
}

// addArc() inserts a new directed edge from u to v, i.e. v is added to the adjacency List of u
// (but not u to the adjacency List of v)
void addArc(Graph G, int u, int v)
{
    if(G != NULL && ( 1 <= u && u <= getOrder(G)) && ( 1 <= v && v <= getOrder(G)))
    {
        int possibleNeighbor = -5;
        bool thereIsAGreaterVertexThanV = false;
        for(moveFront(G->vertices[u]); index(G->vertices[u]) >= 0; moveNext(G->vertices[u]))
        {
            possibleNeighbor = get(G->vertices[u]);
            if(possibleNeighbor > v)
            {
                thereIsAGreaterVertexThanV = true;
                break;
            }
        }
        // I can do this coz I break the loop as soon as I reach the vertex with the greater
        // vertex.So, I insert right before that element in the list pointed by G->vertices[u].
        // cursor is at the node with the greater vertex.
        if(thereIsAGreaterVertexThanV == true)
        {
            insertBefore(G->vertices[u], v);
            G->noOfEdges += 1;
        }
        // Now I know, there is no vertex greater than v. There is either no non-zero elements
        // or all of them are vertices less than v. Either way, I don't care.
        // We just append the new vertex to the adjacency list.
        else // if(thereIsAGreaterVertexThanV == false)
        {
            append(G->vertices[u], v);
            G->noOfEdges += 1;
        }
    }
    else
    {
        printf("Graph Error: addArc() is called on a non-existing graph or with invalid vertices"
               " u and/or v.\n");
        exit(1);
    }
    return;
}

// Function BFS() runs the BFS algorithm on the Graph G with source s, setting the color, distance,
// parent, and source fields of G accordingly. Algorithm is taken from CLRS book.
void BFS(Graph G, int s)
{
    for(int i = 0; i < G->noOfVertices + 1; i++)
    {
        if(i != s)
        {
            G->color[i] = WHITE;
            G->distance[i] = INF;
            G->predecessor[i] = NIL;
        }
    }
    G->color[s] = GRAY;
    G->distance[s] = 0;
    G->predecessor[s] = NIL;
    G->mostRecentSourceBFS = s;
    List queue = newList();
    append(queue, s);
    while(length(queue))
    {
        moveFront(queue);
        int x = get(queue);
        delete(queue);
        for(moveFront(G->vertices[x]); index(G->vertices[x]) >= 0; moveNext(G->vertices[x]))
        {
            if(G->color[get(G->vertices[x])] == WHITE)
            {
                G->color[get(G->vertices[x])] = GRAY;
                G->distance[get(G->vertices[x])] = G->distance[x] + 1;
                G->predecessor[get(G->vertices[x])] = x;
                append(queue, get(G->vertices[x]));
            }
        }
        G->color[x] = BLACK;
    }
    freeList(&queue);
    return;
}


/*** Other operations ***/

// Finally, function printGraph() prints the adjacency list representation of G to the file pointed
// to by out.
void printGraph(FILE* out, Graph G)
{
    for(int i = 1; i < G->noOfVertices + 1; i++)
    {
        bool printedTheVertex = false;
        if(printedTheVertex == false)
        {
            printedTheVertex = true;
            fprintf(out, "%d:", i);
        }
        for(moveFront(G->vertices[i]); index(G->vertices[i]) >= 0; moveNext(G->vertices[i]))
        {            
            fprintf(out, " %d", get(G->vertices[i]));
        }
        fprintf(out, "\n");
    }
}