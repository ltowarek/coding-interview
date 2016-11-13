// Sort Stack: Write a program to sort a stack such that the smallest items are
// on the top. You can use an additional temporary stack, but you may not copy
// the elements into any other data structure (such as an array). The stack
// supports the following operations: push, pop, peek, and isEmpty.

#include <stack>
#include "gtest/gtest.h"

template <class T>
void SortStack(std::stack<T> &stack) {
  auto tmp_stack = std::stack<T>();
  while (!stack.empty()) {
    auto top = stack.top();
    stack.pop();
    while (!tmp_stack.empty() && tmp_stack.top() > top) {
      stack.push(tmp_stack.top());
      tmp_stack.pop();
    }
    tmp_stack.push(top);
  }
  while (!tmp_stack.empty()) {
    stack.push(tmp_stack.top());
    tmp_stack.pop();
  }
}

TEST(sort_stack_test, PushSingleElement) {
  auto stack = std::stack<int>();
  stack.push(1);
  SortStack(stack);
  EXPECT_EQ(stack.top(), 1);
}

TEST(sort_stack_test, PushInDescendingOrder) {
  auto stack = std::stack<int>();
  stack.push(4);
  stack.push(3);
  stack.push(2);
  stack.push(1);
  SortStack(stack);
  EXPECT_EQ(stack.top(), 1);
}

TEST(sort_stack_test, PushInAscendingOrder) {
  auto stack = std::stack<int>();
  stack.push(1);
  stack.push(2);
  stack.push(3);
  stack.push(4);
  SortStack(stack);
  EXPECT_EQ(stack.top(), 1);
}

TEST(sort_stack_test, PushUnordered) {
  auto stack = std::stack<int>();
  stack.push(2);
  stack.push(1);
  stack.push(4);
  stack.push(3);
  SortStack(stack);
  EXPECT_EQ(stack.top(), 1);
}
