#include "../s21_matrix_oop.h"
#include "gtest/gtest.h"

TEST(test_class, basic_constructor) {
  S21Matrix m;
  EXPECT_EQ(m.get_cols(), 2);
  EXPECT_EQ(m.get_rows(), 2);
}

TEST(test_class, rc_constructor) {
  S21Matrix m(34, 400);
  EXPECT_EQ(m.get_rows(), 34);
  EXPECT_EQ(m.get_cols(), 400);
}

TEST(test_class, assert_one) { ASSERT_ANY_THROW(S21Matrix m(-1, -1)); }

TEST(test_class, assert_two) {
  S21Matrix m(34, 400);
  ASSERT_ANY_THROW(m.set_rows(-2));
  ASSERT_ANY_THROW(m.set_cols(-3));
}

TEST(test_class, RowsColsConstructorTest) {
  S21Matrix m1(2, 2);
  EXPECT_EQ(2, m1.get_cols());
  EXPECT_EQ(2, m1.get_rows());
  for (int i = 0; i < m1.get_rows(); ++i)
    for (int j = 0; j < m1.get_cols(); ++j) EXPECT_DOUBLE_EQ(0, m1(i, j));
}

TEST(test_class, CopyConstructorTest) {
  S21Matrix m1(2, 2);
  m1(0, 1) = 2;
  S21Matrix m2(m1);
  EXPECT_EQ(2, m2.get_cols());
  EXPECT_EQ(2, m2.get_rows());
  for (int i = 0; i < m2.get_rows(); ++i)
    for (int j = 0; j < m2.get_cols(); ++j)
      if (i == 0 && j == 1)
        EXPECT_DOUBLE_EQ(2, m1(0, 1));
      else
        EXPECT_DOUBLE_EQ(0, m1(i, j));
}

TEST(test_class, DefaultConstructorTest) {
  S21Matrix m1;
  EXPECT_EQ(2, m1.get_cols());
  EXPECT_EQ(2, m1.get_rows());
  for (int i = 0; i < m1.get_rows(); ++i)
    for (int j = 0; j < m1.get_cols(); ++j) EXPECT_DOUBLE_EQ(0, m1(i, j));
}

TEST(test_class, MoveConstructor) {
  S21Matrix a;
  S21Matrix c;

  a(0, 0) = 2;
  a(0, 1) = 4;
  a(1, 0) = 6;
  a(1, 1) = 8;

  c(0, 0) = 2;
  c(0, 1) = 4;
  c(1, 0) = 6;
  c(1, 1) = 8;

  S21Matrix b(std::move(a));

  EXPECT_EQ(b.EqMatrix(c), 1);
  EXPECT_EQ(a.get_rows(), 0);
  EXPECT_EQ(a.get_cols(), 0);
}

TEST(test_class, ParenthesesOperatorTest) {
  S21Matrix m1;
  m1(0, 0) = 10;
  for (int i = 0; i < m1.get_rows(); ++i)
    for (int j = 0; j < m1.get_cols(); ++j)
      if (i == 0 && j == 0)
        EXPECT_DOUBLE_EQ(10, m1(0, 0));
      else
        EXPECT_DOUBLE_EQ(0, m1(i, j));

  ASSERT_ANY_THROW(m1(5, 5));
  ASSERT_ANY_THROW(m1(-5, -5));
}

TEST(test_class, SetRowsTest) {
  S21Matrix m1;
  S21Matrix m2;
  m1.set_rows(2);
  EXPECT_EQ(2, m1.get_rows());
  for (int i = 0; i < m1.get_rows(); ++i)
    for (int j = 0; j < m1.get_cols(); ++j) EXPECT_DOUBLE_EQ(0, m1(i, j));

  m2.set_rows(4);
  EXPECT_EQ(4, m2.get_rows());
  for (int i = 0; i < m2.get_rows(); ++i)
    for (int j = 0; j < m2.get_cols(); ++j) EXPECT_DOUBLE_EQ(0, m2(i, j));

  ASSERT_ANY_THROW(m1.set_rows(-1));
}

TEST(test_class, SetColsTest) {
  S21Matrix m1;
  S21Matrix m2;
  m1.set_cols(2);
  EXPECT_EQ(2, m1.get_cols());

  m2.set_cols(25);
  EXPECT_EQ(25, m2.get_cols());

  ASSERT_ANY_THROW(m1.set_cols(-1));
}

TEST(test_class, EqTest) {
  S21Matrix m1;
  S21Matrix m2;
  m1(0, 0) = 2.4;
  m2(0, 0) = 2.4;
  m1(0, 1) = 4.8;
  m2(0, 1) = 4.8;
  m1(1, 0) = 7.2;
  m2(1, 0) = 7.2;
  m1(1, 1) = 9.6;
  m2(1, 1) = 9.6;

  EXPECT_TRUE(m1.EqMatrix(m2));
  m2(0, 1) = 10;
  EXPECT_FALSE(m1.EqMatrix(m2));
}

TEST(test_class, AddTest) {
  S21Matrix m1;
  S21Matrix m2;
  m1.set_cols(6);
  m2.set_cols(6);
  m1.set_rows(6);
  m2.set_rows(6);
  m1(0, 1) = 10;
  m2(0, 1) = 12;
  m1.SumMatrix(m2);
  S21Matrix m3(10, 10);
  EXPECT_DOUBLE_EQ(22, m1(0, 1));

  ASSERT_ANY_THROW(m1.SumMatrix(m3));
}

TEST(test_class, DivTest) {
  S21Matrix m1;
  S21Matrix m2;
  m1.set_cols(6);
  m2.set_cols(6);
  m1.set_rows(6);
  m2.set_rows(6);
  m1(0, 1) = 10;
  m2(0, 1) = 12;
  m1.SubMatrix(m2);
  S21Matrix m3(10, 10);
  EXPECT_DOUBLE_EQ(-2, m1(0, 1));

  ASSERT_ANY_THROW(m1.SumMatrix(m3));
}

TEST(test_class, MulNumberTest) {
  int number = 6;
  S21Matrix m1;
  m1.set_cols(6);
  m1.set_rows(6);
  m1(0, 1) = 10;
  m1.MulNumber(number);
  EXPECT_DOUBLE_EQ(60, m1(0, 1));
}

TEST(test_class, MulMatrixTest) {
  S21Matrix m1;
  S21Matrix m2;
  m1.set_cols(6);
  m2.set_rows(6);
  m2.set_cols(5);
  m1.set_rows(7);
  m1(0, 0) = 2;
  m1(0, 1) = 1;
  m1(1, 0) = -3;
  m1(1, 1) = 0;
  m1(2, 0) = 4;
  m1(2, 1) = -1;
  m2(0, 0) = 5;
  m2(0, 1) = -1;
  m2(0, 2) = 6;
  m2(1, 0) = -3;
  m2(1, 1) = 0;
  m2(1, 2) = 7;

  m1.MulMatrix(m2);
  EXPECT_DOUBLE_EQ(7, m1(0, 0));
  EXPECT_DOUBLE_EQ(3, m1(1, 1));
  EXPECT_DOUBLE_EQ(17, m1(2, 2));
}

TEST(test_class, TransposeOne) {
  S21Matrix a;
  S21Matrix b;
  S21Matrix c;

  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;

  c(0, 0) = 1;
  c(0, 1) = 3;
  c(1, 0) = 2;
  c(1, 1) = 4;

  b = a.Transpose();

  EXPECT_EQ(b.EqMatrix(c), 1);
}

TEST(test_class, TransposeTwo) {
  S21Matrix a(1, 1);
  S21Matrix b(1, 1);
  S21Matrix c(1, 1);

  a(0, 0) = 1;

  c(0, 0) = 1;

  b = a.Transpose();

  EXPECT_EQ(b.EqMatrix(c), 1);
}

TEST(test_class, CalcComplementsOne) {
  S21Matrix a;
  S21Matrix b;
  S21Matrix c;

  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;

  c(0, 0) = 4;
  c(0, 1) = -3;
  c(1, 0) = -2;
  c(1, 1) = 1;

  b = a.CalcComplements();
  // std::cout << c(0, 0) << "\n";
  // std::cout << c(0, 1) << "\n";
  // std::cout << c(1, 0) << "\n";
  // std::cout << c(1, 1) << "\n";
  EXPECT_EQ(b.EqMatrix(c), 1);
}

TEST(test_class, CalcComplementsTwo) {
  S21Matrix a(1, 1);
  S21Matrix b(1, 1);
  S21Matrix c(1, 1);

  a(0, 0) = 1;

  c(0, 0) = 1;

  b = a.CalcComplements();

  EXPECT_EQ(b.EqMatrix(c), 1);
}

TEST(test_class, CalcComplementsThree) {
  S21Matrix a(1, 2);

  EXPECT_ANY_THROW(a.CalcComplements());
}

TEST(test_class, DeterminantOne) {
  S21Matrix a;

  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;

  double det = a.Determinant();

  EXPECT_DOUBLE_EQ(det, -2);
}

TEST(test_class, DeterminantTwo) {
  S21Matrix a(3, 3);

  a(0, 0) = 1;
  a(0, 1) = 2;
  a(0, 2) = 3;
  a(1, 0) = 4;
  a(1, 1) = 5;
  a(1, 2) = 6;
  a(2, 0) = 7;
  a(2, 1) = 8;
  a(2, 2) = 9;

  double det = a.Determinant();

  EXPECT_DOUBLE_EQ(det, 0);
}

TEST(test_class, DeterminantThree) {
  S21Matrix a(3, 3);

  a(0, 0) = 10;
  a(0, 1) = 2;
  a(0, 2) = 3;
  a(1, 0) = 4;
  a(1, 1) = 5;
  a(1, 2) = 6;
  a(2, 0) = 7;
  a(2, 1) = 8;
  a(2, 2) = 9;

  double det = a.Determinant();

  EXPECT_DOUBLE_EQ(det, -27);
}
TEST(test_class, DeterminantFour) {
  S21Matrix a(4, 4);

  a(0, 0) = 10;
  a(0, 1) = 2;
  a(0, 2) = 3;
  a(0, 3) = 3;
  a(1, 0) = 4;
  a(1, 1) = 5;
  a(1, 2) = 6;
  a(1, 3) = 6;
  a(2, 0) = 7;
  a(2, 1) = 8;
  a(2, 2) = 9;
  a(2, 3) = 9;
  a(3, 0) = 10;
  a(3, 1) = 11;
  a(3, 2) = 12;
  a(3, 3) = 13;

  double det = a.Determinant();

  EXPECT_DOUBLE_EQ(det, -27);
}

TEST(test_class, DeterminantFive) {
  S21Matrix a(4, 4);

  a(0, 0) = 1;
  a(0, 1) = 2;
  a(0, 2) = 3;
  a(0, 3) = 4;
  a(1, 0) = 5;
  a(1, 1) = 6;
  a(1, 2) = 7;
  a(1, 3) = 8;
  a(2, 0) = 9;
  a(2, 1) = 10;
  a(2, 2) = 11;
  a(2, 3) = 12;
  a(3, 0) = 13;
  a(3, 1) = 14;
  a(3, 2) = 15;
  a(3, 3) = 16;

  double det = a.Determinant();

  EXPECT_DOUBLE_EQ(det, 0);
}

TEST(test_class, InverseMatrixOne) {
  S21Matrix a;
  S21Matrix b;
  S21Matrix c;

  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;

  c(0, 0) = -2;
  c(0, 1) = 1;
  c(1, 0) = 1.5;
  c(1, 1) = -0.5;

  b = a.InverseMatrix();

  EXPECT_EQ(b.EqMatrix(c), 1);
}

TEST(test_class, InverseMatrixTwo) {
  S21Matrix a(3, 3);
  S21Matrix b(3, 3);

  a(0, 0) = 10;
  a(0, 1) = 2;
  a(0, 2) = 3;
  a(1, 0) = 4;
  a(1, 1) = 5;
  a(1, 2) = 6;
  a(2, 0) = 7;
  a(2, 1) = 8;
  a(2, 2) = 9;

  b = a.InverseMatrix();

  EXPECT_DOUBLE_EQ(b(0, 0), 1. / 9);
  EXPECT_DOUBLE_EQ(b(0, 1), -2. / 9);
  EXPECT_DOUBLE_EQ(b(0, 2), 1. / 9);
  EXPECT_DOUBLE_EQ(b(1, 0), -2. / 9);
  EXPECT_DOUBLE_EQ(b(1, 1), -23. / 9);
  EXPECT_DOUBLE_EQ(b(1, 2), 16. / 9);
  EXPECT_DOUBLE_EQ(b(2, 0), 1. / 9);
  EXPECT_DOUBLE_EQ(b(2, 1), 22. / 9);
  EXPECT_DOUBLE_EQ(b(2, 2), -14. / 9);
}

TEST(test_class, InverseMatrixThree) {
  S21Matrix a(1, 1);
  S21Matrix b(1, 1);
  S21Matrix c(1, 1);

  a(0, 0) = 10;

  c(0, 0) = 1.0 / 10;

  b = a.InverseMatrix();

  EXPECT_EQ(b.EqMatrix(c), 1);
}

TEST(test_class, InverseMatrixThrow) {
  S21Matrix a(3, 3);
  S21Matrix b(3, 3);
  S21Matrix c(3, 3);

  a(0, 0) = 1;
  a(0, 1) = 2;
  a(0, 2) = 3;
  a(1, 0) = 4;
  a(1, 1) = 5;
  a(1, 2) = 6;
  a(2, 0) = 7;
  a(2, 1) = 8;
  a(2, 2) = 9;

  EXPECT_ANY_THROW(a.InverseMatrix());
}

TEST(func_operator, test1) {
  S21Matrix a;
  S21Matrix b;
  S21Matrix c;
  S21Matrix d;

  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;

  b(0, 0) = 1;
  b(0, 1) = 2;
  b(1, 0) = 3;
  b(1, 1) = 4;

  c(0, 0) = 2;
  c(0, 1) = 4;
  c(1, 0) = 6;
  c(1, 1) = 8;

  d = a + b;

  EXPECT_EQ(d.EqMatrix(c), 1);
}

TEST(func_operator, test2) {
  S21Matrix a;
  S21Matrix b;
  S21Matrix c;
  S21Matrix d;

  a(0, 0) = 2;
  a(0, 1) = 4;
  a(1, 0) = 6;
  a(1, 1) = 8;

  b(0, 0) = 1;
  b(0, 1) = 2;
  b(1, 0) = 3;
  b(1, 1) = 4;

  c(0, 0) = 1;
  c(0, 1) = 2;
  c(1, 0) = 3;
  c(1, 1) = 4;

  d = a - b;

  EXPECT_EQ(d.EqMatrix(c), 1);
}

TEST(func_operator, test3) {
  S21Matrix a;
  S21Matrix b;
  S21Matrix c;
  S21Matrix d;

  a(0, 0) = 2;
  a(0, 1) = 4;
  a(1, 0) = 6;
  a(1, 1) = 8;

  b(0, 0) = 1;
  b(0, 1) = 2;
  b(1, 0) = 3;
  b(1, 1) = 4;

  c(0, 0) = 14;
  c(0, 1) = 20;
  c(1, 0) = 30;
  c(1, 1) = 44;

  d = a * b;

  EXPECT_EQ(d.EqMatrix(c), 1);
}

TEST(func_operator, test4) {
  S21Matrix a;
  S21Matrix b;
  S21Matrix c;

  a(0, 0) = 2;
  a(0, 1) = 4;
  a(1, 0) = 6;
  a(1, 1) = 8;

  c(0, 0) = 2.4;
  c(0, 1) = 4.8;
  c(1, 0) = 7.2;
  c(1, 1) = 9.6;

  b = a * 1.2;

  // std::cout << b(0, 0) << "\n";
  // std::cout << b(0, 1) << "\n";
  // std::cout << b(1, 0) << "\n";
  // std::cout << b(1, 1) << "\n";
  // std::cout << b(1, 2) << "\n";
  // std::cout << c(0, 0) << "\n";
  // std::cout << c(0, 1) << "\n";
  // std::cout << c(1, 0) << "\n";
  // std::cout << c(1, 1) << "\n";
  // std::cout << c(1, 2) << "\n";

  EXPECT_TRUE(b.EqMatrix(c));
  // EXPECT_EQ(b.EqMatrix(c), true);
}

TEST(func_operator, test5) {
  S21Matrix a;
  S21Matrix b;

  a(0, 0) = 2;
  a(0, 1) = 4;
  a(1, 0) = 6;
  a(1, 1) = 8;

  b(0, 0) = 2;
  b(0, 1) = 4;
  b(1, 0) = 6;
  b(1, 1) = 8;

  EXPECT_EQ(a == b, 1);
}

TEST(func_operator, test6) {
  S21Matrix a;
  S21Matrix b;
  S21Matrix c;

  a(0, 0) = 2;
  a(0, 1) = 4;
  a(1, 0) = 6;
  a(1, 1) = 8;

  b(0, 0) = 1;
  b(0, 1) = 2;
  b(1, 0) = 3;
  b(1, 1) = 4;

  c(0, 0) = 3;
  c(0, 1) = 6;
  c(1, 0) = 9;
  c(1, 1) = 12;

  a += b;

  EXPECT_EQ(a.EqMatrix(c), 1);
}

TEST(func_operator, test7) {
  S21Matrix a;
  S21Matrix b;
  S21Matrix c;

  a(0, 0) = 2;
  a(0, 1) = 4;
  a(1, 0) = 6;
  a(1, 1) = 8;

  b(0, 0) = 1;
  b(0, 1) = 2;
  b(1, 0) = 3;
  b(1, 1) = 4;

  c(0, 0) = 1;
  c(0, 1) = 2;
  c(1, 0) = 3;
  c(1, 1) = 4;

  a -= b;

  EXPECT_EQ(a.EqMatrix(c), 1);
}

TEST(func_operator, test8) {
  S21Matrix a;
  S21Matrix b;
  S21Matrix c;

  a(0, 0) = 2;
  a(0, 1) = 4;
  a(1, 0) = 6;
  a(1, 1) = 8;

  b(0, 0) = 1;
  b(0, 1) = 2;
  b(1, 0) = 3;
  b(1, 1) = 4;

  c(0, 0) = 14;
  c(0, 1) = 20;
  c(1, 0) = 30;
  c(1, 1) = 44;

  a *= b;

  EXPECT_EQ(a.EqMatrix(c), 1);
}

TEST(func_operator, test9) {
  S21Matrix a;
  S21Matrix c;

  a(0, 0) = 2;
  a(0, 1) = 4;
  a(1, 0) = 6;
  a(1, 1) = 8;

  c(0, 0) = 2.2;
  c(0, 1) = 4.4;
  c(1, 0) = 6.6;
  c(1, 1) = 8.8;

  a *= 1.1;

  EXPECT_EQ(a.EqMatrix(c), 1);
}

TEST(func_operator, test10) {
  S21Matrix a;
  S21Matrix c;

  a(0, 0) = 2;
  a(0, 1) = 4;
  a(1, 0) = 6;
  a(1, 1) = 8;

  a = c;

  EXPECT_EQ(a.EqMatrix(c), 1);
}

TEST(func_operator, test11) {
  S21Matrix a;
  S21Matrix b;
  S21Matrix c;

  a(0, 0) = 2;
  a(0, 1) = 4;
  a(1, 0) = 6;
  a(1, 1) = 8;

  c(0, 0) = 2.4;
  c(0, 1) = 4.8;
  c(1, 0) = 7.2;
  c(1, 1) = 9.6;

  b = 1.2 * a;

  // std::cout << b(0, 0) << "\n";
  // std::cout << b(0, 1) << "\n";
  // std::cout << b(1, 0) << "\n";
  // std::cout << b(1, 1) << "\n";
  // std::cout << b(1, 2) << "\n";
  // std::cout << c(0, 0) << "\n";
  // std::cout << c(0, 1) << "\n";
  // std::cout << c(1, 0) << "\n";
  // std::cout << c(1, 1) << "\n";
  // std::cout << c(1, 2) << "\n";

  EXPECT_TRUE(b.EqMatrix(c));
  // EXPECT_EQ(b.EqMatrix(c), true);
}

TEST(test_class, DeterminantSix) {
  S21Matrix matrix1{5, 5};

  matrix1(0, 0) = 561.395;
  matrix1(0, 1) = 356.219;
  matrix1(0, 2) = 356.219;
  matrix1(0, 3) = -952.484;
  matrix1(0, 4) = -506.042;

  matrix1(1, 0) = 370.469;
  matrix1(1, 1) = 356.219;
  matrix1(1, 2) = 356.219;
  matrix1(1, 3) = 441.733;
  matrix1(1, 4) = 919.346;

  matrix1(2, 0) = 113.190;
  matrix1(2, 1) = 356.219;
  matrix1(2, 2) = 356.219;
  matrix1(2, 3) = 577.491;
  matrix1(2, 4) = -770.006;

  matrix1(3, 0) = -629.533;
  matrix1(3, 1) = 356.219;
  matrix1(3, 2) = 356.219;
  matrix1(3, 3) = 370.425;
  matrix1(3, 4) = -226.376;

  matrix1(4, 0) = 964.659;
  matrix1(4, 1) = 356.219;
  matrix1(4, 2) = 356.219;
  matrix1(4, 3) = 907.791;
  matrix1(4, 4) = 679.804;

  double det = matrix1.Determinant();
  std::cout << det << "\n";
  EXPECT_DOUBLE_EQ(det, 0);
}
