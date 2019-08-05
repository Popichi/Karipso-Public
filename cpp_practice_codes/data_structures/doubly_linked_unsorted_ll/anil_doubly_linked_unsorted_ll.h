/* This is an implementation of linked list as a dynamically growing
   unsorted and doubly-linked list! */

/* TO DO: 1) Should I do anything with the tail member?*/

#ifndef ANIL_DOUBLY_LINKED_UNSORTED_LL_H
#define ANIL_DOUBLY_LINKED_UNSORTED_LL_H

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

            bool is_empty();
            bool is_full();

        public:
            linked_list() : head(NULL), tail(NULL) {}
            void insert(int new_data);
            void remove(node* x);
            node* search(int data);
            ~linked_list();
    };
}

#endif /* ANIL_DOUBLY_LINKED_UNSORTED_LL_H */