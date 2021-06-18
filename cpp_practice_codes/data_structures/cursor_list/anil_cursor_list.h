/* This is an implementation of the list class which is similar to C++ STL
   std::list class. The difference is that this class has a cursor and index
   member which allows to underlie a specific node at any given time. */

/* TO DO: */

#ifndef ANIL_CURSOR_LIST_H
#define ANIL_CURSOR_LIST_H

#include <cstddef>
#include <iostream>

namespace anil {
  class bst_node {  // Binary search tree node
    private:
      int data;
      bst_node* left;
      bst_node* right;
      bst_node* parent;
      friend class bst; 
  };

  class bst { // Binary search tree
    private:

      // Data:
      bst_node* root;

      // Functions:
      #ifdef ANIL_BST_USE_RECURSIVE_VERSIONS
      bst_node* insert(bst_node* node, int new_data);
      bst_node* search(bst_node* node, 
        int data_that_we_search_for);
      bst_node* find_min(bst_node* node);
      bst_node* find_max(bst_node* node);
      #elif ANIL_BST_USE_ITERATIVE_VERSIONS
      bst_node* insert(bst_node* new_node);
      bst_node* search(bst_node* node, 
        int data_that_we_search_for);
      bst_node* find_min(bst_node* node);
      bst_node* find_max(bst_node* node);
      #endif
      void print_inorder(std::ostream& os, bst_node* node);
      void transplant(bst_node* replaced, bst_node* replacing);
      void delete_bst(bst_node* node);

    public:
      bst() : root(nullptr) {}
      #ifdef ANIL_BST_USE_RECURSIVE_VERSIONS
      bst_node* insert(int new_data);
      bst_node* search(int data);
      bst_node* find_min();
      bst_node* find_max();
      #elif ANIL_BST_USE_ITERATIVE_VERSIONS
      bst_node* insert(int new_data);
      bst_node* search(int data);
      bst_node* find_min();
      bst_node* find_max();
      #endif
      bool is_empty();
      void print_inorder(std::ostream& os);
      int get_node_data(bst_node* node);
      bst_node* successor(bst_node* node);
      bst_node* predecessor(bst_node* node);
      void remove(bst_node* node_to_be_deleted);
      ~bst();
  };
}

#endif /* ANIL_BINARY_SEARCH_TREE_H */
