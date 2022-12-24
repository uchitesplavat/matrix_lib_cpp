#ifndef S21_MATRIX_OOP_H
#define S21_MATRIX_OOP_H

#include <cmath>
#include <algorithm>
#include <utility>
#include <stdexcept>
#include <iostream>

class S21Matrix {
private:
    // attributes
    int _rows, _cols;                                       // rows and columns attributes
    double **_p;                                                // pointer to the memory where the matrix will be allocated

public:
    S21Matrix();                                       // default constructor
    S21Matrix(int rows, int cols);                      // parameterized constructor
    S21Matrix(const S21Matrix& other);                              // copy cnstructor
    S21Matrix(S21Matrix&& other);                                   // move cnstructor
    ~S21Matrix();                                               // destructor

    int get_rows() const noexcept;
    int get_cols() const noexcept;
    void set_rows(int32_t rows);
    void set_cols(int32_t cols);

    double& operator()(int rows, int cols);
    double& operator()(int rows, int cols) const;
    S21Matrix& operator=(const S21Matrix& other);
};


#endif //S21_MATRIX_OOP_H