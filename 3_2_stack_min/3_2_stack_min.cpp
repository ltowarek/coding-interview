// Stack Min: How would you design a stack wh ich, in addition to push and pop,
// has a function min which returns the minimum element? Push, pop and min
// should all operate in 0(1) time.

#include <limits>
#include <stack>
#include "gtest/gtest.h"

template <class T>
class MinStack {
public:
  void Push(const T& data) {
    if (data < Min()) {
      min_stack_.push(data);
    }
    values_stack_.push(data);
  }

  void Pop() {
    if (values_stack_.top() == min_stack_.top()) {
      min_stack_.pop();
    }
    values_stack_.pop();
  }

  T Top() const {
    return values_stack_.top();
  }

  bool IsEmpty() const {
    return values_stack_.empty();
  }

  T Min() const {
    if (IsEmpty()) {
      return std::numeric_limits<T>::max();
    } else {
      return min_stack_.top();
    }
  }

private:
  std::stack<T> values_stack_;
  std::stack<T> min_stack_;
};

TEST(stack_min_test, PushSingleElement) {
  auto stack = MinStack<int>();
  stack.Push(1);
  EXPECT_EQ(stack.Min(), 1);
}

TEST(stack_min_test, PushAscendingElements) {
  auto stack = MinStack<int>();
  stack.Push(1);
  EXPECT_EQ(stack.Min(), 1);
  stack.Push(2);
  EXPECT_EQ(stack.Min(), 1);
  stack.Push(3);
  EXPECT_EQ(stack.Min(), 1);
}

TEST(stack_min_test, PushDescendingElements) {
  auto stack = MinStack<int>();
  stack.Push(3);
  EXPECT_EQ(stack.Min(), 3);
  stack.Push(2);
  EXPECT_EQ(stack.Min(), 2);
  stack.Push(1);
  EXPECT_EQ(stack.Min(), 1);
}

TEST(stack_min_test, PushUnorderedElements) {
  auto stack = MinStack<int>();
  stack.Push(3);
  EXPECT_EQ(stack.Min(), 3);
  stack.Push(2);
  EXPECT_EQ(stack.Min(), 2);
  stack.Push(4);
  EXPECT_EQ(stack.Min(), 2);
  stack.Push(5);
  EXPECT_EQ(stack.Min(), 2);
  stack.Push(1);
  EXPECT_EQ(stack.Min(), 1);
  stack.Push(7);
  EXPECT_EQ(stack.Min(), 1);
}
