/*###############################################
# Anil Celik Maral - amaral
# amaral@ucsc.edu
# 1454995
# Assignment - 2
# Lab: Friday, 9:00am - 10:00am
# Lab Partner: None
# Date: 04/29/17
###############################################*/

# include "insertionsort.h"
# include "statistics.h"

// This is the insertion sort algorithm. It is provided in the assignment - 2 lab manual for 
// CS - 12B. The credit for providing the code goes to Professor Darrell Don Earl Long from UCSC.

// Note: There aren't comments in the code because the pseudocode for it was given. Additionally,
// it is straightforward enough to be understandable without any comments.

void insertionSort(uint32_t a[], uint32_t length)
{
    uint32_t temporary = 0;
    long int j = 0;
    for (uint32_t i = 1; i < length; i++)
    {
        temporary = a[i];
        j = i - 1;
        while (j >= 0 && a[j] > temporary)
        {
            ++compares;
            a[j + 1] = a[j];
            ++moveCount;
            j = j - 1;
        }
        a[j + 1] = temporary;
        ++moveCount;
    }
    return;
}