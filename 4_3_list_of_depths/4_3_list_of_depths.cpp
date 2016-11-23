// List of Depths: Given a binary tree, design an algorithm which creates a
// linked list of all the nodes at each depth (e.g., if you have a tree with
// depth D, you'll have D linked lists).

#include <list>
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
using List = std::list<Node<T>*>;

template <class T>
using VectorOfLists = std::vector<List<T>>;

template <class T>
void CreateListOfDepths(Node<T> *node, VectorOfLists<T> &vector, int level) {
  if (node == nullptr) {
    return;
  }

  if (vector.size() == level) {
    vector.push_back(List<T>{});
  }

  vector[level].push_back(node);
  CreateListOfDepths(node->left.get(), vector, level + 1);
  CreateListOfDepths(node->right.get(), vector, level + 1);
}

template <class T>
VectorOfLists<T> CreateListOfDepths(const BinaryTree<T> &input) {
  auto output = VectorOfLists<T>();
  CreateListOfDepths(input.root.get(), output, 0);
  return output;
}

TEST(list_of_depths_test, EmptyTree) {
  const auto expected = VectorOfLists<int>{};
  const auto input = BinaryTree<int>();
  EXPECT_EQ(CreateListOfDepths(input), expected);
}

TEST(list_of_depths_test, Depth1) {
  auto n0 = std::make_unique<Node<int>>(0);
  const auto expected = VectorOfLists<int>{{n0.get()}};
  const auto input = BinaryTree<int>(std::move(n0));
  EXPECT_EQ(CreateListOfDepths(input), expected);
}

TEST(list_of_depths_test, Depth2) {
  auto n0 = std::make_unique<Node<int>>(0);
  auto n1 = std::make_unique<Node<int>>(1);
  auto n2 = std::make_unique<Node<int>>(2);

  const auto expected = VectorOfLists<int>{{n0.get()},
                                           {n1.get(), n2.get()}};

  n0->left = std::move(n1);
  n0->right = std::move(n2);

  const auto input = BinaryTree<int>(std::move(n0));
  EXPECT_EQ(CreateListOfDepths(input), expected);
}

TEST(list_of_depths_test, Depth3) {
  auto n0 = std::make_unique<Node<int>>(0);
  auto n1 = std::make_unique<Node<int>>(1);
  auto n2 = std::make_unique<Node<int>>(2);
  auto n3 = std::make_unique<Node<int>>(3);
  auto n4 = std::make_unique<Node<int>>(4);
  auto n5 = std::make_unique<Node<int>>(5);
  auto n6 = std::make_unique<Node<int>>(6);

  const auto expected = VectorOfLists<int>{{n0.get()},
                                           {n1.get(), n2.get()},
                                           {n3.get(), n4.get(), n5.get(), n6.get()}};

  n1->left = std::move(n3);
  n1->right = std::move(n4);
  n2->left = std::move(n5);
  n2->right = std::move(n6);
  n0->left = std::move(n1);
  n0->right = std::move(n2);

  const auto input = BinaryTree<int>(std::move(n0));
  EXPECT_EQ(CreateListOfDepths(input), expected);
}
