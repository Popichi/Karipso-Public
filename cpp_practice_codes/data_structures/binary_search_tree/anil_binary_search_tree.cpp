/* This is an implementation of a binary search tree! */
/* TO DO: 1) Cite the quotes from CLRS! */

#include "anil_binary_search_tree.h"

bool anil::bst::is_empty() {
    return root == NULL;
}

/**
 * @param new_node is the node that will be inserted into the binary search 
 *        tree.
 * @param new_data is the data that will be inserted into the binary search 
 *        tree.
 * @return The node that is inserted into the binary search tree is returned.
 * @brief The function recursively searches the tree according to the rules of
 *        a general binary search tree to insert the new data accordingly by
 *        creating a new node.
 * @author Anil Celik Maral, 2019.08.11  */
anil::bst_node* anil::bst::insert_recursively(bst_node* node, int new_data) {
  if (node == NULL) {
    node = new bst_node;
    node->data = new_data;
    //node->left = NULL; Check if new initializes them to NULL
    //node->right = NULL;
    //node->parent = NULL;
    if (root == NULL) { // Tree was empty
      root = node;
      root->parent = NULL;
    }
  } else if (new_data > node->data) {
    node->right = insert_recursively(node->right, new_data);
    node->right->parent = node;
  } else {
    node->left = insert_recursively(node->left, new_data);
    node->left->parent = node;
  }
  return node;
}

/**
 * @param new_data is the data that will be inserted into the binary search 
 *        tree.
 * @return The node that is created to insert the new data into the binary
 *         search tree is returned or if the value specified by new data
 *         already exists, the functions returns the address of that node.
 * @brief This is a wrapper function for the actual recursive insert function.
 *        Duplicates are not allowed; therefore, the function checks if the 
 *        data that is to be inserted already exists or not. If it exists, the
 *        address of the existing node is returned. Otherwise, a new node
 *        is created with new_data as its member and the function returns the
 *        address to this newly created node.
 * @author Anil Celik Maral, 2019.08.11 */
anil::bst_node* anil::bst::insert_recursively(int new_data) {
  bst_node* node = search_recursively(new_data);
  if (!node) { // If the data doesn't already exist
    node = insert_recursively(root, new_data);
  }
  return node;
}

/**
 * @param new_node is the node that will be inserted into the binary search 
 *        tree.
 * @return The node that is inserted into the binary search tree is returned.
 * @brief The function iteratively searches the tree according to the rules
 *        of a general binary search tree to insert the new node.
 * @credit The insertion algorithm is taken from page 294 of 3rd edition of
 *         CLRS.
 * @author Anil Celik Maral, 2019.08.10  */
anil::bst_node* anil::bst::insert_iteratively(bst_node* new_node) {
  bst_node* parent_of_new_node = NULL;
  bst_node* position_that_new_node_will_be_inserted_at = root;
  while (position_that_new_node_will_be_inserted_at != NULL) {
    parent_of_new_node = position_that_new_node_will_be_inserted_at;
    if (new_node->data < position_that_new_node_will_be_inserted_at->data) {
      position_that_new_node_will_be_inserted_at = 
        position_that_new_node_will_be_inserted_at->left;
    } else {
      position_that_new_node_will_be_inserted_at = 
        position_that_new_node_will_be_inserted_at->right;
    }
  }
  new_node->parent = parent_of_new_node;
  if (parent_of_new_node == NULL) {
    root = new_node;  // Tree was empty
  } else if (new_node->data < parent_of_new_node->data) {
    parent_of_new_node->left = new_node;
  } else {
    parent_of_new_node->right = new_node;
  }
  return new_node;
}

/**
 * @param new_data is the data that will be inserted into the binary search 
 *        tree.
 * @return The node that is created to insert the new data into the binary
 *         search tree is returned or if the value specified by new data
 *         already exists, the functions returns the address of that node.
 * @brief This is a wrapper function for the actual iterative insert function.
 *        Duplicates are not allowed; therefore, the function checks if the data
 *        that is to be inserted already exists or not. If it exists, the
 *        address of the existing node is returned. Otherwise, a new node
 *        is created with new_data as its member and the function returns the 
 *        address to this newly created node.
 * @author Anil Celik Maral, 2019.08.10  */
anil::bst_node* anil::bst::insert_iteratively(int new_data) {
  bst_node* new_node = search_iteratively(new_data);
  if (!new_node) { // If the data doesn't already exist
    new_node = new bst_node;
    new_node->data = new_data;
    insert_iteratively(new_node);
  }
  return new_node;
}

/**
 * @param node is the node that we start our inorder tree walk at.
 * @return void
 * @brief This function uses inorder tree walk algorithm to print node's
 *        subtree and itself inorder. This means that "it prints the key of 
 *        the root of a subtree between printing the values in its left subtree
 *        and printing thos in its right subtree."
 * @credit The inorder tree walk algorithm is taken from page 288 of 3rd 
 *         edition of CLRS.
 * @author Anil Celik Maral, 2019.08.11  */
void anil::bst::print_inorder(bst_node* node) {
  if (node != NULL) {
    print_inorder(node->left);
    std::cout << node->data << ' ';
    print_inorder(node->right);
  }
}

/**
 * @param none
 * @return void
 * @brief This is a wrapper function for the actual print inorder function.
 *        This is done to reduce usage errors and so that the printing always
 *        starts at the root.
 * @author Anil Celik Maral, 2019.08.11  */
void anil::bst::print_inorder() {
  print_inorder(root);
}

/**
 * @param node is the node that we start the search at.
 * @param data is the value that we look for in the binary search tree.
 * @return This function returns a pointer to a node with the value data
 *         if one exists; otherwise, it returns NULL.
 * @brief This function starts at the node specified by the node parameter and
 *        searches for a node that contains the value data using the binary
 *        search tree properties. "It traces a simple path downward".
 * @credit The recursive search algorithm is taken from page 290 of 3rd 
 *         edition of CLRS.
 * @author Anil Celik Maral, 2019.08.12  */
anil::bst_node* anil::bst::search_recursively(bst_node* node,
  int data_that_we_search_for) {
  if (node == NULL || data_that_we_search_for == node->data) {
    return node;
  }
  if (data_that_we_search_for < node->data) {
    return search_recursively(node->left, data_that_we_search_for);
  } else { // data_that_we_search_for > node->data
    return search_recursively(node->right, data_that_we_search_for);
  }
}

/**
 * @param data is the value that we look for in the binary search tree.
 * @return This function returns a pointer to a node with the value data
 *         if one exists; otherwise, it returns NULL.
 * @brief This is a wrapper function for the actual recursive search function.
 *        This is done to reduce usage errors and so that the search always 
 *        starts at the root.
 * @author Anil Celik Maral, 2019.08.12  */
anil::bst_node* anil::bst::search_recursively(int data) {
  return search_recursively(root, data);
}

/**
 * @param node is the node that we start the search at.
 * @param data is the value that we look for in the binary search tree.
 * @return This function returns a pointer to a node with the value data
 *         if one exists; otherwise, it returns NULL.
 * @brief This function starts at the node specified by the node parameter and
 *        searches for a node that contains the value data using the binary
 *        search tree properties. "It traces a simple path downward".
 * @credit The iterative search algorithm is taken from page 291 of 3rd 
 *         edition of CLRS.
 * @author Anil Celik Maral, 2019.08.12  */
anil::bst_node* anil::bst::search_iteratively(bst_node* node, 
  int data_that_we_search_for) {
  while (node != NULL && data_that_we_search_for != node->data) {
    if (data_that_we_search_for < node->data) {
      node = node->left;
    } else {  // data_that_we_search_for > node->data
      node = node->right;
    }
  }
  return node;
}

/**
 * @param data is the value that we look for in the binary search tree.
 * @return This function returns a pointer to a node with the value data
 *         if one exists; otherwise, it returns NULL.
 * @brief This is a wrapper function for the actual iterative search function.
 *        This is done to reduce usage errors and so that the search always
 *        starts at the root.
 * @author Anil Celik Maral, 2019.08.12  */
anil::bst_node* anil::bst::search_iteratively(int data) {
  return search_iteratively(root, data);
}

/**
 * @param node is the node that we check to see if it contains the minimum 
 *        element in the binary search tree.
 * @return This function returns a pointer to a node with the minimum value
 *         if one exists; otherwise, it returns NULL (if the tree is empty).
 * @brief This function finds the minimum value in the binary search tree "by
 *        following left child pointers from the root until we encounter a" 
 *        NULL. This means that to get the minimum value in our binary search
 *        tree, we only need to go to the leftmost node.
 * @credit The recursive search algorithm for the minimum value is taken from
 *         https://github.com/gzc/CLRS/blob/master/C12-Binary-Search-Trees/
 *         12.2.md.
 * @author Anil Celik Maral, 2019.08.13  */
anil::bst_node* anil::bst::find_min_recursively(bst_node* node) {
  if (node->left != NULL) {
    return find_min_recursively(node->left);
  }
  return node;
}

/**
 * @param none
 * @return This function returns a pointer to a node with the minimum value
 *         if one exists; otherwise, it returns NULL (if the tree is empty).
 * @brief This is a wrapper function for the actual recursive search function
 *        for the minimum value. This is done to reduce usage errors and so 
 *        that the search always starts at the root.
 * @author Anil Celik Maral, 2019.08.13  */
anil::bst_node* anil::bst::find_min_recursively() {
  return find_min_recursively(root); 
}

/**
 * @param node is the node that we check to see if it contains the maximum 
 *        element in the binary search tree.
 * @return This function returns a pointer to a node with the maximum value
 *         if one exists; otherwise, it returns NULL (if the tree is empty).
 * @brief This function finds the maximum value in the binary search tree by
 *        following the right child pointers from the root until we encounter a
 *        NULL. This means that to get the maximum value in our binary search
 *        tree, we only need to go to the rightmost node.
 * @credit The recursive search algorithm for the maximum value is taken from
 *         https://github.com/gzc/CLRS/blob/master/C12-Binary-Search-Trees/
 *         12.2.md.
 * @author Anil Celik Maral, 2019.08.13  */
anil::bst_node* anil::bst::find_max_recursively(bst_node* node) {
  if (node->right != NULL) {
    return find_max_recursively(node->right);
  }
  return node;
}

/**
 * @param none
 * @return This function returns a pointer to a node with the maximum value
 *         if one exists; otherwise, it returns NULL (if the tree is empty).
 * @brief This is a wrapper function for the actual recursive search function
 *        for the maximum value. This is done to reduce usage errors and so 
 *        that the search always starts at the root.
 * @author Anil Celik Maral, 2019.08.13  */
anil::bst_node* anil::bst::find_max_recursively() {
  return find_max_recursively(root); 
}

int anil::bst::successor(bst_node* node) {
    // The successor is the minimum data value of the right-subtree
    if (node->right != NULL) {
        return find_min(node->right);
    }

    // If there is no right-subtree:
    bst_node* pano = node->parent;  // Parent node = pano
    bst_node* cuno = node;          // Current node = cuno

    // While we haven't reached the root and current node is its
    // parent's right child:
    while ((pano != NULL) && (cuno == pano->right)) {
        cuno = pano;
        pano = cuno->parent;
    }

    // If the parent node is not NULL, then we found a successor!
    return pano == NULL ? -1 : pano->data;
}

int anil::bst::successor(int data) {
    // First, search and find data's node!
    bst_node* node = search(root, data);

    // If the data's node or its successor wasn't found return -1.
    return node == NULL ? -1 : successor(node);
}

int anil::bst::predecessor(bst_node* node) {
    // The predecessor is the maximum data value of the left-subtree
    if (node->left != NULL) {
        return find_max(node->left);
    }

    // If there is no left-subtree:
    bst_node* pano = node->parent;  // Parent node = pano
    bst_node* cuno = node;          // Current node = cuno

    // While we haven't reached the root and current node is its
    // parent's left child:
    while ((pano != NULL) && (cuno == pano->left)) {
        cuno = pano;
        pano = cuno->parent;
    }
    
    // If the parent node is not NULL, then we found a predecessor!
    return pano == NULL ? -1 : pano->data;
}

int anil::bst::predecessor(int data) {
    // First, search and find data's node!
    bst_node* node = search(root, data);

    // If the data's node or its predecessor wasn't found return -1.
    return node == NULL ? -1 : predecessor(node);
}

/*
 * Explanation: "In order to move subtrees around within the binary
 *              search tree, we define a subroutine" transplant(), "
 *              which replaces one subtree as a child of its parent
 *              with another subtree". "When" transplant() "replaces
 *              the subtree rooted at node" replaced "with the subtree
 *              rooted at node" replacing," node " replaced's" parent
 *              becomes node "replacing's" parent, and "replaced's"
 *              parent ends up having "replacing" as its appropriate
 *              child".
 * 
 * Note: transplant() "does not attempt to update replacing->left and
 *       replacing->right; doing so, or not doing so, is the 
 *       responsibility of" transplant()'s "caller".
 * 
 * Note-2: u and v variables in the book are changed with replaced and
 *         replacing respectively.
 * 
 * Credit: The implementation and some of the explanations are taken
 *         from CLRS 3rd edition chapter 12.
 *  */
void anil::bst::transplant(bst_node* replaced, bst_node* replacing) {
    if (replaced->parent == NULL) {
        root = replacing;
    } else if (replaced == replaced->parent->left) {
        replaced->parent->left = replacing;
    } else {    // replaced == replaced->parent->right
        replaced->parent->right = replacing;
    }

    if (replacing != NULL) {
        replacing->parent = replaced->parent;
    }
}

// Add the explanation from the book!
anil::bst_node* anil::bst::remove(bst_node* node, int data) {
    if (node->left == NULL) {
        transplant(node, node->right);
    } else if (node->right == NULL) {
        transplant(node, node->left);
    } else {    // node has a left and right child
        bst_node* successor = find_min(node->right);
        if (successor->parent != node) {
            transplant(successor, successor->right);
            successor->right = node->right;
            successor->right->parent = successor;
        }
        transplant(node, successor);
        successor->left = node->left;
        successor->left->parent = successor;    
}

// IN ORDER REMOVE?
// How do you delete an entire bst?
anil::bst::~bst() {
    while (!is_empty()) {
        remove();
    }
}
