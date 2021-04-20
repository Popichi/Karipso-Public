/* This is the test harness for a stack data structure which utilizes a dynamic
   array*/

/* TO DO: 1) Determine the test cases!
            i) Determine the enumerations!
            ii) Code the "run_tests" function! */

#include "anil_stack_dynamic_array.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>

// The following enumeration contains the names of the tests conducted in
// this test harness and associates each one with a number to make the code
// more readable / understandable as this method eliminates the need to use
// magic numbers.
enum stack_tests {
  STACK_CONSTRUCTOR,
  STACK_PUSH,
  STACK_POP,
  STACK_PEEK,
  STACK_IS_EMPTY,
  STACK_IS_FULL,
  NO_OF_TESTS,
};

// The following array of strings associate enumeration values of tests
// declared in the enumeration 'stack_tests' with their string equivalents.
// For example, 'std::cout << stack_test_names[STACK_CONSTRUCTOR];' will
// print 'STACK_CONSTRUCTOR' as expected. This makes reporting and logging 
// easier.
static const char* stack_test_names[] = {
	"STACK_CONSTRUCTOR",
  "STACK_PUSH",
  "STACK_POP",
  "STACK_PEEK",
  "STACK_IS_EMPTY",
  "STACK_IS_FULL",
  "NO_OF_TESTS",
};

bool run_tests(std::ostream& os, int stack_test, bool verbose) {
  switch(stack_test) {
    case STACK_CONSTRUCTOR:
      {
        // Test to construct a stack.
        if (verbose) {
          os << "\nSTACK_CONSTRUCTOR:" << std::endl <<
            "Starting the construction operation:" <<
            std::endl;
        }
        anil::stack my_stack;
        if (&my_stack == nullptr) {
          if (verbose) {
            os << "\nConstruction unsuccessful!" << std::endl;
          }
          return false;
        } else {
          if (verbose) {
            os << "\nConstruction successful!" << std::endl;
          }
          return true;
        }
        break;
      }
    case STACK_PUSH:
      {
        // Test to insert elements:
        anil::stack my_stack;

        std::vector<int> numbers {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

        if (verbose) {
          os << "\nSTACK_PUSH:" << std::endl <<
            "Starting the push operation:" << std::endl;
        }
        
        for (auto x : numbers) {
          my_stack.push(x);
          if (verbose) {
            os << x << ' ';
          }
        }

        for (int i = numbers.size() - 1; i > 0; --i) {
          int popped_element = my_stack.pop();
          if (popped_element != numbers[i]) { return false; }
        }
        return true;
        break;
      }
    case STACK_POP:
      {
        // Test to pop elements:
        anil::stack my_stack;

        std::vector<int> numbers {15, 6, 18, 3, 7, 17, 20, 2, 4, 13, 9};

        for (auto x : numbers) {
          my_stack.push(x);
          if (verbose) {
            os << x << ' ';
          }
        }

        if (verbose) {
          os << "\nSTACK_POP:" << std::endl <<
            "Starting the pop operation:" <<
            std::endl;
        }

        for (int i = numbers.size() - 1; i > 0; --i) {
          int popped_element = my_stack.pop();
          if (popped_element != numbers[i]) { return false; }
        }
        return true;
        break;
      }
    case STACK_PEEK:
      {
        // Test to peep into the stack:
        anil::stack my_stack;

        std::vector<int> numbers {43, 44, 43, 44, 43, 44, 43, 44, 43, 44, 420};

        for (auto x : numbers) {
          my_stack.push(x);
          if (verbose) {
            os << x << ' ';
          }
        }

        if (verbose) {
          os << "\nSTACK_PEEK:" << std::endl <<
            "Starting the peep operation:" <<
            std::endl;
        }

        int peeked_element = my_stack.peek();
        if (peeked_element != 420) { return false; }
        return true;
        break;
      }
    case STACK_IS_EMPTY:
      {
        // Test to check if is_empty function works correctly:
        anil::stack my_stack;

        if (verbose) {
          os << "\nSTACK_IS_EMPTY:" << std::endl <<
            "Starting the is_empty operation:" <<
            std::endl;
        }

        if(my_stack.is_empty() != true) { return false; }
        return true;
        break;
      }
    case STACK_IS_FULL:
      {
        // Test to check if is_full function works correctly:
        anil::stack my_stack;

        std::vector<int> numbers {1, 2};

        for (auto x : numbers) {
          my_stack.push(x);
          if (verbose) {
            os << x << ' ';
          }
        }

        if (verbose) {
          os << "\nSTACK_IS_FULL:" << std::endl <<
            "Starting the is_full operation:" <<
            std::endl;
        }

        if (my_stack.is_full() != true) { return false; }
        return true;
        break;
      }
  }
}

int main (int argc, char **argv) {
  bool verbose = false;

  if (argc > 2 || (argc == 2 and strcmp(argv[1], "-v") != 0)) {
    std::cout << "Usage: ./stack_dynamic_array [-v]"  << std::endl;
    return 1;
  } else if (argc == 2 and strcmp(argv[1], "-v") == 0) {
    verbose = true;
  }

  const int number_of_tests = 3;
  std::ofstream log_file ("stack_dynamic_array_log.txt", std::ios::trunc);
  if (!log_file.is_open()) {
    std::cout << "There was a problem opening 'stack_dynamic_array_log.txt'" <<
      std::endl;
  }

  int no_of_tests_passed {0};

  for (int i = STACK_CONSTRUCTOR; i < NO_OF_TESTS; ++i) {
    bool test_result = run_tests(log_file, i, verbose);
    log_file << "Test " << stack_test_names[i] << ": " <<
      (test_result == true ? "PASSED" : "FAILED") << std::endl;
    if (test_result) { ++no_of_tests_passed; }
  }

  log_file << no_of_tests_passed << "/" << NO_OF_TESTS <<
    " tests were passed." << std::endl;

  log_file.close();

  return 0;
}