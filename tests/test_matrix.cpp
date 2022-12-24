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

