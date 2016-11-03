// Return Kth to Last: Implement an algorithm to find the kth to last element
// of a singly linked list.

#include <forward_list>
#include <exception>
#include "gtest/gtest.h"

template <class T>
T KthToLast(const std::forward_list<T> &list, const size_t k) {
  if (list.empty()) {
    throw std::out_of_range("Empty list");
  }

  auto last = list.begin();
  for (auto i = 0; i < k; ++i) {
    if (last == list.end()) {
      throw std::out_of_range("k bigger than list size");
    }
    last++;
  }

  auto current = list.begin();
  while (last != list.end()) {
    current++;
    last++;
  }

  return *current;
}

TEST(kth_to_last_test, EmptyList) {
  const auto list = std::forward_list<int>{};
  ASSERT_THROW(KthToLast(list, 0), std::out_of_range);
}

TEST(kth_to_last_test, KBiggerThanSize) {
  const auto list = std::forward_list<int>{0, 1, 2, 3};
  ASSERT_THROW(KthToLast(list, 5), std::out_of_range);
}

TEST(kth_to_last_test, ReturnLastElement) {
  const auto list = std::forward_list<int>{0, 1, 2, 3};
  EXPECT_EQ(KthToLast(list, 1), 3);
}

TEST(kth_to_last_test, ReturnFirstElement) {
  const auto list = std::forward_list<int>{0, 1, 2, 3};
  EXPECT_EQ(KthToLast(list, 4), 0);
}
