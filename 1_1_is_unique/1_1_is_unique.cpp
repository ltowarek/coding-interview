// Is Unique: Implement an algorithm to determine if a string has all unique
// characters. What if you cannot use additional data structures?

#include "gtest/gtest.h"

#include <algorithm>

bool is_unique(const std::string &s) {
  auto sorted = s;
  std::sort(sorted.begin(), sorted.end());
  for (int i = 1; i < sorted.size(); ++i) {
    if (sorted[i-1] == sorted[i]) {
      return false;
    }
  }
  return true;
}

TEST(is_unique_test, EmptyString) {
  EXPECT_EQ(is_unique(""), true);
}

TEST(is_unique_test, 2Chars_Duplicated) {
  EXPECT_EQ(is_unique("aa"), false);
}

TEST(is_unique_test, 2Chars_Unique) {
  EXPECT_EQ(is_unique("ab"), true);
}

TEST(is_unique_test, 4Chars_Duplicated) {
  EXPECT_EQ(is_unique("aaaa"), false);
}

TEST(is_unique_test, 4Chars_Unique) {
  EXPECT_EQ(is_unique("syen"), true);
}

TEST(is_unique_test, 4Chars_Duplicated_Start_End) {
  EXPECT_EQ(is_unique("abca"), false);
}
