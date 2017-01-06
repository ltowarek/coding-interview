// String Compression: Implement a method to perform basic string compression
// using the counts of repeated characters. For example, the string aabcccccaaa
// would become a2blc5a3 . If the "compressed" string would not become smaller
// than the original string, your method should return the original string. You
// can assume the string has only uppercase and lowercase letters (a - z).

#include "gtest/gtest.h"

std::string CompressString(const std::string &s) {
  auto output = std::string("");
  auto current_char_count = size_t{0};
  for (auto i = 0; i < s.size(); ++i) {
    current_char_count++;
    if (i + 1 >= s.size() || s[i] != s[i + 1]) {
      output += s[i];
      output += std::to_string(current_char_count);
      current_char_count = 0;
    }
  }
  return output.size() < s.size() ? output : s;
}

TEST(string_compression_test, EmptyString) {
  EXPECT_EQ(CompressString(""), "");
}

TEST(string_compression_test, SameString) {
  EXPECT_EQ(CompressString("abcd"), "abcd");
}

TEST(string_compression_test, Example) {
  EXPECT_EQ(CompressString("aabcccccaaa"), "a2b1c5a3");
}
