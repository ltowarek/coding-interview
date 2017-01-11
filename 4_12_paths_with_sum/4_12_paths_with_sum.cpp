// Paths with Sum: You are given a binary tree in which each node contains an
// integer value (which might be positive or negative). Design an algorithm to
// count the number of paths that sum to a given value. The path does not need
// to start or end at the root or a leaf, but it must go downwards (traveling
// only from parent nodes to child nodes).

#include "gtest/gtest.h"
#include <map>

template <class T> struct Node {
  Node(T _data) : data(_data), left(nullptr), right(nullptr) {}

  T data;
  std::unique_ptr<Node<T>> left;
  std::unique_ptr<Node<T>> right;
};

template <class T>
size_t CountPathsWithSum(const Node<T> *node, T target_sum, T running_sum,
                         std::map<T, size_t> path_count) {
  if (node == nullptr) {
    return 0;
  }

  running_sum += node->data;
  const auto sum = running_sum - target_sum;
  auto total_paths = path_count[sum];

  if (running_sum == target_sum) {
    total_paths++;
  }

  path_count[sum]++;
  total_paths +=
      CountPathsWithSum(node->left.get(), target_sum, running_sum, path_count);
  total_paths +=
      CountPathsWithSum(node->right.get(), target_sum, running_sum, path_count);
  path_count[sum] = path_count[sum] > 0 ? path_count[sum] - 1 : 0;

  return total_paths;
}

template <class T>
size_t PathsWithSum(const Node<T> *node, const T target_sum) {
  return CountPathsWithSum(node, target_sum, 0, std::map<T, size_t>());
}

TEST(paths_with_sum_test, Depth1_EmptyTree) {
  EXPECT_EQ(PathsWithSum<int>(nullptr, 1), 0);
}

TEST(paths_with_sum_test, Depth1_WithPaths) {
  const auto node_1 = std::make_unique<Node<int>>(1);

  EXPECT_EQ(PathsWithSum(node_1.get(), 1), 1);
  EXPECT_EQ(PathsWithSum(node_1.get(), 2), 0);
}

TEST(paths_with_sum_test, Depth2_SameNodes) {
  auto node_1 = std::make_unique<Node<int>>(1);
  auto node_2 = std::make_unique<Node<int>>(1);
  auto node_3 = std::make_unique<Node<int>>(1);

  node_1->left = std::move(node_2);
  node_1->right = std::move(node_3);

  EXPECT_EQ(PathsWithSum(node_1.get(), 1), 1);
  EXPECT_EQ(PathsWithSum(node_1.get(), 2), 2);
  EXPECT_EQ(PathsWithSum(node_1->left.get(), 1), 1);
  EXPECT_EQ(PathsWithSum(node_1->right.get(), 1), 1);
  EXPECT_EQ(PathsWithSum(node_1->left.get(), 2), 0);
  EXPECT_EQ(PathsWithSum(node_1->right.get(), 2), 0);
}

TEST(paths_with_sum_test, Depth2_DifferentNodes) {
  auto node_1 = std::make_unique<Node<int>>(1);
  auto node_2 = std::make_unique<Node<int>>(2);
  auto node_3 = std::make_unique<Node<int>>(3);

  node_1->left = std::move(node_2);
  node_1->right = std::move(node_3);

  EXPECT_EQ(PathsWithSum(node_1.get(), 1), 1);
  EXPECT_EQ(PathsWithSum(node_1.get(), 2), 0);
  EXPECT_EQ(PathsWithSum(node_1.get(), 3), 1);
  EXPECT_EQ(PathsWithSum(node_1.get(), 4), 1);
  EXPECT_EQ(PathsWithSum(node_1.get(), 0), 0);
  EXPECT_EQ(PathsWithSum(node_1->left.get(), 3), 0);
  EXPECT_EQ(PathsWithSum(node_1->right.get(), 3), 1);
}
