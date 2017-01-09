// BST Sequences: A binary search tree was created by traversing through an
// array from left to right and inserting each element.Given a binary search
// tree with distinct elements, print all possible arrays that could have led to
// this tree.
// EXAMPLE
// Input:
//    2
//   /\
//  1  3
// Output: {2, 1, 3}, {2, 3, 1}

#include "gtest/gtest.h"
#include <algorithm>

template <class T> struct Node {
  Node(T _data) : data(_data), left(nullptr), right(nullptr) {}
  T data;
  std::unique_ptr<Node<T>> left;
  std::unique_ptr<Node<T>> right;
};

enum POSITIONS_FROM { LEFT = 0, RIGHT = 1 };

template <class T>
std::vector<std::vector<T>> BSTSequences(const Node<T> *root) {
  auto output = std::vector<std::vector<T>>();

  if (root == nullptr) {
    output.push_back({});
    return output;
  }

  if (root->left == nullptr && root->right == nullptr) {
    output.push_back({root->data});
    return output;
  }

  const auto left_sequences = BSTSequences(root->left.get());
  const auto right_sequences = BSTSequences(root->right.get());

  auto positions = std::vector<POSITIONS_FROM>(left_sequences[0].size(),
                                               POSITIONS_FROM::LEFT);
  positions.insert(positions.end(), right_sequences[0].size(),
                   POSITIONS_FROM::RIGHT);

  for (const auto left_sequence : left_sequences) {
    for (const auto right_sequence : right_sequences) {
      do {
        auto tmp_output = std::vector<T>(positions.size() + 1);
        tmp_output[0] = root->data;
        auto left_id = 0;
        auto right_id = 0;
        for (auto i = 0; i < positions.size(); ++i) {
          tmp_output[i + 1] = (positions[i] == POSITIONS_FROM::LEFT)
                                  ? left_sequence[left_id++]
                                  : right_sequence[right_id++];
        }
        output.push_back(tmp_output);
      } while (std::next_permutation(positions.begin(), positions.end()));
    }
  }

  return output;
}

TEST(bst_sequences_test, EmptyTree) {
  auto node_1 = std::unique_ptr<Node<int>>(nullptr);
  const auto expected = std::vector<std::vector<int>>{{}};
  EXPECT_EQ(BSTSequences(node_1.get()), expected);
}

TEST(bst_sequences_test, Depth1) {
  auto node_1 = std::make_unique<Node<int>>(1);
  const auto expected = std::vector<std::vector<int>>{{1}};
  EXPECT_EQ(BSTSequences(node_1.get()), expected);
}

TEST(bst_sequences_test, Depth2) {
  auto node_1 = std::make_unique<Node<int>>(1);
  auto node_2 = std::make_unique<Node<int>>(2);
  auto node_3 = std::make_unique<Node<int>>(3);

  node_2->left = std::move(node_1);
  node_2->right = std::move(node_3);

  const auto expected = std::vector<std::vector<int>>{{2, 1, 3}, {2, 3, 1}};
  EXPECT_EQ(BSTSequences(node_2.get()), expected);
}

TEST(bst_sequences_test, Depth3) {
  auto node_50 = std::make_unique<Node<int>>(50);
  auto node_20 = std::make_unique<Node<int>>(20);
  auto node_60 = std::make_unique<Node<int>>(60);
  auto node_25 = std::make_unique<Node<int>>(25);
  auto node_10 = std::make_unique<Node<int>>(10);
  auto node_70 = std::make_unique<Node<int>>(70);

  node_20->left = std::move(node_10);
  node_20->right = std::move(node_25);
  node_60->right = std::move(node_70);
  node_50->left = std::move(node_20);
  node_50->right = std::move(node_60);

  const auto expected = std::vector<std::vector<int>>{
      {50, 20, 10, 25, 60, 70}, {50, 20, 10, 60, 25, 70},
      {50, 20, 10, 60, 70, 25}, {50, 20, 60, 10, 25, 70},
      {50, 20, 60, 10, 70, 25}, {50, 20, 60, 70, 10, 25},
      {50, 60, 20, 10, 25, 70}, {50, 60, 20, 10, 70, 25},
      {50, 60, 20, 70, 10, 25}, {50, 60, 70, 20, 10, 25},
      {50, 20, 25, 10, 60, 70}, {50, 20, 25, 60, 10, 70},
      {50, 20, 25, 60, 70, 10}, {50, 20, 60, 25, 10, 70},
      {50, 20, 60, 25, 70, 10}, {50, 20, 60, 70, 25, 10},
      {50, 60, 20, 25, 10, 70}, {50, 60, 20, 25, 70, 10},
      {50, 60, 20, 70, 25, 10}, {50, 60, 70, 20, 25, 10}};
  EXPECT_EQ(BSTSequences(node_50.get()), expected);
}
