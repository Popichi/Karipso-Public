/* This is an implementation of linked list as a dynamically growing
   unsorted and doubly-linked list! */

#ifndef ANIL_DOUBLY_LINKED_UNSORTED_LL_H
#define ANIL_DOUBLY_LINKED_UNSORTED_LL_H

#include <cstddef>

namespace anil {

    class linked_list {
        private:

            struct node {
                int key;
                node* next;
                node* prev;
            };

            node* head;
            node* tail;

            bool is_empty();
            bool is_full();

        public:
            linked_list() : head(NULL), tail(NULL) {}
            void insert(int new_data);
            void remove();
            node* search();
            ~linked_list();
    };
}

#endif /* ANIL_DOUBLY_LINKED_UNSORTED_LL_H */