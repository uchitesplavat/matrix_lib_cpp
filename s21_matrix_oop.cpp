#include "s21_matrix_oop.h"

//  Default constructor (4X4)
S21Matrix::S21Matrix() : _rows(4), _cols(4){
    _p = new double *[_rows];
    for(int i = 0; i < _rows; i++) {
        _p[i] = new double[_cols];
    }
}

//  This constructor generates a matrix of dimensions rows by cols, with all elements initialized to zero
//  The assignment of rows to rows_ using the initialization syntax "_rows(rows)" serves as a shortcut, eliminating the need for an additional assignment statement "_rows = rows"
S21Matrix::S21Matrix(int rows, int cols) : _rows(rows), _cols(cols){
    if (rows < 0 || cols < 0) {
        throw std::length_error("It is not possible for the size of an array to be zero");
    }
    _p = new double *[_rows];
    for(int i = 0; i < _rows; i++) {
        _p[i] = new double[_cols];
    }
}

//This constructor generates a copy of a specified matrix
//The use of the ':' syntax in this case invokes another member function
S21Matrix::S21Matrix(const S21Matrix& other)
    : S21Matrix::S21Matrix(other._rows, other._cols) {
    std::copy(&other._p, &other._p + _rows * _cols, &_p);
}

//This constructor move the matrix from the given to this one
//P.S.
//int z = std::exchange(x, y);
//After this line of code executes:
//"x" is assigned the value of "y",
//"z" is assigned the value that "x" had initially.
S21Matrix::S21Matrix(S21Matrix&& other)
    : _rows(std::exchange(other._rows, 0)), _cols(std::exchange(other._cols, 0)),
    _p(std::exchange(other._p, nullptr)){}
//    _rows = std::exchange(other._rows, 0);
//    _cols = std::exchange(other._cols, 0);
//    _p = std::exchange(other._p, nullptr);

//This destructor simply deallocates the memory of _p
S21Matrix::~S21Matrix() {
    for(int i = 0; i < _rows; i++) {
        delete[] _p[i];
    }
    delete[] _p;
}

//Tis mutator realloc _p and change value of _rows
void S21Matrix::set_rows(int rows) {
    if (rows <= 0)
        throw std::length_error("It is not possible for the size of an array to be zero");

    if (rows == _rows) return;  // no changes needed

    double** p = new double*[rows];
    int min_rows = std::min(rows, _rows);  // copy values from the smaller matrix
    for (int i = 0; i < min_rows; ++i) {
        p[i] = new double[_cols]; // allocate new row
        for (int j = 0; j < _cols; ++j)
            p[i][j] = _p[i][j]; // copy values from existing row
    }
    // initialize new rows with default values
    for (int i = min_rows; i < rows; ++i) {
        p[i] = new double[_cols]();
    }
    this->~S21Matrix();  // deallocate old matrix
    _p = p; // update matrix with new array of row pointers
    _rows = rows; // update number of rows
}

void S21Matrix::set_cols(int cols) {
    if (cols <= 0)
        throw std::length_error("It is not possible for the size of an array to be zero");

//    if (cols != _cols) {
//        for (int32_t i = 0; i < _rows; i++) {
//            double *pi_temp = new double[cols]();
//            for (int32_t j = 0; j < cols; ++j) {
//                if (j < _cols)
//                    pi_temp[j] = _p[i][j];
//            }
//            delete[] _p[i];
//            _p[i] = pi_temp;
//        }
//        _cols = cols;
//    }

    if (cols != _cols) {
        for (int i = 0; i < _rows; i++) {
            // Allocate a new array of double with 'cols' elements, initialized to 0.0
            double* pi_temp = new double[cols]();
            // Copy the elements from the old array to the new one
            std::copy(_p[i], _p[i] + _cols, pi_temp);
            // Free the memory of the old array
            delete[] _p[i];
            // Replace the old array with the new one
            _p[i] = pi_temp;
        }
        // Update the number of columns
        _cols = cols;
    }
}

int S21Matrix::get_rows() const noexcept {
return _rows;
}

int S21Matrix::get_cols() const noexcept {
return _cols;
}

