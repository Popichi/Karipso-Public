/*###############################################
# Name: Anil Celik Maral
# Cruz ID: amaral
# amaral@ucsc.edu
# Student ID: 1454995
# CMPS101, Programming Assignment-2(pa)
# Date: 10/13/17
###############################################*/

//-----------------------------------------------------------------------------
// List.c
// Implementation file for List ADT
//-----------------------------------------------------------------------------

# include "List.h"

// Note: Structs are defined in List.h file.

// Constructors-Destructors ---------------------------------------------------

// Creates(allocates memory and initializes) a new empty list and returns the pointer to it.
List newList(void)
{ 
    List list = NULL;
    list = malloc(sizeof(listObj));
    if(list != NULL)
    {
        list->front = list->back = list->cursor = NULL;
        list->length = 0;
        list->index = -1;
        return list;
    }
    else // if list == NULL
    {   
        printf("List Error: newList() failed allocating memory space for the list.\n");
        exit(1);
        return NULL;
    }
}

// Frees all the heap memory associated with its List* argument, and sets *pL to NULL.
void freeList(List *pL)
{
    if(pL != NULL && *pL != NULL)
    {
        // We start deleting and free()ing the elements of the list using the cursor.
        moveFront(*pL);
        listNode *previousPlaceOfCursor = (*pL)->cursor;
        while(previousPlaceOfCursor != NULL)
        {
            moveNext(*pL);
            freeNode(previousPlaceOfCursor);
            previousPlaceOfCursor = (*pL)->cursor;
        }
        (*pL)->front = (*pL)->back = (*pL)->cursor = NULL; 
        (*pL)->length = 0;
        (*pL)->index = -1;
        free(*pL);
        *pL = NULL;
    }
    else
    {
        printf("List Error: freeList() called on an empty List.\n");
        exit(1);
    }
    return;
}

// Creates(allocates memory and initializes) a new empty node.
// Data is set to nodeData and pointers to NULL.
// This is a helper function only used in List.c
listNode *newNode(int nodeData)
{
    listNode *node = NULL;
    node = malloc(sizeof(listNode));
    if(node != NULL)
    {
        node->next = node->previous = NULL;
        node->data = nodeData;
        return node;
    }
    else // if node == NULL
    {   
        printf("List Error: newNode() failed allocating memory space for the node.\n");
        exit(1);
        return NULL;
    }
}

// Frees all the heap memory associated with its listNode* argument, and sets *node to NULL.
// This is a helper function only used in List.c
void freeNode(listNode *node)
{
    if(node != NULL)
    {
        node->next = node->previous = NULL;
        free(node);
        node = NULL;
    }
    else
    {
        printf("List Error: freeNode() is called on a non-existing node.\n");
        exit(1);
    }
    return;
}


// Access functions -----------------------------------------------------------

// Returns true if this List is empty, false otherwise.
bool isEmpty(List L)
{
    if(L != NULL)
    {
        return L->length == 0;
    }
    else
    {
        printf("List Error: isEmpty() is called on a non-existing list.\n");
        exit(1);
    }
}

// Returns the number of elements in this List.
int length(List L)
{
    if(L != NULL)
    {
        return L->length;
    }
    else
    {
        printf("List Error: length() is called on a non-existing list.\n");
        exit(1);
    }
}

// If cursor is defined, returns the index of the cursor element, otherwise returns -1.
// Precondition: cursor != null(cursor is defined).
int index(List L)
{
    if(L != NULL)
    {
        if (L->cursor != NULL)
        {
            return L->index;
        }
        return -1;
    }
    else
    {
        printf("List Error: index() is called on a non-existing list.\n");
        exit(1);
    }
}

// Returns front element.
// Precondition: !this.isEmpty() which means length() > 0.
int front(List L)
{
    if(L != NULL)
    {
        if(isEmpty(L)) // if length() == 0.
        {
            printf("List Error: front() is called on an empty List.\n");
            exit(1);
        }
        return (L->front)->data;
    }
    else
    {
        printf("List Error: front() is called on a non-existing list.\n");
        exit(1);
    }
}

// Returns back element.
// Precondition: !this.isEmpty() which means length() > 0.
int back(List L)
{
    if(L != NULL)
    {
        if(isEmpty(L)) // if length() == 0.
        {
            printf("List Error: back() is called on an empty List.\n");
            exit(1);
        }
        return (L->back)->data;
    }
    else
    {
        printf("List Error: back() is called on a non-existing list.\n");
        exit(1);
    }
}

// Returns cursor element.
// Precondition: length() > 0, index()>=0.
int get(List L)
{
    if(L != NULL)
    {
        int cursorIndex = index(L);
        if(!isEmpty(L) && cursorIndex >= 0) // if length() !=0 and index >= 0.
        {
            return L->cursor->data;
        }
        else
        {
            printf("List Error: get() called on an empty List or index < 0.\n");
            exit(1);
        }
    }
    else
    {
        printf("List Error: get() is called on a non-existing list.\n");
        exit(1);
    }
}

// Returns true if and only if this List A and B are the same
// integer sequence. The states of the cursors in the two Lists
// are not used in determining equality.
int equals(List A, List B)
{
    if(A == NULL || B == NULL)
    {
        printf("List Error: equals() called on an empty List(s).\n");
        exit(1);
    }
    bool eq  = false;
    listNode *N, *M;
    if(A != NULL && B != NULL)
    {
        N = A->front;
        M = B->front;
        eq = (A->length == B->length);
        while(eq && N != NULL && M != NULL)
        {
            eq = (N->data == M->data);
            N = N->next;
            M = M->next;
        }
    }
    return eq;
}


// Manipulation procedures ----------------------------------------------------

// Resets this List to its original empty state if it exists, otherwise does nothing.
void clear(List L)
{
    if(L != NULL)
    {
        if(!isEmpty(L)) // If the list is not empty.
        {
            moveFront(L);
            listNode *previousPlaceOfCursor = L->cursor;
            while(previousPlaceOfCursor != NULL)
            {
                moveNext(L);
                freeNode(previousPlaceOfCursor);
                previousPlaceOfCursor = (L)->cursor;
            }
            L->front = L->back = L->cursor = NULL; 
            L->length = 0;
            L->index = -1;
        }
    }
    return;
}

// If List is non-empty, places the cursor under the front element, otherwise does nothing.
void moveFront(List L)
{
    if(L != NULL)
    {
        if(!isEmpty(L)) // If the list is not empty.
        {
            L->cursor = L->front;
            L->index = 0;
        }
    }
    else
    {
        printf("List Error: moveFront() is called on a non-existing list.\n");
        exit(1);
    }
    return;
}

// If List is non-empty, places the cursor under the back element, otherwise does nothing.
void moveBack(List L)
{
    if(L != NULL)
    {
        if(!isEmpty(L)) // If the list is not empty.
        {
            L->cursor = L->back;
            L->index = (L->length - 1);
        }
    }
    else
    {
        printf("List Error: moveBack() is called on a non-existing list.\n");
        exit(1);
    }
    return;
}

// If cursor is defined and not at front, moves cursor one step toward
// front of this List, if cursor is defined and at front, cursor becomes
// undefined, if cursor is undefined does nothing.
void movePrev(List L)
{
    if(L != NULL)
    {
        if(L->cursor != NULL && L->cursor != L->front)
        {
            listNode *cursorNode = NULL;    // SIMPLIFY THIS PART TO L->CURSOR = L->CURSOR->PREVIOUS
            cursorNode = L->cursor;
            cursorNode = cursorNode->previous;
            L->cursor = cursorNode;
            L->index += -1;     // SIMPLIFY TO --(L->index)
        }
        else if(L->cursor != NULL && L->cursor == L->front)
        {
            L->cursor = NULL;
            L->index = -1;
        }
    }
    else
    {
        printf("List Error: movePrev() is called on a non-existing list.\n");
        exit(1);
    }
    return;
}

// If cursor is defined and not at back, moves cursor one step toward
// back of this List, if cursor is defined and at back, cursor becomes
// undefined, if cursor is undefined does nothing.
void moveNext(List L)
{
    if(L != NULL)
    {
        if(L->cursor != NULL && L->cursor != L->back)
        {
            listNode *cursorNode = NULL;    // SIMPLIFY THIS PART TO L->CURSOR = L->CURSOR->PREVIOUS
            cursorNode = L->cursor;
            cursorNode = cursorNode->next;
            L->cursor = cursorNode;
            L->index += 1;      // SIMPLIFY TO --(L->index)
        }
        else if(L->cursor != NULL && L->cursor == L->back)
        {
            L->cursor = NULL;
            L->index = -1;
        }
    }
    else
    {
        printf("List Error: moveNext() is called on a non-existing list.\n");
        exit(1);
    }
    return;
}

// Insert new element into this List. If List is non-empty,
// insertion takes place before front element.
void prepend(List L, int data)
{
    if(L == NULL)
    {
        printf("List Error: prepend() called on an non-existing List.\n");
        exit(1);
    }
    listNode *node = newNode(data);
    int cursorIndex = index(L);
    // PARTS OF THE IF ELSE STATEMENT CAN BE COMBINED AS:
    // NODE->PREVIOUS = NULL
    // NODE->NEXT = L->FRONT??
    // L->FRONT = NODE AFTER THE IF ELSE STATEMENT
    // IS THIS OPTIMIZATION GOOD FOR COMPREHENSION OR NOT?
    if(!isEmpty(L)) // If the list is not empty.
    {
        node->previous = NULL;
        node->next = L->front;
        L->front->previous = node;
        L->front = node;
        if (L->length == 1)     // THIS IS UNNECESSARY?
        {
            L->back = node->next;
        }
    }
    else // If the list is empty.
    {
        node->previous = NULL;
        node->next = NULL;
        L->front = L->back = node;
    }

    // Since we prepend a node, it will always increase the index by 1. This is
    // also true when our index is 0 i.e. cursor is at the front.
    if (cursorIndex != -1)
    {
        L->index += 1;  // ++(L->INDEX)
    }
    L->length += 1;     // ++(L->LENGTH)
    return;
}

// Insert new element into this List. If List is non-empty,
// insertion takes place after back element.
// Since we append a node, it will never increase the index by 1. This is also
// true when our index is n - 1 i.e. cursor is at the back. This is because we
// technically (list might be empty) always insert after the back element.
void append(List L, int data)
{
    if(L == NULL)
    {
        printf("List Error: append() called on an non-existing List.\n");
        exit(1);
    }
    listNode *node = newNode(data);
    // PARTS OF THE IF ELSE STATEMENT CAN BE COMBINED AS:
    // NODE->NEXT = NULL
    // NODE->PREVIOUS = L->BACK??
    // L->BACK = NODE AFTER THE IF ELSE STATEMENT
    // IS THIS OPTIMIZATION GOOD FOR COMPREHENSION OR NOT?
    if(!isEmpty(L)) // If the list is not empty.
    {
        node->previous = L->back;
        node->next = NULL;
        L->back->next = node;
        L->back = node;
        if(L->length == 1)      // THIS IS UNNECESSARY?
        {
            L->front = node->previous;
        }
    }
    else // If the list is empty.
    {
        node->previous = NULL;
        node->next = NULL;
        L->front = L->back = node;
    }
    L->length += 1;     //++(L->LENGTH)
    return;
}

// Insert new element before cursor.
// Pre: length() > 0, index() >= 0
// CHECK DOUBLY LINKED LIST IMPLEMENTATIONS TO SEE IF THERE CAN BE ANY
// OPTIMIZATION IN TERMS OF INSERTING!
void insertBefore(List L, int data)
{
    if(L == NULL)
    {
        printf("List Error: insertBefore() called on an non-existing List.\n");
        exit(1);
    }

    int cursorIndex = index(L);
    if(!isEmpty(L) && cursorIndex >= 0) // if length() !=0 and index >= 0.
    {
        if(L->cursor == L->front) // Cursor is defined and at the front, prepend!
        {
            prepend(L, data);
        }
        else if(L->cursor == L->back) // Cursor defined and at the back, put it before the back element.
        {
            listNode *node = newNode(data);
            node->previous = L->back->previous;
            L->back->previous->next = node;
            L->back->previous = node;
            node->next = L->back;
            L->index += 1;
            L->length += 1;
        }
        else // Cursor is defined and somewhere in the middle
        {
            listNode *node = newNode(data);
            node->previous = L->cursor->previous;
            L->cursor->previous->next = node;
            L->cursor->previous = node;
            node->next = L->cursor;
            L->index += 1;
            L->length += 1;
        }
    }
    else
    {
        printf("List Error: insertBefore() called on an empty List or index < 0.\n");
        exit(1);
    }
    return;
}

// Inserts new element after cursor.
// Pre: length() > 0, index() >= 0
// CHECK DOUBLY LINKED LIST IMPLEMENTATIONS TO SEE IF THERE CAN BE ANY
// OPTIMIZATION IN TERMS OF INSERTING!
void insertAfter(List L, int data)
{
    if(L == NULL)
    {
        printf("List Error: insertAfter() called on an non-existing List.\n");
        exit(1);
    }
    int cursorIndex = index(L);
    if(!isEmpty(L) && cursorIndex >= 0) // if length() !=0 and index >= 0.
    {
        if(L->cursor == L->back) // Cursor is defined and at the back, append!
        {
            append(L, data);
        }
        else if(L->cursor == L->front) // Cursor defined and at the front, put it after the front element.
        {
            listNode *node = newNode(data);
            L->front->next->previous = node;
            node->next = L->front->next;
            L->front->next = node;
            node->previous = L->front;
            L->index += 1;  // SINCE THE INDEX IS AT THE FRONT ELEMENT, WE SHOULDN'T INCREASE THE INDEX! DELETE THIS AFTER TESTING!
            L->length += 1;
        }
        else // Cursor is defined and somewhere in the middle
        {
            listNode *node = newNode(data);
            node->next = L->cursor->next;
            node->previous = L->cursor;
            L->cursor->next->previous = node;
            L->cursor->next = node;
            L->index += 1;  // SINCE THE INDEX IS AT THE ELEMENT THAT WE INSERT AFTER, WE SHOULDN'T INCREASE THE INDEX! DELETE THIS AFTER TESTING!
            L->length += 1;
        }
    }
    else
    {
        printf("List Error: insertAfter() called on an empty List or index < 0.\n");
        exit(1);
    }
    return;
}


// Deletes the front element. Pre: length() > 0.
// CHECK DOUBLY LINKED LIST IMPLEMENTATIONS TO SEE IF THERE CAN BE ANY
// OPTIMIZATION IN TERMS OF INSERTING!
void deleteFront(List L)
{
    if(L == NULL)
    {
        printf("List Error: deleteFront() called on an non-existing List.\n");
        exit(1);
    }
    listNode *frontTemp = NULL;
    int cursorIndex = index(L);
    if(!isEmpty(L)) // if length() != 0.
    {
        if(L->front == L->back)
        {
            freeNode(L->front); // Note: sets L->front = NULL too.
            L->front = L->back = L->cursor = NULL; 
            L->length = 0;
            L->index = -1;
            return;
        }
        frontTemp = L->front;
        L->front->next->previous = NULL;
        if(cursorIndex != -1)
        {
            if(L->cursor == L->front)
            {
                L->cursor = NULL;
                L->index = -1;
            }
            else
            {
                L->index += -1;     // CHANGE TO L->INDEX -= 1!
            }
        }
        L->front = L->front->next;
        freeNode(frontTemp); // Note: sets frontTemp = NULL too.
        L->length += -1;    // CHANGE TO L->LENGTH -= 1!
    }
    else
    {
        printf("List Error: deleteFront() called on an empty List.\n");
        exit(1);
    }
    return;
}

// Deletes the back element. Pre: length() > 0
void deleteBack(List L)
{
    if(L == NULL)
    {
        printf("List Error: deleteBack() called on an non-existing List.\n");
        exit(1);
    }
    listNode *backTemp = NULL;
    int cursorIndex = index(L);
    if(!isEmpty(L)) // if length() != 0.
    {
        if(L->back == L->front)
        {
            freeNode(L->back); // Note: sets L->back = NULL too.
            L->front = L->back = L->cursor = NULL; 
            L->length = 0;
            L->index = -1;
            return;
        }
        backTemp = L->back;
        L->back->previous->next = NULL;
        if(cursorIndex != -1)
        {
            if(L->cursor == L->back)
            {
                L->cursor = NULL;
                L->index = -1;
            }
        }
        L->back = L->back->previous;
        freeNode(backTemp); // Note: sets backTemp = NULL too.
        L->length += -1;
    }
    else
    {
        printf("List Error: deleteBack() called on an empty List.\n");
        exit(1);
    }
    return;
}

// Deletes cursor element, making cursor undefined.
// Pre: length() > 0, index() >= 0
void delete(List L)
{
    if(L == NULL)
    {
        printf("List Error: delete() called on an non-existing List.\n");
        exit(1);
    }
    int cursorIndex = index(L);
    if(!isEmpty(L) && cursorIndex >= 0) // if length() !=0 and index >= 0.
    {
        if(L->cursor == L->front)
        {
            deleteFront(L);
        }
        else if(L->cursor == L->back)
        {
            deleteBack(L);
        }
        else // Cursor is somewhere in the middle.
        {
            L->cursor->previous->next = L->cursor->next;
            L->cursor->next->previous = L->cursor->previous;
            freeNode(L->cursor); // Note: sets L->cursor = NULL too.
            L->index = -1;
            L->length += -1;
        }
    }
    else
    {
        printf("List Error: delete() called on an empty List.\n");
        exit(1);
    }
    return;
}


// Other operations -----------------------------------------------------------

// Prints the list to the file pointed to by out, formatted as a space-separated string. This
// function plays roughly the same role as the toString() function in Java.
void printList(FILE *out, List L)
{
    if(L == NULL)
    {
        printf("List Error: printList() called on a non-existing List.\n");
        exit(1);
    }
    
    if(out == NULL)
    {
        printf("List Error: printList() file point by FILE *out doesn't exits i.e out == NULL.\n");
        exit(1);
    }
        
    bool firstElementNoSpace = true;
    for(moveFront(L); index(L) >= 0; moveNext(L))
    {
        if(firstElementNoSpace == true)
        {
            fprintf(out, "%d", get(L));
            firstElementNoSpace = false;
        }
        else
        {
            fprintf(out, " %d", get(L));
        }
    }
    return;
}

// Returns a new List representing the same integer sequence as this
// List. The cursor in the new list is undefined, regardless of the
// state of the cursor in this List. This List is unchanged.
// Returns a new List identical to this List.
List copyList(List L)
{
    if(L != NULL)
    {
        List newCopyList = newList();
        listNode *backUpCursor = L->cursor;
        int backUpCursorIndex = index(L);
        if(newCopyList != NULL)
        {
            for(moveFront(L); index(L) >= 0; moveNext(L))
            {
                append(newCopyList, get(L));
            }
            L->index = backUpCursorIndex;
            L->cursor = backUpCursor;
            return newCopyList;
        }
        else
        {
            printf("List Error: copyList() failed.\n");
            exit(1);
        }
    }
    else
    {
        printf("List Error: copyList() is called on a non-existing list.\n");
        exit(1);
    }
    return NULL;
}