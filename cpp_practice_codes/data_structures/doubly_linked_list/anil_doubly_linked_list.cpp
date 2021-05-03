/* This is an implementation of a linked list as a static, unsorted and
   doubly-linked list!
   
   The implementation is based on the linked list specified in CLRS */

/* TO DO: 1) Code a dynamic version of this linked list */

#include "anil_doubly_linked_list.h"

/**
 * @param void
 * @return void
 * @brief This function checks if there are any nodes in the linked list.
 * @time complexity: O(1)
 * @space complexity: O(1)
 * @author Anil Celik Maral, 2019.07.21
 * @update Anil Celik Maral, 2021.04.28  */
bool anil::linked_list::is_empty() {
    return head == NULL;
}

/**
 * @param new_data is the element that will be inserted into the linked list.
 * @return void
 * @brief This function insert the element new_data into the linked list
 *        by creating a new node, whose element is new_data, and splicing
 *        this node onto the front of the linked list.
 * @time complexity: O(1)
 * @space complexity: O(1)
 * @credit This function was partly inspired by the LIST-INSERT function
 *         description at page 238 of CLRS 3rd Edition.
 * @author Anil Celik Maral, 2019.07.21
 * @update Anil Celik Maral, 2021.04.26  */
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

/**
 * @param node is the pointer to the node that will be removed from the
 *             linked list.
 * @return the element that was stored inside the removed node.
 * @brief This function removes the node by updating the pointers of the
 *        previous and next nodes before deleting the node.
 * @time complexity: O(1). However, if we wish to delete an element with a
 *       given key, O(n) time is required in the worst case because we must
 *       first call the "insert" function to find the node.
 * @space complexity: O(1)
 * @credit This function was partly inspired by the LIST-DELETE function
 *         description at page 238 of CLRS 3rd Edition.
 * @author Anil Celik Maral, 2019.07.21
 * @update Anil Celik Maral, 2021.05.03  */
int anil::linked_list::remove(node* x) {
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

    int temp = x->data;

    delete x;

    return temp;
}

/**
 * @param data is the element that will be searched in the linked list.
 * @return the pointer to the node that contains the element data or the null
 *         pointer if no node contains the element data.
 * @brief This function finds the first node with the element data by a simple
 *        linear search, returning a pointer to this node. If no element with
 *        data appears in the list, then the procedure returns NULL.
 * @time complexity: O(n)
 * @space complexity: O(1)
 * @credit This function was partly inspired by the LIST-SEARCH function
 *         description at page 237 of CLRS 3rd Edition.
 * @author Anil Celik Maral, 2019.07.21
 * @update Anil Celik Maral, 2021.04.26  */
anil::node* anil::linked_list::search(int data) {
    node* temp = head;
    while (temp != NULL && temp->data != data) {
        temp = temp->next;
    }
    return temp;
}

/**
 * @param void
 * @return void
 * @brief This function iteratively deletes all of the nodes, if any,
 *        in the linked list.
 * @time complexity: O(n)
 * @space complexity: O(1)
 * @author Anil Celik Maral, 2019.07.21
 * @update Anil Celik Maral, 2021.04.28  */
anil::linked_list::~linked_list() {
    while (!is_empty()) {
        remove(head);
    }
}
