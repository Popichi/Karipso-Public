/* This is an implementation of a trie based on the LeetCode question
   "208. Implement Trie (Prefix Tree)!

   It is assumed that all inputs are lowercase letters a - z.

   It is, also, assumed that all inputs are guaranteed to be non-empty strings.

   Lastly, no word maybe the prefix of other words.
*/

/* TO DO: */

#include "anil_trie.h"

/**
 * @param node is the node that will be inserted into the binary search tree.
 * @return void
 * @brief The function recursively searches the tree according to the rules of
 *        a general binary search tree to insert the new data accordingly by
 *        creating a new node.
 * @time complexity: O(h), where h is the height of the tree. The nodes
 *       encountered during the operation form a simple path downward from
 *       the root of the tree.
 * @space complexity: O(1)
 * @credit The insert algorithm is taken from https://youtu.be/giialofn31A
 * @author Anil Celik Maral, 2021.06.10  */
void anil::trie::insert(std::string word) {
  trie_node* current_node = root;
  for (int i = 0; i < word.size(); ++i) {
    char letter_of_word = word[i];
    if(current_node->children[letter_of_word - 'a'] == nullptr) {
      current_node->children[letter_of_word - 'a'] = new trie_node(letter_of_word);
      current_node = &current_node->children[letter_of_word - 'a'];
    }
    current_node->is_word = true;
  }
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
 * @credit The insert algorithm is taken from https://youtu.be/giialofn31A
 * @author Anil Celik Maral, 2021.06.10  */
anil::trie_node* get_node(std::string word) {
  trie_node* current_node = root;
  for (int i = 0; i < word.size(); ++i) {
    char letter_of_word = word[i];
    if (current_node->children[letter_of_word - 'a'] == nullptr) {
      return nullptr;
    }
    current_node = &current_node->children[letter_of_word - 'a'];
  }
  return current_node;
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
 * @credit The insert algorithm is taken from https://youtu.be/giialofn31A
 * @author Anil Celik Maral, 2021.06.10  */
bool search(std::string word) {
  trie_node* node_of_last_char = get_node(word);
  return node_of_last_char != nullptr && node_of_last_char->is_word;
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
 * @credit The insert algorithm is taken from https://youtu.be/giialofn31A
 * @author Anil Celik Maral, 2021.06.10  */
bool starts_with(std::string prefix) {
  return get_node(prefix) != nullptr;
}