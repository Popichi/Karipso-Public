/* This is an implementation of a linked list as a dynamic, unsorted and
   doubly-linked list!
*/

/* TO DO: 1) Post your code to codereview.stackexchange*/

#include "anil_singly_linked_list.h"

/**
 * @param void
 * @return void
 * @brief This function checks if there are any nodes in the linked list.
 * @time complexity: O(1)
 * @space complexity: O(1)
 * @author Anil Celik Maral, 2021.05.19 */
bool anil::singly_linked_list::is_empty() {
  return head == nullptr;
}

/**
 * @param new_data is the element that will be inserted into the linked list.
 * @return void
 * @brief This function insert the element new_data into the linked list
 *        by creating a new node, whose element is new_data, and splicing
 *        this node onto the back of the linked list.
 * @time complexity: O(1)
 * @space complexity: O(1)
 * @author Anil Celik Maral, 2021.05.19
 * @update Anil Celik Maral, 2021,05.27 */
void anil::singly_linked_list::insert(int new_data) {
  node* temp;
  temp = new node;
  temp->data = new_data;
  if (is_empty()) {
    head = temp;
    tail = head;
  } else {
    tail->next = temp;
    tail = temp;
  }
  temp->next = nullptr;
}

/**
 * @param node_to_be_removed is the pointer to the node that will be removed
 *        from the linked list.
 * @return the element that was stored inside the removed node.
 * @brief This function removes the node by connecting the node that comes
 *        before it to the node that comes after it.
 * @time complexity: O(n) because if we wish to delete an element with a
 *       given key, O(n) time is required in the worst case because we must
 *       first call the "search" function to find the node and if this node
 *       is the tail, we must iterate all the way to the n-1th node. Therefore,
 *       O(2n) --> O(n)
 * @space complexity: O(1)
 * @author Anil Celik Maral, 2021.05.23
 * @update Anil Celik Maral, 2021.05.27 */
int anil::singly_linked_list::remove(node* node_to_be_removed) {
  int removed_element (0);

  // Search for the node before the node that we want to delete so that
  // we can connect it to the node (or nullptr) that comes after the node
  // that we want to delete. Removing the head and tail are special cases.
  for (node* temp = head; temp != nullptr; temp = temp->next) {

    // If the node_to_be_removed is somewhere in between the head and the tail!
    if (temp->next == node_to_be_removed && temp->next != tail) {
      removed_element = temp->next->data;

      // Connect the node before node_to_be_removed to the node after
      // node_to_be_removed!
      temp->next = temp->next->next;
      delete temp->next;
      break;

    // If node_to_be_removed is the current head!
    } else if (temp == head) {
      // Removing the head is a special case that doesn't have a previous node.
      // Therefore, instead, head pointer is updated to be head->next and the
      // previous head is deleted.
      removed_element = temp->data;
      head = temp->next;
      delete temp;
      break;
      
    // If the node_to_be_removed is the current tail!
    } else if(temp->next == node_to_be_removed && temp->next == tail) {
      removed_element = temp->next->data;
      delete temp->next;
      temp->next = nullptr;
      tail = temp;
      break;
    }
  }

  return removed_element;
}

/**
 * @param data is the element that will be searched in the linked list.
 * @return the pointer to the node that contains the element data or the null
 *         pointer if no node contains the data.
 * @brief This function finds the first node with the element data by a simple
 *        linear search, returning a pointer to this node. If no element with
 *        data appears in the list, then the procedure returns nullptr.
 * @time complexity: O(n)
 * @space complexity: O(1)
 * @credit This function was partly inspired by the LIST-SEARCH function
 *         description at page 237 of CLRS 3rd Edition.
 * @author Anil Celik Maral, 2019.07.21
 * @update Anil Celik Maral, 2021.05.23  */
anil::node* anil::singly_linked_list::search(int data) {
    node* temp = head;
    while (temp != nullptr && temp->data != data) {
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
 * @update Anil Celik Maral, 2021.05.23  */
anil::singly_linked_list::~singly_linked_list() {
    while (!is_empty()) {
        remove(head);
    }
}
