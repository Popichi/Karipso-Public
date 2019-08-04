// A practical problem based on unordered_map – given a string of words, find frequencies of individual words.

/* Input :  str = "geeks for geeks geeks quiz practice qa for";
Output : Frequencies of individual words are
   (practice, 1)
   (for, 2)
   (qa, 1)
   (quiz, 1)
   (geeks, 3) */


// C++ program to find freq of every word using 
// unordered_map 
#include <bits/stdc++.h> 
using namespace std; 
  
// Prints frequencies of individual words in str 
void printFrequencies(const string &str) 
{ 
    // declaring map of <string, int> type, each word 
    // is mapped to its frequency 
    unordered_map<string, int> wordFreq; 
  
    // breaking input into word using string stream 
    stringstream ss(str);  // Used for breaking words 
    string word; // To store individual words 
    while (ss >> word) 
        ++wordFreq[word];   // Originally changed from wordFreq[word]++; So, both work. I assume ++wordFreq[word] is faster? Why doesn't it try to increment the pointer first?
  
    // now iterating over word, freq pair and printing 
    // them in <, > format 
    unordered_map<string, int>:: iterator p; 
    for (p = wordFreq.begin(); p != wordFreq.end(); p++) 
        cout << "(" << p->first << ", " << p->second << ")\n"; 
} 
  
// Driver code 
int main() 
{ 
    string str = "geeks for geeks geeks quiz "
                 "practice qa for"; 
    printFrequencies(str); 
    return 0; 
} 
