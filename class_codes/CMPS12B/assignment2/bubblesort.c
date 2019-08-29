/*###############################################
# Anil Celik Maral - amaral
# amaral@ucsc.edu
# 1454995
# Assignment - 2
# Lab: Friday, 9:00am - 10:00am
# Lab Partner: None
# Date: 04/29/17
###############################################*/

# include "bubblesort.h"
# include "statistics.h"

// This is the bubble sort algorithm. It is provided in the assignment - 2 lab manual for CS - 12B.
// The credit for providing the code goes to Professor Darrell Don Earl Long from UCSC.

// Note: There aren't comments in the code because the pseudocode for it was given. Additionally,
// it is straightforward enough to be understandable without any comments.

void bubbleSort(uint32_t a[], uint32_t length)
{
    uint32_t n = length;
    uint8_t swappedFlag = false;
    do
    {
        swappedFlag = false;
        for (uint32_t i = 1; i <= (n - 1); i++)
        {
            if (a[i - 1] > a[i])
            {
                SWAP (a[i - 1], a[i]);
                swappedFlag = true;
                ++compares;
            }
        }
        n = n - 1;
    } while (swappedFlag == true);
}