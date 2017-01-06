// Palindrome: Implement a function to check if a linked list is a palindrome.

#include "gtest/gtest.h"
#include <forward_list>

template <class T> bool IsPalindrome(const std::forward_list<T> &list) {
  auto reversed = list;
  reversed.reverse();
  return list == reversed;
}

TEST(palindrome_test, EmptyList) {
  const auto list = std::forward_list<int>{};
  EXPECT_EQ(IsPalindrome(list), true);
}

TEST(palindrome_test, OneElementList) {
  const auto list = std::forward_list<int>{1};
  EXPECT_EQ(IsPalindrome(list), true);
}

TEST(palindrome_test, NoPalindrome) {
  const auto list = std::forward_list<int>{1, 2, 3};
  EXPECT_EQ(IsPalindrome(list), false);
}

TEST(palindrome_test, Palindrome) {
  const auto list = std::forward_list<int>{1, 2, 1};
  EXPECT_EQ(IsPalindrome(list), true);
}
