// Is Unique: Implement an algorithm to determine if a string has all unique
// characters. What if you cannot use additional data structures?

#include "gtest/gtest.h"

#include <algorithm>

bool IsUnique(const std::string &s) {
  auto sorted = s;
  std::sort(sorted.begin(), sorted.end());
  for (int i = 1; i < sorted.size(); ++i) {
    if (sorted[i - 1] == sorted[i]) {
      return false;
    }
  }
  return true;
}

TEST(is_unique_test, EmptyString) { EXPECT_EQ(IsUnique(""), true); }

TEST(is_unique_test, 2Chars_Duplicated) { EXPECT_EQ(IsUnique("aa"), false); }

TEST(is_unique_test, 2Chars_Unique) { EXPECT_EQ(IsUnique("ab"), true); }

TEST(is_unique_test, 4Chars_Duplicated) { EXPECT_EQ(IsUnique("aaaa"), false); }

TEST(is_unique_test, 4Chars_Unique) { EXPECT_EQ(IsUnique("abcd"), true); }

TEST(is_unique_test, 4Chars_Duplicated_Start_End) {
  EXPECT_EQ(IsUnique("abca"), false);
}
