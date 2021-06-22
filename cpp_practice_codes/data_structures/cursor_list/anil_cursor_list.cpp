/* This is an implementation of the list class which is similar to C++ STL
   std::list class. The difference is that this class has a cursor and index
   member which allows to underlie a specific node at any given time. */

/* TO DO: */

#include "anil_cursor_list.h"

/**
 * @return true if the binary search tree is empty and false if not.
 * @brief This function checks if a binary search tree is empty or not.
 * @author Anil Celik Maral, 2019.10.18
 * @update Anil Celik Maral, 2021.06.07  */
bool anil::bst::is_empty() {
    return root == nullptr;
}

/**
 * @param node is the node that will be inserted into the binary search tree.
 * @param new_data is the data that will be inserted into the binary search 
 *        tree.
 * @return The node that is inserted into the binary search tree is returned.
 * @brief The function recursively searches the tree according to the rules of
 *        a general binary search tree to insert the new data accordingly by
 *        creating a new node.
 * @time complexity: O(h), where h is the height of the tree. The nodes
 *       encountered during the operation form a simple path downward from
 *       the root of the tree.
 * @space complexity: O(1)
 * @credit The recursive insert algorithm for the is taken from
 *         https://github.com/gzc/CLRS/blob/master/C12-Binary-Search-Trees/
 *         12.3.md.
 * @author Anil Celik Maral, 2019.08.11
 * @update Anil Celik Maral, 2021.06.07  */
anil::bst_node* anil::bst::insert(bst_node* node, int new_data) {

}

/**
 * @param node is the node whose subtree and itself gets deleted.
 * @return void
 * @brief This function deletes a binary search subtree whose root is located
 *        at the node parameter by recursively deleting every node in the tree
 *        following a post-order tree traversal.
 * @author Anil Celik Maral, 2019.08.15
 * @update Anil Celik Maral, 2021.06.07  */
void anil::bst::delete_bst(bst_node* node) {
  if (node == nullptr) { return; }
  delete_bst(node->left);  
  delete_bst(node->right); 
  delete node;
  node = nullptr;
}

/**
 * @param none
 * @return void
 * @brief This function deletes an entire binary search tree by triggering a
 *        call to delete_bst(), which then recursively deletes every
 *        node in the tree following a post-order tree traversal.
 * @author Anil Celik Maral, 2019.08.14
 * @update Anil Celik Maral, 2021.06.07  */
anil::bst::~bst() {
  delete_bst(root);
}


cursor_list& operator= (const cursor_list& rhs);  // rhs = right hand side
/* Example good assignment operator code:
MyString& MyString::operator= (const MyString& str)
{
  // self-assignment check
  if (this == &str)
    return *this

  // if data exists in the current string, delete it
  if (m_data) delete[] m_data;

  m_length = str.m_length;

  // copy the data from str to the implicit object
  m_data = new char[str.m_length];

  for (int i = 0; i < str.m_length; ++i)
    m_data[i] = str.m_data[i];

  // return the existing object so we can chain this operator
  return *this;
}
*/