#include <iostream>
#include <deque> 
#include <sstream>
using namespace std;

    // a       b 
    // 4 5 6 2 3 5 6 7 8 4 3 2 4 5 6 7
    // max is 6 at position 2
    // slide range forward one
        
    //   a       b 
    // 4 5 6 2 3 5 6 7 8 4 3 2 4 5 6 7
    // just two checks:
    // 1. Did the max go out of range? Was it at position a-1?
    // 2. Is the new value at b greater than the max?
    // No, no; Max is still 6 at position 2.
    // print it, and move on. Cheap! :^)
void printKMax(int arr[], int n, int k) 
{ 
    // Create a Double Ended Queue, Qi that will store indexes of array elements 
    // The queue will store indexes of useful elements in every window and it will 
    // maintain decreasing order of values from front to rear in Qi, i.e., 
    // arr[Qi.front[]] to arr[Qi.rear()] are sorted in decreasing order 
    std::deque<int> Qi(k); 
  
    /* Process first k (or first window) elements of array */
    int i; 
    for (i = 0; i < k; ++i) { 
        // For every element, the previous smaller elements are useless so 
        // remove them from Qi 
        while ((!Qi.empty()) && arr[i] >= arr[Qi.back()]) 
            Qi.pop_back(); // Remove from rear 
  
        // Add new element at rear of queue 
        Qi.push_back(i); 
    } 
  
    // Process rest of the elements, i.e., from arr[k] to arr[n-1] 
    for (; i < n; ++i) { 
        // The element at the front of the queue is the largest element of 
        // previous window, so print it 
        cout << arr[Qi.front()] << " "; 
  
        // Remove the elements which are out of this window 
        while ((!Qi.empty()) && Qi.front() <= i - k) 
            Qi.pop_front(); // Remove from front of queue 
  
        // Remove all elements smaller than the currently 
        // being added element (remove useless elements) 
        while ((!Qi.empty()) && arr[i] >= arr[Qi.back()]) 
            Qi.pop_back(); 
  
        // Add current element at the rear of Qi 
        Qi.push_back(i); 
    } 
  
    // Print the maximum element of last window 
    cout << arr[Qi.front()] << endl; 
} 

// Input
//     2

//     5 2

//     3 4 6 3 4

//     7 4

//     3 4 5 8 1 4 10

int main() {

  std::stringstream string_stream;
  string_stream << "2\n" << "5 2\n" << "3 4 6 3 4\n" << "7 4\n" << "3 4 5 8 1 4 10\n";

  int t;
	string_stream >> t;
	while(t>0) {
		int n,k;
    string_stream >> n >> k;
    int i;
    int arr[n];
    for(i=0;i<n;i++)
      string_stream >> arr[i];
    printKMax(arr, n, k);
    t--;
  }
  return 0;
}

// int main(){
  
// 	int t;
// 	cin >> t;
// 	while(t>0) {
// 		int n,k;
//     	cin >> n >> k;
//     	int i;
//     	int arr[n];
//     	for(i=0;i<n;i++)
//       		cin >> arr[i];
//     	printKMax(arr, n, k);
//     	t--;
//   	}
//   	return 0;
// }

