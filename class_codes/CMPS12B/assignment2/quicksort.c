/*###############################################
# Anil Celik Maral - amaral
# amaral@ucsc.edu
# 1454995
# Assignment - 2
# Lab: Friday, 9:00am - 10:00am
# Lab Partner: None
# Date: 04/29/17
###############################################*/

// Note: Comment your code so that you can later understand it.

// This is the quick sort algorithm. A python version was provided in the assignment - 2 lab manual
// for CS - 12B as a guide to convert to "C".The credit for providing the code goes to 
// Professor Darrell Don Earl Long from UCSC.

# include "quicksort.h"
# include "statistics.h"

void quickSort(uint32_t a[], uint32_t length)
{
    if (length > 1) // A list of size 1 is already sorted.
    {
        partitionInfo partitionInfoStruct;
        (partitionInfoStruct.pivotPointer) = &(a[0]); // Choose the pivot as the firs element.
        (partitionInfoStruct.lengthOfTheArrayBeingPartitioned) = length; // Save the length.
        partitionTheArray(&partitionInfoStruct); // Divide the list between those less than
                                                 // the pivot and greater than the pivot.
        quickSort(partitionInfoStruct.pivotOfTheLeftArray, 
        partitionInfoStruct.lengthOfTheLeftPartOfTheArray); // Call on the less than the pivot list
        quickSort(partitionInfoStruct.pivotOfTheRightArray, 
        partitionInfoStruct.lengthOfTheRightPartOfTheArray); // Call on the greater than the pivot 
                                                             // list.
    }
    return;
}

// The gif from https://www.tutorialspoint.com/data_structures_algorithms/quick_sort_algorithm.htm
// was used to understand partitioning algorithm. However, nothing beside the gif was used in the 
// link. Therefore, all of the coding is my own work.
void partitionTheArray(partitionInfo *partitionInfoStruct) 
{
    uint8_t lessThanIndexFirstTimeFlag = true; // Used to set the correct length for the left list.
    uint8_t threeMembersExceptionFlag = false; // Used to check for a special case for the 
                                               // three membered list.
    uint8_t greaterThanIndexFirstTimeFlag = true;  // Used to set the correct length for the left 
                                                   //list.
    uint8_t lessThanIndexCaugthTheOtherIndex = false;
    uint8_t greaterThanIndexCaugthTheOtherIndex = false;
    uint8_t lessThanOutOfOrderFlag = false;
    uint8_t greaterThanOutOfOrderFlag = false;
    uint8_t indicesMetEachOtherFlag = false;
    uint8_t lessThanIndexExceptionFlag = false;
    uint32_t greaterThanIndex = (partitionInfoStruct -> lengthOfTheArrayBeingPartitioned) - 1;
    uint32_t lessThanIndex = 1; //(partitionInfoStruct -> pivotPointer)[1];
    partitionInfoStruct -> lengthOfTheLeftPartOfTheArray = 0;
    partitionInfoStruct -> lengthOfTheRightPartOfTheArray = 0;
    //(lessThanIndex == greaterThanIndex) 
    if ((partitionInfoStruct -> lengthOfTheArrayBeingPartitioned) == 2)
    {
        if ((partitionInfoStruct -> pivotPointer)[0] > (partitionInfoStruct -> pivotPointer)[1]) 
        {
            ++compares;
            SWAP((partitionInfoStruct -> pivotPointer)[0], 
            (partitionInfoStruct -> pivotPointer)[1]);
        }
        indicesMetEachOtherFlag = true;
    }
    while (indicesMetEachOtherFlag == false) //(greaterThanIndex != lessThanIndex);
    {
        while (lessThanOutOfOrderFlag == false && indicesMetEachOtherFlag == false) 
        {
            if ((partitionInfoStruct -> pivotPointer)[lessThanIndex] <= 
            (partitionInfoStruct -> pivotPointer)[0])
            {
                ++compares;
                ++lessThanIndex;
                if (lessThanIndex == greaterThanIndex) 
                {
                    indicesMetEachOtherFlag = true;
                    lessThanIndexCaugthTheOtherIndex = true;
                    if (lessThanIndexFirstTimeFlag == true) 
                    {
                        ++(partitionInfoStruct -> lengthOfTheLeftPartOfTheArray);
                        lessThanIndexFirstTimeFlag = false;
                    }
                } 
                else 
                {
                    ++(partitionInfoStruct -> lengthOfTheLeftPartOfTheArray);
                }
            }
            else 
            {
                ++compares;
                lessThanOutOfOrderFlag = true;
            }
        }
        while (greaterThanOutOfOrderFlag == false && indicesMetEachOtherFlag == false) 
        {
            if ((partitionInfoStruct -> pivotPointer)[greaterThanIndex] > 
            (partitionInfoStruct -> pivotPointer)[0]) 
            {
				++compares;
                --greaterThanIndex;
                if (lessThanIndex == greaterThanIndex) 
                {
                    indicesMetEachOtherFlag = true;
                    greaterThanIndexCaugthTheOtherIndex = true;
                    if (greaterThanIndexFirstTimeFlag == true) 
                    {
                        ++(partitionInfoStruct -> lengthOfTheRightPartOfTheArray);
                        greaterThanIndexFirstTimeFlag = false;
                    }
                } 
                else 
                {
                    ++(partitionInfoStruct -> lengthOfTheRightPartOfTheArray);
                }
            } 
            else 
            {
                ++compares;
                greaterThanOutOfOrderFlag = true;
            }
        }
        if (lessThanOutOfOrderFlag == true && greaterThanOutOfOrderFlag == true && 
        indicesMetEachOtherFlag == false)
        {
            SWAP((partitionInfoStruct -> pivotPointer)[lessThanIndex], 
            (partitionInfoStruct -> pivotPointer)[greaterThanIndex]); //Swap the two.
            lessThanOutOfOrderFlag = false;
            greaterThanOutOfOrderFlag = false;
        }
        if (indicesMetEachOtherFlag == true) 
        {
            if ((partitionInfoStruct -> pivotPointer)[lessThanIndex] <= 
           (partitionInfoStruct -> pivotPointer)[0]) 
            {
                ++compares;
                ++(partitionInfoStruct -> lengthOfTheLeftPartOfTheArray);
            } 
            else 
            {
                ++compares;
                ++(partitionInfoStruct -> lengthOfTheRightPartOfTheArray);
            }
            if (lessThanIndexCaugthTheOtherIndex == true) 
            {
                if (lessThanIndex != 0 && (partitionInfoStruct -> pivotPointer)[lessThanIndex - 1] 
                < (partitionInfoStruct -> pivotPointer)[lessThanIndex] && 
                (partitionInfoStruct -> pivotPointer)[greaterThanIndex] > 
                (partitionInfoStruct -> pivotPointer)[0]) 
                {
                    ++compares;
                    SWAP((partitionInfoStruct -> pivotPointer)[lessThanIndex - 1], 
                    (partitionInfoStruct -> pivotPointer)[0]);
                    lessThanIndexExceptionFlag = true;
                    if ((partitionInfoStruct -> lengthOfTheArrayBeingPartitioned) == 3) 
                    {
                        if ((partitionInfoStruct -> pivotPointer)[lessThanIndex - 1] > 
                        (partitionInfoStruct -> pivotPointer)[lessThanIndex]) 
                        {
                            ++compares;
                            SWAP((partitionInfoStruct -> pivotPointer)[lessThanIndex - 1], 
                            (partitionInfoStruct -> pivotPointer)[lessThanIndex]);
                            threeMembersExceptionFlag = true;
                        }
                    }
                } 
                else 
                {
                    ++compares;
                    SWAP((partitionInfoStruct -> pivotPointer)[lessThanIndex], 
                    (partitionInfoStruct -> pivotPointer)[0]);
                }
            } 
            else if (greaterThanIndexCaugthTheOtherIndex == true) 
            {
                SWAP((partitionInfoStruct -> pivotPointer)[lessThanIndex - 1], 
               (partitionInfoStruct -> pivotPointer)[0]);
            }
            lessThanOutOfOrderFlag = false;
            greaterThanOutOfOrderFlag = false;
        }
    }
    (partitionInfoStruct -> pivotOfTheLeftArray) = &((partitionInfoStruct -> pivotPointer)[0]);
    if ((lessThanIndex == ((partitionInfoStruct -> lengthOfTheArrayBeingPartitioned) - 1) && 
    (partitionInfoStruct -> lengthOfTheArrayBeingPartitioned) != 3) || 
    threeMembersExceptionFlag == true) 
    {
        (partitionInfoStruct -> pivotOfTheRightArray) = NULL;
    } 
    else if (greaterThanIndexCaugthTheOtherIndex == true || lessThanIndexExceptionFlag == true || 
    (threeMembersExceptionFlag == false && 
    (partitionInfoStruct -> lengthOfTheArrayBeingPartitioned) == 3)) 
    {
        (partitionInfoStruct -> pivotOfTheRightArray) = 
        &((partitionInfoStruct -> pivotPointer)[lessThanIndex]);
    } 
    else 
    {
        (partitionInfoStruct -> pivotOfTheRightArray) = 
        &((partitionInfoStruct -> pivotPointer)[lessThanIndex + 1]);
    }
    return;
}