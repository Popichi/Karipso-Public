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

// This is the merge sort algorithm. A python version was provided in the assignment - 2 lab manual
// for CS - 12B as a guide to convert to "C".The credit for providing the code goes to 
// Professor Darrell Don Earl Long from UCSC.

# include "mergesort.h"
# include "statistics.h"

uint32_t *mergeSort(uint32_t a[], uint32_t length)
{
    uint8_t baseCaseFlag = false;
    uint32_t leftListLength = 0;
    uint32_t *headOfTheLeftList = NULL;
    uint32_t rightListLength = 0;
    uint32_t *headOfTheRightList = NULL;
    uint32_t *headOfTheMergedList = NULL;
    uint32_t middlePointOfTheList = 0;
    if (length > 1)
    {
        middlePointOfTheList = (length / 2);
        //0 to middle will be leftlist
        leftListLength = middlePointOfTheList;
        headOfTheLeftList = &(a[0]);
        //middle(not inclusive) to the end will be right list.
        rightListLength = (length - middlePointOfTheList);
        headOfTheRightList = &(a[middlePointOfTheList]);
        //mergesort returns the combined list from each side after they are split and combined.
        headOfTheLeftList = mergeSort(headOfTheLeftList, leftListLength);
        if (headOfTheLeftList == NULL)
        {
            return NULL;
        }
        headOfTheRightList = mergeSort(headOfTheRightList, rightListLength);
        if (headOfTheRightList == NULL)
        {
            return NULL;
        }
    }
    if (length == 1)
    {
        headOfTheMergedList = (uint32_t*)calloc(1, sizeof(uint32_t));
        baseCaseFlag = true;
        if (headOfTheMergedList == NULL)
        {
            return NULL;
        }
    }
    else
    {
        headOfTheMergedList = (uint32_t*)calloc((leftListLength + rightListLength), 
        sizeof(uint32_t));
        if (headOfTheMergedList == NULL)
        {
            return NULL;
        }
    }
    uint32_t leftIndex = 0;
    uint32_t rigthIndex = 0;
    for (uint32_t i = 0; i < length; i++)
    {
        if (leftIndex < leftListLength && rigthIndex < rightListLength) //&& baseCaseFlag == false)
        {
            //Left is smaller.
            if (headOfTheLeftList[leftIndex] < headOfTheRightList[rigthIndex])
            {
                //Add the number in the left list to the allocated list.
                headOfTheMergedList[i] = headOfTheLeftList[leftIndex];
                leftIndex += 1;
                ++compares;
                ++moveCount;
            }
            //Right is smaller.
            else
            {
                //add the number in the right list to the allocated list.
                headOfTheMergedList[i] = headOfTheRightList[rigthIndex];
                rigthIndex += 1;
                ++compares;
                ++moveCount;
            }
        }
        //only the left has any elements.
        else if (leftIndex < leftListLength) //&& baseCaseFlag == false)
        {
            //add the number in the left list to the allocated list.
            headOfTheMergedList[i] = headOfTheLeftList[leftIndex];
            leftIndex += 1;
            ++moveCount;
        }
        //only the right has any elements.
        else if (rigthIndex < rightListLength) //&& baseCaseFlag == false)
        {
            //add the number in the right list to the allocated list.
            headOfTheMergedList[i] = headOfTheRightList[rigthIndex];
            rigthIndex += 1;
            ++moveCount;
        }
        else if (baseCaseFlag == true)
        {
            headOfTheMergedList[i] = a[0];
            ++moveCount;
        }
    }
    if (baseCaseFlag != true)
    {
        free(headOfTheLeftList);
        headOfTheLeftList = NULL;
        free(headOfTheRightList);
        headOfTheRightList = NULL;
    }
    return headOfTheMergedList;
}