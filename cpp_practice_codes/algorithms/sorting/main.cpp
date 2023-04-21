#include "heapsort.h"
#include <iostream>

int main() {
  std::array<int, 10> unsorted_array = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
  for (size_t i = 0; i < unsorted_array.size(); ++i) {
    if (i != unsorted_array.size() - 1) {
      std::cout << unsorted_array[i] << ", ";
    } else {
      std::cout << unsorted_array[i] << std::endl;
    }
  }
  std::array<int, 10>& sorted_array = anil::heapsort(unsorted_array);
  for (size_t i = 0; i < sorted_array.size(); ++i) {
    if (i != sorted_array.size() - 1) {
      std::cout << sorted_array[i] << ", ";
    } else {
      std::cout << sorted_array[i] << std::endl;
    }
  }

  std::array<int, 10> unsorted_array2 = {243, 1043, 4399, 456, 0, 1, 34323433, 533, 17, 49};
  for (size_t i = 0; i < unsorted_array2.size(); ++i) {
    if (i != unsorted_array2.size() - 1) {
      std::cout << unsorted_array2[i] << ", ";
    } else {
      std::cout << unsorted_array2[i] << std::endl;
    }
  }
  std::array<int, 10>& sorted_array1 = anil::heapsort(unsorted_array2);
  for (size_t i = 0; i < sorted_array1.size(); ++i) {
    if (i != sorted_array1.size() - 1) {
      std::cout << sorted_array1[i] << ", ";
    } else {
      std::cout << sorted_array1[i] << std::endl;
    }
  }
  return 0;
}