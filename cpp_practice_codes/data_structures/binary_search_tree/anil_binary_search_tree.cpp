/* This is an implementation of a binary search tree! This source code follows
   Google's C++ Style Guidelines with minimal modification. */
/* TO DO: 1) Combine iterative and recursive implementations and make it
             possible to change between using flags! */

#include "anil_binary_search_tree.h"

/**
 * @return true if the binary search tree is empty and false if not.
 * @brief This function checks if a binary search tree is empty or not.
 * @author Anil Celik Maral, 2019.10.18  */
bool anil::bst::is_empty() {
    return root == NULL;
}

/**
 * @param node is the node that will be inserted into the binary search tree.
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
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
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
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->parent = NULL;
    insert_iteratively(new_node);
  }
  return new_node;
}

/**
 * @param node is the node that we start our inorder tree walk at.
 * @param ostream is an object such as a file or stdout where the information
 *        will be printed to.
 * @return void
 * @brief This function uses inorder tree walk algorithm to print node's
 *        subtree and itself inorder. This means that it prints the key of 
 *        the root of a subtree between printing the values in its left subtree
 *        and printing those in its right subtree.
 * @credit The inorder tree walk algorithm is taken from page 288 of 3rd 
 *         edition of CLRS.
 * @author Anil Celik Maral, 2019.08.11
 * @update Anil Celik Maral, 2021.05.31  */
void anil::bst::print_inorder(std::ostream& os, bst_node* node) {
  if (node != nullptr) {
    print_inorder(os, node->left);
    os << node->data << ' ';
    print_inorder(os, node->right);
  }
}

/**
 * @param ostream is an object such as a file or stdout where the information
 *        will be printed to.
 * @return void
 * @brief This is a wrapper function for the actual print inorder function.
 *        This is done to reduce usage errors and so that the printing always
 *        starts at the root.
 * @author Anil Celik Maral, 2019.08.11
 * @update Anil Celik Maral, 2021.05.31  */
void anil::bst::print_inorder(std::ostream& os) {
  print_inorder(os, root);
}

/**
 * @param an ostream object such as a file or stdout where the information
 *        will be printed to.
 * @return void
 * @brief This function prints node's own, node's parent's, node's right
 *        child's and node's left child's data respectively. This is a
 *        debug function.
 * @author Anil Celik Maral, 2019.08.20  */
void anil::bst::print_node_info(std::ostream& os, bst_node* node) {
  if (node != NULL) {

    os << "Node: " << node->data << ", ";

    if (node->parent != NULL) {
      os << "Node's parent: " << node->parent->data << ", ";
    } else {
      os << "Node's parent is NULL!, ";
    }

    if (node ->right != NULL) {
      os << "Node's right child: " << node->right->data << ", ";
    } else {
      os << "Node's right child is NULL!, ";
    }

    if (node->left != NULL) {
      os << "Node's left child: " << node->left->data << ' ';
    } else {
      os << "Node's left child is NULL! ";
    }
  } else {
    os << "Node is NULL!";
  }
  os << std::endl;
}

/**
 * @param an ostream object such as a file or stdout where the information
 *        will be printed to.
 * @param node whose information will be printed to the file given by 'os'.
 * @return void
 * @brief This function prints node's own, node's parent's, node's right
 *        child's and node's left child's data respectively for each node
 *        in the tree. This is a debug function.
 * @author Anil Celik Maral, 2019.10.20  */
void anil::bst::print_tree_info(std::ostream& os, bst_node* node) {
  if (node != NULL) {
    print_node_info(os, node->left);
    print_node_info(os, node->right);
  }
}

/**
 * @param an ostream object such as a file or stdout where the information
 *        will be printed to.
 * @return void
 * @brief This function prints node's own, node's parent's, node's right
 *        child's and node's left child's data respectively for each node
 *        in the tree. This is a debug function.
 * @author Anil Celik Maral, 2019.10.20  */
void anil::bst::print_tree_info(std::ostream& os) {
  print_tree_info(os, root);
}

/**
 * @param node is the node that we start the search at, which is usually the
 *             root.
 * @param data_we_search_for is the value that we look for in the binary
 *        search tree.
 * @return This function returns a pointer to the node with the value 
 *         data_we_search_for, if one exists; otherwise, it returns 
 *         nullptr.
 * @brief This function starts at the node specified by the node parameter and
 *        searches for the node that contains the value data_we_search_for
 *        using the binary search tree properties.
 * @time complexity: O(h), where h is the height of the tree. The nodes
 *       encountered during the recursion form a simple path downward from
 *       the root of the tree.
 * @space complexity: O(1)
 * @credit The recursive search algorithm is taken from page 290 of 3rd 
 *         edition of CLRS.
 * @author Anil Celik Maral, 2019.08.12
 * @update Anil Celik Maral, 2021.05.31  */
anil::bst_node* anil::bst::search_recursively(bst_node* node,
  int data_we_search_for) {
  if (node == nullptr || data_we_search_for == node->data) {
    return node;
  }
  if (data_we_search_for < node->data) {
    return search_recursively(node->left, data_we_search_for);
  } else { // data_we_search_for > node->data
    return search_recursively(node->right, data_we_search_for);
  }
}

/**
 * @param data_we_search_for is the value that we look for in the binary
 *        search tree.
 * @return This function returns a pointer to the node with the value
 *         data_we_search_for, if one exists; otherwise, it returns NULL.
 * @brief This is a wrapper function for the actual recursive search function.
 *        This is done to reduce usage errors and so that the search always 
 *        starts at the root.
 * @author Anil Celik Maral, 2019.08.12
 * @update Anil Celik Maral, 2021.05.31  */
anil::bst_node* anil::bst::search_recursively(int data_we_search_for) {
  return search_recursively(root, data_we_search_for);
}

/**
 * @param node is the node that we start the search at, which is usually the
 *             root.
 * @param data_we_search_for is the value that we look for in the binary
 *        search tree.
 * @return This function returns a pointer to a node with the
 *         value data_we_search_for, if one exists; otherwise, it returns 
 *         nullptr.
 * @brief This function starts at the node specified by the node parameter and
 *        searches for the node that contains the value data_we_search_for
 *        using the binary search tree properties.
 * @time complexity: O(h), where h is the height of the tree. The nodes
 *       encountered during the recursion form a simple path downward from
 *       the root of the tree.
 * @space complexity: O(1)
 * @credit The iterative search algorithm is taken from page 291 of 3rd 
 *         edition of CLRS.
 * @author Anil Celik Maral, 2019.08.12
 * @update Anil Celik Maral, 2021.05.31  */
anil::bst_node* anil::bst::search_iteratively(bst_node* node, 
  int data_we_search_for) {
  while (node != nullptr && data_we_search_for != node->data) {
    if (data_we_search_for < node->data) {
      node = node->left;
    } else {  // data_we_search_for > node->data
      node = node->right;
    }
  }
  return node;
}

/**
 * @param data_we_search_for is the value that we look for in the binary search
 *        tree.
 * @return This function returns a pointer to the node with the value
 *         data_we_search_for, if one exists; otherwise, it returns nullptr.
 * @brief This is a wrapper function for the actual iterative search function.
 *        This is done to reduce usage errors and so that the search always
 *        starts at the root.
 * @author Anil Celik Maral, 2019.08.12
 * @update Anil Celik Maral, 2021.05.31  */
anil::bst_node* anil::bst::search_iteratively(int data_we_search_for) {
  return search_iteratively(root, data_we_search_for);
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

/**
 * @param node is the node that we check to see if it contains the minimum 
 *        element in the binary search tree.
 * @return This function returns a pointer to the node with the minimum value
 *         if one exists; otherwise, it returns nullptr (if the tree is empty).
 * @brief This function finds the minimum value in the binary search tree by
 *        following left child pointers from the root until we encounter a
 *        nullptr. This means that to get the minimum value in our binary search
 *        tree, we only need to go to the leftmost node.
 * @credit The iterative search algorithm for the minimum value is taken from
 *         page 291 of 3rd edition of CLRS.
 * @time complexity: O(h), where h is the height of the tree. The sequence of
 *                   nodes encountered forms a simple path downward from the
 *                   root.
 * @space complexity: O(1)
 * @author Anil Celik Maral, 2019.08.13
 * @update Anil Celik Maral, 2021.06.03  */
anil::bst_node* anil::bst::find_min_iteratively(bst_node* node) {
  while (node->left != nullptr) {
    node = node->left;
  }
  return node;
}

/**
 * @param none
 * @return This function returns a pointer to a node with the minimum value
 *         if one exists; otherwise, it returns nullptr (if the tree is empty).
 * @brief This is a wrapper function for the actual iterative search function
 *        for the minimum value. This is done to reduce usage errors and so 
 *        that the search always starts at the root.
 * @author Anil Celik Maral, 2019.08.13
 * @update Anil Celik Maral, 2021.06.03  */
anil::bst_node* anil::bst::find_min_iteratively() {
  return find_min_iteratively(root);
}

/**
 * @param node is the node that we check to see if it contains the maximum 
 *        element in the binary search tree.
 * @return This function returns a pointer to the node with the maximum value
 *         if one exists; otherwise, it returns a nullptr (if the tree is
 *         empty).
 * @brief This function finds the maximum value in the binary search tree by
 *        following the right child pointers starting from the root until we
 *        encounter a nullptr. This means that to get the maximum value in our
 *        binary search tree, we only need to go to the rightmost node.
 * @time complexity: O(h), where h is the height of the tree. The sequence of
 *                   nodes encountered forms a simple path downward from the
 *                   root.
 * @space complexity: O(1)
 * @credit The iterative search algorithm for the maximum value is taken from
 *         page 291 of 3rd edition of CLRS.
 * @author Anil Celik Maral, 2019.08.13
 * @update Anil Celik Maral, 2021.06.03  */
anil::bst_node* anil::bst::find_max_iteratively(bst_node* node) {
  while (node->right != nullptr) {
    node = node->right;
  }
  return node;
}

/**
 * @param none
 * @return This function returns a pointer to a node with the maximum value
 *         if one exists; otherwise, it returns a nullptr (if the tree is
 *         empty).
 * @brief This is a wrapper function for the actual iterative search function
 *        for the maximum value. This is done to reduce usage errors and so 
 *        that the search always starts at the root.
 * @author Anil Celik Maral, 2019.08.13
 * @update Anil Celik Maral, 2021.06.03  */
anil::bst_node* anil::bst::find_max_iteratively() {
  return find_max_iteratively(root);
}

/**
 * @param node is the node whose data we return to the caller.
 * @return This function returns the data stored in the node.
 * @brief This is an access function that returns the data stored in a node.
 * @author Anil Celik Maral, 2019.09.02  */
int anil::bst::data(bst_node* node) {
  return node->data;
}

/**
 * @param node is the node whose successor we search for.
 * @return This function returns a pointer to the node that is the successor of
 *         the node given in the node parameter of this function, if one
 *         exists; otherwise, it returns nullptr if the tree is empty or the
 *         node given in the node parameter of this function has the largest
 *         value in the binary search tree.
 * @brief This function finds the successor of the node given in the node
 *        parameter of this function. The successor of a node is the node with
 *        the smallest value greater than the value of the node whose successor
 *        we are looking for.
 * @time complexity: O(h), where h is the height of the tree, since we either
 *                   follow a simple path up the tree or follow a simple path
 *                   down the tree.
 * @space complexity: O(1)
 * @credit The algorithm for finding the successor of a node is taken from page
 *         292 of 3rd edition of CLRS.
 * @author Anil Celik Maral, 2019.08.13
 * @update Anil Celik Maral, 2021.06.03  */
anil::bst_node* anil::bst::successor(bst_node* node) {

  // If the right subtree of node is nonempty, then the successor of node is
  // just the leftmost node in node's right subtree.
  if (node->right != nullptr) {
#ifdef ANIL_BST_USE_RECURSIVE_VERSIONS
    return find_min_recursively(node->right);
#elif ANIL_BST_USE_ITERATIVE VERSIONS
    return find_min_iteratively(node->right);
#endif
  }

  // If the right subtree of node is empty and node has a successor y, then y
  // is the lowest ancestor of node whose left child is also an ancestor of
  // node. To find y, we simply go up the tree from node until we encounter
  // a node that is the left child of its parent.
  bst_node* temp = node;
  bst_node* possible_successor_node = node->parent;
  while (possible_successor_node != nullptr &&
    temp == possible_successor_node->right) {
    temp = possible_successor_node;
    possible_successor_node = possible_successor_node->parent;
  }
  return possible_successor_node;
}

/**
 * @param node is the node whose predecessor we search for.
 * @return This function returns a pointer to the node that is the predecessor
 *         of the node given in the node parameter of this function, if one 
 *         exists; otherwise, it returns nullptr if the tree is empty or the
 *         node given in the node parameter of this function has the smallest
 *         value in the binary search tree.
 * @brief This function finds the predecessor of the node given in the node 
 *        parameter of this function. The predecessor of a node is the node
 *        with the largest value less than the value of node whose predecessor
 *        we are looking for.
 * @time complexity: O(h), where h is the height of the tree, since we either
 *                   follow a simple path up the tree or follow a simple path
 *                   down the tree.
 * @space complexity: O(1)
 * @credit Predecessor algorithm is written by me; however, it is symmetric to
 *         the successor algorithm given on page 292 of 3rd edition of CLRS.
 * @author Anil Celik Maral, 2019.08.13
 * @update Anil Celik Maral, 2021.06.03  */
anil::bst_node* anil::bst::predecessor(bst_node* node) {

  // If the left subtree of node is nonempty, then the predecessor of node
  // is just the rightmost node in node's left subtree.
  if (node->left != nullptr) {
#ifdef ANIL_BST_USE_RECURSIVE_VERSIONS
    return find_max_recursively(node->left);
#elif ANIL_BST_USE_ITERATIVE VERSIONS
    return find_max_iteratively(node->left);
#endif
  }

  // If the left subtree of node is empty and node has a predecessor y, then y
  // is the lowest ancestor of node whose right child is also an ancestor of
  // node. To find y, we simply go up the tree from node until we encounter
  // a node that is the right child of its parent.
  bst_node* temp = node;
  bst_node* possible_predecessor_node = node->parent;
  while (possible_predecessor_node != nullptr &&
    temp == possible_predecessor_node->left) {
    temp = possible_predecessor_node;
    possible_predecessor_node = possible_predecessor_node->parent;
  }
  return possible_predecessor_node;
}

/**
 * @param replaced is the node that we replace with the node pointed at
 *        replacing parameter.
 * @param replacing is the node that replaces the node pointed at replaced
 *        parameter.
 * @return void
 * @brief "In order to move subtrees around within the binary search tree, we
 *        define a subroutine" transplant(), "which replaces one subtree as a
 *        child of its parent with another subtree". "When" transplant() 
 *        "replaces the subtree rooted at node" replaced "with the subtree 
 *        rooted at node" replacing, "node" replaced's "parent becomes node"
 *        replacing's "parent, and" replaced's "parent ends up having" 
 *        replacing "as its appropriate child".
 * @warning transplant() "does not attempt to update replacing->left and 
 *          replacing->right; doing so, or not doing so, is the responsibility
 *          of" transplant()'s "caller".
 * @credit The algorithm for replacing one subtree as a child of its parent
 *         with another subtree is taken from page 296 of 3rd edition of CLRS.
 * @author Anil Celik Maral, 2019.08.13  */
void anil::bst::transplant(bst_node* replaced, bst_node* replacing) {
  if (replaced->parent == NULL) {
    root = replacing;
  } else if (replaced == replaced->parent->left) {
    replaced->parent->left = replacing;
  } else {  // replaced == replaced->parent->right
    replaced->parent->right = replacing;
  }

  if (replacing != NULL) {
    replacing->parent = replaced->parent;
  }
}

/**
 * @param node_to_be_deleted is the node that we delete from the binary search
 *        tree.
 * @return void
 * @brief This function removes the node pointed by the parameter 
 *        node_to_be_deleted from the binary search tree while protecting the
 *        properties of the binary search tree. Therefore, all of the binary
 *        search tree properties still hold for the remaining tree after the
 *        said node has been removed from the tree.
 * @credit The algorithm for removing a node from the binary search tree is
 *         taken from page 298 of 3rd edition of CLRS.
 * @author Anil Celik Maral, 2019.08.14  */
void anil::bst::remove(bst_node* node_to_be_deleted) {
  if (node_to_be_deleted == NULL) {
    return;
  }

  /* "If" node to be deleted "has no left child, then we replace" node to be
     deleted "by its right child, which may or may not be NIL. When" node to
     be deleted's "right child is NIL, this case deals with the situation in
     which" node to be deleted "has no children. When" node to be deleted's
     "right child is non-NIL, this case handles the situation in which" node
     to be deleted "has just one child, which is its right child". */
  if (node_to_be_deleted->left == NULL) {
    transplant(node_to_be_deleted, node_to_be_deleted->right);

  /* "If" node to be deleted "has just one child, which is its left child, 
     then we replace" node to be deleted "by its left child". */
  } else if (node_to_be_deleted->right == NULL) {
        transplant(node_to_be_deleted, node_to_be_deleted->left);

  /* "Otherwise," node to be deleted "has both a left and a right child. We
     find" node to be deleted's "successor, which lies in" node to be deleted's
     "right subtree and has no left child. We want to splice" successor "out of
     its current location and have it replace" node to be deleted "in the
     tree". */      
  } else {
#ifdef ANIL_BST_USE_RECURSIVE_VERSIONS
    bst_node* successor = find_min_recursively(node_to_be_deleted->right);
#elif ANIL_BST_USE_ITERATIVE VERSIONS
    bst_node* successor = find_min_iteratively(node_to_be_deleted->right);
#endif

    /* "If" successor "is" node to be deleted's "right child, then we replace"
       node to be deleted "by" successor, leaving" successor's "right child 
       alone. Otherwise," successor "lies within" node to be deleted's "right
       subtree but its not" node to be deleted's "right child. In this case,
       we first replace" successor "by its own right child, and then we 
       replace" node to be delete "by" successor. */
    if (successor->parent != node_to_be_deleted) {
      transplant(successor, successor->right);
      successor->right = node_to_be_deleted->right;
      successor->right->parent = successor;
    }
    transplant(node_to_be_deleted, successor);
    successor->left = node_to_be_deleted->left;
    successor->left->parent = successor;   
  }
  delete node_to_be_deleted; 
}

/**
 * @param node is the node whose subtree and itself gets deleted.
 * @return void
 * @brief This function deletes a binary search subtree whose root is located
 *        at the node parameter by recursively deleting every node in the tree
 *        following a post-order tree traversal.
 * @author Anil Celik Maral, 2019.08.15  */
void anil::bst::delete_recursively(bst_node* node) {
  if (node == NULL) { return; }
  delete_recursively(node->left);  
  delete_recursively(node->right); 
  delete node;
  node = NULL;
}

/**
 * @param none
 * @return void
 * @brief This function deletes an entire binary search tree by triggering a
 *        call to delete_recursively(), which then recursively deletes every
 *        node in the tree following a post-order tree traversal.
 * @author Anil Celik Maral, 2019.08.14  */
anil::bst::~bst() {
  delete_recursively(root);
}
