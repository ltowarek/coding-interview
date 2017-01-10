// Random Node: You are implementing a binary search tree class from scratch,
// which, in addition to insert, find, and delete, has a method getRandomNode()
// which returns a random node from the tree. All nodes should be equally likely
// to be chosen. Design and implement an algorithm for getRandomNode, and
// explain how you would implement the rest of the methods.

#include "gtest/gtest.h"
#include <random>

template <class T> struct Node {
  Node(T _data) : data(_data), left(nullptr), right(nullptr), size(1) {}

  void Insert(T _data) {
    if (_data <= data) {
      if (left == nullptr) {
        left = std::make_unique<Node<T>>(_data);
      } else {
        left->Insert(_data);
      }
    } else {
      if (right == nullptr) {
        right = std::make_unique<Node<T>>(_data);
      } else {
        right->Insert(_data);
      }
    }
    size++;
  }

  const Node<T> *Find(T _data) const {
    if (_data == data) {
      return this;
    } else if (_data < data) {
      return left != nullptr ? left->Find(_data) : nullptr;
    } else if (_data > data) {
      return right != nullptr ? right->Find(_data) : nullptr;
    }
  }

  const Node<T> *GetIthNode(size_t i) const {
    const auto left_size = left == nullptr ? 0 : left->size;
    if (i < left_size) {
      return left->GetIthNode(i);
    } else if (i == left_size) {
      return this;
    } else {
      return right->GetIthNode(i - (left_size + 1));
    }
  }

  T data;
  std::unique_ptr<Node<T>> left;
  std::unique_ptr<Node<T>> right;
  size_t size;
};

template <class T> class BinarySearchTree {
public:
  BinarySearchTree() : root_(nullptr) {}

  void Insert(T data) {
    if (root_ == nullptr) {
      root_ = std::make_unique<Node<T>>(data);
    } else {
      root_->Insert(data);
    }
  }

  const Node<T> *Find(T data) const { return root_->Find(data); }

  const Node<T> *GetRandomNode() const {
    static std::random_device device;
    static auto generator = std::mt19937_64(device());
    auto distribution =
        std::uniform_int_distribution<size_t>(0, root_->size - 1);

    if (root_ == nullptr) {
      return nullptr;
    }

    const auto i = distribution(generator);
    return root_->GetIthNode(i);
  }

private:
  std::unique_ptr<Node<T>> root_;
};

TEST(random_node_test, Depth1_Insert) {
  auto tree = BinarySearchTree<int>();

  tree.Insert(1);

  EXPECT_EQ(tree.Find(1)->data, 1);
  EXPECT_EQ(tree.Find(1)->left, nullptr);
  EXPECT_EQ(tree.Find(1)->right, nullptr);
}

TEST(random_node_test, Depth1_Find) {
  auto tree = BinarySearchTree<int>();

  tree.Insert(1);

  EXPECT_EQ(tree.Find(1)->data, 1);
}

TEST(random_node_test, Depth1_GetRandomNode) {
  auto tree = BinarySearchTree<int>();

  tree.Insert(1);

  EXPECT_EQ(tree.GetRandomNode()->data, 1);
}

TEST(random_node_test, Depth2_Insert) {
  auto tree = BinarySearchTree<int>();

  tree.Insert(2);
  tree.Insert(1);
  tree.Insert(3);

  EXPECT_EQ(tree.Find(2)->data, 2);
  EXPECT_EQ(tree.Find(2)->left->data, 1);
  EXPECT_EQ(tree.Find(2)->right->data, 3);
  EXPECT_EQ(tree.Find(1)->left, nullptr);
  EXPECT_EQ(tree.Find(1)->right, nullptr);
  EXPECT_EQ(tree.Find(3)->left, nullptr);
  EXPECT_EQ(tree.Find(3)->right, nullptr);
}

TEST(random_node_test, Depth2_Find) {
  auto tree = BinarySearchTree<int>();

  tree.Insert(2);
  tree.Insert(1);
  tree.Insert(3);

  EXPECT_EQ(tree.Find(1)->data, 1);
  EXPECT_EQ(tree.Find(2)->data, 2);
  EXPECT_EQ(tree.Find(3)->data, 3);
}

TEST(random_node_test, Depth2_GetRandomNode) {
  auto tree = BinarySearchTree<int>();

  tree.Insert(2);
  tree.Insert(1);
  tree.Insert(3);

  const auto output = tree.GetRandomNode();

  EXPECT_TRUE(output->data == 1 || output->data == 2 || output->data == 3);
}
