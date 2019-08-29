/*###############################################
# Anil Celik Maral - amaral
# amaral@ucsc.edu
# 1454995
# Assignment - 2
# Lab: Friday, 9:00am - 10:00am
# Lab Partner: None
# Date: 04/29/17
###############################################*/

# include "minsort.h"
# include "statistics.h"
// This is the min sort algorithm. The code is provided in the assignment - 2 lab manual for CS - 12B.The
// credit for providing the code goes to Professor Darrell Don Earl Long from UCSC.

uint32_t minIndex(uint32_t a[], uint32_t first, uint32_t last)
{
    uint32_t smallest = first; //Assume the first is the least.
    for (uint32_t i = first; i < last; i += 1)
    {
        smallest = a[i] < a[smallest] ? i : smallest;
		++compares;
    }
    return smallest;
}

// minSort: sort by repeatedly finding the least element.

void minSort(uint32_t a[], uint32_t length)
{
    for (uint32_t i = 0; i < length - 1; i += 1)
    {
        uint32_t smallest = minIndex(a, i, length);
        if (smallest != i) // It's silly to swap with yourself!
        {
            SWAP (a[smallest], a[i]);
        }
    }
    return;
}