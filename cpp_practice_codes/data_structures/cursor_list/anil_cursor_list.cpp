/* This is an implementation of the list class which is similar to C++ STL
   std::list class. The difference is that this class has a cursor and index
   member which allows to underlie a specific node at any given time. */

/* TO DO: */

#include "anil_cursor_list.h"

/**
 * @param copied_cursor_list is the cursor list that will be copied onto a
 *        new cursor list.
 * @brief This copy constructor copies the list referenced by the parameter
 *        copied_cursor_list onto a new cursor list. These two cursor lists
 *        are identical except the m_index and cursor elements. These two
 *        members are undefined for the newly created list.
 * @time complexity: O(n), where n is the number of elements in the cursor
 *                   list. The whole cursor list is traversed while copying
 *                   it.
 * @space complexity: O(n), where n is the number of elements in the cursor
 *                   list. The whole cursor list is copied onto a new cursor
 *                   list.
 * @precondition: copied_cursor_list.is_empty() == false &&
 *                copied_cursor_list.index() >= 0
 * @author Anil Celik Maral, 2021.06.25  */
anil::cursor_list::cursor_list(cursor_list& copied_cursor_list) {
  if (copied_cursor_list.is_empty() == false &&
      copied_cursor_list.index() >= 0) {
    cursor_list_node* back_up_cursor = copied_cursor_list.cursor;
    int back_up_index = copied_cursor_list.index();
    if (this != nullptr) {
      for (copied_cursor_list.move_cursor_front();
          copied_cursor_list.index() >= 0;
          copied_cursor_list.move_cursor_next()) {
            this->append(copied_cursor_list.cursor_data());
      }
      copied_cursor_list.cursor = back_up_cursor;
    }
  }
}

/**
 * @return true if the cursor list is empty and false if not.
 * @brief This function checks if a cursor list is empty or not.
 * @time complexity: O(1)
 * @space complexity: O(1)
 * @author Anil Celik Maral, 2021.06.25  */
bool anil::cursor_list::is_empty() {
  return this->m_size == 0;
}

/**
 * @brief This function returns the number of elements in this cursor list.
 * @time complexity: O(1)
 * @space complexity: O(1)
 * @author Anil Celik Maral, 2021.06.25  */
int anil::cursor_list::size() {
  if (this != nullptr) {
    return this->m_size;
  }
}

/**
 * @return This function either returns the index of the cursor node or -1.
 * @brief This function returns the index of the cursor element,
 *        if cursor is defined. Otherwise it returns -1.
 * @time complexity: O(1)
 * @space complexity: O(1)
 * @precondition: cursor != nullptr
 * @author Anil Celik Maral, 2021.06.25  */
int anil::cursor_list::index() {
  if (this != nullptr && this->cursor != nullptr) {
    return this->m_index;
  }
  return -1;
}

/**
 * @return This function returns the data stored in the front node.
 * @brief This function returns the data stored in the front node if it exists.
 * @time complexity: O(1)
 * @space complexity: O(1)
 * @precondition: this->is_empty == false
 * @author Anil Celik Maral, 2021.06.25  */
int anil::cursor_list::front_data() {
  if (this != nullptr && this->is_empty() == false) {
    return this->front->data;
  }
}

/**
 * @return This function returns the data stored in the back node.
 * @brief This function returns the data stored in the back node if it exists.
 * @time complexity: O(1)
 * @space complexity: O(1)
 * @precondition: this->is_empty == false
 * @author Anil Celik Maral, 2021.06.25  */
int anil::cursor_list::back_data() {
  if (this != nullptr && this->is_empty() == false) {
    return this->back->data;
  }
}

/**
 * @return This function returns the data stored in the cursor node.
 * @brief This function returns the data stored in the cursor node if it exists
 *        and is defined.
 * @time complexity: O(1)
 * @space complexity: O(1)
 * @precondition: this->is_empty == false && this->index() >= 0
 * @author Anil Celik Maral, 2021.06.25  */
int anil::cursor_list::cursor_data() {
  if (this != nullptr && this->is_empty() == false && this->index() >= 0) {
    return this->cursor->data;
  }
}

/**
 * @param rhs (right hand side) is the cursor list whose integer list will be
 *        compared to the integer list of the cursor list pointed by 'this'.
 * @return ??
 * @brief This functions checks if two cursor lists have the same integer list
 *        or not. The cursor member and its state are not used during this
 *        comparison. This, also, means that the state of the cursor elements
 *        for the two lists will be unchanged.
 * @time complexity: O(n), where n is the number of elements in the cursor
 *                   list that has the most elements. The whole cursor list
 *                   is traversed while comparing the integer sequence.
 * @space complexity: O(1)
 * @precondition: this != nullptr &&
 *                &rhs != nullptr
 * @author Anil Celik Maral, 2021.06.25  */
bool anil::cursor_list::operator==(cursor_list& rhs) {
  if (this != nullptr && &rhs != nullptr) {
    cursor_list_node* lhs_node = nullptr;
    cursor_list_node* rhs_node = nullptr;
    bool comparison_flag = (this->size() == rhs.size());
    while (comparison_flag && lhs_node != nullptr && rhs_node != nullptr) {
      comparison_flag = lhs_node->data == rhs_node->data;
      lhs_node = lhs_node->next;
      rhs_node = rhs_node->next;
    }
    return comparison_flag;
  }
}

/**
 * @param rhs (right hand side) is the cursor list that will be
 *        copied / assigned onto a new cursor list.
 * @return ??
 * @brief The assignment operator copies the list referenced by the parameter
 *        rhs onto a new cursor list. This means a deep copy assignment is
 *        done. As a result, the previous list that is pointed by 'this' will
 *        be deleted. The function has a check for self-assignment. The
 *        copied / assigned and the lhs (left hand side) cursor lists are
 *        identical except the m_index and cursor elements. These two members
 *        are undefined for the lhs list.
 * @time complexity: O(n), where n is the number of elements in the cursor
 *                   list. The whole cursor list is traversed while copying
 *                   it.
 * @space complexity: O(n), where n is the number of elements in the cursor
 *                   list. The whole cursor list is copied onto a new cursor
 *                   list.
 * @precondition: copied_cursor_list.is_empty() == false &&
 *                copied_cursor_list.index() >= 0
 * @author Anil Celik Maral, 2021.06.25  */
anil::cursor_list& anil::cursor_list::operator= (cursor_list& rhs) {
  // Self-assignment check
  if (this == &rhs) {
    return *this;
  }

  if (rhs.is_empty() == false && rhs.index() >= 0) {
    // If the lhs cursor list is not empty, clear it
    if (this->is_empty() != false) {
      this->clear();
    }

    cursor_list_node* back_up_cursor = rhs.cursor;
    int back_up_index = rhs.index();
    if (this != nullptr) {
      for (rhs.move_cursor_front(); rhs.index() >= 0; rhs.move_cursor_next()) {
            this->append(rhs.cursor_data());
      }
      rhs.cursor = back_up_cursor;
    }

    // Return the existing object so that we can chain this operator
    return *this;
  }
}

/**
 * @return void
 * @brief This function returns the cursor list to its original empty state
 *        i.e. all of the cursor list nodes are deleted and member values
 *        are set to their original states. If the list is empty, this
 *        function does nothing.
 * @time complexity: O(n), where n is the number of elements in the cursor
 *                   list. The whole cursor list is traversed while clearing
 *                   it.
 * @space complexity: O(1)
 * @precondition: this != nullptr &&
 *                this->index() >= 0
 * @author Anil Celik Maral, 2021.06.25  */
void anil::cursor_list::clear() {
  if (this != nullptr && this->index() >= 0) {
    cursor_list_node* node = this->front;
    while (node != nullptr) {
      cursor_list_node* node_to_be_deleted = node;
      node = node->next;
      delete node_to_be_deleted;
    }
    this->front = this->back = this->cursor = nullptr;
    this->m_size = 0;
    this->m_index = -1;
  }
}

/**
 * @param node is the node whose subtree and itself gets deleted.
 * @return void
 * @brief This function deletes a binary search subtree whose root is located
 *        at the node parameter by recursively deleting every node in the tree
 *        following a post-order tree traversal.
 * @author Anil Celik Maral, 2019.08.15
 * @update Anil Celik Maral, 2021.06.07  */
// void anil::bst::delete_bst(bst_node* node) {
//   if (node == nullptr) { return; }
//   delete_bst(node->left);  
//   delete_bst(node->right); 
//   delete node;
//   node = nullptr;
// }

/**
 * @param none
 * @return void
 * @brief This function deletes an entire binary search tree by triggering a
 *        call to delete_bst(), which then recursively deletes every
 *        node in the tree following a post-order tree traversal.
 * @author Anil Celik Maral, 2019.08.14
 * @update Anil Celik Maral, 2021.06.07  */
// anil::bst::~bst() {
//   delete_bst(root);
// }