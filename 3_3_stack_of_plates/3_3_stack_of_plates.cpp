// Stack of Plates: Imagine a (literal) stack of plates. If the stack gets too
// high, it might topple. Therefore, in real life, we would likely start a new
// stack when the previous stack exceeds some threshold. Implement a data
// structure SetOfStacks that mimics this. SetOfStacks should be composed of
// several stacks and should create a new stack once the previous one exceeds
// capacity. SetOfStacks.push() and SetOfStacks.pop() should behave identically
// to a single stack (that is, pop() should return the same values as it would
// if there were just a single stack).
// Implement a function popAt(int index) which performs a pop operation on a
// specific sub-stack.

#include <stack>
#include "gtest/gtest.h"

template <class T>
class SetOfStacks {
public:
  SetOfStacks(const size_t max_sub_stack_size) :
    max_sub_stack_size_(max_sub_stack_size) {}

  void Push(const T& data) {
    auto* last_stack = LastStack();
    if (last_stack != nullptr && last_stack->size() < max_sub_stack_size_) {
      last_stack->push(data);
    } else {
      auto stack = std::stack<T>();
      stack.push(data);
      stacks_.push_back(stack);
    }
  }

  void Pop() {
    auto* stack = LastStack();
    stack->pop();
    if (stack->empty()) {
      stacks_.pop_back();
    }
  }

  void PopAt(const size_t stack_id) {
    auto& stack = stacks_[stack_id];
    stack.pop();
    if (stack.empty()) {
      stacks_.erase(stacks_.begin() + stack_id);
    }
  }

  T Top() {
    auto* stack = LastStack();
    return stack->top();
  }

  bool IsEmpty() {
    auto* stack = LastStack();
    return stack == nullptr || stack->empty();
  }

  size_t NumberOfStacks() const {
    return stacks_.size();
  }

private:
  std::stack<T>* LastStack() {
    if (stacks_.empty()) {
      return nullptr;
    }
    return &stacks_.back();
  }

  const size_t max_sub_stack_size_;
  std::vector<std::stack<T>> stacks_;
};

TEST(stack_of_plates_test, PushSingleElement) {
  auto stack = SetOfStacks<int>(2);
  stack.Push(1);
  EXPECT_EQ(stack.Top(), 1);
  EXPECT_EQ(stack.NumberOfStacks(), 1);
}

TEST(stack_of_plates_test, PopSingleElement) {
  auto stack = SetOfStacks<int>(2);
  stack.Push(1);
  stack.Push(2);
  stack.Pop();
  EXPECT_EQ(stack.Top(), 1);
  EXPECT_EQ(stack.NumberOfStacks(), 1);
}

TEST(stack_of_plates_test, PushNewStack) {
  auto stack = SetOfStacks<int>(2);
  stack.Push(1);
  stack.Push(2);

  stack.Push(3);
  stack.Push(4);

  stack.Push(5);
  stack.Push(6);

  EXPECT_EQ(stack.Top(), 6);
  EXPECT_EQ(stack.NumberOfStacks(), 3);
}

TEST(stack_of_plates_test, PopLastStack) {
  auto stack = SetOfStacks<int>(2);
  stack.Push(1);
  stack.Push(2);

  stack.Push(3);
  stack.Push(4);

  stack.Push(5);
  stack.Push(6);

  stack.Pop();
  stack.Pop();

  EXPECT_EQ(stack.Top(), 4);
  EXPECT_EQ(stack.NumberOfStacks(), 2);
}

TEST(stack_of_plates_test, PopAtWholeStack) {
  auto stack = SetOfStacks<int>(2);
  stack.Push(1);
  stack.Push(2);

  stack.Push(3);
  stack.Push(4);

  stack.Push(5);
  stack.Push(6);

  stack.PopAt(1);  // Remove 4
  stack.PopAt(1);  // Remove 3
  EXPECT_EQ(stack.Top(), 6);
  EXPECT_EQ(stack.NumberOfStacks(), 2);

  stack.Pop();
  EXPECT_EQ(stack.Top(), 5);
  stack.Pop();
  EXPECT_EQ(stack.Top(), 2);
  stack.Pop();
  EXPECT_EQ(stack.Top(), 1);
}

TEST(stack_of_plates_test, PopAtPartOfStack) {
  auto stack = SetOfStacks<int>(2);
  stack.Push(1);
  stack.Push(2);

  stack.Push(3);
  stack.Push(4);

  stack.Push(5);
  stack.Push(6);

  stack.PopAt(1);  // Remove 4
  EXPECT_EQ(stack.Top(), 6);
  EXPECT_EQ(stack.NumberOfStacks(), 3);

  stack.Pop();
  EXPECT_EQ(stack.Top(), 5);
  stack.Pop();
  EXPECT_EQ(stack.Top(), 3);
  stack.Pop();
  EXPECT_EQ(stack.Top(), 2);
  stack.Pop();
  EXPECT_EQ(stack.Top(), 1);
}
