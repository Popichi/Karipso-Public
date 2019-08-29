/*###############################################
# Name: Anil Celik Maral
# Cruz ID: amaral
# amaral@ucsc.edu
# Student ID: 1454995
# CMPS101, Programming Assignment-4(pa)
# Date: 11/18/17
###############################################*/

# include <string.h>
# include "Graph.h"

# define MAX_LEN 20000

int main(int argc, char**argv)
{
    FILE *inputFile = NULL;
    FILE *outputFile = NULL;
    char line[MAX_LEN];
    char *token = NULL;
    Graph myGraph = NULL; // Pointer to our graphADT.

    // Check command line for correct number of arguments.
    if(argc != 3)
    {
        printf("There are more or less than expected command line arguments.\n"
               "Correct usage is as follows: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }
    
    // open files for reading and writing 
    inputFile = fopen(argv[1], "r");
    outputFile = fopen(argv[2], "w");
    if(inputFile == NULL)
    {
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }
    if(outputFile == NULL)
    {
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }

    int graphSize = 0;
    int vertex = 0;
    int neighbor = 0;
    int source = 0;
    int destination = 0;
    bool readTheGraphSize = false;
    bool readTheVertices = false;
    bool readTheBFSValues = false;
    bool savedVertex = false;
    bool savedNeighbor = false;
    bool savedSource = false;
    bool savedDestination = false;
    List pathList = NULL; // Pointer to our listADT.
    while(fgets(line, MAX_LEN, inputFile) != NULL)
    {
        token = strtok(line, " ");
        while(token != NULL)
        {
            if(readTheGraphSize == false) // Allocate memory of the graph.
            {
                graphSize = atoi(token);
                myGraph = newGraph(graphSize);
                readTheGraphSize = true;
            }
            // The part we construct the adjacency list.
            else if(readTheGraphSize == true && readTheVertices == false)
            {
                if(savedVertex == false && savedNeighbor == false)
                {
                    vertex = atoi(token);
                    savedVertex = true;
                }
                else if(savedVertex == true && savedNeighbor == false)
                {
                    neighbor = atoi(token);
                    savedNeighbor = true;
                }
                if(vertex != 0 && neighbor != 0 && (savedVertex == true && savedNeighbor == true))
                {
                    addEdge(myGraph, neighbor, vertex);
                    savedVertex = savedNeighbor = false;
                }
                else if(vertex == 0 && neighbor == 0 && (savedVertex == true &&
                        savedNeighbor == true))
                {
                    printGraph(outputFile, myGraph);
                    fprintf(outputFile, "\n");
                    savedVertex = savedNeighbor = false;
                    readTheVertices = true;
                }
            }
            // The part where we calculate the distance and the path.
            else if(readTheGraphSize == true && readTheVertices == true &&
                    readTheBFSValues == false)
            {
                if(savedSource == false && savedDestination == false)
                {
                    source = atoi(token);
                    savedSource = true;
                }
                else if(savedSource == true && savedDestination == false)
                {
                    destination = atoi(token);
                    savedDestination = true;
                }
                if(source != 0 && destination != 0 && (savedSource == true &&
                   savedDestination == true))
                {
                    pathList = newList();
                    BFS(myGraph, source);
                    getPath(pathList, myGraph, destination);
                    if(myGraph->distance[destination] != INF)
                    {
                        fprintf(outputFile, "The distance from %d to %d is %d\n", source,
                                destination, myGraph->distance[destination]);
                        fprintf(outputFile, "A shortest %d-%d path is: ", source, destination);
                        printList(outputFile, pathList);
                    }
                    else if(myGraph->distance[destination] == INF)
                    {
                        fprintf(outputFile, "The distance from %d to %d is infinity\n", source,
                                destination);
                        fprintf(outputFile, "No %d-%d path exists", source, destination);
                    }
                    fprintf(outputFile, "\n\n");
                    savedDestination = savedSource = false;
                    freeList(&pathList);
                }
                else if(source == 0 && destination == 0 && (savedSource == true &&
                        savedDestination == true))
                {
                    readTheBFSValues = true;
                    savedDestination = savedSource = false;
                }
            }
        token = strtok(NULL, " ");
        }
    }

    // free the graph.
    freeGraph(&myGraph);

    // Close files.
    fclose(inputFile);
    fclose(outputFile);
    return 0;
}