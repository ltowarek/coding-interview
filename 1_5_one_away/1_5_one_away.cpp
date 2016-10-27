// One Away: There are three types of edits that can be performed on strings:
// insert a character, remove a character, or replace a character. Given two
// strings, write a function to check if they are one edit (or zero edits) away.

#include "gtest/gtest.h"

bool IsOneAway(const std::string &s1, const std::string &s2) {
  const auto abs_diff = s1.size() > s2.size() ? s1.size() - s2.size() :
                                                s2.size() - s1.size();
  if (abs_diff > 1) {
    return false;
  }

  const auto longer_string = s1.size() > s2.size() ? s1 : s2;
  const auto shorter_string = s1.size() > s2.size() ? s2 : s1;

  auto longer_string_index = size_t{0};
  auto shorter_string_index = size_t{0};

  auto diff_found = false;

  while (longer_string_index < longer_string.size() &&
         shorter_string_index < shorter_string.size()) {
    if (longer_string[longer_string_index] != shorter_string[shorter_string_index]) {
      if (diff_found) {
        return false;
      } else {
        diff_found = true;
      }

      if (longer_string.size() == shorter_string.size()) {
        shorter_string_index++;
      }
    } else {
      shorter_string_index++;
    }
    longer_string_index++;
  }

  return true;
}

TEST(one_away_test, EmptyStrings) {
  EXPECT_EQ(IsOneAway("", ""), true);
}

TEST(one_away_test, Insert_1) {
  EXPECT_EQ(IsOneAway("abc", "abcd"), true);
}

TEST(one_away_test, Insert_2) {
  EXPECT_EQ(IsOneAway("ab", "abcd"), false);
}

TEST(one_away_test, Remove_1) {
  EXPECT_EQ(IsOneAway("abcd", "abc"), true);
}

TEST(one_away_test, Remove_2) {
  EXPECT_EQ(IsOneAway("abcd", "ab"), false);
}

TEST(one_away_test, Replace_1) {
  EXPECT_EQ(IsOneAway("abcd", "abce"), true);
}

TEST(one_away_test, Replace_2) {
  EXPECT_EQ(IsOneAway("abcd", "abef"), false);
}

TEST(one_away_test, Insert_1_Replace_1) {
  EXPECT_EQ(IsOneAway("abc", "xbcd"), false);
}

TEST(one_away_test, Example_1) {
  EXPECT_EQ(IsOneAway("pale", "ple"), true);
}

TEST(one_away_test, Example_2) {
  EXPECT_EQ(IsOneAway("pales", "pale"), true);
}

TEST(one_away_test, Example_3) {
  EXPECT_EQ(IsOneAway("pale", "bale"), true);
}

TEST(one_away_test, Example_4) {
  EXPECT_EQ(IsOneAway("pale", "bae"), false);
}
