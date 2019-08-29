# ifndef _STACK_H
# define _STACK_H
# include <stdint.h>
# include <stdbool.h>
# include "code.h"
# include "huffman.h"

/*Note: Full and Empty are changed to stackFull and stackEmpty respectively to not collide with
Full and Empty from queue.h*/

typedef treeNode *item; // A stack of three nodes.

typedef struct stack
{
    uint32_t size; // How big ?
    uint32_t top;  // Where’s the top?
    item *entries; // Array to hold it (via calloc)
} stack;

stack *newStack();      // Constructor
void delStack(stack *); // Destructor

item pop(stack *);        // Returns the top item
void push(stack *, item); // Adds an item to the top

bool stackEmpty(stack *);      // Is it empty ?
bool stackFull(stack *);       // Is it full ?
# endif
