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
# include "stack.h"

# define MIN_STACK 10 // Taken from the piazza post for stack by Darrell Long, who is a professor 
                      // of Computer Science, from UCSC for CS-12B.

# ifndef NIL
# define NIL (void *) 0
# endif

// We create a stack with the minimum size and set the top to 0
stack *newStack()
{
    uint8_t successFlag = false;
    stack *newStac = NIL;
    newStac = malloc(sizeof(stack));
    if (newStac != NIL)
    {
        newStac->entries = (item *)calloc(MIN_STACK, sizeof(item));
        if (newStac->entries != NIL)
        {
            newStac->size = MIN_STACK;
            newStac->top = 0;
            successFlag = true;
        }
        else
        {
            free(newStac->entries);
        }
    }
    if (successFlag == true) 
    {
        return newStac;
    }
    else 
    {   // successFlag != true
        return NIL;
    }
}

// Delete the array first and then the stack struct itself.
void delStack(stack *stack)
{
    if(stack != NIL)
    {
        for (uint32_t i = 0; i < (stack->size); i++) // Delete the nodes.
        {
            if ((stack->entries)[i] != NIL)
            {
                free(stack->entries[i]);
                stack->entries[i] = NIL;
            }
        }
        free(stack->entries);
        stack->entries = NIL;
        free(stack);
        stack = NIL;
        return;
    }
    return;
}

// Pop a node from the stack.
item pop(stack *stack)
{
    uint8_t successFlag = false;
    item poppedItem = NIL;
    if (stack != NIL)
    {
        bool stackStatusCheck;
        if ((stackStatusCheck = stackEmpty(stack)) == false) // If it is not empty, then we can pop.
        {
            --stack->top;
            poppedItem = stack->entries[stack->top];
            successFlag = true;
        }
    }
    if (successFlag == true) 
    {
        return poppedItem;
    }
    else 
    {   // successFlag != true
        printf("\nCouldn't Pop an item!\n");
        return NIL;
    }
}

// Push a node to the stack.
void push(stack *stack, item stackItem)
{
    if (stack != NIL)
    {
        bool stackStatusCheck;
        if ((stackStatusCheck = stackFull(stack)) == false) // If the stack is not full, then we can push.
        {
            stack->entries[stack->top] = stackItem;
            ++stack->top;
            return;
        }
        else // If it is full, we cannot push.
        {
            printf("\nCouldn't Push an item!\n");
            return;
        }
    }
}

// Stack is empty when there the stack top hasn't moved from 0.
bool stackEmpty(stack *stack)
{
    uint8_t successFlag = false;
    if (stack != NIL)
    {
        if (stack->top == 0) // If the top is equal to 0, then the stack is empty. 
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

// Stack is full when we have as many elements as our size in the stack.
bool stackFull(stack *stack)
{
    uint8_t successFlag = false;
    if (stack != NIL)
    {
        if (stack->top == stack->size) // If the top is equal to the size, then the stack is full.
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