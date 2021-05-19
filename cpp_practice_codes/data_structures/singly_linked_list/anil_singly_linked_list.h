/* This is an implementation of a linked list as a dynamic, unsorted and
   singly-linked list!
*/

/* TO DO: 1) Post you code to codereview.stackexchange*/

#ifndef ANIL_SINGLY_LINKED_LIST_H
#define ANIL_SINGLY_LINKED_LIST_H

#include <cstddef>

namespace anil {

  struct node {
    int data;
    node* next;
  };

  class singly_linked_list {
    private:
      node* head;

    public:
      singly_linked_list() : head(NULL) {}
      void insert(int new_data);
      int remove(node* x);
      node* search(int data);
      bool is_empty();
      ~singly_linked_list();
  };
}

#endif /* ANIL_SINGLY_LINKED_LIST_H */