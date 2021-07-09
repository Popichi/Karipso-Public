/* This is an implementation of a graph class... */

/* TO DO: */

#include "anil_graph.h"

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
 * @precondition: copied_cursor_list.is_empty() == false
 * @author Anil Celik Maral, 2021.06.25  */
anil::cursor_list::cursor_list(cursor_list& copied_cursor_list) {
  this->m_index = -1;
  this->m_size = 0;
  this->front = nullptr;
  this->back = nullptr;
  this->cursor = nullptr;
  if (copied_cursor_list.is_empty() == false) {
    for (cursor_list_node* it = copied_cursor_list.front; it != nullptr;
         it = it->next) {
      this->append(it->data);
    }
  }
}

/**
 * @return void
 * @brief This function deletes an entire cursor list by triggering a
 *        call to delete_list(), which then iteratively deletes every
 *        node in the cursor list.
 * @author Anil Celik Maral, 2021.06.28  */
anil::cursor_list::~cursor_list() {
  delete_list();
}
