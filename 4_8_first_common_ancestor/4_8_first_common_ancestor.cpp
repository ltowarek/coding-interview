// First Common Ancestor: Design an algorithm and write code to find the first
// common ancestor of two nodes in a binary tree. Avoid storing additional nodes
// in a data structure. NOTE: This is not necessarily a binary search tree.

#include "gtest/gtest.h"

template <class T> struct Node {
  Node(T _data, Node<T> *_parent)
      : data(_data), parent(_parent), left(nullptr), right(nullptr) {}
  T data;
  std::unique_ptr<Node<T>> left;
  std::unique_ptr<Node<T>> right;
  Node<T> *parent;
};

template <class T> bool Covers(const Node<T> *root, const Node<T> *node) {
  if (root == nullptr) {
    return false;
  }
  if (root == node) {
    return true;
  }
  return Covers(root->left.get(), node) || Covers(root->right.get(), node);
}

template <class T> Node<T> *GetSibling(const Node<T> *node) {
  if (node == nullptr || node->parent == nullptr) {
    return nullptr;
  }
  return node->parent->left.get() == node ? node->parent->right.get()
                                          : node->parent->left.get();
}

template <class T>
const Node<T> *FirstCommonAncestor(const Node<T> *root, const Node<T> *node_1,
                                   const Node<T> *node_2) {
  if (node_1 == node_2) {
    return node_1 == nullptr ? nullptr : node_1->parent;
  } else if (!Covers(root, node_1) || !Covers(root, node_2)) {
    return nullptr;
  } else if (Covers(node_1, node_2)) {
    return node_1;
  } else if (Covers(node_2, node_1)) {
    return node_2;
  }

  Node<T> *sibling = GetSibling(node_1);
  Node<T> *parent = node_1->parent;
  while (!Covers(sibling, node_2)) {
    sibling = GetSibling(parent);
    parent = parent->parent;
  }
  return parent;
}

TEST(first_common_ancestor_test, EmptyNodes) {
  const auto node_1 = std::unique_ptr<Node<int>>(nullptr);
  const auto node_2 = std::unique_ptr<Node<int>>(nullptr);
  const auto expected = nullptr;
  EXPECT_EQ(FirstCommonAncestor<int>(nullptr, node_1.get(), node_2.get()),
            expected);
}

TEST(first_common_ancestor_test, FirstEmptyNode) {
  const auto node_1 = std::unique_ptr<Node<int>>(nullptr);
  const auto node_2 = std::make_unique<Node<int>>(2, nullptr);
  const auto expected = nullptr;
  EXPECT_EQ(FirstCommonAncestor<int>(node_2.get(), node_1.get(), node_2.get()),
            expected);
}

TEST(first_common_ancestor_test, SecondEmptyNode) {
  const auto node_1 = std::make_unique<Node<int>>(1, nullptr);
  const auto node_2 = std::unique_ptr<Node<int>>(nullptr);
  const auto expected = nullptr;
  EXPECT_EQ(FirstCommonAncestor<int>(node_1.get(), node_1.get(), node_2.get()),
            expected);
}

TEST(first_common_ancestor_test, CommonParent) {
  auto node_0 = std::make_unique<Node<int>>(0, nullptr);
  auto node_1 = std::make_unique<Node<int>>(1, node_0.get());
  auto node_2 = std::make_unique<Node<int>>(2, node_0.get());

  const auto node_1_ptr = node_1.get();
  const auto node_2_ptr = node_2.get();

  node_0->left = std::move(node_1);
  node_0->right = std::move(node_2);

  const auto expected = node_0.get();
  EXPECT_EQ(FirstCommonAncestor(node_0.get(), node_1_ptr, node_2_ptr),
            expected);
}

TEST(first_common_ancestor_test, Node1CoversNode2) {
  auto node_0 = std::make_unique<Node<int>>(0, nullptr);
  auto node_1 = std::make_unique<Node<int>>(1, node_0.get());
  auto node_2 = std::make_unique<Node<int>>(2, node_1.get());

  const auto node_1_ptr = node_1.get();
  const auto node_2_ptr = node_2.get();

  node_1->left = std::move(node_2);
  node_0->left = std::move(node_1);

  const auto expected = node_1_ptr;
  EXPECT_EQ(FirstCommonAncestor(node_0.get(), node_1_ptr, node_2_ptr),
            expected);
}

TEST(first_common_ancestor_test, Node2CoversNode1) {
  auto node_0 = std::make_unique<Node<int>>(0, nullptr);
  auto node_2 = std::make_unique<Node<int>>(2, node_0.get());
  auto node_1 = std::make_unique<Node<int>>(1, node_2.get());

  const auto node_1_ptr = node_1.get();
  const auto node_2_ptr = node_2.get();

  node_2->left = std::move(node_1);
  node_0->left = std::move(node_2);

  const auto expected = node_2_ptr;
  EXPECT_EQ(FirstCommonAncestor(node_0.get(), node_1_ptr, node_2_ptr),
            expected);
}

TEST(first_common_ancestor_test, ParentOnDifferentDepths) {
  auto node_0 = std::make_unique<Node<int>>(0, nullptr);
  auto node_1 = std::make_unique<Node<int>>(1, node_0.get());
  auto node_2 = std::make_unique<Node<int>>(2, node_0.get());
  auto node_3 = std::make_unique<Node<int>>(3, node_2.get());

  const auto node_1_ptr = node_1.get();
  const auto node_3_ptr = node_3.get();

  node_2->left = std::move(node_3);
  node_0->left = std::move(node_1);
  node_0->right = std::move(node_2);

  const auto expected = node_0.get();
  EXPECT_EQ(FirstCommonAncestor(node_0.get(), node_1_ptr, node_3_ptr),
            expected);
}

TEST(first_common_ancestor_test, Complex) {
  auto node_20 = std::make_unique<Node<int>>(20, nullptr);
  auto node_30 = std::make_unique<Node<int>>(30, node_20.get());
  auto node_10 = std::make_unique<Node<int>>(10, node_20.get());
  auto node_5 = std::make_unique<Node<int>>(5, node_10.get());
  auto node_15 = std::make_unique<Node<int>>(15, node_10.get());
  auto node_17 = std::make_unique<Node<int>>(17, node_15.get());
  auto node_7 = std::make_unique<Node<int>>(7, node_5.get());
  auto node_3 = std::make_unique<Node<int>>(3, node_5.get());

  const auto node_7_ptr = node_7.get();
  const auto node_17_ptr = node_17.get();
  const auto node_10_ptr = node_10.get();

  node_5->left = std::move(node_3);
  node_5->right = std::move(node_7);
  node_15->right = std::move(node_17);
  node_10->left = std::move(node_5);
  node_10->right = std::move(node_15);
  node_20->left = std::move(node_10);
  node_20->right = std::move(node_30);

  const auto expected = node_10_ptr;
  EXPECT_EQ(FirstCommonAncestor(node_20.get(), node_7_ptr, node_17_ptr),
            expected);
}

TEST(first_common_ancestor_test, SameNode) {
  auto node_0 = std::make_unique<Node<int>>(0, nullptr);
  auto node_1 = std::make_unique<Node<int>>(1, node_0.get());

  const auto node_1_ptr = node_1.get();

  node_0->left = std::move(node_1);

  const auto expected = node_0.get();
  EXPECT_EQ(FirstCommonAncestor(node_0.get(), node_1_ptr, node_1_ptr),
            expected);
}
