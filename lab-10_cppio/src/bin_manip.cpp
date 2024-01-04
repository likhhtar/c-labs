#include "bin_manip.h"

write_le_int32::write_le_int32(int32_t x) : _x(x) {}
read_le_int32::read_le_int32(int32_t &x) : _x(x) {}
write_bool::write_bool(bool x) : _x(x) {}
read_bool::read_bool(bool &x) : _x(x) {}
write_c_str::write_c_str(const char *x) : _x(x) {}
read_c_str::read_c_str(char *x, size_t size) : _x(x), _size(size) {}

std::ostream &operator<<(std::ostream &out, const write_le_int32 &data) {
    uint8_t buffer[4];
    buffer[0] = (data._x      ) & 255;
    buffer[1] = (data._x >> 8 ) & 255;
    buffer[2] = (data._x >> 16) & 255;
    buffer[3] = (data._x >> 24) & 255;
    return out.write(reinterpret_cast<const char *>(buffer), sizeof buffer);
}

std::istream &operator>>(std::istream &in, const read_le_int32 &data) {
    uint8_t buffer[4];
    in.read(reinterpret_cast<char *>(buffer), sizeof buffer);
    data._x = 0;
    for (int32_t i = 3; i >= 0; i--)
        data._x = data._x * 256 + buffer[i];
    return in;
}

std::ostream &operator<<(std::ostream &out, const write_bool &data) {
    return out.write(reinterpret_cast<const char *>(&data._x), sizeof data._x);
}

std::istream &operator>>(std::istream &in, const read_bool &data) {
    return in.read(reinterpret_cast<char *>(&data._x), sizeof data._x);
}

std::ostream &operator<<(std::ostream &out, const write_c_str &data) {
    return out.write(data._x, (strlen(data._x) + 1) * sizeof(char));
}

std::istream &operator>>(std::istream &in, const read_c_str &data) {
    for (int32_t i = 0; i < (int32_t) data._size; i++) {
        in.read(data._x + i, sizeof(char));
        if (data._x[i] == '\0')
            return in;
    }
    throw ("String is too long");
}