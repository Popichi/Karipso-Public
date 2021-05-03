/* This is an implementation of a stack data structure as described in CLRS
   starting at page 232 and ending at page 234. It has some modifications
   in order to make the stack dynamic and more usable. */

/* TO DO: 1) Add the time and memory big 0s in the function documentation */

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
      stack() : top(0), size(0), array(nullptr), growth_factor(2) {}
      void push(int value);
      int pop(void);
      int peek(void);
      bool is_empty(void);
      bool is_full(void);
      ~stack();
  };
}

#endif /* ANIL_STACK_H */