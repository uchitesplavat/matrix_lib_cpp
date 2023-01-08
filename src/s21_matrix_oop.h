#ifndef MATRIX_LIB_CPP_S21_MATRIX_OOP_H_
#define MATRIX_LIB_CPP_S21_MATRIX_OOP_H_

#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <utility>

class S21Matrix {
 public:
  // default constructor
  S21Matrix();
  // parameterized constructor
  S21Matrix(int rows, int cols);
  // copy cnstructor
  S21Matrix(const S21Matrix& other);
  // move cnstructor
  S21Matrix(S21Matrix&& other);

  // overload () operator for matrix access
  double& operator()(int rows, int cols);
  // overload () operator for matrix access (const version)
  double& operator()(int rows, int cols) const;
  // overload == operator for matrix comparison
  bool operator==(const S21Matrix& other);
  // overload += operator for matrix addition
  S21Matrix& operator+=(const S21Matrix& other);
  // overload + operator for matrix addition
  S21Matrix operator+(const S21Matrix& other);
  // overload -= operator for matrix subtraction
  S21Matrix& operator-=(const S21Matrix& other);
  // overload - operator for matrix subtraction
  S21Matrix operator-(const S21Matrix& other);
  // overload *= operator for matrix multiplication
  S21Matrix& operator*=(const S21Matrix& other);
  // overload * operator for matrix multiplication
  S21Matrix operator*(const S21Matrix& other);
  // overload *= operator for scalar multiplication
  S21Matrix& operator*=(const double num);
  // overload * operator for scalar multiplication
  S21Matrix operator*(const double num);
  // overload = operator for matrix assignment
  S21Matrix& operator=(const S21Matrix& other);
  // overload * operator for scalar-matrix multiplication
  friend S21Matrix operator*(const double num, const S21Matrix& matrix);

  // destructor
  ~S21Matrix();

  // get number of rows
  int get_rows() const noexcept;
  // get number of columns
  int get_cols() const noexcept;
  // set number of rows
  void set_rows(int rows);
  // set number of columns
  void set_cols(int cols);

  // compare two matrices for equality
  bool EqMatrix(const S21Matrix& other);
  // add two matrices
  void SumMatrix(const S21Matrix& other);
  // subtract two matrices
  void SubMatrix(const S21Matrix& other);
  // multiply matrix by a scalar
  void MulNumber(const double num);
  // multiply two matrices
  void MulMatrix(const S21Matrix& other);
  // transpose matrix
  S21Matrix Transpose();
  // calculate matrix complements
  S21Matrix CalcComplements();
  // calculate matrix determinant
  double Determinant();
  // calculate matrix inverse
  S21Matrix InverseMatrix();

 private:
  // attributes
  int rows_, cols_;  // rows and columns attributes
  double** matrix_;  // pointer to the memory where the matrix will be allocated

  // helpers
  void Complements(S21Matrix& result);
  void ResMatrix(S21Matrix& result);
  double GetMinor(int i, int j);
  double DetTwo(S21Matrix& res);
};

#endif  // MATRIX_LIB_CPP_S21_MATRIX_OOP_H_