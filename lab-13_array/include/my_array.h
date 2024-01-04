#ifndef MY_ARRAY_H_
#define MY_ARRAY_H_

#include <cstddef>
#include <stdexcept>

namespace lab_13 {

template<typename T, std::size_t N>
class my_array {
public:
    T& at(std::size_t index) {
        if (index >= N) {
            throw std::out_of_range("Index is out of a range");
        }
        return _data[index];
    }
    const T& at(std::size_t index) const {
        if (index >= N) {
            throw std::out_of_range("Index is out of a range");
        }
        return _data[index];
    }

    T& operator[](std::size_t index) {
        return _data[index];
    }
    const T& operator[](std::size_t index) const {
        return _data[index];
    }

    bool empty() const {
        return N == 0;
    }
    std::size_t size() const {
        return N;
    }

    void fill(const T& val) {
        for (T* idx = _data; idx < _data + N; idx++) {
            *idx = val;
        }
    }

private:
    T _data[N] = {};
};

template<std::size_t N>
class my_array<bool, N> {
private:
    class proxy {
    public:
        proxy(char& data, std::size_t index) : _data(data), _index(index) {}

        operator bool() const {
            return _data >> _index & 1;
        }

        proxy& operator=(bool value) {
            char mask = value << _index;
            _data = ((_data & (uint8_t(-1) ^ (1 << _index))) | mask);
            return *this;
        }

        proxy& operator=(const proxy &other) {
            return operator=(bool(other));
        }
    private:
        char& _data;
        std::size_t _index;
    };
public:
    proxy at(std::size_t index) {
        if (index >= N) {
            throw std::out_of_range("Index is out of a range");
        }
        return proxy(_data[index / _cellSize], index % _cellSize);
    }

    bool at(std::size_t index) const {
        if (index >= N) {
            throw std::out_of_range("Index is out of a range");
        }
        return get(index);
    }

    proxy operator[](std::size_t index) {
        return proxy(_data[index / _cellSize], index % _cellSize);
    }

    bool operator[](std::size_t index) const {
        return get(index);
    }

    bool empty() const {
        return N == 0;
    }
    std::size_t size() const {
        return N;
    }

    void fill(bool val) {
        for (std::size_t i = 0; i < N; i++) {
            at(i) = val;
        }
    }
private:
    static const std::size_t _cellSize = 8;
    char _data[(N + _cellSize - 1) / _cellSize] = {};

    [[nodiscard]] bool get(std::size_t index) const {
        return _data[index / _cellSize] & (1 << (index % _cellSize));
    }
};

}  // namespace lab_13

#endif  // MY_ARRAY_H_
