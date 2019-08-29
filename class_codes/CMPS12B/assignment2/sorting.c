/*###############################################
# Anil Celik Maral - amaral
# amaral@ucsc.edu
# 1454995
# Assignment - 2
# Lab: Friday, 9:00am - 10:00am
# Lab Partner: None
# Date: 04/29/17
###############################################*/

// Note: The idea of using bit vectors to save the inputs using getopt was suggested by Professor
// Darrell Don Earl Long from UCSC during the class for CS-12B. Therefore, the credit goes to him.

// Note-2: Check for when n is 0 for minSort and bubbleSort. Otherwise, they fail.

# include <unistd.h>
# include <getopt.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include "statistics.h"
# include "bv.h"
# include "bubblesort.h"
# include "insertionsort.h"
# include "mergesort.h"
# include "minsort.h"
# include "quicksort.h"

// Global variable declarations. These are used by sorting algorithms to get statistical data.
// They are defined in statistics.h.
uint64_t moveCount = 0;
uint64_t compares = 0;

int main(int argc, char**argv)
{
    char inputCharacter = 0;
    uint32_t printingFormatter = 0;
    uint64_t randomSeed = 8062022;
    uint64_t printingLength = 100;
    uint64_t arraySize = 100;
    uint8_t desiredBit = 11;    //This variable is used to check the value of the bit at a certain
                                //position in the bit vector. Eleven is used to differentiate the
                                //value from '0' and '1' in case of an error.
    uint8_t desiredBitTwo = 11;
    uint32_t desiredLength = 16;    //This represent the length, the number of bits,
                                   //for the bit vector.
    uint32_t *integerArray = NULL;    //This is the original pointer to the integer array.
    uint32_t *temporaryPointer = NULL;   //This is the pointer variable used to prevent a leak in
                                         //during calling the function merge sort.
    bitV *bitVector = NULL;
    bitVector = newVec(desiredLength);    //The bit vector is created.
    // https://linux.die.net/man/3/getopt is the site where they explain the usage of getopt.
    // Also, the while loop was given by Professor Darrell Long in the lab manual.
    while ((inputCharacter = getopt(argc, argv, "AmbiqMp:r:n:")) != -1)
    {
        if (inputCharacter == 'A')
        {
            setBit(bitVector, 0);    //0th bit represents all algorithms.
        } else if (inputCharacter == 'm')
        {
            setBit(bitVector, 1);    //1st bit represents min sort.
        } else if (inputCharacter == 'b')
        {
            setBit(bitVector, 2);    //2nd bit represents bubble sort.
        } else if (inputCharacter == 'i')
        {
            setBit(bitVector, 3);    //3rd bit represents insertion sort.
        } else if (inputCharacter == 'q')
        {
            setBit(bitVector, 4);    //4th bit represents quick sort.
        } else if (inputCharacter == 'M')
        {
            setBit(bitVector, 5);    //5th bit represents merge sort.
        } else if (inputCharacter == 'p')
        {
            setBit(bitVector, 6);    //6th bit represents a new printing length input.
            printingLength = atoi(optarg);    //The usage of optarg is from 
                                              //https://linux.die.net/man/3/getopt.
        } else if (inputCharacter == 'r')
        {
            setBit(bitVector, 7);    //7th bit represents a new random seed input.
            randomSeed = atoi(optarg);    //The usage of optarg is from 
                                          //https://linux.die.net/man/3/getopt.
        } else if (inputCharacter == 'n')
        {
            setBit(bitVector, 8);    //8th bit represents a new array size input.
            arraySize = atoi(optarg);    //The usage of optarg is from 
                                         //https://linux.die.net/man/3/getopt.
        }
    }
    //Here, we give the entered or default seed to srand so that we can later call rand().
    srand(randomSeed);
    integerArray = calloc(arraySize, sizeof (uint32_t));    //This creates the original array of
                                                            //size arraySize.
    if (integerArray != NULL)    //If the calloc() doesn't fail, we start sorting the array. 
    {
        //Initialize the array with random numbers.
        for (uint64_t i = 0; i < arraySize; i++)
        {
            integerArray[i] = (rand() % 16777216);
        }
        //Check if a bit is set(user prompted special getopt option) and then call the algorithm 
        // if it is. This is check is for min sort. If -A was used with getopt. We call all of the
        // sorting algorithms.
        if ((desiredBit = valBit(bitVector, 1)) == 0x01 || 
        (desiredBitTwo = valBit(bitVector, 0)) == 0x01)
        {
            //Call min sort.
            minSort(integerArray, arraySize);
            //Print the number of elements.
            printf("Min Sort\n%lu elements\n", arraySize);
            //Print the number of moves in the algorithm.
            printf("%lu moves\n", moveCount);
            //Print the number of compares in the algorithm.
            printf("%lu compares\n", compares);
            //Print the sorted array.
            if (printingLength > arraySize)
            {
                printingLength = arraySize;
            }
            for (uint64_t i = 0; i < printingLength; i++)
            {
                printf("  %8u", integerArray[i]);
                if (printingFormatter == 6) // Used to make the output nicer(They line up better).
                {
                    printingFormatter = 0;
                    printf("\n");
                }
                else 
                {
                    ++printingFormatter;
                }
            }
            printingFormatter = 0;
            printf("\n");
            moveCount = 0; // Reset the statistical data for following algorithms.
            compares = 0;
        }
        //Regenerate the array. So that we always sort the same list with same numbers.
        srand(randomSeed);
        for (uint64_t i = 0; i < arraySize; i++)
        {
            integerArray[i] = (rand() % 16777216);
        }
        //Check for bubble sort.
        if ((desiredBit = valBit(bitVector, 2)) == 0x01 || 
        (desiredBitTwo = valBit(bitVector, 0)) == 0x01)
        {
            //Call bubble sort.
            bubbleSort(integerArray, arraySize);
            //Print the number of elements.
            printf("Bubble Sort\n%lu elements\n", arraySize);
            //Print the number of moves.
            printf("%lu moves\n", moveCount);
            //Print the number of compares.
            printf("%lu compares\n", compares);
            //Print the sorted array.
            if (printingLength > arraySize)
            {
                printingLength = arraySize;
            }
            for (uint64_t i = 0; i < printingLength; i++)
            {
                printf("  %8u", integerArray[i]);
                if (printingFormatter == 6) // Used to make the output nicer(They line up better).
                {
                    printingFormatter = 0;
                    printf("\n");
                }
                else 
                {
                    ++printingFormatter;
                }
            }
            printingFormatter = 0;
            printf("\n");
            moveCount = 0; // Reset the statistical data for following algorithms.
            compares = 0;
        }
        //Regenerate the array. So that we always sort the same list with same numbers.
        srand(randomSeed);
        for (uint64_t i = 0; i < arraySize; i++)
        {
            integerArray[i] = (rand() % 16777216);
        }		
        //Check for insertion sort.
        if ((desiredBit = valBit(bitVector, 3)) == 0x01 || 
        (desiredBitTwo = valBit(bitVector, 0)) == 0x01)
        {
            //Call insertion sort.
            insertionSort(integerArray, arraySize);
            //Print the number of elements.
            printf("Insertion Sort\n%lu elements\n", arraySize);
            //Print the number of moves.
            printf("%lu moves\n", moveCount);
            //Print the number of compares.
            printf("%lu compares\n", compares);
            //Print the sorted array.
            if (printingLength > arraySize)
            {
                printingLength = arraySize;
            }
            for (uint64_t i = 0; i < printingLength; i++)
            {
                printf("  %8u", integerArray[i]);
                if (printingFormatter == 6) // Used to make the output nicer(They line up better).
                {
                    printingFormatter = 0;
                    printf("\n");
                }
                else 
                {
                    ++printingFormatter;
                }
            }
            printingFormatter = 0;
            printf("\n");
            moveCount = 0; // Reset the statistical data for following algorithms.
            compares = 0;
        }
        //Regenerate the array. So that we always sort the same list with same numbers.
        srand(randomSeed);
        for (uint64_t i = 0; i < arraySize; i++)
        {
            integerArray[i] = (rand() % 16777216);
        }
        //Check for quick sort.
        if ((desiredBit = valBit(bitVector, 4)) == 0x01 || 
        (desiredBitTwo = valBit(bitVector, 0)) == 0x01)
        {
            //Call quick sort.
            quickSort(integerArray, arraySize);
            //Print the number of elements.
            printf("Quick Sort\n%lu elements\n", arraySize);
            //Print the number of moves.
            printf("%lu moves\n", moveCount);
            //Print the number of compares.
            printf("%lu compares\n", compares);
            //Print the sorted array.
            if (printingLength > arraySize)
            {
                printingLength = arraySize;
            }
            for (uint64_t i = 0; i < printingLength; i++)
            {
                printf("  %8u", integerArray[i]);
                if (printingFormatter == 6) // Used to make the output nicer(They line up better).
                {
                    printingFormatter = 0;
                    printf("\n");
                }
                else 
                {
                    ++printingFormatter;
                }
            }
            printingFormatter = 0;
            printf("\n");
            moveCount = 0; // Reset the statistical data for following algorithms.
            compares = 0;
        }
        //Regenerate the array. So that we always sort the same list with same numbers.
        srand(randomSeed);
        for (uint64_t i = 0; i < arraySize; i++)
        {
            integerArray[i] = (rand() % 16777216);
        }
        //Check for merge sort.
        if ((desiredBit = valBit(bitVector, 5)) == 0x01 || 
        (desiredBitTwo = valBit(bitVector, 0)) == 0x01)
        {
            //Call merge sort.
            //We save the pointer to the original list because after merge sort finishes it's job.
            //It gives the pointer to the sorted version of the original list. Therefore, to be
            //able to free the original array, we save the pointer to it. Later, we free it
            //because we no longer need it. We already have the sorted one.
            temporaryPointer = integerArray;
            integerArray = mergeSort(integerArray, arraySize);
            free(temporaryPointer);
            temporaryPointer = NULL;
            if (integerArray == NULL)
            {
                return 1;
            }
            //Print the number of elements.
            printf("Merge Sort\n%lu elements\n", arraySize);
            //Print the number of moves.
            printf("%lu moves\n", moveCount);
            //Print the number of compares.
            printf("%lu compares\n", compares);
            //Print the sorted array.
            if (printingLength > arraySize)
            {
                printingLength = arraySize;
            }
            for (uint64_t i = 0; i < printingLength; i++)
            {
                printf("  %8u", integerArray[i]);
                if (printingFormatter == 6) // Used to make the output nicer(They line up better).
                {
                    printingFormatter = 0;
                    printf("\n");
                }
                else 
                {
                    ++printingFormatter;
                }
            }
            printingFormatter = 0;
            printf("\n");
            moveCount = 0; // Reset the statistical data for following algorithms.
            compares = 0;
        }
    }
    free(integerArray); // Free the array that we sorted.
    integerArray = NULL;
    delVec(bitVector); // Free the bit vector that was used to get getopt options.
    bitVector = NULL;
    return 0; 
}