#include "../s21_matrix_oop.h"
#include "gtest/gtest.h"

TEST(test_class, basic_constructor) {
S21Matrix m;
EXPECT_EQ(m.get_cols(), 4);
EXPECT_EQ(m.get_rows(), 4);
}


TEST(test_class, rc_constructor) {
S21Matrix m(34, 400);
EXPECT_EQ(m.get_rows(), 34);
EXPECT_EQ(m.get_cols(), 400);
}

TEST(test_class, assert_one) {
ASSERT_ANY_THROW (S21Matrix m(-1, -1));
}

TEST(test_class, assert_two) {
S21Matrix m(34, 400);
ASSERT_ANY_THROW (m.set_rows(-2));
ASSERT_ANY_THROW (m.set_cols(-3));
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
EXPECT_EQ(4, m1.get_cols());
EXPECT_EQ(4, m1.get_rows());
for (int i = 0; i < m1.get_rows(); ++i)
for (int j = 0; j < m1.get_cols(); ++j) EXPECT_DOUBLE_EQ(0, m1(i, j));
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
for (int j = 0; j < m1.get_cols(); ++j)
EXPECT_DOUBLE_EQ(0, m1(i, j));

m2.set_rows(4);
EXPECT_EQ(4, m2.get_rows());
for (int i = 0; i < m2.get_rows(); ++i)
for (int j = 0; j < m2.get_cols(); ++j)
EXPECT_DOUBLE_EQ(0, m2(i, j));

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
EXPECT_TRUE(m1.EqMatrix(m2));
m2(0, 2) = 10;
EXPECT_FALSE(m1.EqMatrix(m2));
}

TEST(test_class, AddTest) {
S21Matrix m1;
S21Matrix m2;
    m1.set_cols(6);
    m2.set_cols(6);
    m1.set_rows(6);
    m2.set_rows(6);
    m1(0,1) = 10;
    m2(0,1) = 12;
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
m1(0,1) = 10;
m2(0,1) = 12;
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
m1(0,1) = 10;
m1.MulNumber(number);
EXPECT_DOUBLE_EQ(60, m1(0, 1));
}

TEST(test_class, MulMatrixTest) {
S21Matrix m1;
S21Matrix m2;
m1.set_cols(6);
m2.set_rows(6);
m1(0,0) = 2;
m1(0,1) = 1;
m1(1,0) = -3;
m1(1,1) = 0;
m1(2,0) = 4;
m1(2,1) = -1;
m2(0,0) = 5;
m2(0,1) = -1;
m2(0,2) = 6;
m2(1,0) = -3;
m2(1,1) = 0;
m2(1,2) = 7;

m1.MulMatrix(m2);
EXPECT_DOUBLE_EQ(7, m1(0, 0));
EXPECT_DOUBLE_EQ(3, m1(1, 1));
EXPECT_DOUBLE_EQ(17, m1(2, 2));
}