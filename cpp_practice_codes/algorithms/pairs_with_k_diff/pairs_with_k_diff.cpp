/*
 * Author: Anil Celik Maral
 * Last Update: 08/03/19, 7:44 PM
 * Email: anilcelikmaral@gmail.com
 * */

/* TO DO: 1) Make it possible get input from the terminal.
          2) Make it possible to accept float etc.
          3) What is the run time of the brute force method?
          4) Implement the somewhat optimized version described
             at page 67 of Cracking the Coding Interview.
          5) Add the explanations for each method from page 67!
          6) Comment the function you created to document its
             usage
          7) Upload the code to github to practice version control! */

/*  Example: Given an array of distinct integer values, count the
             number of pairs of integers that have difference k.
             For example, given the array {1, 7, 5, 9, 2, 12, 3}
             and the difference k = 2, there are four pairs with
             difference 2: (1, 3), (3, 5), (5, 7), (7, 9). */

#include <iostream>
#include <array>
#include <vector>
#include <utility>
#include <unordered_map>

namespace pairs_with_k_diff {
    void inc_and_push_back (const int& pair_st, const int& pair_nd,
        std::vector<std::pair<int, int> >& vec, int& cnt) {
        ++cnt;
        // Add the pair that satisfies the difference condition to a
        // vector to be able to print it later.
        // dis_pr = discovered pair
        std::pair<int, int> dis_pr (pair_st, pair_nd);
        vec.push_back(dis_pr);
    }
}

int main() {
    std::string method;

    // Choose between the brute force method and the optimized method!
    std::cout << "Choose between the brute force method (bf) and the " 
        "optimized method (opt): ";
    std::cin >> method;
    std::cout << std::endl;

    // Array of distinct integers
    std::vector<int> aodints {1, 7, 5, 9, 2, 12, 3};
    
    // Hash table of distinct integers
    std::unordered_map<int, bool> htodints {{1, true}, {7, true},
        {5, true}, {9, true}, {2, true}, {12, true}, {3, true}};

    int k = 2;  // The difference that we are looking for
    
    // Number of pairs with the desired difference
    int nopwdd_cnt = 0;

    // Vector of pairs to store the pairs with the desired difference
    // paroints = pair of integers
    std::vector<std::pair<int, int> > paroints;

    // Brute force method:
    if (method == "bf") {
        std::cout << "Using brute force method:" << std::endl;
        for (int i = 0; i < aodints.size(); ++i) {
            for (int j = i + 1; j < aodints.size(); ++j) {
                if (abs(aodints[i] - aodints[j]) == k) {
                    pairs_with_k_diff::inc_and_push_back(aodints[i],
                        aodints[j], paroints, nopwdd_cnt);
                }
            }
        }
    // Optimized method O(N):
    // We use an std::undordered_map which uses a hashtable for its
    // underlying implementation.
    } else if (method == "opt") {
        std::cout << "Using optimized method:" << std::endl;
        for (std::unordered_map<int, bool>::iterator it =
            htodints.begin(); it != htodints.end(); ++it) {
            if (htodints.find(it->first + k) != htodints.end()) {
                if ((htodints.find(it->first + k))->second != false) {
                    pairs_with_k_diff::inc_and_push_back(it->first,
                        it->first + k, paroints, nopwdd_cnt);
                }
            }
            
            if (htodints.find(it->first - k) != htodints.end()) {
                if ((htodints.find(it->first - k))->second != false) {
                    pairs_with_k_diff::inc_and_push_back(it->first,
                        it->first - k, paroints, nopwdd_cnt);
                }
            }
            it->second = false; // Labeling the number as already checked!
        }
    }

    // Print the pairs that satisfy the difference condition:
    std::cout << "The pairs of integers that have difference k: ";
    for (int i = 0; i < nopwdd_cnt; ++i) {
        std::cout << '(' << paroints[i].first << ", " <<
            paroints[i].second <<
            ((i == (nopwdd_cnt - 1)) ? ")." : "), ");
    }

    std::cout << std::endl;

    std::cout << "Number of pairs with the desired difference is: " <<
        nopwdd_cnt << std::endl;

    return 0;
}