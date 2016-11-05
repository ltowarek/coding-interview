// Partition: Write code to partition a linked list around a value x, such that
// all nodes less than x come before all nodes greater than or equal to x.
// If x is contained within the list, the values of x only need to be after the
// elements less than x. The partition element x can appear anywhere in the
// "right partition"; it does not need to appear between the left and right
// partitions.

#include <forward_list>
#include "gtest/gtest.h"

template <class T>
std::forward_list<T> Partition(const std::forward_list<T> list, const size_t partition) {
  auto output = std::forward_list<T>{};
  auto current = list.begin();
  auto tail = output.begin();

  while (current != list.end()) {
    if (output.empty()) {
      output.push_front(*current);
      tail = output.begin();
    } else if (*current < partition) {
      output.push_front(*current);
    } else {
      tail = output.insert_after(tail, *current);
    }
    current++;
  }

  return output;
}

template <class T>
bool IsPartitioned(const std::forward_list<T> list, const size_t partition) {
  auto current = list.begin();
  auto reached_partition = false;
  while (current != list.end()) {
    if (*current >= partition) {
      reached_partition = true;
    }
    if (reached_partition && *current < partition) {
      return false;
    }
    current++;
  }
  return true;
}

TEST(partition_test, EmptyList) {
  auto list = std::forward_list<int>{};
  const auto output = Partition(list, 5);
  EXPECT_TRUE(IsPartitioned(output, 5));
}

TEST(partition_test, NoPartitionRequired_FirstElement) {
  auto list = std::forward_list<int>{1, 2, 3, 4, 5};
  const auto output = Partition(list, 1);
  EXPECT_TRUE(IsPartitioned(output, 1));
}

TEST(partition_test, NoPartitionRequired_LastElement) {
  auto list = std::forward_list<int>{1, 2, 3, 4, 5};
  const auto output = Partition(list, 5);
  EXPECT_TRUE(IsPartitioned(output, 5));
}

TEST(partition_test, NoPartitionRequired_MiddleElement) {
  auto list = std::forward_list<int>{1, 2, 3, 4, 5};
  const auto output = Partition(list, 3);
  EXPECT_TRUE(IsPartitioned(output, 3));
}

TEST(partition_test, PartitionRequired_MiddleElement) {
  auto list = std::forward_list<int>{4, 5, 3, 1, 2};
  const auto output = Partition(list, 3);
  EXPECT_TRUE(IsPartitioned(output, 3));
}

TEST(partition_test, PartitionRequired_NoPartitionElement) {
  auto list = std::forward_list<int>{4, 5, 6, 1, 2};
  const auto output = Partition(list, 3);
  EXPECT_TRUE(IsPartitioned(output, 3));
}

TEST(partition_test, PartitionRequired_MultiplePartitionElements) {
  auto list = std::forward_list<int>{6, 3, 7, 1, 3, 2, 2, 8, 9, 3, 4};
  const auto output = Partition(list, 3);
  EXPECT_TRUE(IsPartitioned(output, 3));
}

TEST(partition_test, Example) {
  auto list = std::forward_list<int>{3, 5, 8, 5, 10, 2, 1};
  const auto output = Partition(list, 5);
  EXPECT_TRUE(IsPartitioned(output, 5));
}
