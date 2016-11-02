// String Rotation: Assume you have a method isSubstring which checks if one
// word is a substring of another. Given two strings, s1 and s2, write code to
// check if s2 is a rotation of s1 using only one call to isSubstring.

#include "gtest/gtest.h"

bool isSubstring(const std::string &s1, const std::string &s2) {
  return s1.find(s2) != std::string::npos;
}

bool IsRotation(const std::string &s1, const std::string &s2) {
  if (s1.size() == s2.size() && s1.size() > 0) {
    const auto tmp = s1 + s1;
    return isSubstring(tmp, s2);
  }
  return false;
}

TEST(string_rotation_test, EmptyString) {
  EXPECT_EQ(IsRotation("", ""), false);
}

TEST(string_rotation_test, EmptyFirstString) {
  EXPECT_EQ(IsRotation("", "erbottlewat"), false);
}

TEST(string_rotation_test, EmptySecondString) {
  EXPECT_EQ(IsRotation("waterbottle", ""), false);
}

TEST(string_rotation_test, DifferentLengths) {
  EXPECT_EQ(IsRotation("water", "erbottlewat"), false);
}

TEST(string_rotation_test, NoRotation) {
  EXPECT_EQ(IsRotation("abcd", "bcad"), false);
}

TEST(string_rotation_test, Example) {
  EXPECT_EQ(IsRotation("waterbottle", "erbottlewat"), true);
}
