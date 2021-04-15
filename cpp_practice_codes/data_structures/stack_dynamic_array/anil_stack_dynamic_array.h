/* This is an implementation of a stack data structure as described in CLRS
   starting at page 232 and ending at page 234. It has some modifications
   in order to make the stack dynamic and more usable. */

/* TO DO: Implement the data structures as described in CLRS starting at page
          232 and ending at page 234 */

#ifndef ANIL_STACK_H
#define ANIL_STACK_H

#include <iostream>

namespace anil {
  class stack {
    private:
      int top;
      int size;
      int* array;
      int growth_factor;

    public:
      stack() : top(0), size(0) {}
      void push(int value);
      int pop(void);
      int peek(void);
      bool is_empty(void);
      bool is_full(void);
      ~stack();
  };
}

#endif /* ANIL_STACK_H */