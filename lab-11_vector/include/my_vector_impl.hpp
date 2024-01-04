#ifndef MY_VECTOR_IMPL_HPP_
#define MY_VECTOR_IMPL_HPP_

#include <cstddef>
#include "my_vector.hpp"

namespace containers{
    template<typename T>
    my_vector<T>::my_vector() {
        size_ = 0;
        capacity_ = 1;
        array_ = reinterpret_cast<T *>(new char[sizeof(T) * capacity_]);
    }

    static std::size_t new_capacity(std::size_t n){
        std::size_t cap = 1;
        while (cap < n) cap *= 2;
        return cap;
    }

    template<typename T>
    my_vector<T>::my_vector(std::size_t n) {
        size_ = 0;
        capacity_ = 1;
        array_ = nullptr;
        reserve(n);
        size_ = n;
        for (std::size_t i = 0; i < size_; i++) {
            new(&array_[i]) T();
        }
    }

    template<typename T>
    my_vector<T>::my_vector(my_vector const &other) {
        capacity_ = other.capacity_;
        size_ = other.size_;
        array_ = reinterpret_cast<T *>(new char[sizeof(T) * capacity_]);
        for (std::size_t i = 0; i < size_; i++) {
            new(&array_[i]) T(other[i]);
        }
    }

    template<typename T>
    my_vector<T> & my_vector<T>::operator=(const my_vector &other) {
        if (this == &other)
            return *this;
        my_vector<T> tmp = other;
        swap(tmp);
        return *this;
    }

    template<typename T>
    my_vector<T>::~my_vector() {
        for (size_t i = 0; i < size_; i++) {
            array_[i].~T();
        }
        delete[] reinterpret_cast<char * >(array_);
    }

    template<typename T>
    std::size_t my_vector<T>::size() const {
        return size_;
    }

    template<typename T>
    std::size_t my_vector<T>::capacity() const {
        return capacity_;
    }

    template<typename T>
    bool my_vector<T>::empty() const {
        return size_ == 0;
    }

    template<typename T>
    void my_vector<T>::resize(std::size_t n) {
        reserve(n);
        for (std::size_t i = n; i < size_; i++) {
            array_[i].~T();
        }
        for (std::size_t i = size_; i < n; i++) {
            new(&array_[i]) T();
        }
        size_ = n;
    }

    template<typename T>
    void my_vector<T>::swap(my_vector <T> &other) {
        using std::swap;
        swap(capacity_, other.capacity_);
        swap(size_, other.size_);
        swap(array_, other.array_);
    }

    template<typename T>
    void my_vector<T>::reserve(std::size_t n) {
        std::size_t new_cap = new_capacity(n);
        if (new_cap <= capacity_) {
            return;
        }
        capacity_ = new_cap;
        T *array = reinterpret_cast<T *>(new char[sizeof(T) * capacity_]);
        for (size_t i = 0; i < size_; i++) {
            new(&array[i]) T(array_[i]);
            array_[i].~T();
        }
        delete[] reinterpret_cast<char *>(array_);
        array_ = reinterpret_cast<T *>(array);
    }

    template<typename T>
    T &my_vector<T>::operator[](std::size_t index) {
        return array_[index];
    }

    template<typename T>
    const T &my_vector<T>::operator[](std::size_t index) const {
        return array_[index];
    }

    template<typename T>
    void my_vector<T>::push_back(const T &t) {
        reserve(size_ + 1);
        new(&array_[size_++]) T(t);
    }

    template<typename T>
    void my_vector<T>:: pop_back() {
        array_[--size_].~T();
    }

    template<typename T>
    void my_vector<T>::clear() {
        for (std::size_t i = 0; i < size_; i++) {
            array_[i].~T();
        }
        size_ = 0;
    }

    template<typename T>
    std::ostream & operator<<(std::ostream &out, const my_vector<T> &arr) {
        for (std::size_t i = 0; i < arr.size_; i++) {
            if(i != 0) out << ' ';
            out << arr.array_[i];
        }
        return out;
    }
}

#endif  // MY_VECTOR_IMPL_HPP_
