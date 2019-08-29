# ifndef _QUEUE_H
# define _QUEUE_H
# include <stdint.h>
# include <stdbool.h>

/*Note: typdef treeNode item was changed to the expression below to be able to pass tree nodes to
the enqueue and dequeue functions and to make the name more explicit.*/

typedef treeNode *treeItemPointer; // treeNode is defined in huffman.h

typedef struct queue
{
    uint32_t size;        // How big is it?
    uint32_t head, tail;  // Front and rear locations
    treeItemPointer *Q;   // Array to hold it (via calloc)
} queue;

queue *newQueue(uint32_t size); // Constructor
void delQueue(queue *q);        // Destructor

bool empty(queue *q);           // Is it empty ?
bool full(queue *q);            // Is it full ?

bool enqueue(queue *q, treeItemPointer i);  // Add an item
bool dequeue(queue *q, treeItemPointer *i); // Remove from the rear
# endif