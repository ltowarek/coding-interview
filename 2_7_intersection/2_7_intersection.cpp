// Intersection: Given two (singly) linked lists, determine if the two lists
// intersect. Return the intersecting node. Note that the intersection is
// defined based on reference, not value. That is, if the kth node of the first
// linked list is the exact same node (by reference) as the jth node of the
// second linked list, then they are intersecting.

#include "gtest/gtest.h"

template <class T>
struct Node {
  Node(T _data) : next(nullptr), data(_data) {}

  Node* next;
  T data;
};

template <class T>
Node<T>* Intersection(Node<T> &l1, Node<T> &l2) {
  auto *output = static_cast<Node<T>*>(nullptr);

  auto *current_l1 = &l1;
  auto l1_length = 0;
  while (current_l1->next != nullptr) {
    l1_length++;
    current_l1 = current_l1->next;
  }

  auto *current_l2 = &l2;
  auto l2_length = 0;
  while (current_l2->next != nullptr) {
    l2_length++;
    current_l2 = current_l2->next;
  }

  if (current_l1 == current_l2) {
    auto shorter_list = l1_length < l2_length ? &l1 : &l2;
    auto longer_list = l1_length < l2_length ? &l2 : &l1;

    for (auto i = 0; i < std::abs(l1_length - l2_length); ++i) {
      longer_list = longer_list->next;
    }

    while (shorter_list != longer_list) {
      shorter_list = shorter_list->next;
      longer_list = longer_list->next;
    }

    output = shorter_list;
  }

  return output;
}

TEST(intersection_test, EmptyLists) {
  auto l1 = Node<int>(1);
  auto l2 = Node<int>(2);
  const auto intersection = nullptr;
  EXPECT_EQ(Intersection(l1, l2), intersection);
}

TEST(intersection_test, NoIntersection) {
  auto n1 = Node<int>(1);
  auto n2 = Node<int>(2);
  auto n3 = Node<int>(3);
  auto n4 = Node<int>(4);
  auto n5 = Node<int>(5);
  auto n6 = Node<int>(6);

  n1.next = &n2;
  n2.next = &n3;

  n4.next = &n5;
  n5.next = &n6;

  const auto intersection = nullptr;
  EXPECT_EQ(Intersection(n1, n4), intersection);
}

TEST(intersection_test, TheSameList) {
  auto n1 = Node<int>(1);
  auto n2 = Node<int>(2);
  auto n3 = Node<int>(3);

  n1.next = &n2;
  n2.next = &n3;

  const auto intersection = &n1;
  EXPECT_EQ(Intersection(n1, n1), intersection);
}

TEST(intersection_test, Intersection_Front) {
  auto n1 = Node<int>(1);
  auto n2 = Node<int>(2);
  auto n3 = Node<int>(3);
  auto n4 = Node<int>(4);
  auto n5 = Node<int>(5);
  auto n6 = Node<int>(6);

  n1.next = &n2;
  n2.next = &n3;

  n4.next = &n5;
  n5.next = &n6;
  n6.next = &n1;

  const auto intersection = &n1;
  EXPECT_EQ(Intersection(n1, n4), intersection);
}

TEST(intersection_test, Intersection_Middle) {
  auto n1 = Node<int>(1);
  auto n2 = Node<int>(2);
  auto n3 = Node<int>(3);
  auto n4 = Node<int>(4);
  auto n5 = Node<int>(5);
  auto n6 = Node<int>(6);

  n1.next = &n2;
  n2.next = &n3;

  n4.next = &n5;
  n5.next = &n6;
  n6.next = &n2;

  const auto intersection = &n2;
  EXPECT_EQ(Intersection(n1, n4), intersection);
}

TEST(intersection_test, Intersection_Tail) {
  auto n1 = Node<int>(1);
  auto n2 = Node<int>(2);
  auto n3 = Node<int>(3);
  auto n4 = Node<int>(4);
  auto n5 = Node<int>(5);

  n1.next = &n2;
  n2.next = &n3;

  n4.next = &n5;
  n5.next = &n3;

  const auto intersection = &n3;
  EXPECT_EQ(Intersection(n1, n4), intersection);
}
