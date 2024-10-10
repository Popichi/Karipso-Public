#include "simpleIterator.hpp"

// Constructor for SimpleContainer
SimpleContainer::SimpleContainer(int* data, std::size_t size)
    : data_(data), size_(size) {}

// Constructor for SimpleIterator
SimpleContainer::SimpleIterator::SimpleIterator(int* ptr)
    : ptr_(ptr) {}

// Dereference operator for SimpleIterator
int& SimpleContainer::SimpleIterator::operator*() const {
    return *ptr_;
}

// Increment operator for SimpleIterator
SimpleContainer::SimpleIterator& SimpleContainer::SimpleIterator::operator++() {
    ++ptr_;
    return *this;
}

// Comparison operators for SimpleIterator
bool SimpleContainer::SimpleIterator::operator==(const SimpleIterator& other) const {
    return ptr_ == other.ptr_;
}

bool SimpleContainer::SimpleIterator::operator!=(const SimpleIterator& other) const {
    return ptr_ != other.ptr_;
}

// Begin and end methods for SimpleContainer
SimpleContainer::SimpleIterator SimpleContainer::begin() const {
    return SimpleIterator(data_);
}

SimpleContainer::SimpleIterator SimpleContainer::end() const {
    return SimpleIterator(data_ + size_);
}
