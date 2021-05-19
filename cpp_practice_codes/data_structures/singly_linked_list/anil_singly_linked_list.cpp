/* This is an implementation of a linked list as a dynamic, unsorted and
   doubly-linked list!
*/

/* TO DO: 1) Post you code to codereview.stackexchange*/

#include "anil_singly_linked_list.h"

/**
 * @param void
 * @return void
 * @brief This function checks if there are any nodes in the linked list.
 * @time complexity: O(1)
 * @space complexity: O(1)
 * @author Anil Celik Maral, 2021.05.19 */
bool anil::singly_linked_list::is_empty() {
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
 * @author Anil Celik Maral, 2021.05.19 */
void anil::singly_linked_list::insert(int new_data) {
    node* temp;
    temp = new node;
    temp->data = new_data;
    temp->next = head;
    head = temp;
}

/**
 * @param node is the pointer to the node that will be removed from the
 *             linked list.
 * @return the element that was stored inside the removed node.
 * @brief This function removes the node by updating the pointers of the
 *        previous and next nodes before deleting the node.
 * @time complexity: O(1). However, if we wish to delete an element with a
 *       given key, O(n) time is required in the worst case because we must
 *       first call the "search" function to find the node.
 * @space complexity: O(1)
 * @credit This function was partly inspired by the LIST-DELETE function
 *         description at page 238 of CLRS 3rd Edition.
 * @author Anil Celik Maral, 2019.07.21
 * @update Anil Celik Maral, 2021.05.03  */
int anil::singly_linked_list::remove(node* x) {
  // If the node is the head
  if (x == head) {
    head = x->next;
  // If the node is somewhere in between the head and tail (including tail).
  } else (x->next == NULL) {
    // Search for the node before the node that we want to delete so that
    // we can connect it to the node (or nullptr) that comes after the node
    // that we want to delete
    int removed_element (0);
    for (node* temp = head; temp->next != nullptr; temp = temp->next) {
      if (temp->next-> == x) {
        removed_element = temp->next->data;
        temp->next = temp->next->next;
        delete temp->next;
        break;
      }
    }
  }

  return removed_element;
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
