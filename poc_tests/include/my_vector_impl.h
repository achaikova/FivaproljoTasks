#ifndef LAB_12_MY_VECTOR_IMPL_H
#define LAB_12_MY_VECTOR_IMPL_H

#include "my_vector.h"
#include <algorithm>
#include <memory>

template<typename T>
my_vector::my_vector<T>::my_vector()
        :capacity_(DEFAULT_VECTOR_SIZE), size_(DEFAULT_VECTOR_SIZE),
         array_(reinterpret_cast<T *>(new char[DEFAULT_VECTOR_SIZE])) {}

template<typename T>
my_vector::my_vector<T>::my_vector(std::size_t n)
        : capacity_(n), size_(n), array_(reinterpret_cast<T *>(new char[n * sizeof(T)])) {}

template<typename T>
// TODO properly (?)
my_vector::my_vector<T>::my_vector(my_vector<T> const &other)
        : capacity_(other.size_), size_(DEFAULT_VECTOR_SIZE),
          array_(reinterpret_cast<T *>(new char[capacity_ * sizeof(T)])) {
    try {
        for (std::size_t i = 0; i < other.size_; i++) {
            push_back(other.array_[i]);
        }
    } catch (...) {
        throw;
    }
}

template<typename T>
my_vector::my_vector<T>::my_vector(my_vector &&v) noexcept
        : capacity_(0), size_(0), array_(nullptr) {
    v.swap(*this);
}

template<typename T>
my_vector::my_vector<T> &my_vector::my_vector<T>::operator=(my_vector<T> const &other) {
    my_vector tmp(other);
    tmp.swap(*this);
    return *this;
}

template<typename T>
my_vector::my_vector<T> &my_vector::my_vector<T>::operator=(my_vector &&v) noexcept {
    v.swap(*this);
    return *this;
}

template<typename T>
my_vector::my_vector<T>::~my_vector() {
    delete[] array_;
}

template<typename T>
std::size_t my_vector::my_vector<T>::size() const noexcept {
    return size_;
}

template<typename T>
std::size_t my_vector::my_vector<T>::capacity() const noexcept {
    return capacity_;
}

template<typename T>
bool my_vector::my_vector<T>::empty() const noexcept {
    return size_ == 0;
}


template<typename T>
void my_vector::my_vector<T>::reserve(std::size_t n) { //TODO properly
    if (capacity_ >= n) {
        return;
    }
    try {
        capacity_ = n;
        T *dst = reinterpret_cast<T *>(new char[sizeof(T) * capacity_]);
        for (std::size_t i = 0; i < size_; ++i) {
            new(&dst[i])T(std::move(array_[i]));
            array_[i].~T();
        }
        delete[] reinterpret_cast<char *>(array_);
        array_ = dst;
    } catch (...) {
        throw;
    }
}

template<typename T>
void my_vector::my_vector<T>::push_back(T &&t) {
    if (size_ == capacity_)
        reserve(pow(2, ceil(log2(size_ + 1))));
    new(&array_[size_++]) T(std::move(t));
}

template<typename T>
void my_vector::my_vector<T>::push_back(T const &t) {
    if (size_ == capacity_)
        reserve(pow(2, ceil(log2(size_ + 1))));
    new(&array_[size_++]) T(t);
}

template<typename T>
const T &my_vector::my_vector<T>::operator[](std::size_t index) const {
    return array_[index];
}

template<typename T>
T &my_vector::my_vector<T>::operator[](std::size_t index) {
    return array_[index];
}

template<typename T>
void my_vector::my_vector<T>::clear() {
    for (std::size_t i = 0; i < size_; i++) {
        array_[i].~T();
    }
    size_ = 0;
}

template<typename T>
void my_vector::my_vector<T>::pop_back() {
    assert(!empty());
    array_[--size_].~T();
}

template<typename T>
void my_vector::my_vector<T>::swap(my_vector<T> &other) noexcept {
    std::swap(capacity_, other.capacity_);
    std::swap(size_, other.size_);
    std::swap(array_, other.array_);
}

// does not initialize int with 0
template<typename T>
void my_vector::my_vector<T>::resize(std::size_t n) { //TODO properly
    try {
        T *dst = new T[sizeof(T) * n];
        for (std::size_t i = 0; i < min(n, size_); i++) {
            new(&dst[i])T(std::move(array_[i]));
            array_->~T();
        }
        delete[] reinterpret_cast<char *>(array_);
        array_ = dst;
        size_ = n;
        capacity_ = n;
    } catch (...) {
        throw;
    }
}

template<typename T>
std::size_t my_vector::my_vector<T>::min(std::size_t a, std::size_t b) {
    if (a < b)return a;
    return b;
}

#endif //LAB_12_MY_VECTOR_IMPL_H
