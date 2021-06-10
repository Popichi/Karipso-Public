/* This is an implementation of a trie based on the LeetCode question
   "208. Implement Trie (Prefix Tree)!

   It is assumed that all inputs are lowercase letters a - z.

   It is, also, assumed that all inputs are guaranteed to be non-empty strings.

   Lastly, no word maybe the prefix of other words.
*/

/* TO DO: */

#ifndef ANIL_TRIE_H
#define ANIL_TRIE_H

#include <cstddef>
#include <iostream>

namespace anil {
  class trie_node {  // Binary search tree node
    private:
      char c;
      bool is_word;
      trie_node* children;
      friend class trie;

    public:
      trie_node() {
        c = '\0';
        is_word = false;
        children = new trie_node[26];
      }

      trie_node(char letter) {
        c = letter;
        is_word = false;
        children = new trie_node[26];
      }
      ~trie_node();
  };

  class trie { // A trie data structure
    private:

      // Data:
      trie_node* root;

      // Functions:
      trie_node* get_node(std::string word);

    public:
      trie() {
        root = new trie_node('\0');
      }
      void insert(std::string word);  // Add word to the trie data structure. For example, insert(cats)
      bool search(std::string word);  // Determine if a word is in the trie data structure. For example, search(cats) --> true or false
      bool starts_with(std::string prefix); // Determine if a prefix is in the trie data structure. For example, starts_with("cat") --> true or false
      ~trie();
  };
}

#endif /* ANIL_TRIE_H */
