/* This is an implementation of a heapsort algorithm using an array as the
   underlying data structure to simulate heap behavior. */

/* TO DO: 1) 243, 1043, 4399, 456, 0, 1, 34323433, 533, 17, 49 returns
             0, 1, 17, 49, 243, 533, 456, 1043, 4399, 34323433 which is
             incorrect. Fix the bug! */

#ifndef ANIL_HEAPSORT_H
#define ANIL_HEAPSORT_H

#include <array>
#include <utility>

namespace anil {
  std::array<int, 10>& heapsort(std::array<int, 10>& array_to_be_sorted);

  // Helper function to restore the heap property by sifting down an element
  // to its correct position
  void sift_down(std::array<int, 10>& array, size_t start_index_of_the_array, 
                 size_t end_index_of_the_array);
}

#endif /* ANIL_HEAPSORT_H */
