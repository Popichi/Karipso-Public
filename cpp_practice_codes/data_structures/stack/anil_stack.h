/* This is an implementation of a stack data structure as described in CLRS
   starting at page 232 and ending at page 234. It has some modifications
   in order to make the stack dynamic. */

/* TO DO: Implement the data structures as described in CLRS starting at page
          232 and ending at page 234 */

#ifndef ANIL_STACK_H
#define ANIL_STACK_H

namespace anil {
  class stack {
    private:
      int top;
      int size;
      int* array;
      int growth_factor;

    public:
      stack() : top(0), size(0) {}
      void push(int value); // Place an entity onto the top of the stack.
      int pop(void);        // Remove an entity from the top of the stack and return it.
      int peek(void);       // Look at the entity at the top of stack, but don't remove it.
      bool is_empty(void);  // A boolean value, true if the stack is empty and false if it has at least one element.
      bool is_full(void);
      ~stack();
  };
}

#endif /* ANIL_STACK_H */