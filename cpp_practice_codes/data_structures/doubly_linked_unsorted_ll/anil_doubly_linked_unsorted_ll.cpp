/* This is an implementation of linked list as a dynamically growing
   unsorted and doubly-linked list!
   
   The implementation is based on the linked list specified in CLRS */

#include "anil_doubly_linked_unsorted_ll.h"

bool anil::linked_list::is_empty() {
    return head == NULL;
}

bool anil::linked_list::is_full() {
    // 2 * current capacity = new capacity
}

void anil::linked_list::insert(int new_data) {
    node* temp;
    temp = new node;
    temp->data = new_data;
    temp->next = head;

    // If the linked list is not empty
    if (!is_empty()) {
        head->prev = temp;
    }

    head = temp;
    temp->prev = NULL;
}
    
void anil::linked_list::remove(node* x) {
    // If the element is not the head
    if (x->prev != NULL) {
        x->prev->next = x->next;

    // If the element is the head
    } else {
        head = x->next;
    }

    // If the element is not the tail
    if (x->next != NULL) {
        x->next->prev = x->prev;
    }

    delete x;
}

anil::node* anil::linked_list::search(int data) {
    node* temp = head;
    while (temp != NULL && temp->data != data) {
        temp = temp->next;
    }
    return temp;
}

anil::linked_list::~linked_list() {
    while (!is_empty()) {
        remove(head);
    }
}
