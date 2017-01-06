// Rotate Matrix: Given an image represented by an NxN matrix, where each pixel
// in the image is 4 bytes, write a method to rotate the image by 90 degrees.
// Can you do this in place?

#include "gtest/gtest.h"

template <class T, size_t N> using Matrix = std::array<std::array<T, N>, N>;

template <class T, size_t N> void Print(const Matrix<T, N> &m) {
  for (const auto &row : m) {
    for (const auto &value : row) {
      printf("%d ", value);
    }
    printf("\n");
  }
  printf("\n");
}

template <class T> void RotateValues(T &a, T &b, T &c, T &d) {
  auto tmp = a;
  a = d;
  d = c;
  c = b;
  b = tmp;
}

template <class T, size_t N> void RotateMatrix(Matrix<T, N> &m) {
  for (auto row = 0; row < N / 2; ++row) {
    for (auto column = 0; column < (N + 1) / 2; ++column) {
      RotateValues(m[row][column],                 // top left
                   m[column][N - 1 - row],         // top right
                   m[N - 1 - row][N - 1 - column], // bottom right
                   m[N - 1 - column][row]);        // bottom left
    }
  }
}

TEST(rotate_matrix_test, EmptyMatrix) {
  auto m = Matrix<int, 0>();
  const auto expected = Matrix<int, 0>();
  RotateMatrix(m);
  EXPECT_EQ(m, expected);
}

TEST(rotate_matrix_test, 1x1) {
  auto m = Matrix<int, 1>{{1}};
  const auto expected = Matrix<int, 1>{{1}};
  RotateMatrix(m);
  EXPECT_EQ(m, expected);
}

TEST(rotate_matrix_test, 2x2) {
  auto m = Matrix<int, 2>{{{1, 2}, {3, 4}}};
  const auto expected = Matrix<int, 2>{{{3, 1}, {4, 2}}};
  RotateMatrix(m);
  EXPECT_EQ(m, expected);
}

TEST(rotate_matrix_test, 3x3) {
  auto m = Matrix<int, 3>{{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}};
  const auto expected = Matrix<int, 3>{{{7, 4, 1}, {8, 5, 2}, {9, 6, 3}}};
  RotateMatrix(m);
  EXPECT_EQ(m, expected);
}

TEST(rotate_matrix_test, 4x4) {
  auto m = Matrix<int, 4>{
      {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}}};
  const auto expected = Matrix<int, 4>{
      {{13, 9, 5, 1}, {14, 10, 6, 2}, {15, 11, 7, 3}, {16, 12, 8, 4}}};
  RotateMatrix(m);
  EXPECT_EQ(m, expected);
}
