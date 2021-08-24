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
      
      int m_backup_index;
      cursor_list_node* backup_cursor;

      // Functions:
      void delete_list();

    public:
      cursor_list() : m_index(-1), m_size(0), front(nullptr), back(nullptr),
        cursor(nullptr), m_backup_index(-1), backup_cursor(nullptr) {}
      cursor_list(const cursor_list& copied_list);
      bool is_empty();
      bool is_empty() const;
      int size();
      int index();
      int front_data();
      int back_data();
      int cursor_data();
      bool operator==(cursor_list& rhs); // rhs = right hand side
      cursor_list& operator= (cursor_list& rhs);  // rhs = right hand side
      friend std::ostream& operator<<(std::ostream& out, cursor_list& rhs); // rhs = right hand side
      void clear();
      void move_cursor_front();
      void move_cursor_back();
      void move_cursor_prev();
      void move_cursor_next();
      void save_cursor_state();
      void restore_cursor_state();
      void prepend(int new_data);
      void append(int new_data);
      void insert_before_cursor(int new_data);
      void insert_after_cursor(int new_data);
      void delete_front();
      void delete_back();
      void delete_cursor();
      ~cursor_list();
  };
}

#endif /* ANIL_CURSOR_LIST_H */
