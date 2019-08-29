/*###############################################
# Name: Anil Celik Maral
# Cruz ID: amaral
# amaral@ucsc.edu
# Student ID: 1454995
# CMPS101, Programming Assignment-5(pa5)
# Date: 12/05/17
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
    Graph myTransposeGraph = NULL; // Pointer to our graphADT(transposed).

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
    bool readTheGraphSize = false;
    bool readTheVertices = false;
    bool readyForDFS = false;
    bool savedVertex = false;
    bool savedNeighbor = false;
    bool computedSCCs = false;
    List stack = NULL; // Pointer to our listADT.
    while(fgets(line, MAX_LEN, inputFile) != NULL)
    {
        token = strtok(line, " \t\r\n\v\f"); // Tokenize for any whitespace.
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
                    addArc(myGraph, vertex, neighbor);
                    savedVertex = savedNeighbor = false;
                }
                else if(vertex == 0 && neighbor == 0 && (savedVertex == true &&
                        savedNeighbor == true))
                {
                    fprintf(outputFile, "Adjacency list representation of G:\n");
                    printGraph(outputFile, myGraph);
                    fprintf(outputFile, "\n");
                    savedVertex = savedNeighbor = false;
                    readTheVertices = true;
                    readyForDFS = true;
                }
            }
            // The part where we calculate calculate the strongly connected components of the graph
            if(readTheGraphSize == true && readTheVertices == true &&
                    readyForDFS == true && computedSCCs == false)
            {
                // Create the list to give the correct processing order to DFS.
                stack = newList();
                for(int i = 1; i < myGraph->noOfVertices + 1; i++)
                {
                    append(stack, i);
                }
                DFS(myGraph, stack);
                myTransposeGraph = transpose(myGraph);
                DFS(myTransposeGraph, stack);
                int numberOfStronglyConnectedComponents = 0;
                for(moveBack(stack); index(stack) >= 0; movePrev(stack))
                {
                    if(myTransposeGraph->predecessor[get(stack)] == NIL)
                    {
                        ++numberOfStronglyConnectedComponents;
                    }
                }

                // Start printing the strongly connected components.
                fprintf(outputFile, "G contains %d strongly connected components:\n",
                        numberOfStronglyConnectedComponents);
                List *SCCs = (List*)calloc((numberOfStronglyConnectedComponents), sizeof(List));
                for(int i = 0; i < numberOfStronglyConnectedComponents; i++)
                {
                    SCCs[i] = newList();
                }
                int SCC = 0; // SCC = Strongly Connected Component!
                for(moveBack(stack); index(stack) >= 0; movePrev(stack))
                {
                    if(myTransposeGraph->predecessor[get(stack)] == NIL)
                    {
                        prepend(SCCs[SCC], get(stack));
                        ++SCC;
                        fprintf(outputFile, "Component %d: ", SCC);
                        printList(outputFile, SCCs[(SCC - 1)]);
                        fprintf(outputFile, "\n");
                    }
                    else
                    {
                        prepend(SCCs[SCC], get(stack));
                    }
                }

                // Frees the memory used in scope of this if statement!
                for(int i = 0; i < numberOfStronglyConnectedComponents; i++)
                {
                    freeList(&(SCCs[i]));
                }
                free(SCCs);
                SCCs = NULL;
                freeList(&stack);
                computedSCCs = true;
            }
        token = strtok(NULL, " \t\r\n\v\f");
        }
    }

    // free the graphs.
    freeGraph(&myGraph);
    freeGraph(&myTransposeGraph);

    // Close files.
    fclose(inputFile);
    fclose(outputFile);
    return 0;
}