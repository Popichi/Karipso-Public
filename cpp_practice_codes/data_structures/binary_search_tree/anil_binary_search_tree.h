/* This is an implementation of a binary search tree! */

/* TO DO: 1) Check if "new" keyword initializes pointers inside the
             insert function to null or not!
          2) Modify the tree to make it work with negative integers!
          3) Compare these methods with the ones in the CLRS book!
             Convert the implementations to those shown in CLRS if
             there is a difference!
          4) Check the recursive calls to ~bst_node() triggered by ~bst()  */

#ifndef ANIL_BINARY_SEARCH_TREE_H
#define ANIL_BINARY_SEARCH_TREE_H

#include <cstddef>
#include <iostream>

/* Hash defines below are used to switch between recursive and iterative
   implementations of the binary search tree.*/
#define ANIL_BST_USE_RECURSIVE_VERSIONS 0
//#define ANIL_BST_USE_ITERATIVE_VERSIONS 1

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
      bool is_empty();
      bst_node* insert_recursively(bst_node* node, int new_data);
      bst_node* insert_iteratively(bst_node* new_node);
      void print_inorder(bst_node* node);
      bst_node* search_recursively(bst_node* node, 
        int data_that_we_search_for);
      bst_node* search_iteratively(bst_node* node, 
        int data_that_we_search_for);
      bst_node* find_min_recursively(bst_node* node);
      bst_node* find_min_iteratively(bst_node* node);
      bst_node* find_max_recursively(bst_node* node);
      bst_node* find_max_iteratively(bst_node* node);
      void transplant(bst_node* replaced, bst_node* replacing);
      void delete_recursively(bst_node* node);

    public:
      bst() : root(NULL) {}
      bst_node* insert_recursively(int new_data);
      bst_node* insert_iteratively(int new_data);
      void print_inorder();
      bst_node* search_recursively(int data);
      bst_node* search_iteratively(int data);
      bst_node* find_min_recursively();
      bst_node* find_min_iteratively();
      bst_node* find_max_recursively();
      bst_node* find_max_iteratively();
      bst_node* successor(bst_node* node);
      bst_node* predecessor(bst_node* node);
      void remove(bst_node* node_to_be_deleted);
      ~bst();
  };
}

#endif /* ANIL_BINARY_SEARCH_TREE_H */
