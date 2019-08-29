/*###############################################
# Name: Anil Celik Maral
# Cruz ID: amaral
# amaral@ucsc.edu
# Student ID: 1454995
# CMPS101, Programming Assignment-5(pa5)
# Date: 12/05/17
###############################################*/

# include "Graph.h"

int main(int argc, char**argv)
{   
    Graph myGraph = NULL;
    Graph myUndirectedGraph = NULL;
    int graphSize = 6;

    // Create a graph of size 6. 
    myGraph = newGraph(graphSize);
    myUndirectedGraph = newGraph(graphSize);

    //Get the order of the graph.
    printf("The number of vertices(order) in the graph is: %d --> Should be 6\n",
           getOrder(myGraph));

    //Get the size of the graph.
    printf("The number of edges(order) in the graph is: %d --> Should be 0\n", getSize(myGraph));

    //Get the parent of vertex 4.
    printf("The parent of vertex 4 is: %d --> Should be NIL(0)\n", getParent(myGraph, 4));

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

    //Add directed edges.
    addArc(myGraph, 2, 1);
    addArc(myGraph, 3, 1);
    addArc(myGraph, 4, 2);
    addArc(myGraph, 5, 2);
    addArc(myGraph, 6, 2);
    addArc(myGraph, 4, 3);
    addArc(myGraph, 4, 5);
    addArc(myGraph, 5, 6);

    printGraph(stdout, myGraph); // Should print the undirected version.
    printf("\n");

    //Create the undirected one.
    addEdge(myUndirectedGraph, 2, 1);
    addEdge(myUndirectedGraph, 3, 1);
    addEdge(myUndirectedGraph, 4, 2);
    addEdge(myUndirectedGraph, 5, 2);
    addEdge(myUndirectedGraph, 6, 2);
    addEdge(myUndirectedGraph, 4, 3);
    addEdge(myUndirectedGraph, 4, 5);
    addEdge(myUndirectedGraph, 5, 6);

    // Print the created adjacency list. It should look as below:
    /*
    1: 2 3
    2: 1 4 5 6
    3: 1 4
    4: 2 3 5
    5: 2 4 6
    6: 2 5
    */
    printGraph(stdout, myUndirectedGraph);
    printf("\n");

    // Create the list to give the correct processing order to DFS.
    List stack = newList();
    for(int i = 1; i < myGraph->noOfVertices + 1; i++)
    {
        append(stack, i);
    }
    DFS(myGraph, stack);
    
    //Check the order of the stack.
    printList(stdout, stack);
    printf("\n");

    //Test transpose function with and DFS with it!
    Graph myTransposeGraph = transpose(myGraph);
    DFS(myTransposeGraph, stack);

    //Test copyGraph()!
    Graph copyMyTransposeGraph = copyGraph(myTransposeGraph);
    printGraph(stdout, copyMyTransposeGraph); // Should be equivalent to myTransposeGraph!
    printf("\n");

    //Test getDiscover() and getFinish() functions!
    getDiscover(myTransposeGraph, 1);
    getFinish(myTransposeGraph, 1);

    //Free the heap memory associated with the graphs.
    freeList(&stack);
    freeGraph(&myGraph);
    freeGraph(&myUndirectedGraph);
    freeGraph(&myTransposeGraph);
    freeGraph(&copyMyTransposeGraph);
}
