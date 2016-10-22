// URLify: Write a method to replace all spaces in a string with '%20'.
// You may assume that the string has sufficient space at the end to hold the
// additional characters, and that you are given the "true" length of the
// string. (Note: if implementing in Java, please use a character array so that
// you can perform this operation in place.)

#include "gtest/gtest.h"

void URLify(char str[], const size_t initial_str_size) {
  auto spaces_count = 0;
  for (int i = 0; i < initial_str_size; ++i) {
    if (str[i] == ' ') {
      spaces_count++;
    }
  }
  auto back_index = initial_str_size + spaces_count * 2;
  for (int i = initial_str_size - 1; i >= 0; --i) {
    if (str[i] == ' ') {
      str[back_index - 1] = '0';
      str[back_index - 2] = '2';
      str[back_index - 3] = '%';
      back_index -= 3;
    } else {
      str[back_index - 1] = str[i];
      back_index--;
    }
  }
}

TEST(urlify_test, EmptyString) {
  char str[] = "";
  URLify(str, 0);
  EXPECT_EQ(std::string(str), "");
}

TEST(urlify_test, OnlySpaces) {
  char str[] = "      ";
  URLify(str, 2);
  EXPECT_EQ(std::string(str), "%20%20");
}

TEST(urlify_test, Example) {
  char str[] = "Mr John Smith    ";
  URLify(str, 13);
  EXPECT_EQ(std::string(str), "Mr%20John%20Smith");
}
