#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

int main() {
    int n = 0;
    int q = 0;
    int elm = 0;

    // Create a vector of integer vectors
    vector<vector<int> > vov;

    ifstream myfile("cin_while_test.txt");
    if (myfile.is_open()) {
        cout << "Successfully open the file\n";
        myfile >> n >> q;

        // Create the integer vectors and push them to VoV
        for(int i = 0; i < n; ++i) {
            int k = 0;
            myfile >> k;
            vector<int> vec;

            // Populate integer vectors with the given integers before
            // pushing them to VoV
            for(int j = 0; j < k; ++j) {
                myfile >> elm;
                vec.push_back(elm); 
            }
            vov.push_back(vec);
        }

        // Perform queries
        while(q-- > 0) {
            int r = 0;    // row 
            int c = 0;    // column
            myfile >> r >> c;

            // Print the element located at the given spot to stdout
            cout << vov[r][c] << endl;
        }
        myfile.close();
    } else {
        cout << "Error opening the file\n";
    }
    return 0;
}
