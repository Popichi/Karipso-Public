/* This is an implementation of a binary search tree. No duplicates are allowed
   and only positive integers are accepted!
*/

/* TO DO: 1) Check if "new" keyword initializes pointers inside the
             insert function to null or not!
          2) Code a version to make bst work with negative integers!
          4) Check the recursive calls to ~bst_node() triggered by ~bst() */

#ifndef ANIL_BINARY_SEARCH_TREE_H
#define ANIL_BINARY_SEARCH_TREE_H

#include <cstddef>
#include <iostream>

/* Hash defines below are used to switch between recursive and iterative
   implementations of the binary search tree.*/
//#define ANIL_BST_USE_RECURSIVE_VERSIONS 0
#define ANIL_BST_USE_ITERATIVE_VERSIONS 1

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
