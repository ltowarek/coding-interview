// Validate BST: Implement a function to check if a binary tree is a
// binary search tree.

#include "gtest/gtest.h"

template <class T>
struct Node {
  Node(T _data): data(_data), left(nullptr), right(nullptr) {}
  T data;
  std::unique_ptr<Node<T>> left;
  std::unique_ptr<Node<T>> right;
};

template <class T>
struct BinaryTree {
  BinaryTree(): root(nullptr) {}
  BinaryTree(std::unique_ptr<Node<T>> _root): root(std::move(_root)) {}

  std::unique_ptr<Node<T>> root;
};

template <class T>
bool ValidateBST(const Node<T> *node, const Node<T> *min, const Node<T> *max) {
  if (node == nullptr) {
    return true;
  }

  if ((min != nullptr && node->data <= min->data) ||
      (max != nullptr && node->data > max->data)) {
        return false;
  }

  if ((!ValidateBST(node->left.get(), min, node)) ||
       !ValidateBST(node->right.get(), node, max)) {
    return false;
  }

  return true;
}

template <class T>
bool ValidateBST(const BinaryTree<T> &input) {
  return ValidateBST<T>(input.root.get(), nullptr, nullptr);
}

TEST(validate_bst_test, EmptyTree) {
  const auto input = BinaryTree<int>();
  EXPECT_EQ(ValidateBST(input), true);
}

TEST(validate_bst_test, Depth1_BST) {
  auto n0 = std::make_unique<Node<int>>(0);
  const auto input = BinaryTree<int>(std::move(n0));
  EXPECT_EQ(ValidateBST(input), true);
}

TEST(validate_bst_test, Depth2_BST) {
  auto n0 = std::make_unique<Node<int>>(1);
  auto n1 = std::make_unique<Node<int>>(0);
  auto n2 = std::make_unique<Node<int>>(2);

  n0->left = std::move(n1);
  n0->right = std::move(n2);

  const auto input = BinaryTree<int>(std::move(n0));
  EXPECT_EQ(ValidateBST(input), true);
}

TEST(validate_bst_test, Depth2_Not_BST) {
  auto n0 = std::make_unique<Node<int>>(2);
  auto n1 = std::make_unique<Node<int>>(0);
  auto n2 = std::make_unique<Node<int>>(1);

  n0->left = std::move(n1);
  n0->right = std::move(n2);

  const auto input = BinaryTree<int>(std::move(n0));
  EXPECT_EQ(ValidateBST(input), false);
}

TEST(validate_bst_test, Depth2_Equal_Values_BST) {
  auto n0 = std::make_unique<Node<int>>(1);
  auto n1 = std::make_unique<Node<int>>(1);
  auto n2 = std::make_unique<Node<int>>(2);

  n0->left = std::move(n1);
  n0->right = std::move(n2);

  const auto input = BinaryTree<int>(std::move(n0));
  EXPECT_EQ(ValidateBST(input), true);
}

TEST(validate_bst_test, Depth2_Equal_Values_Not_BST) {
  auto n0 = std::make_unique<Node<int>>(1);
  auto n1 = std::make_unique<Node<int>>(0);
  auto n2 = std::make_unique<Node<int>>(1);

  n0->left = std::move(n1);
  n0->right = std::move(n2);

  const auto input = BinaryTree<int>(std::move(n0));
  EXPECT_EQ(ValidateBST(input), false);
}

TEST(validate_bst_test, Depth3_BST) {
  auto n0 = std::make_unique<Node<int>>(20);
  auto n1 = std::make_unique<Node<int>>(10);
  auto n2 = std::make_unique<Node<int>>(30);
  auto n3 = std::make_unique<Node<int>>(15);

  n1->right = std::move(n3);
  n0->left = std::move(n1);
  n0->right = std::move(n2);

  const auto input = BinaryTree<int>(std::move(n0));
  EXPECT_EQ(ValidateBST(input), true);
}

TEST(validate_bst_test, Depth3_Not_BST) {
  auto n0 = std::make_unique<Node<int>>(20);
  auto n1 = std::make_unique<Node<int>>(10);
  auto n2 = std::make_unique<Node<int>>(30);
  auto n3 = std::make_unique<Node<int>>(25);

  n1->right = std::move(n3);
  n0->left = std::move(n1);
  n0->right = std::move(n2);

  const auto input = BinaryTree<int>(std::move(n0));
  EXPECT_EQ(ValidateBST(input), false);
}
