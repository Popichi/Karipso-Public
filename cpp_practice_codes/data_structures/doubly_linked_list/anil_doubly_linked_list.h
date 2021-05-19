/* This is an implementation of a linked list as a dynamic, unsorted and
   doubly-linked list!
   
   The implementation is based on the linked list specified in CLRS */

/* TO DO: 1) Code a singly linked version of this linked list */

#ifndef ANIL_DOUBLY_LINKED_LIST_H
#define ANIL_DOUBLY_LINKED_LIST_H

#include <cstddef>

namespace anil {

    struct node {
        int data;
        node* next;
        node* prev;
    };

    class linked_list {
        private:

            node* head;

        public:
            linked_list() : head(NULL) {}
            void insert(int new_data);
            int remove(node* x);
            node* search(int data);
            bool is_empty();
            ~linked_list();
    };
}

#endif /* ANIL_DOUBLY_LINKED_LIST_H */