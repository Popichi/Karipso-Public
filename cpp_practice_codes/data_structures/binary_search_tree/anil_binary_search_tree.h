/* This is an implementation of a binary search tree! */

/* TO DO: 1) Check if "new" keyword initializes pointers inside the
             insert function to null or not!
          2) Modify the tree to make it work with negative integers!
          3) Compare these methods with the ones in the CLRS book!
             Convert the implementations to those shown in CLRS if
             there is a difference! */

#ifndef ANIL_BINARY_SEARCH_TREE_H
#define ANIL_BINARY_SEARCH_TREE_H

#include <cstddef>
#include <iostream>

namespace anil {
    class bst_node {    // Binary search tree node
        public:
            int data;
            bst_node* left;
            bst_node* right;
            bst_node* parent;
    };

    class bst {         // Binary search tree
        private:

            // Data:
            bst_node* root;

            // Functions:
            bool is_empty();
            bst_node* insert(bst_node* node, int new_data);
            bst_node* insert_iteratively(bst_node* node);
            void print_io(bst_node* node); // Print in order = print_io
            bst_node* search(bst_node* node, int data);
            bst_node* find_min(bst_node* node);
            bst_node* find_max(bst_node* node);
            int successor(bst_node* node);
            int predecessor(bst_node* node);
            void transplant(bst_node* u, bst_node* v);
            bst_node* remove(bst_node*, int data);

        public:
            bst() : root(NULL) {}
            void insert(int new_data);
            anil::bst_node* insert_iteratively(int new_data);
            void print_io();               // Print in order = print_io
            bool search(int data);
            int find_min() { return find_min(root); }
            int find_max() { return find_max(root); }
            int successor(int data);
            int predecessor(int data);
            void remove(int data) { remove(root, data); }
            ~bst();
    };
}

#endif /* ANIL_BINARY_SEARCH_TREE_H */