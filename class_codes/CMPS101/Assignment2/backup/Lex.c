/*###############################################
# Name: Anil Celik Maral
# Cruz ID: amaral
# amaral@ucsc.edu
# Student ID: 1454995
# CMPS101, Programming Assignment-2(pa)
# Date: 10/13/17
###############################################*/

# include <string.h>
# include "List.h"

#define MAX_LEN 1024

/* --Function prototypes and Global Variables-- */
void insertionSort(char **s, int k[], int stringLength); // Description below.

// This function copies and allocates memory for a given string and then returns the pointer
// to the copied function if it is successfull.
char *stringDuplicate(char *source); // Got help from stackoverflow.com for this function.
                                     // see stackoverflow.com strdup implementation.
                                     // Wrote it because c99 doesn't support it.

int main(int argc, char**argv)
{
    FILE *inputFile = NULL;
    FILE *outputFile = NULL;
    int numberOfWords = 0;
    int *sortedIndexes = NULL; // Pointer to the array of indexes for the input array.
    int *tempSortedIndexes = NULL; // Temporary pointer to the array of indexes for input array.
    uint64_t arrayLength = 0; // Length of array of pointers for the input array.
    uint64_t arrayCapacity = 8; // Capacity of array of pointers for the input array.
    char line[MAX_LEN];
    char *token = NULL;
    char **stringArray = NULL; // Pointer to the array of pointers for the input array.
    char **temporaryPointer = NULL;    //This is the pointer variable used to prevent
                                       // a leak in case realloc() fails.
    List myList = NULL; // Pointer to our listADT.

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

    // Create an array to hold the words in the input file.
    stringArray = (char **)calloc(arrayCapacity, sizeof(char *)); // Create array of pointers for
                                                                  // the input words.
    if(stringArray == NULL)
    {
        printf("Unable to allocate memory for the input array\n");
        exit(1);
    }

    // Create an array to hold the indexes of the words in the input file.
    sortedIndexes = (int *)calloc(arrayCapacity, sizeof(int *)); // Create array of integers for
                                                                 // the input words' indexes.
    if(sortedIndexes == NULL)
    {
        printf("Unable to allocate memory for the input index array\n");
        exit(1);
    }

    // Count the number of words and put the words into an array while putting their respective
    // indexes into a different array. Realloc if there are no space in either of these two
    // arrays.
    while(fgets(line, MAX_LEN, inputFile) != NULL)
    {
        token = strtok(line, "\n");
        while(token != NULL)
        {
            stringArray[arrayLength] = (char *)stringDuplicate(token); //Save the input. 
            sortedIndexes[arrayLength] = arrayLength;
            ++arrayLength;
            if(arrayCapacity == arrayLength) //If the array is full.
            {
                temporaryPointer = stringArray;    //Save the pointer so we don't lose it.
                arrayCapacity = (arrayCapacity * 2);  //This is the doubling algorithm.
                //We realloc the array and protect the first pointer by using a temporary pointer.
                temporaryPointer = (char **)realloc(stringArray, sizeof(char *) * arrayCapacity);
                if(temporaryPointer != NULL)    //If realloc didn't fail... 
                {
                    stringArray = temporaryPointer;    //Save the new pointer as the original.
                }
                else
                {
                    printf("Unable to reallocate memory for the input array.\n");
                    exit(1);
                }
                //We realloc the array and protect the first pointer by using a temporary pointer.
                tempSortedIndexes = (int *)realloc(sortedIndexes, sizeof(int *) * arrayCapacity);
                if(tempSortedIndexes != NULL)    //If realloc didn't fail... 
                {
                    sortedIndexes = tempSortedIndexes;    //Save the new pointer as the original.
                }
                else
                {
                    printf("Unable to reallocate memory for the input index array.\n");
                    exit(1);
                }
            }
            numberOfWords++;
            token = strtok(NULL, "\n");
        }
    }

    // Creates the list.
    myList = newList(); 
    if(myList == NULL)
    {
        printf("Unable to create the listADT\n");
        exit(1);
    }
    
    // Sort the indexes of the array so that we may use the integer sortedIndexes array to
    // insert to the list(myList) in a sorted way one by one.
    insertionSort(stringArray, sortedIndexes, numberOfWords);

    // Insert the indices of the array one by one into the appropriate positions of the List.
    // In other words, we will insert the indexes to the list in the sorted order.
    for(int j = 0; j < numberOfWords ; j++)
    {
        append(myList, sortedIndexes[j]);
    }

    //We start writing into the output file which is indicated by command line argument 2.
    for(moveFront(myList); index(myList) >= 0; moveNext(myList))
    {
        fprintf(outputFile, "%s\n", stringArray[get(myList)]);
    }

    // Free all the used memory by deleting the variables etc.
    if (arrayLength != 0) // Free the strings.
    {
        for (uint64_t i = 0; i <= arrayLength - 1; i++)
        {
            free(stringArray[i]);
        }
    }
    free(stringArray);
    free(sortedIndexes);
    freeList(&myList);

    // Close files.
    fclose(inputFile);
    fclose(outputFile);
    return 0;
}

/* This is the insertion sort algorithm. Pseudocode was provided in the assignment - 2 
lab manual for CS - 12B. The credit for providing the pseudocode goes to Professor
Darrell Don Earl Long from UCSC.*/
// This algorithm takes the string that stores the words that will be used to correctly
// sort String array's indexes which will be placed in the integer array k. The sorting
// (placement) of the indexes are made lexicographically.
// Precondition: stringLength() > 0, k != null and s != null.
void insertionSort(char **s, int k[], int stringLength)
{
    int temporary = 0;
    int j = 0;
    for(int i = 1; i < stringLength; i++)
    {
        temporary = k[i];
        j = i - 1;
        while(j >= 0 && strcmp(s[k[j]], s[temporary]) > 0) // Sort lexicographically.
        {
            k[j + 1] = k[j];
            j = j - 1;
        }
        k[j + 1] = temporary;
    }
    return;
}

// This function copies and allocates memory for a given string and then returns the pointer
// to the copied function if it is successfull.
char *stringDuplicate(char *source) // Got help from stackoverflow.com for this function.
{
    char *copiedString = NULL;
    size_t byteLength = strlen(source);
    copiedString = malloc(byteLength + 1);
    if(copiedString != NULL)
    {
        memcpy(copiedString, source, byteLength + 1); // +1 because we need a space for \0.
        if(copiedString == NULL)
        {
            printf("stringDuplicate Error: Unable to memcpy() for the copied string.");
            exit(1);
        }
        copiedString[byteLength] = '\0';
    }
    else
    {
        printf("stringDuplicate Error: Unable to allocate memory for the copied string.");
        exit(1);
    }
    return copiedString;
}