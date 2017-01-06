// Remove Dups: Write code to remove duplicates from an unsorted linked list.
// How would you solve this problem if a temporary buffer is not allowed?

#include "gtest/gtest.h"
#include <forward_list>

template <class T> void RemoveDuplicates(std::forward_list<T> &list) {
  auto current = list.begin();
  while (current != list.end()) {
    auto next = current;
    while (std::next(next) != list.end()) {
      if (*std::next(next) == *current) {
        list.erase_after(next);
      } else {
        next++;
      }
    }
    current++;
  }
}

TEST(remove_dups_test, EmptyList) {
  auto list = std::forward_list<int>{};
  const auto expected = std::forward_list<int>{};
  RemoveDuplicates(list);
  EXPECT_EQ(list, expected);
}

TEST(remove_dups_test, NoDuplicates_1_Element) {
  auto list = std::forward_list<int>{3};
  const auto expected = list;
  RemoveDuplicates(list);
  EXPECT_EQ(list, list);
}

TEST(remove_dups_test, NoDuplicates_2_Elements) {
  auto list = std::forward_list<int>{3, 2};
  const auto expected = list;
  RemoveDuplicates(list);
  EXPECT_EQ(list, list);
}

TEST(remove_dups_test, NoDuplicates_3_Elements) {
  auto list = std::forward_list<int>{3, 2, 4};
  const auto expected = list;
  RemoveDuplicates(list);
  EXPECT_EQ(list, list);
}

TEST(remove_dups_test, Duplicates_2_Elements) {
  auto list = std::forward_list<int>{3, 3};
  const auto expected = std::forward_list<int>{3};
  RemoveDuplicates(list);
  EXPECT_EQ(list, expected);
}

TEST(remove_dups_test, Duplicates_3_Elements) {
  auto list = std::forward_list<int>{3, 3, 3};
  const auto expected = std::forward_list<int>{3};
  RemoveDuplicates(list);
  EXPECT_EQ(list, expected);
}

TEST(remove_dups_test, Duplicates_6_Elements) {
  auto list = std::forward_list<int>{3, 2, 4, 2, 5, 3};
  const auto expected = std::forward_list<int>{3, 2, 4, 5};
  RemoveDuplicates(list);
  EXPECT_EQ(list, expected);
}
