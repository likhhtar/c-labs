#include <cstdio>
#include "Rectangle.hpp"

Rectangle::Rectangle(int id, int x, int y, int width, int height) : Figure(id, x, y) {
    _height = height;
    _width = width;
}
Rectangle::~Rectangle() = default;

void Rectangle::print() const {
    printf("Rectangle %d: x = %d y = %d width = %d height = %d\n", id, x, y, _width, _height);
}
bool Rectangle::is_inside(int x, int y) const {
    return (2 * x >= 2 * this->x - _width && 2 * x <= 2 * this->x + _width &&
            2 * y >= 2 * this->y - _height && 2 * y <= 2 * this->y + _height);
}
void Rectangle::zoom(int factor) {
    _height *= factor;
    _width *= factor;
}
