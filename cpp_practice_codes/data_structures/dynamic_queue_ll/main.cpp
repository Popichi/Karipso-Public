// This is the test harness for the dynamic queue data structure that I
// built

#include "anil_dynamic_queue_ll.h"
#include <iostream>

int main() {
    anil::queue my_queue;

    std::cout << "Starting enqueue operation:" << std::endl;
    for (int i = 10; i < 20; ++i) {
        my_queue.enqueue(i);
        std::cout << i << ' ';
    }
    std::cout << std::endl;

    std::cout << "Starting dequeue operation:" << std::endl;
    for (int i = 1; i < 11; ++i) {
        std::cout << my_queue.dequeue() << ' ';
    }
    std::cout << std::endl;

    std::cout << "Program works!" << std::endl;
}