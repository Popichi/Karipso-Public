/*###############################################
# Name: Anil Celik Maral
# Cruz ID: amaral
# amaral@ucsc.edu
# Student ID: 1454995
# CMPS101, Programming Assignment-5(pa5)
# Date: 12/05/17
###############################################*/

# ifndef _graphADT
# define _graphADT

# include "List.h"

/*Macros*/
# ifndef NIL
# define NIL (int) 0
# endif

# ifndef UNDEF
# define UNDEF (int) -5
# endif

# ifndef WHITE
# define WHITE (int) -2
# endif

# ifndef GRAY
# define GRAY (int) -3
# endif

# ifndef BLACK
# define BLACK (int) -4
# endif

// structs --------------------------------------------------------------------

/*Note: It is recommended that all arrays be of length n + 1 , where n is the number of vertices in
the graph, and that only indices 1 through n be used. This is so that array indices can be directly
identified with vertex labels.*/

typedef struct GraphObj
{
    // An array of Lists whose ith element contains the neighbors of vertex i.
    List *vertices;
    
    // An array of int whose ith element is the color (white, gray, black) of vertex i.
    int *color;

    // An array of ints whose ith element is the parent of vertex i.
    int *predecessor;

    // The discover and finish times of vertices will be undefined before DFS is called.
    // An array of ints whose ith element is the discover time of vertex i.
    int *discoverTime;

    // An array of ints whose ith element is the finish time of vertex i.
    int *finishTime;
    
    // The number of vertices (called the order of the graph).
    int noOfVertices;

    // The number of edges (called the size of the graph).
    int noOfEdges;
   
} GraphObj;

typedef struct GraphObj *Graph;

/* Constructors-Destructors */
Graph newGraph(int n);
void freeGraph(Graph* pG);

/* Access functions */
int getOrder(Graph G);
int getSize(Graph G);
int getParent(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */
int getDiscover(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */
int getFinish(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */

/* Manipulation procedures */
void addArc(Graph G, int u, int v); /* Pre: 1<=u<=n, 1<=v<=n */
void addEdge(Graph G, int u, int v); /* Pre: 1<=u<=n, 1<=v<=n */
void DFS(Graph G, List S); /* Pre: length(S)==getOrder(G) */

/* Other Functions */
Graph transpose(Graph G);
Graph copyGraph(Graph G);
void printGraph(FILE* out , Graph G);

# endif