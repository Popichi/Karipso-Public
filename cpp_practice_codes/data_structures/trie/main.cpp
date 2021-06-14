/* This is the test harness for the trie data structure
   that I built */

/* TO DO: 1) Learn how to test the deconstructor!
            1-i) Use a shell program to both run the program and valgrind
            1-ii) What about unit testing a deconstructor? 
*/

#include "anil_trie.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
#include <string>
#include <sstream>

// The following enumeration contains the names of the tests conducted in
// this test harness and associates each one with a number to make the code
// more readable / understandable as this method eliminates the need to use
// magic numbers.
enum trie_tests {
  TRIE_CONSTRUCTOR,
  TRIE_INSERT,
  TRIE_SEARCH,
  TRIE_STARTS_WITH,
  NO_OF_TESTS,
};

// The following array of strings associate enumeration values of tests
// declared in the enumeration 'trie_tests' with their string
// equivalents. For example, 
// 'std::cout<<trie_test_names[TRIE_CONSTRUCTOR];'
// will print 'TRIE_CONSTRUCTOR' as expected. This makes
// reporting and logging easier.
static const char* trie_test_names[] = {
  "TRIE_CONSTRUCTOR",
  "TRIE_INSERT",
  "TRIE_SEARCH",
  "TRIE_STARTS_WITH",
  "NO_OF_TESTS",
};

bool run_tests(std::ostream& os, int trie_test, bool verbose) {
  switch(trie_test) {
    case TRIE_CONSTRUCTOR:
      {
        // Test to construct a trie.
        if (verbose) {
           os << "\nTRIE_CONSTRUCTOR:" << std::endl <<
             "Starting the construction operation:" <<
             std::endl;
        }
        anil::trie my_trie;
        if (&my_trie == nullptr) {
          if (verbose) {
            os << "Construction unsuccessful!" << std::endl;
          }
          return false;
        } else {
          if (verbose) {
            os << "Construction successful!" << std::endl;
          }
          return true;
        }

        break;
      }
    case TRIE_INSERT:
      {
        // Test to insert a word into the trie data structure.
        if (verbose) {
          os << "\nTRIE_INSERT:" << std::endl <<
           "Starting the insert operation:" <<
            std::endl;
        }
        anil::trie my_trie;
        my_trie.insert("apple");
        if (my_trie.search("apple") != true) { return false; }
        my_trie.insert("app");
        if (my_trie.search("app") != true) { return false; }
        
        return true;
        break;
      }
    case TRIE_SEARCH:
      {
        // Test to search a word in the trie data structure.
        if (verbose) {
          os << "\nTRIE_SEARCH:" << std::endl <<
           "Starting the search operation:" <<
            std::endl;
        }
        anil::trie my_trie;
        my_trie.insert("apple");
        if (my_trie.search("apple") != true) { return false; }
        my_trie.insert("app");
        if (my_trie.search("app") != true) { return false; }
        my_trie.insert("karen");
        if (my_trie.search("karen") != true) { return false; }
        
        return true;
        break;
      }
    case TRIE_STARTS_WITH:
      {
        // Test to check if a word starts with the given prefix in the trie
        // data structure.
        if (verbose) {
          os << "\nTRIE_STARTS_WITH:" << std::endl <<
           "Starting the starts_with operation:" <<
            std::endl;
        }
        anil::trie my_trie;
        my_trie.insert("apple");
        if (my_trie.search("apple") != true) { return false; }
        my_trie.insert("app");
        if (my_trie.search("app") != true) { return false; }
        my_trie.insert("karen");
        if (my_trie.search("karen") != true) { return false; }
        my_trie.insert("karl");
        if (my_trie.search("karl") != true) { return false; }
        if (my_trie.starts_with("kar") != true) { return false; }
        
        return true;
        break;
      }
    // case TRIE_DECONSTRUCTOR:
    //   {
    //     return false;
    //     break;
    //   }
  }
}

int main (int argc, char **argv) {
  bool verbose = false;

  if (argc > 2 || (argc == 2 and strcmp(argv[1], "-v") != 0)) {
    std::cout << "Usage: ./trie [-v]"  << std::endl;
    return 1;
  } else if (argc == 2 and strcmp(argv[1], "-v") == 0) {
    verbose = true;
  }

  std::ofstream log_file ("trie_log.txt", std::ios::trunc);
  if (!log_file.is_open()) {
    std::cout << "There was a problem opening 'trie_log.txt'" <<
      std::endl;
  }

  int no_of_tests_passed {0};

  for (int i = TRIE_CONSTRUCTOR; i < NO_OF_TESTS; ++i) {
    bool test_result = run_tests(log_file, i, verbose);
    log_file << "Test " << trie_test_names[i] << ": " <<
      (test_result == true ? "PASSED" : "FAILED") << std::endl;
    if (test_result) { ++no_of_tests_passed; }
  }

  log_file << no_of_tests_passed << "/" << NO_OF_TESTS <<
    " tests were passed." << std::endl;

  log_file.close();

  return 0;
}
