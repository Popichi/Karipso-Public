/* This is an implementation of the list class which is similar to C++ STL
   std::list class. The difference is that this class has a cursor and index
   member which allows to underlie a specific node at any given time. */

/* TO DO: 1) Add the ability to throw exceptions for functions such as
             cursor_data(). 
          2) Change pointer by adding the prefix m_ and create access
             functions for them. Or should I? Figure out how to deal with the
             <<operator!
          3) How can a friend function access private members?
             Check https://www.softwaretestinghelp.com/friend-functions-in-cpp/ */

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
 * @precondition: copied_cursor_list.is_empty() == false
 * @author Anil Celik Maral, 2021.06.25  */
anil::cursor_list::cursor_list(const cursor_list& copied_cursor_list) {
  this->m_index = -1;
  this->m_size = 0;
  this->front = nullptr;
  this->back = nullptr;
  this->cursor = nullptr;
  this->m_backup_index = -1;
  this->backup_cursor = nullptr;
  if (copied_cursor_list.is_empty() == false) {
    for (const cursor_list_node* it = copied_cursor_list.front; it != nullptr;
         it = it->next) {
      this->append(it->data);
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
 * @return true if the cursor list is empty and false if not.
 * @brief This function checks if a cursor list is empty or not.
 * @time complexity: O(1)
 * @space complexity: O(1)
 * @author Anil Celik Maral, 2021.08.23  */
bool anil::cursor_list::is_empty() const {
  return this->m_size == 0;
}

/**
 * @brief This function returns the number of elements in this cursor list.
 * @time complexity: O(1)
 * @space complexity: O(1)
 * @author Anil Celik Maral, 2021.06.25  */
int anil::cursor_list::size() {
  return this->m_size;
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
  if (this->cursor != nullptr) {
    return this->m_index;
  } else {
    return -1;
  }
}

/**
 * @return This function returns the data stored in the front node.
 * @brief This function returns the data stored in the front node if it exists.
 * @time complexity: O(1)
 * @space complexity: O(1)
 * @precondition: this->is_empty == false
 * @author Anil Celik Maral, 2021.06.25  */
int anil::cursor_list::front_data() {
  if (this->is_empty() == false) {
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
  if (this->is_empty() == false) {
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
  if (this->is_empty() == false && this->index() >= 0) {
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
 * @author Anil Celik Maral, 2021.06.25  */
bool anil::cursor_list::operator==(cursor_list& rhs) {
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

  if (rhs.is_empty() == false) {
    // If the lhs cursor list is not empty, clear it
    if (this->is_empty() != false) {
      this->clear();
    }

    cursor_list_node* back_up_cursor = rhs.cursor;
    int back_up_index = rhs.index();
    for (rhs.move_cursor_front(); rhs.index() >= 0; rhs.move_cursor_next()) {
      this->append(rhs.cursor_data());
    }
    rhs.m_index = back_up_index;
    rhs.cursor = back_up_cursor;

    // Return the existing object so that we can chain this operator
    return *this;
  }
}

/**
 * @return void
 * @brief This function prints the entire cursor list as a space seperated
 *        list.
 * @time complexity: O(n), where n is the number of elements in the cursor
 *                   list. The whole cursor list is traversed while printing
 *                   it.
 * @space complexity: O(1)
 * @precondition: rhs.is_empty() != false
 * @author Anil Celik Maral, 2021.07.04  */
namespace anil {
  std::ostream& operator<<(std::ostream& out, cursor_list& rhs) {
    if (rhs.is_empty() == false) {
      anil::cursor_list_node* back_up_cursor = rhs.cursor;
      int back_up_index = rhs.index();
      for (rhs.move_cursor_front(); rhs.index() >= 0; rhs.move_cursor_next()) {
        if (rhs.cursor == rhs.front) {
          out << rhs.cursor_data();
        } else {
          out << ' ' << rhs.cursor_data();
        }
      }
      rhs.m_index = back_up_index;
      rhs.cursor = back_up_cursor;
    }
    return out;
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
 * @precondition: this->index() >= 0
 * @author Anil Celik Maral, 2021.06.25  */
void anil::cursor_list::clear() {
  if (this->is_empty() == false) {
    cursor_list_node* node = this->front;
    while (node != nullptr) {
      cursor_list_node* node_to_be_deleted = node;
      node = node->next;
      delete node_to_be_deleted;
    }
    this->front = this->back = this->cursor = this->backup_cursor = nullptr;
    this->m_size = 0;
    this->m_index = this->m_backup_index = -1;
  }
}

/**
 * @return void
 * @brief If the cursor list is not empty, this function places the cursor
 *        under the front node, otherwise it does nothing.
 * @time complexity: O(1)
 * @space complexity: O(1)
 * @precondition: this->is_empty() == false
 * @author Anil Celik Maral, 2021.06.27  */
void anil::cursor_list::move_cursor_front() {
  if (this->is_empty() == false) {
    this->cursor = this->front;
    this->m_index = 0;
  }
}

/**
 * @return void
 * @brief If the cursor list is not empty, this function places the cursor
 *        under the back node, otherwise it does nothing.
 * @time complexity: O(1)
 * @space complexity: O(1)
 * @precondition: this->is_empty() == false
 * @author Anil Celik Maral, 2021.06.27  */
void anil::cursor_list::move_cursor_back() {
  if (this->is_empty() == false) {
    this->cursor = this->back;
    this->m_index = (this->m_size - 1);
  }
}

/**
 * @return void
 * @brief If the cursor is defined and not at the front, this function moves
 *        the cursor one step toward the front of the cursor list. If the
 *        cursor is defined and points at the front node, then the cursor
 *        becomes undefined. If the cursor is undefined, this function does
 *        nothing.
 * @time complexity: O(1)
 * @space complexity: O(1)
 * @precondition: this->cursor != nullptr
 * @author Anil Celik Maral, 2021.06.27  */
void anil::cursor_list::move_cursor_prev() {
  if (this->cursor != nullptr) {
    this->cursor = this->cursor->previous;
    --this->m_index;
  }
}

/**
 * @return void
 * @brief If the cursor is defined and not at the back, this function moves
 *        the cursor one step toward the back of the cursor list. If the
 *        cursor is defined and points at the back node, then the cursor
 *        becomes undefined. If the cursor is undefined, this function does
 *        nothing.
 * @time complexity: O(1)
 * @space complexity: O(1)
 * @precondition: this->cursor != nullptr
 * @author Anil Celik Maral, 2021.06.27  */
void anil::cursor_list::move_cursor_next() {
  if (this->cursor != nullptr) {

    // If the cursor was at the back of the list, the index becomes undefined.
    // Otherwise, just increment it by one.
    this->m_index = (this->cursor == this->back) ? -1 : this->m_index + 1;

    this->cursor = this->cursor->next;
  }
}

/**
 * @return void
 * @brief This function saves the state of the cursor in a cursor list by
 *        saving which cursor list node the cursor points to and the index
 *        value for that cursor list node.
 * @time complexity: O(1)
 * @space complexity: O(1)
 * @author Anil Celik Maral, 2021.08.06  */
void anil::cursor_list::save_cursor_state() {
  this->backup_cursor = this->cursor;
  this->m_backup_index = m_index;
}

/**
 * @return void
 * @brief This function restores the state of the cursor in a cursor list by
 *        repointing the cursor to the cursor list node that it used to point
 *        to when the function save_cursor_state() was called. Additionally,
 *        the corresponding index value is restored as well. It is possible to
 *        restore the cursor and index to their undefined values i.e. nullptr
 *        and -1.
 * @time complexity: O(1)
 * @space complexity: O(1)
 * @author Anil Celik Maral, 2021.08.06  */
void anil::cursor_list::restore_cursor_state() {
  this->cursor = this->backup_cursor;
  this->m_index = m_backup_index;
}

/**
 * @param new_data is the data that will be inserted into the cursor list.
 * @return void
 * @brief This function inserts the data given by the new_data parameter into
 *        the cursor list. The insertion always takes place before the front
 *        node if the cursor list is non-empty. If the cursor list is empty,
 *        then the inserted node becomes both the front and back node.
 * @time complexity: O(1)
 * @space complexity: O(1)
 * @author Anil Celik Maral, 2021.06.27  */
void anil::cursor_list::prepend(int new_data) {
  cursor_list_node* new_node = new cursor_list_node;
  new_node->data = new_data;
  new_node->previous = nullptr;
  new_node->next = this->front;
  if (this->is_empty() == false) {
    this->front->previous = new_node;
  } else {
    this->back = new_node;
  }
  this->front = new_node;
  ++this->m_index;
  ++this->m_size;
}

/**
 * @param new_data is the data that will be inserted into the cursor list.
 * @return void
 * @brief This function inserts the data given by the new_data parameter into
 *        the cursor list. The insertion always takes place after the back
 *        node if the cursor list is non-empty. If the cursor list is empty,
 *        then the inserted node becomes both the front and back node.
 * @time complexity: O(1)
 * @space complexity: O(1)
 * @author Anil Celik Maral, 2021.06.27  */
void anil::cursor_list::append(int new_data) {
  cursor_list_node* new_node = new cursor_list_node;
  new_node->data = new_data;
  new_node->next = nullptr;
  new_node->previous = this->back;
  if (this->is_empty() == false) {
    this->back->next = new_node;
  } else {
    this->front = new_node;
  }
  this->back = new_node;
  ++this->m_size;
}

/**
 * @param new_data is the data that will be inserted into the cursor list.
 * @return void
 * @brief This function inserts the data given by the new_data parameter into
 *        the cursor list. The insertion always takes place before the cursor
 *        node. If the list is empty or the cursor is undefined, this function
 *        does nothing.
 * @time complexity: O(1)
 * @space complexity: O(1)
 * @precondition: this->is_empty() == false &&
 *                this->cursor != nullptr
 * @author Anil Celik Maral, 2021.06.27  */
void anil::cursor_list::insert_before_cursor(int new_data) {
  if (this->is_empty() == false && this->cursor != nullptr) {
    cursor_list_node* new_node = new cursor_list_node;
    new_node->data = new_data;
    new_node->next = this->cursor;
    new_node->previous = this->cursor->previous;

    // If the cursor has a node before it, adjust its 'next' pointer!
    if (this->cursor->previous != nullptr) {
      this->cursor->previous->next = new_node;

    // If the cursor doesn't have a node before it, i.e. the cursor is the
    // front node, then make the new node the front node.
    } else {
      this->front = new_node;
    }

    this->cursor->previous = new_node;
    ++this->m_size;
    ++this->m_index;
  }
}

/**
 * @param new_data is the data that will be inserted into the cursor list.
 * @return void
 * @brief This function inserts the data given by the new_data parameter into
 *        the cursor list. The insertion always takes place after the cursor
 *        node. If the list is empty or the cursor is undefined, this function
 *        does nothing.
 * @time complexity: O(1)
 * @space complexity: O(1)
 * @precondition: this->is_empty() == false &&
 *                this->cursor != nullptr
 * @author Anil Celik Maral, 2021.06.28  */
void anil::cursor_list::insert_after_cursor(int new_data) {
  if (this->is_empty() == false && this->cursor != nullptr) {
    cursor_list_node* new_node = new cursor_list_node;
    new_node->data = new_data;
    new_node->next = this->cursor->next;
    new_node->previous = this->cursor;

    // If the cursor has a node before it, adjust its 'previous' pointer!
    if (this->cursor->next != nullptr) {
      this->cursor->next->previous = new_node;

    // If the cursor doesn't have a node after it, i.e. the cursor is the
    // back node, then make the new node the back node.
    } else {
      this->back = new_node;
    }

    this->cursor->next = new_node;
    ++this->m_size;
  }
}

/**
 * @return void
 * @brief This function deletes the front node of the cursor list. If the
 *        cursor points to the front node, then the cursor becomes undefined.
 *        If the cursor list is empty, this function does nothing.
 * @time complexity: O(1)
 * @space complexity: O(1)
 * @precondition: this->is_empty() == false
 * @author Anil Celik Maral, 2021.06.28  */
void anil::cursor_list::delete_front() {
  if (this->is_empty() == false) {

    cursor_list_node* node_to_be_deleted = this->front;

    // If the cursor points to the front element, then it becomes undefined.
    if (this->front == this->cursor) {
      this->cursor = nullptr;
      this->m_index = -1;
    }

    // If the front has a node after it, adjust its 'previous' pointer and
    // make it the new front node!
    if (this->front->next != nullptr) {
      this->front->next->previous = nullptr;
      this->front = this->front->next;

    // If the front doesn't have a node after it, i.e. the front is the
    // only node, then adjust the back and front pointers.
    } else {
      this->front = nullptr;
      this->back = nullptr;
    }

    delete node_to_be_deleted;
    --this->m_size;
  }
}

/**
 * @return void
 * @brief This function deletes the back node of the cursor list. If the
 *        cursor points to the back node, then the cursor becomes undefined.
 *        If the cursor list is empty, this function does nothing.
 * @time complexity: O(1)
 * @space complexity: O(1)
 * @precondition: this->is_empty() == false
 * @author Anil Celik Maral, 2021.06.28  */
void anil::cursor_list::delete_back() {
  if (this->is_empty() == false) {

    cursor_list_node* node_to_be_deleted = this->back;

    // If the cursor points to the back element, then it becomes undefined.
    if (this->back == this->cursor) {
      this->cursor = nullptr;
      this->m_index = -1;
    }

    // If the back has a node before it, adjust its 'next' pointer and
    // make it the new back node!
    if (this->back->previous != nullptr) {
      this->back->previous->next = nullptr;
      this->back = this->back->previous;

    // If the back doesn't have a node before it, i.e. the back is the
    // only node, then adjust the back and front pointers.
    } else {
      this->front = nullptr;
      this->back = nullptr;
    }

    delete node_to_be_deleted;
    --this->m_size;
  }
}

/**
 * @return void
 * @brief This function deletes the cursor node of the cursor list. After
 *        the deletion, the cursor becomes undefined. If the cursor list is
 *        empty or the cursor is undefined, this function does nothing.
 * @time complexity: O(1)
 * @space complexity: O(1)
 * @precondition: this->is_empty() == false &&
 *                this->cursor != nullptr
 * @author Anil Celik Maral, 2021.06.28  */
void anil::cursor_list::delete_cursor() {
  if (this->is_empty() == false && this->cursor != nullptr) {

    cursor_list_node* node_to_be_deleted = this->cursor;

    // If the cursor points to the front element, then call delete_front().
    if (this->cursor == this->front) {
      this->delete_front();
      return;
    
    // If the cursor points to the back element, then call delete_back().
    } else if (this->cursor == this->back) {
      this->delete_back();
      return;
    }

    // If the cursor points to a node in between the front and back node,
    // then adjust it's previous and next node's pointers!
    this->cursor->previous->next = this->cursor->next;
    this->cursor->next->previous = this->cursor->previous;

    this->cursor = nullptr;
    this->m_index = -1;
    --this->m_size;
    delete node_to_be_deleted;
  }
}

/**
 * @return void
 * @brief This function deletes every node in the cursor list one by one
 *        by calling delete_front() iteratively. This is a private function.
 * @time complexity: O(n), where n is the number of nodes in the cursor list.
 * @space complexity: O(1)
 * @precondition: this->is_empty() == false
 * @author Anil Celik Maral, 2021.06.28  */
void anil::cursor_list::delete_list() {
  if (this->is_empty() == false) {
    while (this->back != nullptr) {
      this->delete_front();
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
