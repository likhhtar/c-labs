#include "matrix.hpp"
#include <algorithm>

void Matrix::allocSpace()
{
    _data = new int*[_rows];
    for (int i = 0; i < _rows; i++) {
        _data[i] = new int[_cols];
    }
}
Matrix::Matrix(std::size_t r, std::size_t c){
    _rows = r;
    _cols = c;
    allocSpace();
    for (int i = 0; i < _rows; i++){
        for (int j = 0; j < _cols; j++){
            _data[i][j] = 0;
        }
    }
}
Matrix::Matrix(const Matrix& m){
    _rows = m._rows;
    _cols = m._cols;
    allocSpace();
    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _cols; j++) {
            _data[i][j] = m._data[i][j];
        }
    }
}
Matrix::~Matrix(){
    for (int i = 0; i < _rows; i++) {
        delete[] _data[i];
    }
    delete[] _data;
}


size_t Matrix::get_rows() const{
    return _rows;
}
size_t Matrix::get_cols() const{
    return _cols;
}


void Matrix::set(const size_t i, const size_t j, const int val){
    _data[i][j] = val;
}
int Matrix::get(const size_t i, const size_t j) const{
    return _data[i][j];
}

void Matrix::swap(Matrix& first, Matrix& second)
{
    using std::swap;

    swap(first._cols, second._cols);
    swap(first._rows, second._rows);
    swap(first._data, second._data);
}

Matrix& Matrix::operator=(const Matrix& m)
{
    Matrix temp(m);
    swap(*this, temp);

    return *this;
}

bool Matrix::operator==(const Matrix& m) const{
    if (_rows != m._rows || _cols != m._cols){
        return false;
    }
    for (int i = 0; i < _rows; i++){
        for (int j = 0; j < _cols; j++){
            if (_data[i][j] != m._data[i][j]){
                return false;
            }
        }
    }

    return true;
}
bool Matrix::operator!=(const Matrix& m) const{
    return !(*this == m);
}