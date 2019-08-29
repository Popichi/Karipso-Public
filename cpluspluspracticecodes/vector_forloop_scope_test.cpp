/* This program tests whether vectors created inside a for-loop, therefore in its scope, can be accessed outside.
   I asked a question on why this is possible and the link to the question can be found at
   https://stackoverflow.com/questions/57023828/why-is-it-possible-to-access-vectors-created-inside-a-for-loop-that-are-saved-to*/

#include <iostream>
#include <vector>

using namespace std;

void display (const vector<vector<int> >& tdv) {
    for (int i = 0; i < tdv.size(); i++) {        // Loops through each row of tdv (two dimensional vector)
        for (int j = 0; j <tdv[i].size(); j++) {  // Loops through each element of each row
            cout << " " << tdv[i][j];
        }
        cout << endl;
    }
}

int main () {
    vector<vector<int> > vov;
    for (int i = 1; i < 5; ++i) {
        vector<int> vec(i, i);
        vov.push_back(vec);
    }
    display (vov);
    return 0;
}

