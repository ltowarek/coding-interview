// Delete Middle Node: Implement an algorithm to delete a node in the middle
// (i.e., any node but the first and last node, not necessarily the exact
// middle) of a singly linked list, given only access to that node.

#include "gtest/gtest.h"
#include <forward_list>

template <class T, class ForwardIterator>
void DeleteNode(std::forward_list<T> list, ForwardIterator node) {
  *node = *std::next(node);
  list.erase_after(node);
}

TEST(delete_middle_node_test, Example) {
  auto list = std::forward_list<int>{1, 2, 3, 4, 5};
  const auto expected = std::forward_list<int>{1, 2, 4, 5};
  auto node = std::find(list.begin(), list.end(), 3);
  DeleteNode(list, node);
  EXPECT_EQ(list, expected);
}
