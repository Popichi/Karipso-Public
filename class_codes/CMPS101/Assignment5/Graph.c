/*###############################################
# Name: Anil Celik Maral
# Cruz ID: amaral
# amaral@ucsc.edu
# Student ID: 1454995
# CMPS101, Programming Assignment-5(pa5)
# Date: 12/05/17
###############################################*/

# include "Graph.h"

/* --Function prototypes and Global Variables-- */

// This is the private function used by the DFS algorithm. It sets the
// correct paramater as discover and finish times for the vertices in a graph
void Visit(Graph G, int x, int *time, List stack);

/* Constructors-Destructors */

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
        graph->vertices = (List*)calloc((n + 1), sizeof(List));
        graph->color = (int*)calloc((n + 1), sizeof(int));
        graph->predecessor = (int*)calloc((n + 1), sizeof(int));
        graph->discoverTime = (int*)calloc((n + 1), sizeof(int));
        graph->finishTime = (int*)calloc((n + 1), sizeof(int));
        for(int i = 0; i < n + 1; i++) 
        {
            graph->vertices[i] = newList();
            graph->color[i] = WHITE;
            graph->predecessor[i] = NIL;
            graph->discoverTime[i] = UNDEF;
            graph->finishTime[i] = UNDEF;
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
        free((*pG)->discoverTime);
        free((*pG)->finishTime);
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


/* Access functions */

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


// Function getParent() will return the parent of vertex u in the Depth First
// forest created by DFS(), or NIL if DFS() has not yet been called or vertex has no parents.
// Pre: 1<=u<=n=getOrder(G)
int getParent(Graph G, int u)
{
    if(G != NULL && (1 <= u && u <= getOrder(G)))
    {
        return G->predecessor[u];
    }
    else
    {
        printf("Graph Error: getParent() is called on a non-existing graph or invalid vertex.\n");
        exit(1);
    }
}


// Function getDiscover() will return the discovery time of vertex u in the Depth First Search
// or UNDEF if DFS() has not yet been called.
// Pre: 1<=u<=n=getOrder(G)
int getDiscover(Graph G, int u)
{
    if(G != NULL && (1 <= u && u <= getOrder(G)))
    {
        return G->discoverTime[u];
    }
    else
    {
        printf("Graph Error: getDiscover() called on a non-existing graph or invalid vertex.\n");
        exit(1);
    }
}


// Function getFinish() will return the finish time of vertex u in the Depth First Search
// or UNDEF if DFS() has not yet been called.
// Pre: 1<=u<=n=getOrder(G)
int getFinish(Graph G, int u)
{
    if(G != NULL && (1 <= u && u <= getOrder(G)))
    {
        return G->finishTime[u];
    }
    else
    {
        printf("Graph Error: getFinish() is called on a non-existing graph or invalid vertex.\n");
        exit(1);
    }
}


/* Manipulation procedures */

// addEdge() inserts a new edge joining u to v, i.e. u is added to the adjacency List of v, and v
// to the adjacency List of u.
// Pre: 1<=u<=n, 1<=v<=n
void addEdge(Graph G, int u, int v)
{
    if(G != NULL && (1 <= u && u <= getOrder(G)) && (1 <= v && v <= getOrder(G)))
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
// Pre: 1<=u<=n, 1<=v<=n
void addArc(Graph G, int u, int v)
{
    if(G != NULL && (1 <= u && u <= getOrder(G)) && (1 <= v && v <= getOrder(G)))
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


/*Function DFS() will perform the depth first search algorithm on G. The argument List S has two purposes
in this function. First it defines the order in which vertices will be processed in the main loop (5-7) of DFS.
Second, when DFS is complete, it will store the vertices in order of decreasing finish times (hence S can be
considered to be a stack). The List S can therefore be classified as both an input and an output parameter
to function DFS(). DFS() has two preconditions: (i) length(S) == n, and (ii) S contains some permutation
of the integers {1, 2, ..., n} where n = getOrder(G). We are required to check the first precondition but not
the second.
Pre: length(S)==getOrder(G)*/
void DFS(Graph G, List S)
{
    if(length(S) == getOrder(G))
    {
        for(int i = 0; i < G->noOfVertices + 1; i++)
        {
            G->color[i] = WHITE;
            G->predecessor[i] = NIL;
        }
        int time = 0;
        List stack = newList();
        for(moveFront(S); index(S) >= 0; moveNext(S))
        {      
            if(G->color[get(S)] == WHITE)
            {
                Visit(G, get(S), &time, stack);
            }
        }
        clear(S);
        for(moveFront(stack); index(stack) >= 0; moveNext(stack))
        {
            append(S, get(stack));
        }
        freeList(&stack);
    }
    else
    {
        printf("Graph Error: DFS() is called on an unrelated list S and/or graph G.\n");
        exit(1);
    }
    return;
}


/* Other Functions */

// Function transpose() returns a reference to a new graph object representing the transpose of G.
// (The digraph G^T is obtained by reversing the directions on all edges of G.)
// Pre: G != NULL i.e graph exists.
Graph transpose(Graph G)
{
    if(G != NULL)
    {
        Graph GTranspose = newGraph(G->noOfVertices);
        for(int i = 1; i < G->noOfVertices + 1; i++)
        {
            for(moveFront(G->vertices[i]); index(G->vertices[i]) >= 0; moveNext(G->vertices[i]))
            {
                addArc(GTranspose, get(G->vertices[i]), i);
            }
        }
        return GTranspose;
    }
    else
    {
        printf("Graph Error: transpose() is called on a non-existing graph.\n");
        exit(1);
    }
}


// copyGraph() returns a reference to a new graph which is a copy of G.
// Pre: G != NULL i.e graph exists.
Graph copyGraph(Graph G)
{
    if(G != NULL)
    {
        Graph GCopy = newGraph(G->noOfVertices);
        for(int i = 1; i < G->noOfVertices + 1; i++)
        {
            for(moveFront(G->vertices[i]); index(G->vertices[i]) >= 0; moveNext(G->vertices[i]))
            {
                addArc(GCopy, i, get(G->vertices[i]));
            }
        }
        return GCopy;
    }
    else
    {
        printf("Graph Error: transpose() is called on a non-existing graph.\n");
        exit(1);
    }
} 


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


// This is the private function used by the DFS algorithm. It sets the
// correct paramater as discover and finish times for the vertices in a graph
void Visit(Graph G, int x, int *time, List stack)
{
    G->color[x] = GRAY;
    G->discoverTime[x] = ++(*time);
    for(moveFront(G->vertices[x]); index(G->vertices[x]) >= 0; moveNext(G->vertices[x]))
    {
        if(G->color[get(G->vertices[x])] == WHITE)
        {
            G->predecessor[get(G->vertices[x])] = x;
            Visit(G, get(G->vertices[x]), time, stack);
        }
    }
    G->color[x] = BLACK;
    G->finishTime[x] = ++(*time);
    prepend(stack, x);
    return;
}