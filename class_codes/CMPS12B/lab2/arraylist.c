/*###############################################
# Anil Celik Maral - amaral
# amaral@ucsc.edu
# 1454995
# Lab - 2
# Lab: Friday, 9:00am - 10:00am
# Lab Partner: None
# Date: 04/27/17
###############################################*/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

//Note: I have look at the example in the lab manual and learned the algorithm to code this program
//Therefore, there may be similarities. However, all the coding is my own work as I only started
//coding the program once I understood the algorithm in the lab manual. I tried not the copy the
//parts of the code given in the lab manual but there may be similarities that are unavoidable.

int main()
{
    uint64_t arrayLength = 0;    //This variable holds the length of the array due to user input.
    uint64_t arrayCapacity = 8;    //This variable holds the value for the number of integers space
                                   //, which is 4 bytes, will be allocated.
    char userInput = 0;    //This variable is used to save the choice between print, insert and
                                                                                        //quit.
    int userInputTwo = 0;    //This variable is used to user's integer input.
    int *integerArray = NULL;    //This is the original pointer to the integer array.
    int *temporaryPointer = NULL;    //This is the pointer variable used to prevent a leak in case
                                     //realloc() fails.
    integerArray = calloc(arrayCapacity, sizeof (int));    //This creates the original array of
                                                           //size 8.
    if (integerArray != NULL)    //If the calloc() doesn't fail, we ask for input. 
    {
        while (1)    //A forever loop...
        {
            printf("Action? (Insert, Print, or Quit): ");    //We are asking for the action.
            scanf(" %c", &userInput);    //We are getting the input. Credit to Yash Gupta for
                                         //showing how to clear the buffer.
            if (userInput == 'I')    //If the insert option is chosen... 
            {
                printf("Enter an Integer: ");
                scanf("%d", &userInputTwo);    //Save the input as an integer to another variable.
                integerArray[arrayLength] = userInputTwo;    //Save the input.
                ++arrayLength;
                if (arrayCapacity == arrayLength)    //If the array is filled... 
                {
                    temporaryPointer = integerArray;    //Save the pointer so we don't lose it.
                    arrayCapacity = (arrayCapacity * 2);  //This is the doubling algorithm...
                    //We realloc the array and protect the first pointer by using a temporary
                    //pointer.
                    temporaryPointer = realloc(integerArray, sizeof (int) * arrayCapacity);
                    if (temporaryPointer != NULL)    //If realloc didn't fail... 
                    {
                        integerArray = temporaryPointer;    //Save the new pointer as the original.
                    }
                }
            } else if (userInput == 'P')    //If the print option is chosen...
            {
                printf("Length = %lu: ", arrayLength);
                for (uint64_t i = 0; i < arrayLength; i++)    //Print the elements of the array. 
				{
                    printf("%d ", integerArray[i]);
                }
                printf("\n");    //Add a newline after printing is done.
                //print the contents of the array if there is any.
            } else if (userInput == 'Q')    //If quit option is chosen...
            {
                free(integerArray);    //Free the allocated memory...
                return 0;
            }
        }
    }
    return 0;
}