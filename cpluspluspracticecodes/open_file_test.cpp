/*This is a small program to test whether opening a file that doesn't
  exist and trying to write to it will be successful or not.

  Result: It is successful in creation of the file and writing to it*/

#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ofstream outfile;
    outfile.open("out_example.txt");
    outfile << "Writing this to a file.\n";
    outfile.close();
    return 0;
}

