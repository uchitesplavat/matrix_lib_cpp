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
//  Default constructor (2X2)
S21Matrix::S21Matrix() : rows_(2), cols_(2){
    matrix_ = new double *[rows_];
    for(int i = 0; i < rows_; i++) {
        matrix_[i] = new double[cols_]();
    }
}

//  This constructor generates a matrix of dimensions rows by cols, with all elements initialized to zero
//  The assignment of rows to rows_ using the initialization syntax "rows_(rows)" serves as a shortcut, eliminating the need for an additional assignment statement "rows_ = rows"
S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols){
    if (rows < 0 || cols < 0) {
        throw std::length_error("It is not possible for the size of an array to be zero");
    }
    matrix_ = new double *[rows_];
    for(int i = 0; i < rows_; i++) {
        matrix_[i] = new double[cols_]();
    }
}

//This constructor generates a copy of a specified matrix
//The use of the ':' syntax in this case invokes another member function
S21Matrix::S21Matrix(const S21Matrix& other)
        : S21Matrix::S21Matrix(other.rows_, other.cols_) {

//        std::copy(&other.matrix_, &other.matrix_ + i * j, &matrix_);

    for (int i = 0; i < rows_; ++i)
        for (int j = 0; j < cols_; ++j) matrix_[i][j] = other.matrix_[i][j];
}


//This constructor move the matrix from the given to this one
//P.S.
//int z = std::exchange(x, y);
//After this line of code executes:
//"x" is assigned the value of "y",
//"z" is assigned the value that "x" had initially.
S21Matrix::S21Matrix(S21Matrix&& other)
        : rows_(std::exchange(other.rows_, 0)), cols_(std::exchange(other.cols_, 0)),
          matrix_(std::exchange(other.matrix_, nullptr)){}
//    rows_ = std::exchange(other.rows_, 0);
//    cols_ = std::exchange(other.cols_, 0);
//    matrix_ = std::exchange(other.matrix_, nullptr);

//This destructor simply deallocates the memory of matrix_
S21Matrix::~S21Matrix() {
    for(int i = 0; i < rows_; i++) {
        delete[] matrix_[i];
    }
    delete[] matrix_;
}

//Tis mutator realloc matrix_ and change value of rows_
void S21Matrix::set_rows(int rows) {
    if (rows <= 0)
        throw std::length_error("It is not possible for the size of an array to be zero");

    if (rows == rows_) return;  // no changes needed

    double** p = new double*[rows];
    int minrows_ = std::min(rows, rows_);  // copy values from the smaller matrix
    for (int i = 0; i < minrows_; ++i) {
        p[i] = new double[cols_]; // allocate new row
        for (int j = 0; j < cols_; ++j)
            p[i][j] = matrix_[i][j]; // copy values from existing row
    }
    // initialize new rows with default values
    for (int i = minrows_; i < rows; ++i) {
        p[i] = new double[cols_]();
    }
    this->~S21Matrix();  // deallocate old matrix
    matrix_ = p; // update matrix with new array of row pointers
    rows_ = rows; // update number of rows
}

void S21Matrix::set_cols(int cols) {
    if (cols < 0)
        throw std::length_error("It is not possible for the size of an array to be zero");

    if (cols != cols_) {
        for (int i = 0; i < rows_; i++) {
            double *pi_temp = new double[cols]();
            for (int j = 0; j < cols; ++j) {
                if (j < cols_)
                    pi_temp[j] = matrix_[i][j];
            }
            delete[] matrix_[i];
            matrix_[i] = pi_temp;
        }
        cols_ = cols;
    }

//    if (cols != cols_) {
//        for (int i = 0; i < rows_; i++) {
//            // Allocate a new array of double with 'cols' elements, initialized to 0.0
//            double* pi_temp = new double[cols]();
//            // Copy the elements from the old array to the new one
//            std::copy(matrix_[i], matrix_[i] + cols, pi_temp);
//            // Free the memory of the old array
//            delete[] matrix_[i];
//            // Replace the old array with the new one
//            matrix_[i] = pi_temp;
//        }
//        // Update the number of columns
//        cols_ = cols;
}

int S21Matrix::get_rows() const noexcept {
return rows_;
}

int S21Matrix::get_cols() const noexcept {
return cols_;
}

bool S21Matrix::EqMatrix(const S21Matrix& other) {
    // This function compares the current matrix with the other matrix
    // and returns true if they are equal, false otherwise
    // are equal, false otherwise
    bool res = true;
    // Check if the number of rows and columns are the same in both matrices
    if (cols_ != other.cols_ || rows_ != other.rows_) {
        // If the number of rows and columns are not the same, return false
        res = false;
//        std::cout << "here 1" << "\n";
    }
    // If they are the same, compare each element in the matrices
    for (int i = 0; i < rows_; i++) {
//        if (memcmp(matrix_[i], other.matrix_[i], sizeof(matrix_[i]) * cols_) != 0) {
        for (int j = 0; j < rows_; j++) {
            // If any elements are not within 1e-7 of each other, set res to false
            // Note: "fabs" is a function that returns the absolute value of a float or double. It is used here to compare the difference between two elements without regard to their sign.
            if (fabs(matrix_[i][j] - other.matrix_[i][j]) > 1e-7) {
                res = false;
//                std::cout << "here 2" << "\n";
            }
        }
    }
//    res = memcmp(matrix_[0], other.matrix_[0], sizeof(matrix_[0]) * rows_ * cols_) == 0;
    return res;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
    if (cols_ != other.cols_ || rows_ != other.rows_) {
        // If the number of rows and columns are not the same
        throw std::out_of_range("Rows and columns are not the same");
    }
    for (int i = 0; i < rows_; i++)
        for (int j = 0; j < cols_; j++) {
            matrix_[i][j] += other.matrix_[i][j];
        }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
    if (cols_ != other.cols_ || rows_ != other.rows_) {
        // If the number of rows and columns are not the same
        throw std::out_of_range("Rows and columns are not the same");
    }
    for (int i = 0; i < rows_; i++)
        for (int j = 0; j < cols_; j++) {
            matrix_[i][j] -= other.matrix_[i][j];
        }
}

void S21Matrix::MulNumber(const double num) {
    for (int i = 0; i < rows_; i++)
        for (int j = 0; j < cols_; j++) {
            matrix_[i][j] *= num;
        }
}

// This function multiplies the current matrix object with the other matrix object passed as an argument.
void S21Matrix::MulMatrix(const S21Matrix& other) {
    // Check if the number of columns in the current matrix is equal to the number of rows in the other matrix
    if (cols_ != other.rows_) {
        throw std::out_of_range("Multiply matrix only when first matrix cols == second matrix rows");
    }
    // Create a copy of the current matrix object
    S21Matrix copy(*this);
    // Set the number of columns in the current matrix object to be equal to the number of columns in the other matrix
    set_cols(other.cols_);
    // Perform matrix multiplication
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            double sum = 0;
            for (int k = 0; k < copy.cols_; ++k) {
                // Multiply element at ith row and kth column of first matrix with element at kth row and jth column of second matrix
                sum += copy.matrix_[i][k] * other.matrix_[k][j];
            }
            // Set element at ith row and jth column of resulting matrix to sum
            matrix_[i][j] = sum;
        }
    }
}

// This function returns a new matrix object that is the transpose of the current matrix object.
S21Matrix S21Matrix::Transpose() {
    // First, we create a new matrix object with the number of rows and columns swapped.
    // This is because the transpose of a matrix will have the number of rows and columns flipped.
    S21Matrix res(cols_, rows_);
    // Next, we iterate over the rows and columns of the current matrix and set the elements of the resulting matrix to be the transpose of the current matrix.
    for (int i = 0; i < rows_; i++)
        for (int j = 0; j < cols_; j++)
            // We set the element at the jth row and ith column of the resulting matrix to be the element at the ith row and jth column of the current matrix.
            res.matrix_[j][i] = matrix_[i][j];
    return res;
}

void S21Matrix::get_res_matrix(S21Matrix &result) {
    // We iterate over the rows and columns of the result matrix and set the element at each position to be the minor of the corresponding element in the original matrix.
    for (int i = 0; i < result.rows_; i++) {
        for (int j = 0; j < result.cols_; j++) {
            result(i, j) = get_minor(i, j);
        }
    }
}

// This function calculates the minor of an element at a given position in the current matrix object.
// The minor of an element is the determinant of the matrix formed by deleting the row and column containing the element.
double S21Matrix::get_minor(int i, int j) {
    double minor = 0.0;
    // If the matrix is a 2x2 matrix, we simply set the minor to be the element that is not in the same row or column as the given position.
    if (this->rows_ == 2) {
        for (int m = 0; m < rows_; m++) {
            for (int n = 0; n < cols_; n++) {
                if (m != i && n != j) {
                    minor = matrix_[m][n];
                }
            }
        }
        // If the matrix is larger than a 2x2 matrix, we need to calculate the minor using the determinant.
    } else {
        int x = 0;
        int y = 0;
        // First, we create a new matrix object that is the matrix formed by deleting the row and column containing the element.
        S21Matrix res(rows_ - 1, cols_ - 1);
        for (int m = 0; m < rows_; m++) {
            if (m != i) {
                for (int n = 0; n < cols_; n++) {
                    if (n != j) {
                        res(x, y) = matrix_[m][n];
                        y++;
                    }
                }
                x++;
                y = 0;
            }
        }
        // If the resulting matrix is larger than a 2x2 matrix, we calculate the determinant of the matrix.
        if (res.cols_ > 2) {
            minor = res.Determinant();
            // If the resulting matrix is a 2x2 matrix, we call the det_two function to calculate the determinant.
        } else {
            minor = det_two(res);
        }
    }
    return minor;
}

double S21Matrix::det_two(S21Matrix &res) {
    return res(0, 0) * res(1, 1) - res(1, 0) * res(0, 1);
}

// This function calculates the matrix of complements of a matrix object passed as an argument and stores the result in the same object.
// The matrix of complements is obtained by taking the complement of each element in the matrix,
// i.e., by subtracting each element from the total number of elements in the matrix.
void S21Matrix::calc_complements(S21Matrix &result) {
    // First, we call the get_res_matrix function on the result matrix object to calculate the matrix of complements.
    get_res_matrix(result);
    // Next, we iterate over the rows and columns of the result matrix and set the elements to be the complement of the corresponding element in the original matrix,
    // multiplied by (-1) raised to the power of the sum of the row and column indices.
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            result(i, j) = result(i, j) * pow(-1, i + j);
        }
    }
}

// This function returns a new matrix object that is the matrix of complements of the current matrix object.
S21Matrix S21Matrix::CalcComplements() {
    // First, we check if the current matrix is a square matrix.
    if (rows_ != cols_) {
        throw std::logic_error("Its not a square matrix");
    }
    // Next, we create a copy of the current matrix object and assign it to a new matrix object called result.
    S21Matrix result = *this;
    // If the matrix is a 1x1 matrix, we simply set the element in the resulting matrix to be the complement of the element in the current matrix.
    if (rows_ == 1) {
        result(0, 0) = matrix_[0][0];
        // If the matrix is larger than a 1x1 matrix, we call the calc_complements function on the result matrix.
    } else {
        calc_complements(result);
    }

    return result;
}

// This function returns the determinant of the current matrix object.
// The determinant of a matrix is a scalar value that represents the strength of the matrix's contribution to a transformation.
double S21Matrix::Determinant() {
    // First, we check if the current matrix is a square matrix.
    if (rows_ != cols_) {
        throw std::logic_error("Its not a square matrix");
    }
    double result = 0;
    // If the matrix is a 1x1 matrix, the determinant is simply the element in the matrix.
    if (rows_ == 1) {
        result = matrix_[0][0];
        // If the matrix is larger than a 1x1 matrix, we need to calculate the determinant using the matrix of complements.
    } else {
        // Second, we calculate the matrix of complements of the current matrix.
        S21Matrix complement = CalcComplements();
        // Next, we iterate over the columns of the current matrix and sum up the products of the elements in the first row of the matrix of complements
        // with the corresponding elements in the first row of the current matrix.
        for (int i = 0; i < cols_; i++) {
            result += complement(0, i) * matrix_[0][i];
        }
    }
    return result;
}

// This function returns a new matrix object that is the inverse of the current matrix object.
S21Matrix S21Matrix::InverseMatrix() {
    // First, we create a new matrix object with the same dimensions as the current matrix object.
    S21Matrix result(rows_, cols_);
    // Next, we calculate the determinant of the current matrix.
    double det = Determinant();
    // If the determinant is 0, the matrix is not invertible and we throw an exception.
    if (det == 0) {
        throw std::logic_error("determinant of matrix == 0");
        // If the determinant is not 0, we can calculate the inverse of the matrix.
    } else {
        // If the matrix is a 1x1 matrix, the inverse is simply 1/element.
        if (rows_ == 1) {
            result(0, 0) = 1 / matrix_[0][0];
            // If the matrix is larger than a 1x1 matrix, we need to use the matrix of complements to calculate the inverse.
        } else {
            // First, we calculate the matrix of complements of the current matrix.
            S21Matrix complement(rows_, cols_);
            complement = CalcComplements();
            // Next, we transpose the matrix of complements to get the cofactor matrix.
            result = complement.Transpose();
            // Finally, we multiply the cofactor matrix by 1/determinant to get the inverse matrix.
            result.MulNumber(1 / det);
        }
    }
    return result;
}



// mutator of matrix values
double& S21Matrix::operator()(int rows, int cols) {
    if (rows >= rows_ || cols >= cols_ || cols < 0 || rows < 0)
        throw std::out_of_range("Invalid input, index exceeds valid range");
    return matrix_[rows][cols];
}

// accessor of matrix values
double& S21Matrix::operator()(int rows, int cols) const {
    if (rows >= rows_ || cols >= cols_ || cols < 0 || rows < 0)
        throw std::out_of_range("Invalid input, index exceeds valid range");
    return matrix_[rows][cols];
}

// This function assigns the values of the other matrix to the current matrix
S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
//    "Prevention of self-assignment"
    if (this == &other)
        // If the current matrix is the same as the other matrix, return the current matrix
        return *this;
    // Set the number of columns of the current matrix to the number of columns of the other matrix
    this->set_cols(other.cols_);
    // Set the number of rows of the current matrix to the number of rows of the other matrix
    this->set_rows(other.rows_);
    // Copy the values of the other matrix to the current matrix
    for (int i = 0; i < rows_; ++i)
        for (int j = 0; j < cols_; ++j)
            matrix_[i][j] = other.matrix_[i][j];
    // Return the current matrix
    return *this;
}

// The first operator overload is the equality operator (==). It checks if the current matrix object is equal to another matrix object.
// It returns a bool value indicating whether the two matrices are equal.
bool S21Matrix::operator==(const S21Matrix& other) {
    return EqMatrix(other);
}

// The next operator overloads are the compound assignment operators for addition, subtraction, and multiplication.
// These operator overloads modify the current matrix object and return a reference to it.
S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
    SumMatrix(other);
    return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
    SubMatrix(other);
    return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
    MulMatrix(other);
    return *this;
}

// The next operator overloads are the binary operators for addition, subtraction, and multiplication.
// These operator overloads create and return a new matrix object that is the result of the operation.

S21Matrix S21Matrix::operator+(const S21Matrix& other) {
    S21Matrix res(*this);
    res.SumMatrix(other);
    return res;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) {
    S21Matrix res(*this);
    res.SubMatrix(other);
    return res;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) {
    S21Matrix res(*this);
    res.MulMatrix(other);
    return res;
}

// The next operator overloads are the compound assignment and binary operators for scalar multiplication.
// These operator overloads multiply each element in the matrix by a scalar value.
S21Matrix& S21Matrix::operator*=(const double num) {
    MulNumber(num);
    return *this;
}

S21Matrix S21Matrix::operator*(const double num) {
    S21Matrix res(*this);
    res.MulNumber(num);
    return res;
}

