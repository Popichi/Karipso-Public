/* This is an implementation of a trie based on the LeetCode question
   "208. Implement Trie (Prefix Tree)!

   It is assumed that all inputs are lowercase letters a - z.

   It is, also, assumed that all inputs are guaranteed to be non-empty strings.

   Lastly, no word maybe the prefix of other words.
*/

/* TO DO: 1) Test the code on LeetCode!
*/

#include "anil_trie.h"

/**
 * @param word is the word that will be added to the trie data structure.
 * @return void
 * @brief This function adds a word to the trie data structure.
 * @time complexity: ?
 * @space complexity: ?
 * @credit The insert algorithm is taken from https://youtu.be/giialofn31A
 * @author Anil Celik Maral, 2021.06.10  */
void anil::trie::insert(std::string word) {
  trie_node* current_node = root;
  for (int i = 0; i < word.size(); ++i) {
    char letter_of_word = word[i];
    if(current_node->children[letter_of_word - 'a'] == nullptr) {
      current_node->children[letter_of_word - 'a'] = new trie_node(letter_of_word);
      current_node = current_node->children[letter_of_word - 'a'];
    }
  }
  if (current_node != nullptr) { current_node->is_word = true; }
}

/**
 * @param word is the word whose last letter's node that we are trying to find.
 * @return the node of the very last letter of the word if that word is in thr
 *         trie data structure; otherwise, return nullptr.
 * @brief This is a helper function. It returns the very last node of the word
 *        that we are looking for, if it exists; otherwise, it returns nullptr.
 *        It is used by search() and starts_with() to avoid duplicate code and
 *        simplify logic.
 * @time complexity: ?
 * @space complexity: ?
 * @credit The insert algorithm is taken from https://youtu.be/giialofn31A
 * @author Anil Celik Maral, 2021.06.10  */
anil::trie_node* anil::trie::get_node(std::string word) {
  trie_node* current_node = root;
  for (int i = 0; i < word.size(); ++i) {
    char letter_of_word = word[i];
    if (current_node->children[letter_of_word - 'a'] == nullptr) {
      return nullptr;
    }
    current_node = current_node->children[letter_of_word - 'a'];
  }
  return current_node;
}

/**
 * @param word is the word that we are trying to determine whether it is in the
 *        trie data structure or not.
 * @return true or false depending on whether the word is in the trie data
           structure.
 * @brief This function determines if a word is in the trie data structure
          or not.
 * @time complexity: ?
 * @space complexity: ?
 * @credit The insert algorithm is taken from https://youtu.be/giialofn31A
 * @author Anil Celik Maral, 2021.06.10  */
bool anil::trie::search(std::string word) {
  trie_node* node_of_last_char = get_node(word);
  return node_of_last_char != nullptr && node_of_last_char->is_word;
}

/**
 * @param prefix is the prefix that we are trying to determine whether it is
 *        in the trie data structure or not.
 * @return true or false depending on whether the prefix is in the trie data
           structure.
 * @brief This function determines if a prefix is in the trie data structure
 *        or not.
 * @time complexity: ?
 * @space complexity: ?
 * @credit The insert algorithm is taken from https://youtu.be/giialofn31A
 * @author Anil Celik Maral, 2021.06.10  */
bool anil::trie::starts_with(std::string prefix) {
  return get_node(prefix) != nullptr;
}
















// /**
//  * @param node is the node that will be inserted into the binary search tree.
//  * @return void
//  * @brief The function recursively searches the tree according to the rules of
//  *        a general binary search tree to insert the new data accordingly by
//  *        creating a new node.
//  * @time complexity: O(h), where h is the height of the tree. The nodes
//  *       encountered during the operation form a simple path downward from
//  *       the root of the tree.
//  * @space complexity: O(1)
//  * @credit The insert algorithm is taken from https://youtu.be/giialofn31A
//  * @author Anil Celik Maral, 2021.06.10  */
// void anil::trie::insert(std::string word) {
//   trie_node& current_node = root;
//   for (int i = 0; i < word.size(); ++i) {
//     char letter_of_word = word[i];
//     if(current_node.children[letter_of_word - 'a'] == nullptr) {
//       current_node.children[letter_of_word - 'a'] = new trie_node(letter_of_word);
//       current_node = current_node.children[letter_of_word - 'a'];
//     }
//     current_node.is_word = true;
//   }
// }

// /**
//  * @param node is the node that will be inserted into the binary search tree.
//  * @param new_data is the data that will be inserted into the binary search 
//  *        tree.
//  * @return The node that is inserted into the binary search tree is returned.
//  * @brief The function recursively searches the tree according to the rules of
//  *        a general binary search tree to insert the new data accordingly by
//  *        creating a new node.
//  * @time complexity: O(h), where h is the height of the tree. The nodes
//  *       encountered during the operation form a simple path downward from
//  *       the root of the tree.
//  * @space complexity: O(1)
//  * @credit The insert algorithm is taken from https://youtu.be/giialofn31A
//  * @author Anil Celik Maral, 2021.06.10  */
// anil::trie_node* get_node(std::string word) {
//   trie_node& current_node = root;
//   for (int i = 0; i < word.size(); ++i) {
//     char letter_of_word = word[i];
//     if (current_node->children[letter_of_word - 'a'] == nullptr) {
//       return nullptr;
//     }
//     current_node = &current_node->children[letter_of_word - 'a'];
//   }
//   return current_node;
// }

// /**
//  * @param node is the node that will be inserted into the binary search tree.
//  * @param new_data is the data that will be inserted into the binary search 
//  *        tree.
//  * @return The node that is inserted into the binary search tree is returned.
//  * @brief The function recursively searches the tree according to the rules of
//  *        a general binary search tree to insert the new data accordingly by
//  *        creating a new node.
//  * @time complexity: O(h), where h is the height of the tree. The nodes
//  *       encountered during the operation form a simple path downward from
//  *       the root of the tree.
//  * @space complexity: O(1)
//  * @credit The insert algorithm is taken from https://youtu.be/giialofn31A
//  * @author Anil Celik Maral, 2021.06.10  */
// bool search(std::string word) {
//   trie_node* node_of_last_char = get_node(word);
//   return node_of_last_char != nullptr && node_of_last_char->is_word;
// }

// /**
//  * @param node is the node that will be inserted into the binary search tree.
//  * @param new_data is the data that will be inserted into the binary search 
//  *        tree.
//  * @return The node that is inserted into the binary search tree is returned.
//  * @brief The function recursively searches the tree according to the rules of
//  *        a general binary search tree to insert the new data accordingly by
//  *        creating a new node.
//  * @time complexity: O(h), where h is the height of the tree. The nodes
//  *       encountered during the operation form a simple path downward from
//  *       the root of the tree.
//  * @space complexity: O(1)
//  * @credit The insert algorithm is taken from https://youtu.be/giialofn31A
//  * @author Anil Celik Maral, 2021.06.10  */
// bool starts_with(std::string prefix) {
//   return get_node(prefix) != nullptr;
// }