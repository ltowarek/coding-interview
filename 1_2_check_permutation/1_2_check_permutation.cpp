// Check Permutation: Given two strings, write a method to decide if one is a
// permutation of the other.

#include "gtest/gtest.h"

#include <algorithm>

bool CheckPermutation(const std::string &s1, const std::string &s2) {
  if (s1.size() != s2.size()) {
    return false;
  }
  auto sorted_s1 = s1;
  std::sort(sorted_s1.begin(), sorted_s1.end());
  auto sorted_s2 = s2;
  std::sort(sorted_s2.begin(), sorted_s2.end());
  return sorted_s1 == sorted_s2;
}

TEST(check_permutation_test, EmptyStrings) {
  EXPECT_EQ(CheckPermutation("", ""), true);
}

TEST(check_permutation_test, FirstEmptyString) {
  EXPECT_EQ(CheckPermutation("", "abc"), false);
}

TEST(check_permutation_test, SecondEmptyString) {
  EXPECT_EQ(CheckPermutation("abc", ""), false);
}

TEST(check_permutation_test, DifferentSizes) {
  EXPECT_EQ(CheckPermutation("abc", "abcd"), false);
}

TEST(check_permutation_test, NotPermutation) {
  EXPECT_EQ(CheckPermutation("abc", "abd"), false);
  EXPECT_EQ(CheckPermutation("abc", "dfe"), false);
  EXPECT_EQ(CheckPermutation("abc", "xyz"), false);
  EXPECT_EQ(CheckPermutation("aabc", "abc"), false);
  EXPECT_EQ(CheckPermutation("ABC", "abc"), false);
}

TEST(check_permutation_test, Permutation) {
  EXPECT_EQ(CheckPermutation("abc", "cba"), true);
  EXPECT_EQ(CheckPermutation("abc", "bac"), true);
  EXPECT_EQ(CheckPermutation("abc", "acb"), true);
  EXPECT_EQ(CheckPermutation("aabc", "caab"), true);
  EXPECT_EQ(CheckPermutation("ABC", "CBA"), true);
}
