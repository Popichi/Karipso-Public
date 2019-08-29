/*###############################################
# Name: Anil Celik Maral
# Cruz ID: amaral
# amaral@ucsc.edu
# Student ID: 1454995
# CMPS101, Programming Assignment-2(pa)
# Date: 10/13/17
###############################################*/

# ifndef _listADT
# define _listADT

# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdbool.h>


// structs --------------------------------------------------------------------

// private nodeObj type
typedef struct nodeObj listNode;

struct nodeObj
{
    int data;
    listNode *next;
    listNode *previous;
};

// private listObj type
typedef struct listObj
{
    int index;
    uint32_t length;
    listNode *front;
    listNode *back;
    listNode *cursor;
} listObj;

typedef struct listObj *List;


// Constructors-Destructors ---------------------------------------------------

// Creates(allocates memory and initializes) a new empty list and returns the pointer to it.
List newList(void);

// Frees all the heap memory associated with its List* argument, and sets *pL to NULL.
void freeList(List *pL);

// Creates(allocates memory and initializes) a new empty node.
// Data is set to nodeData and pointers to NULL.
// This is a helper function only used in List.c
listNode *newNode(int nodeData);

// Frees all the heap memory associated with its listNode* argument, and sets *node to NULL.
// This is a helper function only used in List.c
void freeNode(listNode *node);

// Access functions -----------------------------------------------------------

// Returns true if this List is empty, false otherwise.
// This is a helper function only used in List.c
bool isEmpty(List L);

// Returns the number of elements in this List.
int length(List L);

// If cursor is defined, returns the index of the cursor element, otherwise returns -1.
// Precondition: cursor != null(cursor is defined).
int index(List L);

// Returns front element.
// Precondition: !this.isEmpty() which means length() > 0.
int front(List L);

// Returns back element.
// Precondition: !this.isEmpty() which means length() > 0.
int back(List L);

// Returns cursor element.
// Precondition: length() > 0, index()>=0.
int get(List L);

// Returns true if and only if this List and L are the same
// integer sequence. The states of the cursors in the two Lists
// are not used in determining equality.
int equals(List A, List B);


// Manipulation procedures ----------------------------------------------------

// Resets this List to its original empty state if it exists, otherwise does nothing.
void clear(List L);

// If List is non-empty, places the cursor under the front element, otherwise does nothing.
void moveFront(List L);

// If List is non-empty, places the cursor under the back element, otherwise does nothing.
void moveBack(List L);

// If cursor is defined and not at front, moves cursor one step toward
// front of this List, if cursor is defined and at front, cursor becomes
// undefined, if cursor is undefined does nothing.
void movePrev(List L);

// If cursor is defined and not at back, moves cursor one step toward
// back of this List, if cursor is defined and at back, cursor becomes
// undefined, if cursor is undefined does nothing.
void moveNext(List L);

// Insert new element into this List. If List is non-empty,
// insertion takes place before front element.
void prepend(List L, int data);

// Insert new element into this List. If List is non-empty,
// insertion takes place after back element.
void append(List L, int data);

// Insert new element before cursor.
// Pre: length()  >0, index()>= 0
void insertBefore(List L, int data);

// Inserts new element after cursor.
// Pre: length() > 0, index() >= 0
void insertAfter(List L, int data);

// Deletes the front element. Pre: length() > 0.
void deleteFront(List L);

// Deletes the back element. Pre: length() > 0
void deleteBack(List L);

// Deletes cursor element, making cursor undefined.
// Pre: length() > 0, index() >= 0
void delete(List L);


// Other operations -----------------------------------------------------------

//Prints the list into the output file.
void printList(FILE *out, List L);

// Returns a new List representing the same integer sequence as this
// List. The cursor in the new list is undefined, regardless of the
// state of the cursor in this List. This List is unchanged.
// Returns a new List identical to this List.
List copyList(List L);

# endif