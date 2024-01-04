#include <cstring>
#include <cstdio>
#include "Circle.hpp"

Circle::Circle(int id, int x, int y, int radius, const char *label) : Figure(id, x, y) {
    _radius = radius;
    if (label != nullptr){
        _label = new char [strlen(label) + 1];
        strcpy(_label, label);
    }
}
Circle::~Circle(){
    delete[] _label;
}

void Circle::print() const {
    printf("Circle %d: x = %d y = %d radius = %d label = %s\n", id, x, y, _radius, _label);
}
bool Circle::is_inside(int x, int y) const {
    return ((this->x - x) * (this->x - x) + (this->y - y) * (this->y - y) <= _radius * _radius);
}
void Circle::zoom(int factor) {
    _radius *= factor;
}