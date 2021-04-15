/* This is an implementation of a stack data structure as described in CLRS
   starting at page 232 and ending at page 234. It has some modifications
   in order to make the stack dynamic. */

/* TO DO: Implement the data structures as described in CLRS starting at page
          232 and ending at page 234 */

#include "anil_stack.h"

/**
 * @return true if the stack is empty and false if not.
 * @brief This function checks if a stack is empty or not.
 * @author Anil Celik Maral, 2021.04.14  */
bool anil::stack::is_empty() {
    return top == 0;
}

/**
 * @return true if the stack is full and false if not.
 * @brief This function checks if a stack is full or not.
 * @author Anil Celik Maral, 2021.04.14  */
bool anil::stack::is_full() {
    return top + 1 == size;
}

/**
 * @param value is the value that will be inserted to the stack.
 * @return void
 * @brief The function inserts a new element into the stack. This new element 
 *        is placed at the top of the stack and is indexed by the stack.top
 *        member. If the stack is full, the size is doubled and then the
 *        element is inserted.
 * @author Anil Celik Maral, 2021.04.14  */
void anil::stack::push(int value) {
  if (is_empty()) {
    array[++top] = value;
  } else if (is_full()) {
    size *= growth_factor;
    int* temp = new int[size];
    for (int i = 0; i < size; ++i) {
      temp[i] = array[i];
    }
    delete[] array;
    array = temp;
    array[++top] = value;

  // If the array for the stack hasn't been created, create it!
  } else if (size == 0) {
    array = new int[growth_factor];
    size = growth_factor;
    array[top] = value;        
  }
  return;
}
