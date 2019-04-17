/*###############################################
# Anil Celik Maral - amaral
# amaral@ucsc.edu
# 1454995
# Assignment - 4
# Lab: Friday, 9:00am - 10:00am
# Lab Partner: None
# Date: 05/27/17
###############################################*/

# include <stdlib.h>
# include "code.h"
# include "huffman.h"
# include "queue.h"
# include "insertionsort.h"

// This is the insertion sort algorithm. It is provided in the assignment - 2 lab manual for 
// CS - 12B. The credit for providing the code goes to Professor Darrell Don Earl Long from UCSC.
// I modified it to sort a queue of tree nodes depending on the count element of the node.

void insertionSort(queue *q, uint32_t length)
{
    treeItemPointer temporary = NIL; // We will use it to back up a node pointer.
    long int j = 0;
    for (uint32_t i = 1; i < length; i++)
    {
        if (q->tail == 0 )
        {
            return;
        }
        temporary = q->Q[i]; // Back up the pointer.
        j = i - 1;
        if ((q->Q)[i] != NIL && (q->Q)[j] != NIL) // Don't do it for empty location in the queue.
        {
            while (j >= 0 && (q->Q[j])->count > (temporary)->count)
            {
                (q->Q[j + 1]) = (q->Q[j]); // Move the bigger count up.
                j = j - 1;
            }
        }
        (q->Q[j + 1]) = temporary; // We (maybe) overwrote the pointer so we get it back.
    }
    return;
}
