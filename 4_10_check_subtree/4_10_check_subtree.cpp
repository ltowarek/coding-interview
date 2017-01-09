// Check Subtree: T1 and T2 are two very large binary trees, with T1 much bigger
// than T2. Create an algorithm to determine if T2 is a subtree of T1.
// A tree T2 is a subtree of T1 if there exists a node n in T1 such that the
// subtree of n is identical to T2. That is, if you cut off the tree at node n,
// the two trees would be identical.

#include "gtest/gtest.h"

template <class T> struct Node {
  Node(T _data) : data(_data), left(nullptr), right(nullptr) {}
  T data;
  std::unique_ptr<Node<T>> left;
  std::unique_ptr<Node<T>> right;
};

template <class T>
bool MatchTree(const Node<T> *tree_1, const Node<T> *tree_2) {
  if (tree_1 == nullptr && tree_2 == nullptr) {
    return true;
  } else if (tree_1 == nullptr || tree_2 == nullptr) {
    return false;
  } else if (tree_1->data != tree_2->data) {
    return false;
  } else {
    return MatchTree(tree_1->left.get(), tree_2->left.get()) &&
           MatchTree(tree_1->right.get(), tree_2->right.get());
  }
}

template <class T>
bool ContainsTree(const Node<T> *tree_1, const Node<T> *tree_2) {
  if (tree_1 == nullptr) {
    return false;
  } else if (tree_1->data == tree_2->data && MatchTree(tree_1, tree_2)) {
    return true;
  }
  return ContainsTree(tree_1->left.get(), tree_2) ||
         ContainsTree(tree_1->right.get(), tree_2);
}

template <class T>
bool CheckSubtree(const Node<T> *tree_1, const Node<T> *tree_2) {
  if (tree_2 == nullptr) {
    return true;
  }
  return ContainsTree(tree_1, tree_2);
}

TEST(check_subtree_test, EmptyTrees) {
  auto tree_1 = std::unique_ptr<Node<int>>(nullptr);
  auto tree_2 = std::unique_ptr<Node<int>>(nullptr);
  EXPECT_EQ(CheckSubtree(tree_1.get(), tree_2.get()), true);
}

TEST(check_subtree_test, T1_Empty) {
  auto tree_1 = std::unique_ptr<Node<int>>(nullptr);
  auto tree_2 = std::make_unique<Node<int>>(1);
  EXPECT_EQ(CheckSubtree(tree_1.get(), tree_2.get()), false);
}

TEST(check_subtree_test, T2_Empty) {
  auto tree_1 = std::make_unique<Node<int>>(1);
  auto tree_2 = std::unique_ptr<Node<int>>(nullptr);
  EXPECT_EQ(CheckSubtree(tree_1.get(), tree_2.get()), true);
}

TEST(check_subtree_test, Depth1_Subtree) {
  auto tree_1 = std::make_unique<Node<int>>(1);
  auto tree_2 = std::make_unique<Node<int>>(1);
  EXPECT_EQ(CheckSubtree(tree_1.get(), tree_2.get()), true);
}

TEST(check_subtree_test, Depth1_NotSubtree) {
  auto tree_1 = std::make_unique<Node<int>>(1);
  auto tree_2 = std::make_unique<Node<int>>(2);
  EXPECT_EQ(CheckSubtree(tree_1.get(), tree_2.get()), false);
}

TEST(check_subtree_test, Depth2_Subtree_Left) {
  auto tree_1_1 = std::make_unique<Node<int>>(1);
  auto tree_1_2 = std::make_unique<Node<int>>(2);
  auto tree_1_3 = std::make_unique<Node<int>>(3);

  tree_1_1->left = std::move(tree_1_2);
  tree_1_1->right = std::move(tree_1_3);

  auto tree_2 = std::make_unique<Node<int>>(2);
  EXPECT_EQ(CheckSubtree(tree_1_1.get(), tree_2.get()), true);
}

TEST(check_subtree_test, Depth2_Subtree_Right) {
  auto tree_1_1 = std::make_unique<Node<int>>(1);
  auto tree_1_2 = std::make_unique<Node<int>>(2);
  auto tree_1_3 = std::make_unique<Node<int>>(3);

  tree_1_1->left = std::move(tree_1_2);
  tree_1_1->right = std::move(tree_1_3);

  auto tree_2 = std::make_unique<Node<int>>(3);

  EXPECT_EQ(CheckSubtree(tree_1_1.get(), tree_2.get()), true);
}

TEST(check_subtree_test, Depth2_Subtree_Root) {
  auto tree_1_1 = std::make_unique<Node<int>>(1);
  auto tree_1_2 = std::make_unique<Node<int>>(2);
  auto tree_1_3 = std::make_unique<Node<int>>(3);

  tree_1_1->left = std::move(tree_1_2);
  tree_1_1->right = std::move(tree_1_3);

  auto tree_2_1 = std::make_unique<Node<int>>(1);
  auto tree_2_2 = std::make_unique<Node<int>>(2);
  auto tree_2_3 = std::make_unique<Node<int>>(3);

  tree_2_1->left = std::move(tree_2_2);
  tree_2_1->right = std::move(tree_2_3);

  EXPECT_EQ(CheckSubtree(tree_1_1.get(), tree_2_1.get()), true);
}

TEST(check_subtree_test, Depth2_NotSubtree_Leaf_Left) {
  auto tree_1_1 = std::make_unique<Node<int>>(1);
  auto tree_1_2 = std::make_unique<Node<int>>(2);
  auto tree_1_3 = std::make_unique<Node<int>>(3);

  tree_1_1->left = std::move(tree_1_2);
  tree_1_1->right = std::move(tree_1_3);

  auto tree_2_1 = std::make_unique<Node<int>>(1);
  auto tree_2_4 = std::make_unique<Node<int>>(4);
  auto tree_2_3 = std::make_unique<Node<int>>(3);

  tree_2_1->left = std::move(tree_2_4);
  tree_2_1->right = std::move(tree_2_3);

  EXPECT_EQ(CheckSubtree(tree_1_1.get(), tree_2_1.get()), false);
}

TEST(check_subtree_test, Depth2_NotSubtree_Leaf_Right) {
  auto tree_1_1 = std::make_unique<Node<int>>(1);
  auto tree_1_2 = std::make_unique<Node<int>>(2);
  auto tree_1_3 = std::make_unique<Node<int>>(3);

  tree_1_1->left = std::move(tree_1_2);
  tree_1_1->right = std::move(tree_1_3);

  auto tree_2_1 = std::make_unique<Node<int>>(1);
  auto tree_2_2 = std::make_unique<Node<int>>(2);
  auto tree_2_4 = std::make_unique<Node<int>>(4);

  tree_2_1->left = std::move(tree_2_2);
  tree_2_1->right = std::move(tree_2_4);

  EXPECT_EQ(CheckSubtree(tree_1_1.get(), tree_2_1.get()), false);
}

TEST(check_subtree_test, Depth2_NotSubtree_Root) {
  auto tree_1_1 = std::make_unique<Node<int>>(1);
  auto tree_1_2 = std::make_unique<Node<int>>(2);
  auto tree_1_3 = std::make_unique<Node<int>>(3);

  tree_1_1->left = std::move(tree_1_2);
  tree_1_1->right = std::move(tree_1_3);

  auto tree_2 = std::make_unique<Node<int>>(4);

  EXPECT_EQ(CheckSubtree(tree_1_1.get(), tree_2.get()), false);
}
