// Successor: Write an algorithm to find the "next" node
// (i.e., in-order successor) of a given node in a binary search tree.
// You may assume that each node has a link to its parent.

#include "gtest/gtest.h"

template <class T>
struct Node {
  Node(T _data, Node<T> *_parent): data(_data), parent(_parent),
                                   left(nullptr), right(nullptr) {}
  T data;
  std::unique_ptr<Node<T>> left;
  std::unique_ptr<Node<T>> right;
  Node<T>* parent;
};

template <class T>
Node<T>* LeftMostChild(Node<T> *node) {
  if (node == nullptr) {
    return nullptr;
  }

  while (node->left.get() != nullptr) {
    node = node->left.get();
  }
  return node;
}

template <class T>
Node<T>* NotTraversedParent(Node<T> *node) {
  if (node == nullptr) {
    return nullptr;
  }

  Node<T> *tmp_parent = node->parent;
  while (tmp_parent != nullptr && tmp_parent->left.get() != node) {
    node = tmp_parent;
    tmp_parent = node->parent;
  }
  return tmp_parent;
}

template <class T>
Node<T>* GetSuccessor(Node<T> *node) {
  if (node == nullptr) {
    return nullptr;
  }

  if (node->right.get() != nullptr) {
    return LeftMostChild(node->right.get());
  } else {
    return NotTraversedParent(node);
  }
}

TEST(successor_test, EmptyTree) {
  EXPECT_EQ(GetSuccessor<int>(nullptr), nullptr);
}

TEST(successor_test, Depth1) {
  auto n0 = std::make_unique<Node<int>>(0, nullptr);
  EXPECT_EQ(GetSuccessor<int>(n0.get()), nullptr);
}

TEST(successor_test, Depth2_Root_Successor) {
  auto n0 = std::make_unique<Node<int>>(0, nullptr);
  auto n1 = std::make_unique<Node<int>>(1, n0.get());
  auto n2 = std::make_unique<Node<int>>(2, n0.get());

  n0->left = std::move(n1);
  n0->right = std::move(n2);

  EXPECT_EQ(GetSuccessor<int>(n0.get()), n0->right.get());
}

TEST(successor_test, Depth2_Left_Successor) {
  auto n0 = std::make_unique<Node<int>>(0, nullptr);
  auto n1 = std::make_unique<Node<int>>(1, n0.get());
  auto n2 = std::make_unique<Node<int>>(2, n0.get());

  n0->left = std::move(n1);
  n0->right = std::move(n2);

  EXPECT_EQ(GetSuccessor<int>(n0->left.get()), n0.get());
}

TEST(successor_test, Depth2_Right_Successor) {
  auto n0 = std::make_unique<Node<int>>(0, nullptr);
  auto n1 = std::make_unique<Node<int>>(1, n0.get());
  auto n2 = std::make_unique<Node<int>>(2, n0.get());

  n0->left = std::move(n1);
  n0->right = std::move(n2);

  EXPECT_EQ(GetSuccessor<int>(n0->right.get()), nullptr);
}

TEST(successor_test, Depth3_Left_Right_Successor) {
  auto n0 = std::make_unique<Node<int>>(0, nullptr);
  auto n1 = std::make_unique<Node<int>>(1, n0.get());
  auto n2 = std::make_unique<Node<int>>(2, n0.get());
  auto n3 = std::make_unique<Node<int>>(3, n1.get());
  auto n4 = std::make_unique<Node<int>>(4, n1.get());

  n1->left = std::move(n3);
  n1->right = std::move(n4);
  n0->left = std::move(n1);
  n0->right = std::move(n2);

  EXPECT_EQ(GetSuccessor<int>(n0->left->right.get()), n0.get());
}

TEST(successor_test, Depth3_Root_Successor) {
  auto n0 = std::make_unique<Node<int>>(0, nullptr);
  auto n1 = std::make_unique<Node<int>>(1, n0.get());
  auto n2 = std::make_unique<Node<int>>(2, n0.get());
  auto n3 = std::make_unique<Node<int>>(3, n1.get());
  auto n4 = std::make_unique<Node<int>>(4, n1.get());
  auto n5 = std::make_unique<Node<int>>(5, n2.get());
  auto n6 = std::make_unique<Node<int>>(6, n2.get());

  n1->left = std::move(n3);
  n1->right = std::move(n4);
  n2->left = std::move(n5);
  n2->right = std::move(n6);
  n0->left = std::move(n1);
  n0->right = std::move(n2);

  EXPECT_EQ(GetSuccessor<int>(n0.get()), n0->right->left.get());
}
