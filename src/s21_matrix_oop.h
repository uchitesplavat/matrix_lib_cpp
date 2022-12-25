#ifndef S21_MATRIX_OOP_H
#define S21_MATRIX_OOP_H

#include <cmath>
#include <algorithm>
#include <utility>
#include <stdexcept>
#include <iostream>
#include <cstring>

class S21Matrix {
private:
    // attributes
    int rows_, cols_;                                       // rows and columns attributes
    double **matrix_;                                                // pointer to the memory where the matrix will be allocated

public:
    S21Matrix();                                       // default constructor
    S21Matrix(int rows, int cols);                      // parameterized constructor
    S21Matrix(const S21Matrix& other);                              // copy cnstructor
    S21Matrix(S21Matrix&& other);                                   // move cnstructor
    ~S21Matrix();                                               // destructor

    int get_rows() const noexcept;
    int get_cols() const noexcept;
    void set_rows(int rows);
    void set_cols(int cols);


    bool EqMatrix(const S21Matrix& other);
    void SumMatrix(const S21Matrix& other);
    void SubMatrix(const S21Matrix& other);
    void MulNumber(const double num);
    void MulMatrix(const S21Matrix& other);
    S21Matrix Transpose();
    S21Matrix CalcComplements();
    double Determinant();
    S21Matrix InverseMatrix();
    void calc_complements(S21Matrix &result);
    void get_res_matrix(S21Matrix &result);
    double get_minor(int i, int j);
    double det_two(S21Matrix &res);

    double& operator()(int rows, int cols);
    double& operator()(int rows, int cols) const;
    bool operator==(const S21Matrix& other);
    S21Matrix& operator+=(const S21Matrix& other);
    S21Matrix operator+(const S21Matrix& other);
    S21Matrix& operator-=(const S21Matrix& other);
    S21Matrix operator-(const S21Matrix& other);
    S21Matrix& operator*=(const S21Matrix& other);
    S21Matrix operator*(const S21Matrix& other);
    S21Matrix& operator*=(const double num);
    S21Matrix operator*(const double num);
    S21Matrix& operator=(const S21Matrix& other);
};


#endif //S21_MATRIX_OOP_H