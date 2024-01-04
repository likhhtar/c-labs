#include "matrix.h"
#include <algorithm>

void Matrix::allocSpace()
{
    _data = new int*[_rows];
    for (int i = 0; i < _rows; i++) {
        _data[i] = new int[_cols];
    }
}
Matrix::Matrix(const size_t r, const size_t c){
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


void Matrix::print(FILE *f) const{
    for (int i = 0; i < _rows; i++){
        for (int j = 0; j < _cols; j++) {
            if(j != 0){
                fprintf(f, " ");
            }
            fprintf(f, "%d", _data[i][j]);
        }
        fprintf(f, "\n");
    }
}


Matrix Matrix::operator+(const Matrix& m){
    Matrix result(*this);
    return (result += m);
}
Matrix Matrix::operator-(const Matrix& m){
    Matrix result(*this);
    return (result -= m);
}
Matrix Matrix::operator*(const Matrix& m){
    Matrix result(*this);
    return (result *= m);
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


Matrix& Matrix::operator+=(const Matrix& m){
    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _cols; j++) {
            _data[i][j] += m._data[i][j];
        }
    }
    return *this;
}
Matrix& Matrix::operator-=(const Matrix& m){
    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _cols; j++) {
            _data[i][j] -= m._data[i][j];
        }
    }
    return *this;
}
Matrix& Matrix::operator*=(const Matrix& m){
    Matrix result(_rows, m._cols);
    for (int i = 0; i < result._rows; i++) {
        for (int j = 0; j < result._cols; j++) {
            for (int k = 0; k < _cols; k++) {
                result._data[i][j] += (_data[i][k] * m._data[k][j]);
            }
        }
    }
    return (*this = result);
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