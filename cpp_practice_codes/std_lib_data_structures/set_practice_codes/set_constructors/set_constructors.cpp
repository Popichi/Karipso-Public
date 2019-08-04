// A program showcasing constructing sets
#include <iostream>
#include <set>

bool fncomp (int lhs, int rhs) { return lhs < rhs; }

struct classcomp {
    bool operator() (const int& lhs, const int& rhs) const {
        return lhs < rhs;
    }
};

int main () {
    // Empty set of ints
    std::set<int> first;

    // Using the range constructor
    int my_ints[]= {10, 20, 30, 40, 50};
    std::set<int> second (my_ints, my_ints + 5);

    // Using the copy constructor (a copy of second)
    std::set<int> third (second);

    // Using the iterator constructor
    std::set<int> fourth (second.begin(), second.end());

    std::set<int, classcomp> fifth;  // Class as Compare

    bool(*fn_pt)(int, int) = fncomp;
    std::set<int, bool(*)(int, int)> sixth (fn_pt);  // function pointer as Compare

  return 0;
}