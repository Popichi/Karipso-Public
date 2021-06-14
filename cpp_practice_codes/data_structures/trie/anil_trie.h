/* This is an implementation of a trie based on the LeetCode question
   "208. Implement Trie (Prefix Tree)!

   It is assumed that all inputs are lowercase letters a - z.

   It is, also, assumed that all inputs are guaranteed to be non-empty strings.

   Lastly, no word maybe the prefix of other words.
*/

/* TO DO:
*/

#ifndef ANIL_TRIE_H
#define ANIL_TRIE_H

#include <cstddef>
#include <iostream>

namespace anil {
  class trie_node {
    private:
      char c;
      bool is_word;
      trie_node* children[26];  // Array of 26 trie_node pointers
      friend class trie;

    public:

      trie_node(char letter) {
        c = letter;
        is_word = false;
        for (int i = 0; i < 26; ++i) {
          children[i] = nullptr;
        }
      }
  };

  class trie { // A trie data structure
    private:

      // Data:
      trie_node* root;

      // Functions:
      trie_node* get_node(std::string word);
      void delete_trie(trie_node* node);

    public:
      trie() {
        root = new trie_node('\0');
      }
      void insert(std::string word);
      bool search(std::string word);
      bool starts_with(std::string prefix);
      ~trie();
  };
}

#endif /* ANIL_TRIE_H */
