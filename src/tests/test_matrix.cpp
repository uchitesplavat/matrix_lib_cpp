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

//ASSERT_ANY_THROW(m1.set_rows(0));
}

TEST(test_class, SetColsTest) {
S21Matrix m1;
S21Matrix m2;
m1.set_cols(2);
EXPECT_EQ(2, m1.get_cols());
for (int i = 0; i < m1.get_rows(); ++i)
for (int j = 0; j < m1.get_cols(); ++j)
EXPECT_DOUBLE_EQ(0, m1(i, j));

m2.set_cols(2);
EXPECT_EQ(2, m2.get_cols());
for (int i = 0; i < m2.get_rows(); ++i)
for (int j = 0; j < m2.get_cols(); ++j)
EXPECT_DOUBLE_EQ(0, m2(i, j));

ASSERT_ANY_THROW(m1.set_cols(0));
}