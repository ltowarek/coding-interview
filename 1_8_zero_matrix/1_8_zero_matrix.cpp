// Zero Matrix: Write an algorithm such that if an element in an MxN matrix
// is 0, its entire row and column are set to 0.

#include "gtest/gtest.h"

template <class T, size_t ROW, size_t COLUMN>
using Matrix = std::array<std::array<T, COLUMN>, ROW>;

template <class T, size_t M, size_t N> void Print(const Matrix<T, M, N> &m) {
  for (const auto &row : m) {
    for (const auto &value : row) {
      printf("%d ", value);
    }
    printf("\n");
  }
  printf("\n");
}

template <class T, size_t M, size_t N>
Matrix<T, M, N> ZeroRow(const size_t row, Matrix<T, M, N> &m) {
  for (auto column = 0; column < N; ++column) {
    m[row][column] = 0;
  }
}

template <class T, size_t M, size_t N>
Matrix<T, M, N> ZeroColumn(const size_t column, Matrix<T, M, N> &m) {
  for (auto row = 0; row < M; ++row) {
    m[row][column] = 0;
  }
}

template <class T, size_t M, size_t N>
Matrix<T, M, N> ZeroMatrix(const Matrix<T, M, N> &m) {
  auto output = m;
  for (auto row = 0; row < M; ++row) {
    for (auto column = 0; column < N; ++column) {
      if (m[row][column] == 0) {
        ZeroRow(row, output);
        ZeroColumn(column, output);
      }
    }
  }
  return output;
}

TEST(zero_matrix_test, EmptyMatrix) {
  const auto input = Matrix<int, 0, 0>();
  const auto expected = Matrix<int, 0, 0>();
  EXPECT_EQ(ZeroMatrix(input), expected);
}

TEST(zero_matrix_test, NoZeros_1x1) {
  const auto input = Matrix<int, 1, 1>{{1}};
  EXPECT_EQ(ZeroMatrix(input), input);
}

TEST(zero_matrix_test, Zeros_1x1) {
  const auto input = Matrix<int, 1, 1>{{0}};
  EXPECT_EQ(ZeroMatrix(input), input);
}

TEST(zero_matrix_test, NoZeros_2x2) {
  const auto input = Matrix<int, 2, 2>{{{1, 2}, {3, 4}}};
  EXPECT_EQ(ZeroMatrix(input), input);
}

TEST(zero_matrix_test, Zeros_2x2_0) {
  const auto input = Matrix<int, 2, 2>{{{0, 2}, {3, 4}}};
  const auto expected = Matrix<int, 2, 2>{{{0, 0}, {0, 4}}};
  EXPECT_EQ(ZeroMatrix(input), expected);
}

TEST(zero_matrix_test, Zeros_2x2_1) {
  const auto input = Matrix<int, 2, 2>{{{1, 0}, {3, 4}}};
  const auto expected = Matrix<int, 2, 2>{{{0, 0}, {3, 0}}};
  EXPECT_EQ(ZeroMatrix(input), expected);
}

TEST(zero_matrix_test, Zeros_2x2_2) {
  const auto input = Matrix<int, 2, 2>{{{1, 2}, {0, 4}}};
  const auto expected = Matrix<int, 2, 2>{{{0, 2}, {0, 0}}};
  EXPECT_EQ(ZeroMatrix(input), expected);
}

TEST(zero_matrix_test, Zeros_2x2_3) {
  const auto input = Matrix<int, 2, 2>{{{1, 2}, {3, 0}}};
  const auto expected = Matrix<int, 2, 2>{{{1, 0}, {0, 0}}};
  EXPECT_EQ(ZeroMatrix(input), expected);
}

TEST(zero_matrix_test, NoZeros_3x3) {
  const auto input = Matrix<int, 3, 3>{{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}};
  EXPECT_EQ(ZeroMatrix(input), input);
}

TEST(zero_matrix_test, Zeros_3x3_4) {
  const auto input = Matrix<int, 3, 3>{{{1, 2, 3}, {4, 0, 6}, {7, 8, 9}}};
  const auto expected = Matrix<int, 3, 3>{{{1, 0, 3}, {0, 0, 0}, {7, 0, 9}}};
  EXPECT_EQ(ZeroMatrix(input), expected);
}
