#ifndef LAB_10_CPPIO_BIN_MANIP_H
#define LAB_10_CPPIO_BIN_MANIP_H

#include <cstring>
#include <iostream>
#include <cassert>

class write_le_int32 {
public:
    explicit write_le_int32(int32_t x);
    friend std::ostream &operator<<(std::ostream &out, const write_le_int32 &data);
private:
    int32_t _x;
};

class read_le_int32 {
public:
    explicit read_le_int32(int32_t &x);
    friend std::istream &operator>>(std::istream &in, const read_le_int32 &data);
private:
    int32_t &_x;
};

class write_bool {
public:
    explicit write_bool(bool x);
    friend std::ostream &operator<<(std::ostream &out, const write_bool &data);
private:
    bool _x;
};

class read_bool {
public:
    explicit read_bool(bool &x);
    friend std::istream &operator>>(std::istream &in, const read_bool &data);
private:
    bool &_x;
};

class write_c_str {
public:
    explicit write_c_str(const char *x);
    friend std::ostream &operator<<(std::ostream &out, const write_c_str &data);
private:
    const char *_x;
};

class read_c_str {
public:
    explicit read_c_str(char *x, size_t size);
    friend std::istream &operator>>(std::istream &in, const read_c_str &data);
private:
    char *_x;
    size_t _size;
};

#endif //LAB_10_CPPIO_BIN_MANIP_H
