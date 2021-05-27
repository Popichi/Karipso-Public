/* This is an implementation of a linked list as a dynamic, unsorted and
   singly-linked list!
*/

/* TO DO: 1) Post your code to codereview.stackexchange*/

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
      node* tail;

    public:
      singly_linked_list() : head(nullptr), tail(nullptr) {}
      void insert(int new_data);
      int remove(node* node_to_be_removed);
      node* search(int data);
      bool is_empty();
      ~singly_linked_list();
  };
}

#endif /* ANIL_SINGLY_LINKED_LIST_H */