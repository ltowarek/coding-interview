// Minimal Tree: Given a sorted (increasing order) array with unique integer
// elements, write an algorithm to create a binary search tree with minimal
// height.

#include "gtest/gtest.h"

template <class T> struct Node {
  Node(T _data) : data(_data), left(nullptr), right(nullptr) {}
  T data;
  std::unique_ptr<Node<T>> left;
  std::unique_ptr<Node<T>> right;
};

template <class T> struct BST {
  BST() : root(nullptr) {}
  BST(std::unique_ptr<Node<T>> _root) : root(std::move(_root)) {}

  bool operator==(const BST<T> &rhs) {
    return AreIdentical(root.get(), rhs.root.get());
  }

  static bool AreIdentical(const Node<T> *lhs, const Node<T> *rhs) {
    if (lhs == nullptr && rhs == nullptr) {
      return true;
    }

    if (lhs != nullptr && rhs != nullptr) {
      return lhs->data == rhs->data &&
             AreIdentical(lhs->left.get(), rhs->left.get()) &&
             AreIdentical(lhs->right.get(), rhs->right.get());
    }

    return false;
  }

  static std::ostream &PrintInorder(std::ostream &stream, const Node<T> *node) {
    if (node == nullptr) {
      return stream;
    }

    PrintInorder(stream, node->left.get());
    stream << node->data << " ";
    PrintInorder(stream, node->right.get());

    return stream;
  }

  std::unique_ptr<Node<T>> root;
};

template <class T> bool operator==(const BST<T> &lhs, const BST<T> &rhs) {
  return BST<T>::AreIdentical(lhs.root.get(), rhs.root.get());
}

template <class T>
std::ostream &operator<<(std::ostream &stream, const BST<T> &bst) {
  return BST<T>::PrintInorder(stream, bst.root.get());
}

template <class T>
std::unique_ptr<Node<T>> CreateMinBST(const std::vector<T> input,
                                      const int start, const int end) {
  if (end < start) {
    return nullptr;
  }
  const auto mid = int((start + end) / 2);
  auto node = std::make_unique<Node<T>>(input[mid]);
  node->left = std::move(CreateMinBST(input, start, mid - 1));
  node->right = std::move(CreateMinBST(input, mid + 1, end));
  return std::move(node);
}

template <class T> BST<T> CreateMinBST(const std::vector<T> input) {
  return BST<T>(std::move(CreateMinBST(input, 0, input.size() - 1)));
}

TEST(minimal_tree_test, EmptyArray) {
  const auto input = std::vector<int>{};

  const auto expected = BST<int>{};
  EXPECT_EQ(CreateMinBST(input), expected);
}

TEST(minimal_tree_test, FullTreeHeight1) {
  const auto input = std::vector<int>{0};
  auto n0 = std::make_unique<Node<int>>(0);

  const auto expected = BST<int>(std::move(n0));
  EXPECT_EQ(CreateMinBST(input), expected);
}

TEST(minimal_tree_test, FullTreeHeight2) {
  const auto input = std::vector<int>{0, 1, 2};
  auto n0 = std::make_unique<Node<int>>(0);
  auto n1 = std::make_unique<Node<int>>(1);
  auto n2 = std::make_unique<Node<int>>(2);

  n1->left = std::move(n0);
  n1->right = std::move(n2);

  const auto expected = BST<int>(std::move(n1));
  EXPECT_EQ(CreateMinBST(input), expected);
}

TEST(minimal_tree_test, FullTreeHeight3) {
  const auto input = std::vector<int>{0, 1, 2, 3, 4, 5, 6};
  auto n0 = std::make_unique<Node<int>>(0);
  auto n1 = std::make_unique<Node<int>>(1);
  auto n2 = std::make_unique<Node<int>>(2);
  auto n3 = std::make_unique<Node<int>>(3);
  auto n4 = std::make_unique<Node<int>>(4);
  auto n5 = std::make_unique<Node<int>>(5);
  auto n6 = std::make_unique<Node<int>>(6);

  n1->left = std::move(n0);
  n1->right = std::move(n2);
  n5->left = std::move(n4);
  n5->right = std::move(n6);
  n3->left = std::move(n1);
  n3->right = std::move(n5);

  const auto expected = BST<int>(std::move(n3));
  EXPECT_EQ(CreateMinBST(input), expected);
}

TEST(minimal_tree_test, UnbalancedTreeHeight1) {
  const auto input = std::vector<int>{0};
  auto n0 = std::make_unique<Node<int>>(0);

  const auto expected = BST<int>(std::move(n0));
  EXPECT_EQ(CreateMinBST(input), expected);
}

TEST(minimal_tree_test, UnbalancedTreeHeight2) {
  const auto input = std::vector<int>{0, 1};
  auto n0 = std::make_unique<Node<int>>(0);
  auto n1 = std::make_unique<Node<int>>(1);

  n0->right = std::move(n1);

  const auto expected = BST<int>(std::move(n0));
  EXPECT_EQ(CreateMinBST(input), expected);
}

TEST(minimal_tree_test, UnbalancedTreeHeight3) {
  const auto input = std::vector<int>{0, 1, 2, 3};
  auto n0 = std::make_unique<Node<int>>(0);
  auto n1 = std::make_unique<Node<int>>(1);
  auto n2 = std::make_unique<Node<int>>(2);
  auto n3 = std::make_unique<Node<int>>(3);

  n2->right = std::move(n3);
  n1->left = std::move(n0);
  n1->right = std::move(n2);

  const auto expected = BST<int>(std::move(n1));
  EXPECT_EQ(CreateMinBST(input), expected);
}
