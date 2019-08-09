/* Write a function that takes a list L and returns a random sublist of
   size N of that list. Assume that the indexes must be in incresing
   order. That is, you cannot go backwards.
   
   Example: 
   
   L = [1, 2, 3, 4, 5]
   N = 3
   
   The function should return one of these lists

   [1, 2, 3]
   [1, 2, 4]
   [1, 2, 5]
   [1, 3, 4]
   [1, 3, 5]
   [1, 4, 5]
   [2, 3, 4]
   [2, 3, 5]
   [2, 4, 5]
   [3, 4, 5]
   
   The mathematical explanation for this question: https://www.quora.com/How-many-three-element-subsets-are-there-in-a-five-element-set-1-2-3-4-5 */


/* TO DO: 1) Understand the solution for this, ask if you still don't get it!
          2) Learn the mathematical reasoning behind this algorithm!
          3) Code a less elegant version by yourself!
          4) Beautify the outputting part!*/
          
/* My thought process: Given an list L with size n, we can find a random sublist of

   My thought process for this specific example: L = [1, 2, 3, 4, 5]
                                                 N = 3
                                                 
   First: Since we want an ascending sublist, we want*/

#include <iostream>
#include <vector>
#include <ctime>
// using namespace std;

// // Optimized helper function?:
// vector<int> helper(vector<int> L, int N) {
//   int idx, count = 0;
//   vector<int> ret;
//   srand(time(NULL));
//   idx = rand() % (L.size()-N);
//   cout << (L.size()-N) << ' ';
//   while(count < N) {
//     ret.push_back(L[idx]);
//     idx = (rand() % (L.size() - N - idx + 1 + count));
//     cout << (L.size() - N - idx + 1 + count) << ' ';
//     idx = (idx + idx + 1);
//     count++;
//   }
//   return ret;
// }

// int main() {
//   vector<int> L;
//   for (int i = 1; i < 6; i++) {
//     L.push_back(i);
//   }
//   vector<int> ret = helper(L, 3);
//   for (int i = 0; i < ret.size(); i++) {
//     cout << ret[i];
//   }
// }

// Less elegant version:
std::vector<int> find_asc_subset(std::vector<int> L, int N) {
    std::vector<int> result;
    srand(time(NULL));
    index = rand() % (L.size - N);
    for (int i = 0; i < N; ++i) {
        result.push_back()
    }
}

int main() {

    std::vector<int> L {1, 2, 3, 4, 5};

    std::vector<int> result = find_asc_subset(L, 3);
    for (auto x : result) {
        std::cout << x << ' ';
    }
    std::cout << std::endl;
  
    return 0;
}