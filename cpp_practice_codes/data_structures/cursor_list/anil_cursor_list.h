/* This is an implementation of the list class which is similar to C++ STL
   std::list class. The difference is that this class has a cursor and index
   member which allows to underlie a specific node at any given time. */

/* TO DO: */

#ifndef ANIL_CURSOR_LIST_H
#define ANIL_CURSOR_LIST_H

#include <cstddef>
#include <iostream>

namespace anil {
  class cursor_list_node {
    private:
      int data;
      cursor_list_node* next;
      cursor_list_node* previous;
      friend class cursor_list; 
  };

  class cursor_list {
    private:

      // Data:
      int m_index;
      int m_size;
      cursor_list_node* front;
      cursor_list_node* back;
      cursor_list_node* cursor;

    public:
      cursor_list() : m_index(-1), m_size(0), front(nullptr), back(nullptr),
        cursor(nullptr) {}
      cursor_list(cursor_list& copied_list);
      bool is_empty();
      int size();
      int index();
      int front_data();
      int back_data();
      int cursor_data();
      bool operator==(cursor_list& rhs); // rhs = right hand side
      cursor_list& operator= (cursor_list& rhs);  // rhs = right hand side
      friend std::ostream& operator<<(std::ostream& out, const cursor_list& rhs); // rhs = right hand side
      void clear();
      void move_cursor_front();
      void move_cursor_back();
      void move_cursor_prev();
      void move_cursor_next();
      void prepend(int new_data);
      void append(int new_data);
      void insert_before_cursor(int new_data);
      void insert_after_cursor(int new_data);
      void delete_front();
      void delete_back();
      void delete_cursor();
      void delete_list();
      ~cursor_list();
  };
}

#endif /* ANIL_BINARY_SEARCH_TREE_H */
