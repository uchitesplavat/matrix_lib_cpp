#include "s21_matrix_oop.h"

//int main() {
//    S21Matrix m;
//    S21Matrix m1;
//    m.set_cols(6);
//    m1.set_cols(6);
//    m.set_rows(6);
//    m1.set_rows(6);
//    m(0,1) = 10;
//    m1(0,1) = 12;
//
//    for (int i = 0; i < m.get_rows(); ++i)
//        for (int j = 0; j < m.get_cols(); ++j) {
//            std::cout << m(i, j) << " ";
//            if (j == m.get_cols() - 1){
//                std::cout << "\n";
//            }
//        }
//    for (int i = 0; i < m1.get_rows(); ++i)
//        for (int j = 0; j < m1.get_cols(); ++j) {
//            std::cout << m1(i, j) << " ";
//            if (j == m1.get_cols() - 1){
//                std::cout << "\n";
//            }
//        }
//    m.SumMatrix(m1);
//    for (int i = 0; i < m.get_rows(); ++i)
//        for (int j = 0; j < m.get_cols(); ++j) {
//            std::cout << m(i, j) << " ";
//            if (j == m.get_cols() - 1){
//                std::cout << "\n";
//            }
//        }
////    bool test = m.EqMatrix(m1);
////    std::cout << test << " ";
//    return 0;
//
//}
//  Default constructor (4X4)
S21Matrix::S21Matrix() : _rows(4), _cols(4){
    _p = new double *[_rows];
    for(int i = 0; i < _rows; i++) {
        _p[i] = new double[_cols]();
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
        _p[i] = new double[_cols]();
    }
}

//This constructor generates a copy of a specified matrix
//The use of the ':' syntax in this case invokes another member function
S21Matrix::S21Matrix(const S21Matrix& other)
        : S21Matrix::S21Matrix(other._rows, other._cols) {

//        std::copy(&other._p, &other._p + i * j, &_p);

    for (int i = 0; i < _rows; ++i)
        for (int j = 0; j < _cols; ++j) _p[i][j] = other._p[i][j];
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
    if (cols < 0)
        throw std::length_error("It is not possible for the size of an array to be zero");

    if (cols != _cols) {
        for (int i = 0; i < _rows; i++) {
            double *pi_temp = new double[cols]();
            for (int j = 0; j < cols; ++j) {
                if (j < _cols)
                    pi_temp[j] = _p[i][j];
            }
            delete[] _p[i];
            _p[i] = pi_temp;
        }
        _cols = cols;
    }

//    if (cols != _cols) {
//        for (int i = 0; i < _rows; i++) {
//            // Allocate a new array of double with 'cols' elements, initialized to 0.0
//            double* pi_temp = new double[cols]();
//            // Copy the elements from the old array to the new one
//            std::copy(_p[i], _p[i] + cols, pi_temp);
//            // Free the memory of the old array
//            delete[] _p[i];
//            // Replace the old array with the new one
//            _p[i] = pi_temp;
//        }
//        // Update the number of columns
//        _cols = cols;
}

int S21Matrix::get_rows() const noexcept {
return _rows;
}

int S21Matrix::get_cols() const noexcept {
return _cols;
}

// mutator of matrix values
double& S21Matrix::operator()(int rows, int cols) {
    if (rows >= _rows || cols >= _cols || cols < 0 || rows < 0)
        throw std::out_of_range("Invalid input, index exceeds valid range");
    return _p[rows][cols];
}

// accessor of matrix values
double& S21Matrix::operator()(int rows, int cols) const {
    if (rows >= _rows || cols >= _cols || cols < 0 || rows < 0)
        throw std::out_of_range("Invalid input, index exceeds valid range");
    return _p[rows][cols];
}

// This function assigns the values of the other matrix to the current matrix
S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
//    "Prevention of self-assignment"
    if (this == &other)
        // If the current matrix is the same as the other matrix, return the current matrix
        return *this;
    // Set the number of columns of the current matrix to the number of columns of the other matrix
    this->set_cols(other._cols);
    // Set the number of rows of the current matrix to the number of rows of the other matrix
    this->set_rows(other._rows);
    // Copy the values of the other matrix to the current matrix
    for (int i = 0; i < _rows; ++i)
        for (int j = 0; j < _cols; ++j)
            _p[i][j] = other._p[i][j];
    // Return the current matrix
    return *this;
}

bool S21Matrix::EqMatrix(const S21Matrix& other) {
    // This function compares the current matrix with the other matrix
    // and returns true if they are equal, false otherwise
    // are equal, false otherwise
    bool res = true;
    // Check if the number of rows and columns are the same in both matrices
    if (_cols != other._cols || _rows != other._rows) {
        // If the number of rows and columns are not the same, return false
        res = false;
    }
    for (int i = 0; i < _rows; i++) {
        // Use memcmp to compare the memory of the underlying arrays
        if (memcmp(_p[i], other._p[i], sizeof(_p[i]) * _cols) != 0) {
            // If memcmp returns a non-zero value, the arrays are not equal, so return false
            res = false;
        }
    }
//    res = memcmp(_p[0], other._p[0], sizeof(_p[0]) * _rows * _cols) == 0;
    return res;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
    if (_cols != other._cols || _rows != other._rows) {
        // If the number of rows and columns are not the same
        throw std::out_of_range("Rows and columns are not the same");
    }
    for (int i = 0; i < _rows; i++)
        for (int j = 0; j < _cols; j++) {
            _p[i][j] += other._p[i][j];
        }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
    if (_cols != other._cols || _rows != other._rows) {
        // If the number of rows and columns are not the same
        throw std::out_of_range("Rows and columns are not the same");
    }
    for (int i = 0; i < _rows; i++)
        for (int j = 0; j < _cols; j++) {
            _p[i][j] -= other._p[i][j];
        }
}

void S21Matrix::MulNumber(const double num) {
    for (int i = 0; i < _rows; i++)
        for (int j = 0; j < _cols; j++) {
            _p[i][j] *= num;
        }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
    if (_cols != other._rows) {
        throw std::out_of_range("Multiply matrix only when first matrix cols == second matrix rows");
    }
    S21Matrix copy(*this);
    set_cols(other._cols);
    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _cols; j++) {
            double sum = 0;
            for (int k = 0; k < copy._cols; ++k) {
                sum += copy._p[i][k] * other._p[k][j];
            }
            _p[i][j] = sum;
        }
    }
}
