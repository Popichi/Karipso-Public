#ifndef SIMPLEITERATOR_HPP
#define SIMPLEITERATOR_HPP

#include <cstddef> // For size_t

class SimpleContainer {
public:
    using ValueType = int;

    // Constructor
    SimpleContainer(int* data, std::size_t size);

    // Define the iterator class within SimpleContainer
    class SimpleIterator {
    public:
        // Constructor for the iterator
        SimpleIterator(int* ptr);

        // Dereference operator
        int& operator*() const;

        // Increment operator (prefix)
        SimpleIterator& operator++();

        // Comparison operators
        bool operator==(const SimpleIterator& other) const;
        bool operator!=(const SimpleIterator& other) const;

    private:
        int* ptr_; // Internal pointer to the current position
    };

    // Begin and end methods to get iterators
    SimpleIterator begin() const;
    SimpleIterator end() const;

private:
    int* data_;       // Pointer to the container's data
    std::size_t size_; // Number of elements in the container
};

#endif // SIMPLEITERATOR_HPP
