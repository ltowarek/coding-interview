// Check Balanced: Implement a function to check if a binary tree is balanced.
// For the purposes of this question, a balanced tree is defined to be a tree
// such that the heights of the two subtrees of any node never differ by more
// than one.

#include "gtest/gtest.h"
#include <exception>

class NotBalancedTree : public std::exception {
public:
  virtual const char *what() const throw() { return "Tree is not balanced"; }
};

template <class T> struct Node {
  Node(T _data) : data(_data), left(nullptr), right(nullptr) {}
  T data;
  std::unique_ptr<Node<T>> left;
  std::unique_ptr<Node<T>> right;
};

template <class T> struct BinaryTree {
  BinaryTree() : root(nullptr) {}
  BinaryTree(std::unique_ptr<Node<T>> _root) : root(std::move(_root)) {}

  std::unique_ptr<Node<T>> root;
};

template <class T> int CheckBalanced(const Node<T> *node) {
  if (node == nullptr) {
    return -1;
  }

  int left_height = CheckBalanced(node->left.get());
  int right_height = CheckBalanced(node->right.get());

  int diff = left_height - right_height;
  if (std::abs(diff) > 1) {
    throw NotBalancedTree();
  } else {
    return std::max(left_height, right_height) + 1;
  }
}

template <class T> bool CheckBalanced(const BinaryTree<T> &input) {
  try {
    CheckBalanced(input.root.get());
    return true;
  } catch (NotBalancedTree &e) {
    return false;
  }
}

TEST(check_balanced_test, EmptyTree) {
  const auto input = BinaryTree<int>();
  EXPECT_EQ(CheckBalanced(input), true);
}

TEST(check_balanced_test, Depth1) {
  auto n0 = std::make_unique<Node<int>>(0);
  const auto input = BinaryTree<int>(std::move(n0));
  EXPECT_EQ(CheckBalanced(input), true);
}

TEST(check_balanced_test, Depth2) {
  auto n0 = std::make_unique<Node<int>>(0);
  auto n1 = std::make_unique<Node<int>>(1);
  auto n2 = std::make_unique<Node<int>>(2);

  n0->left = std::move(n1);
  n0->right = std::move(n2);

  const auto input = BinaryTree<int>(std::move(n0));
  EXPECT_EQ(CheckBalanced(input), true);
}

TEST(check_balanced_test, Depth3_Balanced) {
  auto n0 = std::make_unique<Node<int>>(0);
  auto n1 = std::make_unique<Node<int>>(1);
  auto n2 = std::make_unique<Node<int>>(2);
  auto n3 = std::make_unique<Node<int>>(3);
  auto n4 = std::make_unique<Node<int>>(4);
  auto n5 = std::make_unique<Node<int>>(5);
  auto n6 = std::make_unique<Node<int>>(6);

  n1->left = std::move(n3);
  n1->right = std::move(n4);
  n2->left = std::move(n5);
  n2->right = std::move(n6);
  n0->left = std::move(n1);
  n0->right = std::move(n2);

  const auto input = BinaryTree<int>(std::move(n0));
  EXPECT_EQ(CheckBalanced(input), true);
}

TEST(check_balanced_test, Depth3_Not_Balanced) {
  auto n0 = std::make_unique<Node<int>>(0);
  auto n1 = std::make_unique<Node<int>>(1);
  auto n2 = std::make_unique<Node<int>>(2);
  auto n3 = std::make_unique<Node<int>>(3);

  n2->left = std::move(n3);
  n1->left = std::move(n2);
  n0->left = std::move(n1);

  const auto input = BinaryTree<int>(std::move(n0));
  EXPECT_EQ(CheckBalanced(input), false);
}

TEST(check_balanced_test, Depth5_Not_Balanced) {
  auto n0 = std::make_unique<Node<int>>(0);
  auto n1 = std::make_unique<Node<int>>(1);
  auto n2 = std::make_unique<Node<int>>(2);
  auto n3 = std::make_unique<Node<int>>(3);
  auto n4 = std::make_unique<Node<int>>(4);
  auto n5 = std::make_unique<Node<int>>(5);

  n4->right = std::move(n5);
  n3->right = std::move(n4);
  n2->right = std::move(n3);
  n1->right = std::move(n2);
  n0->right = std::move(n1);

  const auto input = BinaryTree<int>(std::move(n0));
  EXPECT_EQ(CheckBalanced(input), false);
}

TEST(check_balanced_test, Depth6_Not_Balanced) {
  auto n0 = std::make_unique<Node<int>>(0);
  auto n1 = std::make_unique<Node<int>>(1);
  auto n2 = std::make_unique<Node<int>>(2);
  auto n3 = std::make_unique<Node<int>>(3);
  auto n4 = std::make_unique<Node<int>>(4);
  auto n5 = std::make_unique<Node<int>>(5);
  auto n6 = std::make_unique<Node<int>>(6);

  n5->left = std::move(n6);
  n4->left = std::move(n5);
  n3->left = std::move(n4);
  n2->left = std::move(n3);
  n1->left = std::move(n2);
  n0->left = std::move(n1);

  const auto input = BinaryTree<int>(std::move(n0));
  EXPECT_EQ(CheckBalanced(input), false);
}
