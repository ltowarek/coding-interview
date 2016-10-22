// Palindrome Permutation: Given a string, write a function to check if it is a
// permutation of a palindrome. A palindrome is a word or phrase that is the
// same forwards and backwards. A permutation is a rearrangement of letters. The
// palindrome does not need to be limited to just dictionary words.

#include "gtest/gtest.h"

bool IsPalindromePermutation(const std::string &str) {
  auto chars = std::map<char, int>();
  for (auto c : str) {
    const auto lower_c = std::tolower(c);
    if (lower_c == ' ') {
      continue;
    }
    if (chars.count(lower_c) != 1) {
      chars[lower_c] = 1;
    } else {
      chars[lower_c]++;
    }
  }

  auto odd_chars = 0;
  for (const auto &kv : chars) {
    if (kv.second % 2 != 0) {
      odd_chars++;
    }
  }

  return odd_chars <= 1;
}

TEST(palindrome_permutation_test, EmptyString) {
  EXPECT_EQ(IsPalindromePermutation(""), true);
}

TEST(palindrome_permutation_test, OneChar) {
  EXPECT_EQ(IsPalindromePermutation("a"), true);
}

TEST(palindrome_permutation_test, TwoChars_NotPalindrome) {
  EXPECT_EQ(IsPalindromePermutation("ab"), false);
}

TEST(palindrome_permutation_test, TwoChars_Palindrome) {
  EXPECT_EQ(IsPalindromePermutation("aa"), true);
}

TEST(palindrome_permutation_test, ThreeChars_NotPalindrome) {
  EXPECT_EQ(IsPalindromePermutation("abc"), false);
}

TEST(palindrome_permutation_test, ThreeChars_Palindrome) {
  EXPECT_EQ(IsPalindromePermutation("aba"), true);
}

TEST(palindrome_permutation_test, ThreeCharsWithSpace_NotPalindrome) {
  EXPECT_EQ(IsPalindromePermutation("a b c"), false);
}

TEST(palindrome_permutation_test, ThreeCharsWithSpace_Palindrome) {
  EXPECT_EQ(IsPalindromePermutation("a b a"), true);
}

TEST(palindrome_permutation_test, Example) {
  EXPECT_EQ(IsPalindromePermutation("Tact Coa"), true);
}
