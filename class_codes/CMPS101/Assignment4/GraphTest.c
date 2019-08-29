/*###############################################
# Name: Anil Celik Maral
# Cruz ID: amaral
# amaral@ucsc.edu
# Student ID: 1454995
# CMPS101, Programming Assignment-4(pa)
# Date: 11/18/17
###############################################*/

# include "Graph.h"

int main(int argc, char**argv)
{
    Graph myGraph = NULL;
    int graphSize = 6;

    // Create a graph of size 6. 
    myGraph = newGraph(graphSize);

    //Get the order of the graph.
    printf("The number of vertices(order) in the graph is: %d --> Should be 6\n",
           getOrder(myGraph));

    //Get the size of the graph.
    printf("The number of edges(order) in the graph is: %d --> Should be 0\n", getSize(myGraph));

    //Get the source of the graph.
    printf("The source of the graph is: %d --> Should be NIL(0)\n", getSource(myGraph));

    //Get the parent of vertex 4.
    printf("The parent of vertex 4 is: %d --> Should be NIL(0)\n", getParent(myGraph, 4));

    //Get the distance from source to 4. Since BFS, hasn't been called this should be INF.
    printf("The distance form vertex 4 to source is: %d --> Should be INF(-1)\n",
           getDist(myGraph, 4));

    // Let's create the graph shown below. First element is the size and the following pairs are
    // representing the vertex and its neighbor respectively.
    /*
    6
    1 2
    1 3
    2 4
    2 5
    2 6
    3 4
    4 5
    5 6
    */
    addEdge(myGraph, 2, 1);
    addEdge(myGraph, 3, 1);
    addEdge(myGraph, 4, 2);
    addEdge(myGraph, 5, 2);
    addEdge(myGraph, 6, 2);
    addEdge(myGraph, 4, 3);
    addEdge(myGraph, 4, 5);
    addEdge(myGraph, 5, 6);
    
    //Use makeNull to get rid of the edges.
    makeNull(myGraph);
    printGraph(stdout, myGraph); // Should just print the vertices with no neighbors.
    printf("\n");

    //Add undirected edges.
    addArc(myGraph, 2, 1);
    addArc(myGraph, 3, 1);
    addArc(myGraph, 4, 2);
    addArc(myGraph, 5, 2);
    addArc(myGraph, 6, 2);
    addArc(myGraph, 4, 3);
    addArc(myGraph, 4, 5);
    addArc(myGraph, 5, 6);

    //Use makeNull to get rid of the the vertices.
    printGraph(stdout, myGraph); // Should print the undirected version.
    printf("\n");

    //Use makeNull to get rid of the edges.
    makeNull(myGraph);

    // Add once more.
    addEdge(myGraph, 2, 1);
    addEdge(myGraph, 3, 1);
    addEdge(myGraph, 4, 2);
    addEdge(myGraph, 5, 2);
    addEdge(myGraph, 6, 2);
    addEdge(myGraph, 4, 3);
    addEdge(myGraph, 4, 5);
    addEdge(myGraph, 5, 6);

    // Print the created adjacency list. It should look as below:
    /*
    1: 2 3
    2: 1 4 5 6
    3: 1 4
    4: 2 3 5
    5: 2 4 6
    6: 2 5
    */
    printGraph(stdout, myGraph);
    printf("\n");

    // Now, let's try the BFS values below. The first number is the source and second number is
    // destination.
    /*
    1 5
    3 6
    2 3
    4 4
    */

    List pathList = NULL; // Pointer to our listADT.
    int sources[4] = {1, 3, 2, 4};
    int destination[4] = {5, 6, 3, 4};
    for(int i = 0; i < 4; i++)
    {
        pathList = newList();
        BFS(myGraph, sources[i]);
        getPath(pathList, myGraph, destination[i]);
        printf("The distance from %d to %d is %d\n", sources[i], destination[i],
                myGraph->distance[destination[i]]);
        printf("A shortest %d-%d path is: ", sources[i], destination[i]);
        printList(stdout, pathList);
        printf("\n\n");
        freeList(&pathList);
    }

    //Free the graph
    freeGraph(&myGraph);
    return 0;
}