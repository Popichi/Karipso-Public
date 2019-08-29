/* Test what happens when you give ios::ate as a second input to
   open(). As far as I know, it should overwrite ios::in |
   ios::out and I should get an open failed signal as explained
   in the following link: 
   https://stackoverflow.com/questions/54271539/
   open-mode-behaviors-for-fstream-ifstream-and-ofstream
*/

#include <iostream>
#include <fstream>
using namespace std;

int main() {
    fstream myfile;
    myfile.open("fstream_test.txt", ios::ate);
    if (myfile.is_open()) {
        myfile << "File successfully open";
        myfile.close();
    } else {
        cout << "Error opening file";
    }
    myfile << "Writing this to a file opened by fstream!\n";
    myfile.close();
    return 0;
}

