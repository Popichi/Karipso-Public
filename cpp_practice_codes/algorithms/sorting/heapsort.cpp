/* This is an implementation of a heapsort algorithm using an array as the
   underlying data structure to simulate heap behavior. */

/* TO DO: 1) 243, 1043, 4399, 456, 0, 1, 34323433, 533, 17, 49 returns
             0, 1, 17, 49, 243, 533, 456, 1043, 4399, 34323433 which is
             incorrect. Fix the bug! */

#include "heapsort.h"

std::array<int, 10>& anil::heapsort(std::array<int, 10>& array_to_be_sorted) {
  size_t end_of_the_unsorted_portion_of_array = array_to_be_sorted.size();

  // Build max heap from the input array
  for (size_t i = end_of_the_unsorted_portion_of_array / 2; i > 0; --i) {
    sift_down(array_to_be_sorted, i, end_of_the_unsorted_portion_of_array);
  }

  // Repeatedly extract the max element from the heap and place it at the 
  // beginning of the sorted portion of the array
  for (size_t i =  end_of_the_unsorted_portion_of_array - 1; i > 0; --i) {
    // Swap the max element (at the root of the heap) with the last element in the heap
    std::swap(array_to_be_sorted[0], array_to_be_sorted[i]);
    // Remove the last element (which is now in the correct sorted position) from the heap
    --end_of_the_unsorted_portion_of_array;
    // Restore the heap property by sifting down the new root element to its correct position
    sift_down(array_to_be_sorted, 0, end_of_the_unsorted_portion_of_array);
  }

  return array_to_be_sorted;
}


// Helper function to restore the heap property by sifting down an element to 
// its correct position
void anil::sift_down(std::array<int, 10>& array, size_t start_index_of_the_array, 
               size_t end_index_of_the_array) {

  // Set it equal to root which is the element that needs to be sifted down.
  size_t index_of_the_element_to_be_sifted_down = 0;

  // In a binary heap, the children of a node at index i are located at indices
  // 2 * i + 1 and 2 * i + 2 when we are using an array as the underlying data
  // structure. So, for a given node, its left child will be at index 2 * i + 1
  // and its right child will be at index 2 * i + 2. If 2 * i + 1 > size of
  // array, then the current root node has no children and the sift_down 
  // operation is complete.
  while (2 * index_of_the_element_to_be_sifted_down + 1 < end_index_of_the_array) {
    
    // Find the index of the largest child of the current node
    // we first set the index of the child we choose to get swapped with as
    // the index of the left child.
    size_t index_of_the_chosen_child = 2 * 
           index_of_the_element_to_be_sifted_down + 1;
    // If the right child of the current node exists and is greater than the
    // left child, then we choose it instead to maintain the heap property.
    if (index_of_the_chosen_child + 1 < end_index_of_the_array and 
        array[index_of_the_chosen_child] < array[index_of_the_chosen_child + 1]) {
      ++index_of_the_chosen_child;
    }

    // If the current node is smaller than its largest child, swap them and 
    // continue sifting down
    if (array[index_of_the_element_to_be_sifted_down] < 
        array[index_of_the_chosen_child]) {
      std::swap(array[index_of_the_element_to_be_sifted_down], 
                array[index_of_the_chosen_child]);
      index_of_the_element_to_be_sifted_down = index_of_the_chosen_child;
    } else {
      return;
    }
  }
}
