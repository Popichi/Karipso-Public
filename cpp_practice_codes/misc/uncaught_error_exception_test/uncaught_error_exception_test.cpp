#include <string>
#include <stdexcept>
#include <iostream>

void error (std::string s) {
  throw std::runtime_error(s);
}

int main () {
  // try {
  //   error("Test");
  // } catch (std::runtime_error& runtime_error) {
  //   std::cerr << runtime_error.what() << std::endl;
  // }
  error("Test");  // Causes a 'core dumped error!
  return 0;
}