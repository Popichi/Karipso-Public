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
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include <stdint.h>
# include "code.h"
# include "huffman.h"
# include "stack.h"
# include "statistics.h"

/* --Function Prototypes--*/
void increaseStackSize(stack *); // Realloc for a stack of nodes.

/*--Global Variables--*/

/* Pointer to get and then free the stack in main that is created in loadTree function */
void *loadTreeStack = NIL;

/*Creates a new huffman tree node with the given symbol, count and also saves if it a leaf or not.
s: smybol
l: leaf or not
c: count*/
treeNode *newNode(uint8_t s, bool l, uint64_t c)
{
    uint8_t successFlag = false;
    treeNode *newTreeNode = NIL;
    newTreeNode = malloc(sizeof(treeNode));
    if (newTreeNode != NIL)
    {
        newTreeNode->symbol = s;
        newTreeNode->count = c;
        newTreeNode->leaf = l;
        newTreeNode->left = NIL;
        newTreeNode->right = NIL;
        successFlag = true;
    }
    if (successFlag == true) 
    {
        return newTreeNode;
    }
    else 
    {   // successFlag != true
        return NIL;
    }
}

/*We perform a post-order traversal of the Huffman tree to write the tree to the output file.
We write L followed by the byte of the symbol for each leaf, and I for interior nodes. We don't
write a symbol for an interior node.
file: file directory from open() etc.*/
void dumpTree(treeNode *t, int file)
{
    ssize_t writeStatusCheck = 0;
    if (t != NIL) // The tree consists of two elements at least.
    {
        dumpTree(t->left, file); // Go left.
        dumpTree(t->right, file); // Go right.
        if (t->leaf == false) // Print only 'I'.
        {
            writeStatusCheck = write(file, "I", 1);
            if (writeStatusCheck < 0)
            {
                printf("\nCouldn't write the interior node\n");
            }
        }
        else // Print 'L' for leaf and the symbol of the char.
        {
            writeStatusCheck = write(file, "L", 1);
            if (writeStatusCheck < 0)
            {
                printf("\nCouldn't write the leaf\n");
            }
            writeStatusCheck = write(file, &t->symbol, 1);
            if (writeStatusCheck < 0)
            {
                printf("\nCouldn't write the leaf\n");
            }
        }
    }
    return;
}

/*This function does a post-order construction of the saved huffman tree by the decoder. We
iterate through the elements of savedTree for treeBytes times. If we see a 'L' that means we are
at a leaf. Therefore, we create a node and push it into the stack. We also skip the next byte as
it is the symbol for leaf. Instead, we grab it and then use it to create the node. Whenever we
see an 'I', we know that it is an interior node. We pop twice to get it's children and then
join them to get the interior node. Afterward, we push the interior node. After we go through
all the elements of the savedTree. We pop one last time to get our root.*/
treeNode *loadTree(uint8_t savedTree[], uint16_t treeBytes)
{
    treeNode *rootNode = NIL;
    treeNode *poppedNode = NIL; // For interior node, this is the right child.
    treeNode *poppedNodeTwo = NIL; // For interior node, this is the left child.
    treeNode *joinedNode = NIL; // This is the interior node.
    treeNode *newTreeNode = NIL;
    stack *stackOne = NIL;
    stackOne = newStack();
    if (stackOne != NIL)
    {
        for (uint32_t i = 0; i < treeBytes; i++)
        {
            if (savedTree[i] == 'L') // If it is a leaf.
            {
                newTreeNode = newNode(savedTree[i + 1], true, 1); // Grab the symbol and create.
                if (newTreeNode != NIL)
                {
                    if (stackOne->top == stackOne->size) // Realloc if stack is full.
                    {
                        increaseStackSize(stackOne);
                    }
                    push(stackOne, newTreeNode);
                    ++i; // Since we grab the symbol, we skip checking it.
                }
                else
                {
                    printf("\nLeaf create error\n");
                }
            }
            else // if (savedTree[i] == 'I')
            {
                poppedNode = pop(stackOne); // Get the right child.
                if (poppedNode != NIL)
                {
                    poppedNodeTwo = pop(stackOne); // Get the left child.
                    if (poppedNodeTwo != NIL)
                    {
                        joinedNode = join(poppedNodeTwo, poppedNode); // Get the interior node.
                        if (joinedNode != NIL)
                        {
                            push(stackOne, joinedNode);
                        }
                        else
                        {
                            printf("\nJoin fail\n");
                        }
                    }
                    else
                    {
                        printf("\nPop two fail\n");
                    }
                }
                else
                {
                    printf("\nPop one fail\n");
                }
            }
        }
    loadTreeStack = stackOne; // Get the pointer to the global ptr. so that we can erase it later.
    }
    else
    {
        printf("\nNew stack fail\n");
    }
    rootNode = pop(stackOne); // Get the root.
    if (rootNode != NIL)
    {
        return rootNode;
    }
    else
    {
        printf("\nRoot node failure\n");
        return NIL;
    }
}

/*We begin at the root and move left whenever we get a 0 and we move right whenever we get a 1.
When we are at the leaf, we return the symbol for that node and reset our current node back to
the tree root. We return -1 when an error occurs and we return 1 when we encounter a leaf node
to signal we are not there yet.*/
int32_t stepTree(treeNode *root , treeNode **t, uint32_t code)
{
    static uint8_t firstTimeFlag = true; // Prevent compiler from complaining about static initial.
    static treeNode *currentNode = NIL;
    if (firstTimeFlag == true)
    {
        currentNode = root; // We get the root once and then never do this again.
        firstTimeFlag = false;
    }
    if (root != NIL)
    {
        if (code == 0)
        {
            currentNode = currentNode->left; // Move left.
            if (currentNode->leaf == true)
            {
                int32_t charSymbol = currentNode->symbol;
                currentNode = root; // Reset.
                return charSymbol;
            }
            else //if currentNode->leaf == false
            {
                return -1;
            }
        }
        else // if code == 1
        {
            currentNode = currentNode->right; // Move right.
            if (currentNode->leaf == true)
            {
                int32_t charSymbol = currentNode->symbol;
                currentNode = root; // Reset.
                return charSymbol;
            }
            else //if currentNode->leaf == false
            {
                return -1;
            }
        }
    }
    return -2;
    t = t; // To stop compiler from complaining since I didn't need it.
}

/*Performs a pre-order traversal of the Huffman tree. If we are at a leaf the current stack
represents the path to the node, and so is the code for it. This code is saved into a stack of
bits which is held by an array of 256 bit-stacks. Each specific location corresponds to the ASCII 
value of specific characters. We push while going to left and 1 for the right path.*/
void buildCode(treeNode *t, code s, code table[256])
{
    if (t != NIL)
    {
        if (t->leaf == false)
        {
            bool pushStatusCheck = pushCode(&s, 0); // Push 0 before going to left.
            if (pushStatusCheck == false)
            {
                printf("\nCouldn't push the code!\n");
                return;
            }
        }
        else // If it is a leaf.
        {
            // Save the code for the given symbol.
            size_t numberOfBytesToBeCopied = 0;
            if ((s.l / 8) == 0 && s.l > 0)
            {
                numberOfBytesToBeCopied = 1;
            }
            else
            {
                numberOfBytesToBeCopied = ((s.l / 8) + 1);
            }
            // Copy the current stack to our char's specific bit-stack.
            memcpy((table[t->symbol]).bits, s.bits, numberOfBytesToBeCopied);
            (table[t->symbol]).l = s.l;
        }
        buildCode(t->left, s, table); // Go left.
        uint32_t poppedCode = 0; // Pop 0 when you come back.
        bool popStatusCheck = popCode(&s, &poppedCode);
        if (popStatusCheck == false)
        {
            printf("\nCouldn't pop the code!\n");
            return;
        }
        bool pushStatusCheckTwo = pushCode(&s, 1); // Push 1 before going to right.
        if (pushStatusCheckTwo == false)
        {
            printf("\nCouldn't push the code - two!\n");
            return;
        }
        buildCode(t->right, s, table); // Go right.
    }
    return;
}

/*Joins two leaves by making them children of an interior node which has a count that is equal to
its children's counts. Additionally, it a symbol of '$'.*/
treeNode *join(treeNode *l, treeNode *r)
{
    uint8_t successFlag = false;
    treeNode *interiorNode = NIL;
    if (l != NIL && r != NIL)
    {
        uint64_t countSum = (l->count + r->count); // Count equals to that of children's.
        interiorNode = newNode('$', false, countSum);
        if (interiorNode != NIL) // Connect it to the children.
        {
            interiorNode->left = l;
            interiorNode->right = r;
            successFlag = true;
        }
    }
    if (successFlag == true) 
    {
        return interiorNode;
    }
    else 
    {   // successFlag != true
        return NIL;
    }
}

/*This function uses doubling algorithm to increase the size of a stack of tree nodes.
It reallocs the stack with the increased size. Additionally, it initializes all of the additional
spacese to NIL(NULL). Original stack positions are left untouched..*/
void increaseStackSize(stack *stack)
{
    if (stack != NIL)
    {
        item *temporaryPointer = NIL; // Safety pointer to avoid mem. leak.
        uint32_t originalSize = stack->size;
        stack->size = (stack->size * 2); // Double the size.
        temporaryPointer = (item *)realloc(stack->entries, sizeof(item) * stack->size);
        if (temporaryPointer != NIL)
        {
            for (uint32_t i = originalSize; i < (stack->size); i++) // Only additional elements.
            {
                temporaryPointer[i] = NIL;
            }
            stack->entries = temporaryPointer; // Give the new pointer.
        }
        else
        {
            printf("\nCouldn't realloc!\n");
        }
    }
    return;
}

void *delTree(treeNode *t)
{
    if (t != NIL)
    {   
        delTree(t->left);
        delTree(t->right);
        delNode(t);
        t = NIL;
        return NIL;
    }
    return NIL;
}