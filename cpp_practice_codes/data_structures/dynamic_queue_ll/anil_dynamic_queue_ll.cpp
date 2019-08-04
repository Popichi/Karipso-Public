// This is an implementation of queue as a dynamically growing linked list

#include "anil_dynamic_queue_ll.h"

bool anil::queue::is_empty() {
    return head == NULL;
}

bool anil::queue::is_full() {
    // 2 * current capacity = new capacity
}

void anil::queue::enqueue(int new_data) {
    node* temp;
    temp = new node;
    temp->data = new_data;
    temp->next = NULL;
    if (tail == NULL) {
        tail = head = temp;
    } else {
        tail->next = temp;
        tail = temp;
    }
}

int anil::queue::dequeue() {
    if (!is_empty()) {
        node* temp = head;
        int temp_data = temp->data;
        head = head->next;
        delete temp;
        if (is_empty()) {
            tail = NULL;
        }
        return temp_data;
    } else {
        // Update it to throw an exception
    }
}

anil::queue::~queue() {
    while (!is_empty()) {
        dequeue();
    }
}
