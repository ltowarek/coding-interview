// Loop Detection: Given a circular linked list, implement an algorithm that
// returns the node at the beginning of the loop.

#include "gtest/gtest.h"

template <class T> struct Node {
  Node(T _data) : next(nullptr), data(_data) {}

  Node *next;
  T data;
};

template <class T> Node<T> *DetectLoop(Node<T> &list) {
  auto *output = static_cast<Node<T> *>(nullptr);

  auto *slow_runner = &list;
  auto *fast_runner = &list;
  while (fast_runner != nullptr && fast_runner->next != nullptr) {
    slow_runner = slow_runner->next;
    fast_runner = fast_runner->next->next;
    if (slow_runner == fast_runner) {
      break;
    }
  }

  if (fast_runner != nullptr && fast_runner->next != nullptr) {
    slow_runner = &list;
    while (slow_runner != fast_runner) {
      slow_runner = slow_runner->next;
      fast_runner = fast_runner->next;
    }
    output = slow_runner;
  }

  return output;
}

TEST(loop_detection_test, EmptyList) {
  auto list = Node<int>(1);
  const auto expected = nullptr;
  EXPECT_EQ(DetectLoop(list), expected);
}

TEST(loop_detection_test, NoCycle) {
  auto n1 = Node<int>(1);
  auto n2 = Node<int>(2);
  auto n3 = Node<int>(3);
  auto n4 = Node<int>(4);
  auto n5 = Node<int>(5);
  auto n6 = Node<int>(6);

  n1.next = &n2;
  n2.next = &n3;
  n3.next = &n4;
  n4.next = &n5;
  n5.next = &n6;

  const auto expected = nullptr;
  EXPECT_EQ(DetectLoop(n1), expected);
}

TEST(loop_detection_test, CycleFromBeginning) {
  auto n1 = Node<int>(1);
  auto n2 = Node<int>(2);
  auto n3 = Node<int>(3);
  auto n4 = Node<int>(4);
  auto n5 = Node<int>(5);
  auto n6 = Node<int>(6);

  n1.next = &n2;
  n2.next = &n3;
  n3.next = &n4;
  n4.next = &n5;
  n5.next = &n6;
  n6.next = &n1;

  const auto expected = &n1;
  EXPECT_EQ(DetectLoop(n1), expected);
}

TEST(loop_detection_test, CycleFromMiddle) {
  auto n1 = Node<int>(1);
  auto n2 = Node<int>(2);
  auto n3 = Node<int>(3);
  auto n4 = Node<int>(4);
  auto n5 = Node<int>(5);
  auto n6 = Node<int>(6);

  n1.next = &n2;
  n2.next = &n3;
  n3.next = &n4;
  n4.next = &n5;
  n5.next = &n6;
  n6.next = &n3;

  const auto expected = &n3;
  EXPECT_EQ(DetectLoop(n1), expected);
}
