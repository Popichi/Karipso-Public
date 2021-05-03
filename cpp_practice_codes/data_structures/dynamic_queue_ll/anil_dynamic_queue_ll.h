// This is an implementation of queue as a dynamically growing linked list

/* TO DO: 1) Add the function documentation
          2) Add the credits etc.
          3) Add the time and memory big 0s in the function documentation */

#ifndef ANIL_DYNAMIC_QUEUE_LL_H
#define ANIL_DYNAMIC_QUEUE_LL_H

#include <cstddef>

namespace anil {

    class queue {
        private:

            struct node {
                int data;
                node* next;
            };

            node* head;
            node* tail;

            bool is_empty();
            bool is_full();

        public:
            queue() : head(NULL), tail(NULL) {}
            void enqueue(int new_data);
            int dequeue();
            ~queue();
    };
}

#endif /* ANIL_DYNAMIC_QUEUE_LL_H */