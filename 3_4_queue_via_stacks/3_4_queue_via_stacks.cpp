// Queue via Stacks: Implement a MyQueue class which implements a queue using
// two stacks.

#include "gtest/gtest.h"
#include <stack>

template <class T> class MyQueue {
public:
  void Push(const T &data) { s1.push(data); }

  void Pop() {
    ReverseStack();
    s2.pop();
  }

  T Top() {
    ReverseStack();
    return s2.top();
  }

private:
  void ReverseStack() {
    if (s2.empty()) {
      while (!s1.empty()) {
        s2.push(s1.top());
        s1.pop();
      }
    }
  }

  std::stack<T> s1;
  std::stack<T> s2;
};

TEST(queue_via_stacks_test, PushSingleElement) {
  auto queue = MyQueue<int>();
  queue.Push(1);
  EXPECT_EQ(queue.Top(), 1);
}

TEST(queue_via_stacks_test, PushMultipleElements) {
  auto queue = MyQueue<int>();
  queue.Push(1);
  queue.Push(2);
  queue.Push(3);
  queue.Push(4);
  EXPECT_EQ(queue.Top(), 1);
}

TEST(queue_via_stacks_test, PopSingleElement) {
  auto queue = MyQueue<int>();
  queue.Push(1);
  queue.Push(2);

  EXPECT_EQ(queue.Top(), 1);
  queue.Pop();
  EXPECT_EQ(queue.Top(), 2);
}

TEST(queue_via_stacks_test, PopMultipleElements) {
  auto queue = MyQueue<int>();
  queue.Push(1);
  queue.Push(2);
  queue.Push(3);
  queue.Push(4);

  EXPECT_EQ(queue.Top(), 1);
  queue.Pop();
  EXPECT_EQ(queue.Top(), 2);
  queue.Pop();
  EXPECT_EQ(queue.Top(), 3);
}
