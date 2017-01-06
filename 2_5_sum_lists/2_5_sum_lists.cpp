// Sum Lists: You have two numbers represented by a linked list, where each node
// contains a single digit. The digits are stored in reverse order, such that
// the 1's digit is at the head of the list. Write a function that adds the two
// numbers and returns the sum as a linked list.
// Suppose the digits are stored in forward order. Repeat the above problem.

#include "gtest/gtest.h"
#include <forward_list>

template <class T> T GetNumber(const std::forward_list<T> &list) {
  auto output = 0;
  auto base = 1;
  auto current = list.begin();
  while (current != list.end()) {
    output += *current * base;
    base *= 10;
    current++;
  }
  return output;
}

template <class T> std::forward_list<T> GetList(const T number) {
  auto output = std::forward_list<T>{};
  auto base = number;
  do {
    output.push_front(base % 10);
    base /= 10;
  } while (base > 0);
  output.reverse();
  return output;
}

template <class T>
std::forward_list<T> SumLists(const std::forward_list<T> &l1,
                              const std::forward_list<T> &l2) {
  if (l1.empty() && l2.empty()) {
    return std::forward_list<T>{};
  }
  const auto l1_number = GetNumber(l1);
  const auto l2_number = GetNumber(l2);
  return GetList(l1_number + l2_number);
}

template <class T> size_t Length(const std::forward_list<T> &list) {
  auto output = 0;
  auto current = list.begin();
  while (current != list.end()) {
    output++;
    current++;
  }
  return output;
}

template <class T>
void AddPadding(std::forward_list<T> &list, const size_t padding) {
  for (auto i = 0; i < padding; ++i) {
    list.push_front(0);
  }
}

template <class T, class ForwardIterator>
std::pair<std::forward_list<T>, T>
SumListsRecursively(const std::forward_list<T> &l1, const ForwardIterator &n1,
                    const std::forward_list<T> &l2, const ForwardIterator &n2) {
  if (n1 == l1.end() && n2 == l2.end()) {
    return std::make_pair(std::forward_list<T>{}, 0);
  }

  auto result = SumListsRecursively(l1, std::next(n1), l2, std::next(n2));
  auto &sum = result.first;
  auto &carry = result.second;

  T value = carry + *n1 + *n2;
  sum.push_front(value % 10);
  carry = value / 10;

  return result;
}

template <class T>
std::forward_list<T> SumListsInForwardOrder(const std::forward_list<T> l1,
                                            const std::forward_list<T> l2) {
  const auto length_l1 = Length(l1);
  const auto length_l2 = Length(l2);

  auto tmp_l1 = l1;
  auto tmp_l2 = l2;
  if (length_l1 < length_l2) {
    AddPadding(tmp_l1, length_l2 - length_l1);
  } else {
    AddPadding(tmp_l2, length_l1 - length_l2);
  }

  auto result =
      SumListsRecursively(tmp_l1, tmp_l1.begin(), tmp_l2, tmp_l2.begin());
  auto &sum = result.first;
  auto &carry = result.second;

  if (carry) {
    sum.push_front(carry);
  }

  return sum;
}

TEST(sum_lists_test, EmptyLists) {
  const auto l1 = std::forward_list<int>{};
  const auto l2 = std::forward_list<int>{};
  const auto expected = std::forward_list<int>{};
  EXPECT_EQ(SumLists(l1, l2), expected);
}

TEST(sum_lists_test, FirstEmptyList) {
  const auto l1 = std::forward_list<int>{};
  const auto l2 = std::forward_list<int>{1, 2, 3};
  const auto expected = std::forward_list<int>{1, 2, 3};
  EXPECT_EQ(SumLists(l1, l2), expected);
}

TEST(sum_lists_test, SecondEmptyList) {
  const auto l1 = std::forward_list<int>{1, 2, 3};
  const auto l2 = std::forward_list<int>{};
  const auto expected = std::forward_list<int>{1, 2, 3};
  EXPECT_EQ(SumLists(l1, l2), expected);
}

TEST(sum_lists_test, Zeroes) {
  const auto l1 = std::forward_list<int>{0};
  const auto l2 = std::forward_list<int>{0};
  const auto expected = std::forward_list<int>{0};
  EXPECT_EQ(SumLists(l1, l2), expected);
}

TEST(sum_lists_test, Sum_OneElement) {
  const auto l1 = std::forward_list<int>{1};
  const auto l2 = std::forward_list<int>{2};
  const auto expected = std::forward_list<int>{3};
  EXPECT_EQ(SumLists(l1, l2), expected);
}

TEST(sum_lists_test, Sum_OneElement_WithOverflow) {
  const auto l1 = std::forward_list<int>{9};
  const auto l2 = std::forward_list<int>{3};
  const auto expected = std::forward_list<int>{2, 1};
  EXPECT_EQ(SumLists(l1, l2), expected);
}

TEST(sum_lists_test, Sum_TwoElements) {
  const auto l1 = std::forward_list<int>{4, 5};
  const auto l2 = std::forward_list<int>{5, 2};
  const auto expected = std::forward_list<int>{9, 7};
  EXPECT_EQ(SumLists(l1, l2), expected);
}

TEST(sum_lists_test, Sum_TwoElements_WithOverflow) {
  const auto l1 = std::forward_list<int>{8, 6};
  const auto l2 = std::forward_list<int>{4, 7};
  const auto expected = std::forward_list<int>{2, 4, 1};
  EXPECT_EQ(SumLists(l1, l2), expected);
}

TEST(sum_lists_test, DifferentSizes) {
  const auto l1 = std::forward_list<int>{3, 6, 1};
  const auto l2 = std::forward_list<int>{4};
  const auto expected = std::forward_list<int>{7, 6, 1};
  EXPECT_EQ(SumLists(l1, l2), expected);
}

TEST(sum_lists_test, Example) {
  const auto l1 = std::forward_list<int>{7, 1, 6};
  const auto l2 = std::forward_list<int>{5, 9, 2};
  const auto expected = std::forward_list<int>{2, 1, 9};
  EXPECT_EQ(SumLists(l1, l2), expected);
}

TEST(sum_lists_in_forward_order_test, EmptyLists) {
  const auto l1 = std::forward_list<int>{};
  const auto l2 = std::forward_list<int>{};
  const auto expected = std::forward_list<int>{};
  EXPECT_EQ(SumListsInForwardOrder(l1, l2), expected);
}

TEST(sum_lists_in_forward_order_test, FirstEmptyList) {
  const auto l1 = std::forward_list<int>{};
  const auto l2 = std::forward_list<int>{1, 2, 3};
  const auto expected = std::forward_list<int>{1, 2, 3};
  EXPECT_EQ(SumListsInForwardOrder(l1, l2), expected);
}

TEST(sum_lists_in_forward_order_test, SecondEmptyList) {
  const auto l1 = std::forward_list<int>{1, 2, 3};
  const auto l2 = std::forward_list<int>{};
  const auto expected = std::forward_list<int>{1, 2, 3};
  EXPECT_EQ(SumListsInForwardOrder(l1, l2), expected);
}

TEST(sum_lists_in_forward_order_test, Zeroes) {
  const auto l1 = std::forward_list<int>{0};
  const auto l2 = std::forward_list<int>{0};
  const auto expected = std::forward_list<int>{0};
  EXPECT_EQ(SumListsInForwardOrder(l1, l2), expected);
}

TEST(sum_lists_in_forward_order_test, Sum_OneElement) {
  const auto l1 = std::forward_list<int>{1};
  const auto l2 = std::forward_list<int>{2};
  const auto expected = std::forward_list<int>{3};
  EXPECT_EQ(SumListsInForwardOrder(l1, l2), expected);
}

TEST(sum_lists_in_forward_order_test, Sum_OneElement_WithOverflow) {
  const auto l1 = std::forward_list<int>{9};
  const auto l2 = std::forward_list<int>{3};
  const auto expected = std::forward_list<int>{1, 2};
  EXPECT_EQ(SumListsInForwardOrder(l1, l2), expected);
}

TEST(sum_lists_in_forward_order_test, Sum_TwoElements) {
  const auto l1 = std::forward_list<int>{4, 5};
  const auto l2 = std::forward_list<int>{5, 2};
  const auto expected = std::forward_list<int>{9, 7};
  EXPECT_EQ(SumListsInForwardOrder(l1, l2), expected);
}

TEST(sum_lists_in_forward_order_test, Sum_TwoElements_WithOverflow) {
  const auto l1 = std::forward_list<int>{8, 6};
  const auto l2 = std::forward_list<int>{4, 7};
  const auto expected = std::forward_list<int>{1, 3, 3};
  EXPECT_EQ(SumListsInForwardOrder(l1, l2), expected);
}

TEST(sum_lists_in_forward_order_test, DifferentSizes) {
  const auto l1 = std::forward_list<int>{3, 6, 1};
  const auto l2 = std::forward_list<int>{4};
  const auto expected = std::forward_list<int>{3, 6, 5};
  EXPECT_EQ(SumListsInForwardOrder(l1, l2), expected);
}

TEST(sum_lists_in_forward_order_test, Example) {
  const auto l1 = std::forward_list<int>{6, 1, 7};
  const auto l2 = std::forward_list<int>{2, 9, 5};
  const auto expected = std::forward_list<int>{9, 1, 2};
  EXPECT_EQ(SumListsInForwardOrder(l1, l2), expected);
}
