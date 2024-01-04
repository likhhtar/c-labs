#include "my_vector.hpp"
#include "math.h"
#include <cassert>

MyVector::MyVector(std::size_t init_capacity){
    _size = 0;
    _capacity = init_capacity;
    _data = new int[_capacity];
}

MyVector::MyVector() : MyVector(2){
    ;
}

MyVector::~MyVector(){
    delete [] _data;
}

MyVector::MyVector(const MyVector& other){
    _size = other._size;
    _capacity = other._capacity;
    _data = new int[_capacity];
    for(int i = 0; i < _size; i++)
      _data[i] = other._data[i];
}

MyVector& MyVector::operator=(const MyVector& other)
{
    if (_capacity < other._size)
    {
        delete[] _data;

        _capacity = other._capacity;
        _data = new int[_capacity];
    }

    _size = other._size;
    for (int i = 0; i < _size; ++i)
        _data[i] = other._data[i];

    return *this;
}

void MyVector::set(std::size_t index, int value){
    assert(index < _size);
    _data[index] = value;
}
int MyVector::get(std::size_t index){
    assert(index < _size);
    return _data[index];
}

std::size_t MyVector::size(){
    return _size;
}
std::size_t MyVector::capacity(){
    return _capacity;
}


void MyVector::reserve(std::size_t new_capacity){
    if(new_capacity > _capacity){
        _capacity = new_capacity;
        int* temp = new int [_capacity];
        for(std::size_t i = 0; i < _size; i++)
            temp[i] = _data[i];
        delete [] _data;
        _data = temp;
    }
}

void MyVector::resize(std::size_t new_size){
    if (new_size > _size){
        reserve(std::max(new_size, 2 * _capacity));
        for(std::size_t i = _size; i < new_size; i++){
            _data[i] = 0;
        }
    }
    _size = new_size;
}


void MyVector::push_back(int value){
    if (_size == _capacity)
        reserve(_capacity * 2);
    _data[_size++] = value;
}
void MyVector::insert(std::size_t index, int value){
    assert(index <= _size);
    if (_size == _capacity)
        reserve(_capacity * 2);

    for (std::size_t i = _size; i > index; i--)
        _data[i] = _data[i - 1];

    _size++;
    _data[index] = value;
}

void MyVector::erase(std::size_t index){
    assert(index < _size);
    for(std::size_t i = index; i < _size - 1; i++)
        _data[i] = _data[i + 1];
    --_size;
}
