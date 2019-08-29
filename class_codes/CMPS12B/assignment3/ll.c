/*#############################################
# Anil Celik Maral - amaral
# amaral@ucsc.edu
# 1454995
# Assignment - 3
# Lab: Friday, 9:00am - 10:00am
# Lab Partner: None
# Date: 05/14/17
###############################################
*/

# include <stdio.h>
# include <string.h>
# include <stdint.h>
# include <stdlib.h>
# include <stdbool.h>
# include "ll.h"
# include "statistics.h"

// Creates a new node but it does nothing else. For example, there is no linking etc.
listNode *newNode(const char *oldWord, const char *newWord)
{
    listNode *newNode = (listNode *)malloc(sizeof(listNode));
    if (newNode != NIL)
    {
        newNode->oldspeak = strdup(oldWord); // Malloc a space for the string and give the pointer.
        newNode->newspeak = strdup(newWord); // Malloc a space for the string and give the pointer.
        newNode->next = NIL;
        return newNode;
    }
    else
    {
        return NIL;
    }
}

// Just deletes the node and does nothing else such as restoring the link.
void delNode(listNode *node)
{
    if (node != NIL)
    {
        free(node->oldspeak); // Remember that strdup mallocs memory so we need to free it.
        node->oldspeak = NIL;
        free(node->newspeak);
        node->newspeak = NIL;
        node->next = NIL;
        free(node);
        return;
    }
    return;
}

// This deletes the whole who linked-list instead of just the node itself.
void delLL(listNode *node)
{
    listNode *backUpNode = NIL;
    while (node != NIL)
    {
        backUpNode = node->next;
        delNode(node);
        node = backUpNode;
    }
    return;
}

// Inserts the new node at the head of desired linked list. The new head is the inserted item.
listNode *insertLL(listNode **headOfALinkedList, const char *oldWord, const char *newWord)
{
    listNode *node = newNode(oldWord, newWord);
    if (node != NIL)
    {
        node->next = *headOfALinkedList;
        return node;
    }
    return NIL;
}

// Finds the node that has the oldspeak word that we are looking for.
listNode *findLL(listNode **headOfALinkedList, const char *oldWord)
{
    int stringCompareValue = 0;
    listNode *node = *headOfALinkedList;
    listNode *backUpOfHeadNode = node;
    listNode *previousNode = NIL;
    if (getStatistics == true)
    {
        ++average;
    }
    while (node != NIL)
    {
        if (getStatistics == true)
        {
            ++seeks;
        }
        stringCompareValue = strcmp(oldWord, node->oldspeak);
        if (stringCompareValue == 0)
        {
            if (moveToFront == true) // If the node was at the head.
            {
                if (backUpOfHeadNode == node)
                {
                    return node;
                }
                else if (node->next == NIL) // If the node was in the middle.
                {
                    previousNode->next = NIL;
                    node->next = backUpOfHeadNode;
                    return node;
                }
                else //If the node was at the end.
                {
                    previousNode->next = node->next;
                    node->next = backUpOfHeadNode;
                    return node;
                }
            }
            return node;
        }
        // Couldn't find it? Then move to the next node.
        previousNode = node;
        node = node->next;
    }
    return NIL;
}

// Prints the elements after the node if there are any. Therefore, the ideal usage is to give the
// head of the linked list.
void printLL(listNode *node)
{
    while (node != NIL)
    {
        printf("%s %s\n", node->oldspeak, node->newspeak);
        node = node->next;
    }
    return;
}

