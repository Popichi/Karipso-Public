/*###############################################
# Anil Celik Maral - amaral
# amaral@ucsc.edu
# 1454995
# Assignment - 4
# Lab: Friday, 9:00am - 10:00am
# Lab Partner: None
# Date: 05/27/17
###############################################*/

# include <stdio.h>
# include <stdlib.h>
# include "code.h"
# include "huffman.h"
# include "queue.h"
# include "insertionsort.h"

# ifndef NIL
# define NIL (void *) 0
# endif

// Creates a new circular queue of tree nodes with head and tail pointing 0 and with the given
// size.
queue *newQueue(uint32_t size)
{
    uint8_t successFlag = false;
    queue *newQ = NIL;
    newQ = malloc(sizeof(queue));
    if (newQ != NIL)
    {
        newQ->Q = (treeItemPointer *)calloc(size, sizeof(treeItemPointer));
        if (newQ->Q != NIL)
        {
            newQ->size = size;
            newQ->head = 0;
            newQ->tail = 0;
            successFlag = true;
        }
        else // If we fail, we may need to free.
        {
            free(newQ->Q);
        }
    }
    if (successFlag == true) 
    {
        return newQ;
    }
    else 
    {   // successFlag != true
        return NIL;
    }
}

// We first delete the nodes and then the queue itself.
void delQueue(queue *q)
{
    if (q != NIL)
    {
        for (uint32_t i = 0; i < (q->size - 1); i++) //Free nodes.
        {
            free(q->Q[i]);
            q->Q[i] = NIL;
        }
        free(q->Q);
        q->Q = NIL;
        free(q);
        q = NIL;
        return;
    }
    return;
}

// We can enqueue a node but we can only do this (n - 1) for a circular queue.
// We enqueue at the tail just like an ATM line.
bool enqueue(queue *q, treeItemPointer i)
{
    // I used Introduction to Algorithms, Third Edition by Thomas H. Cormen to understand the
    // queue data structure. Additionally, I used the algorithm explained as ENQUEUE.
    // Lastly, I got some ideas from Darrell Long's lectures and examples on Piazza too.
    uint8_t successFlag = false;
    if (q != NIL)
    {
        bool queueStatusCheck;
        if ((queueStatusCheck = full(q)) == false) // Is it full?
        {
            q->Q[q->tail] = i; 
            insertionSort(q, q->size); // Sort the array whenever you put a tree node.
            ++q->tail;
            q->tail = (q->tail % q->size); // We keep the queue circular.
            successFlag = true;
        }
    }
    if (successFlag == true)
    {
        return true;
    }
    else 
    {   // successFlag != true
        printf("\nCouldn't enqueue treeItem!\n");
        return false;
    }
}

// We dequeue node but we can only do this until it is empty. We remove from the head just like
// an ATM line. So head moves toward the tail.
bool dequeue(queue *q, treeItemPointer *i)
{
    // I used Introduction to Algorithms, Third Edition by Thomas H. Cormen to understand the
    // queue data structure. Additionally, I used the algorithm explained as DEQUEUE.
    // Lastly, I got some ideas from Darrell Long's lectures and examples on Piazza too.
    uint8_t successFlag = false;
    if (q != NIL)
    {
        bool queueStatusCheck;
        if ((queueStatusCheck = empty(q)) == false) // Is it empty?
        {
            *i = q->Q[q->head]; // Save the node to a pointer to a huffman tree.
            ++q->head;
            q->head = (q->head % q->size); // We keep the queue circular.
            successFlag = true;
        }
    }
    if (successFlag == true)
    {
        return true;
    }
    else 
    {   // successFlag != true
        printf("\nCouldn't dequeue treeItem!\n");
        return false;
    }
}

// A circular queue is empty whenever the tail and the head point to the same location.
bool empty(queue *q)
{
    uint8_t successFlag = false;
    if (q != NIL)
    {
        if ((q->head % q->size) == (q->tail % q->size))
        {
            successFlag = true;
        }
    }
    if (successFlag == true) 
    {
        return true;
    }
    else 
    {   // successFlag != true
        return false;
    }
}

// A circular queue is full whenever the (tail + 1) and the head point to the same location.
// By doing this, we reduce the number of places that hold a node to (n - 1) but otherwise
// it is impossible to tell when a circular queue is full as it would be confused with it
// being empty.
bool full(queue *q)
{
    uint8_t successFlag = false;
    if (q != NIL)
    {
        if (((q->tail + 1) % q->size) == (q->head % q->size))
        {
            successFlag = true;
        }
    }
    if (successFlag == true) 
    {
        return true;
    }
    else 
    {   // successFlag != true
        return false;
    }
}