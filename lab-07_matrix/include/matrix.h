#ifndef LAB_08_MATRIX_H
#define LAB_08_MATRIX_H

#include <cstdio>
#include <cstddef>

class Matrix {
public:
    void allocSpace();
    Matrix(const size_t r, const size_t c);
    ~Matrix();
    Matrix(const Matrix& m);

    size_t get_rows() const;
    size_t get_cols() const;
    void set(const size_t i, const size_t j, const int val);
    int get(const size_t i, const size_t j) const;
    void print(FILE *f) const;

    Matrix operator+(const Matrix& m);
    Matrix operator-(const Matrix& m);
    Matrix operator*(const Matrix& m);

    Matrix& operator+=(const Matrix& m);
    Matrix& operator-=(const Matrix& m);
    Matrix& operator*=(const Matrix& m);
    void swap(Matrix& first, Matrix& second);
    Matrix& operator=(const Matrix& m);

    bool operator==(const Matrix& m) const;
    bool operator!=(const Matrix& m) const;
private:
    size_t _rows;
    size_t _cols;
    int **_data;
};

#endif
