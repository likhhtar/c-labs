#ifndef MATRIX_HPP_
#define MATRIX_HPP_

#include <cstdio>
#include <cstddef>
#include <stdexcept>
#include <string>
#include <iostream>


class MatrixException : public std::invalid_argument {
public:
    MatrixException(const std::string &message);
};

class Matrix {
public:
    void allocSpace();
    Matrix(const size_t r, const size_t c);
    Matrix();
    ~Matrix();
    Matrix(const Matrix& m);

    size_t get_rows() const;
    size_t get_cols() const;
    void set(const size_t i, const size_t j, const int val);
    int get(const size_t i, const size_t j) const;
    void print(FILE *f) const;

    Matrix& operator+=(const Matrix& m);
    Matrix& operator*=(const Matrix& m);
    void swap(Matrix& first, Matrix& second);
    Matrix& operator=(const Matrix& m);

    static Matrix* load(const std::string &filename);
private:
    size_t _rows;
    size_t _cols;
    int **_data;
};

#endif
