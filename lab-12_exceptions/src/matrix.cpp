#include "matrix.hpp"
#include <algorithm>
#include <fstream>

MatrixException::MatrixException(const std::string &message) : std::invalid_argument(message) {}

void Matrix::allocSpace()
{
    try {
        _data = new int*[_rows];
        for (std::size_t i = 0; i < _rows; i++)
            _data[i] = new int[_cols];
    }
    catch (std::bad_alloc &e) {
        delete _data;
        throw MatrixException("Unable to allocate memory.");
    }
}
Matrix::Matrix() : Matrix::Matrix(0, 0) {}
Matrix::Matrix(const size_t r, const size_t c){
    _rows = r;
    _cols = c;
    allocSpace();
    for (size_t i = 0; i < _rows; i++){
        for (size_t j = 0; j < _cols; j++){
            _data[i][j] = 0;
        }
    }
}
Matrix::Matrix(const Matrix& m){
    _rows = m._rows;
    _cols = m._cols;
    allocSpace();
    for (size_t i = 0; i < _rows; i++) {
        for (size_t j = 0; j < _cols; j++) {
            _data[i][j] = m._data[i][j];
        }
    }
}
Matrix::~Matrix(){
    for (size_t i = 0; i < _rows; i++) {
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
    if (i >= _rows || j >= _cols) {
        throw MatrixException("ACCESS: bad index.");
    }
    return _data[i][j];
}


void Matrix::print(FILE *f) const{
    for (size_t i = 0; i < _rows; i++){
        for (size_t j = 0; j < _cols; j++) {
            if(j != 0){
                fprintf(f, " ");
            }
            fprintf(f, "%d", _data[i][j]);
        }
        fprintf(f, "\n");
    }
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
    if (m._rows != _rows || m._cols != _cols) {
        throw MatrixException("ADD: dimensions do not match.");
    }
    for (size_t i = 0; i < _rows; i++) {
        for (size_t j = 0; j < _cols; j++) {
            _data[i][j] += m._data[i][j];
        }
    }
    return *this;
}

Matrix& Matrix::operator*=(const Matrix& m){
    if (_rows != m._cols) {
        throw MatrixException("MUL: #arg1.columns != #arg2.rows.");
    }
    Matrix result(_rows, m._cols);
    for (size_t i = 0; i < result._rows; i++) {
        for (size_t j = 0; j < result._cols; j++) {
            for (size_t k = 0; k < _cols; k++) {
                result._data[i][j] += (_data[i][k] * m._data[k][j]);
            }
        }
    }
    return (*this = result);
}

Matrix* Matrix::load(const std::string &filename) {
    std::ifstream in(filename);
    if (!in) {
        throw MatrixException("LOAD: unable to open file.");
    }
    std::size_t row, column;
    in >> row >> column;
    if (!in) {
        throw MatrixException("LOAD: invalid file format.");
    }
    Matrix *m = new Matrix(row, column);

    try {
        for (std::size_t i = 0; i < m->_rows; i++) {
            for (std::size_t j = 0; j < m->_cols; j++) {
                in >> m->_data[i][j];
            }
        }
        if (!in) {
            throw MatrixException("LOAD: invalid file format.");
        }
    } catch (MatrixException &e) {
        delete m;
        throw e;
    }
    return m;
}
