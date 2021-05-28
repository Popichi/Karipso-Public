/* This is an implementation of a linked list as a dynamic, unsorted and
   doubly-linked list!
   
   The implementation is based on the linked list specified in CLRS */

/* TO DO: 1) */

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
            node* tail;

        public:
            linked_list() : head(nullptr), tail(nullptr) {}
            void insert(int new_data);
            int remove(node* x);
            node* search(int data);
            bool is_empty();
            ~linked_list();
    };
}

#endif /* ANIL_DOUBLY_LINKED_LIST_H */