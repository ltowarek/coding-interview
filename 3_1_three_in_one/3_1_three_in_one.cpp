// Three in One: Describe how you could use a single array to implement three
// stacks.

#include "gtest/gtest.h"

template <class T> class MultiStack {
public:
  MultiStack(const size_t _max_stack_size)
      : max_stack_size(_max_stack_size),
        sizes(std::vector<T>(number_of_stacks, 0)),
        values(std::vector<T>(max_stack_size * number_of_stacks)) {}

  void Push(const size_t stack_id, const T data) {
    sizes[stack_id]++;
    values[IndexOfTop(stack_id)] = data;
  }

  void Pop(const size_t stack_id) { sizes[stack_id]--; }

  T Top(const size_t stack_id) const { return values[IndexOfTop(stack_id)]; }

  bool IsFull(const size_t stack_id) const {
    return sizes[stack_id] == max_stack_size;
  }

  bool IsEmpty(const size_t stack_id) const { return sizes[stack_id] == 0; }

private:
  size_t IndexOfTop(const size_t stack_id) const {
    const auto offset = stack_id * max_stack_size;
    const auto stack_size = sizes[stack_id];
    return offset + stack_size - 1;
  }

  const size_t number_of_stacks = 3;
  const size_t max_stack_size;
  std::vector<T> sizes;
  std::vector<T> values;
};

TEST(three_in_one_test, PushPopAllStacks) {
  const auto number_of_stacks = 3;
  const auto stack_size = 1;
  auto stacks = MultiStack<int>(stack_size);

  for (auto i = 0; i < number_of_stacks; ++i) {
    for (auto j = 0; j < stack_size; ++j) {
      stacks.Push(i, j);
    }
  }

  for (auto i = 0; i < number_of_stacks; ++i) {
    for (auto j = stack_size - 1; j >= 0; --j) {
      stacks.Pop(i);
      EXPECT_EQ(stacks.Top(i), j);
    }
  }
}

TEST(three_in_one_test, PushTopAllStacks) {
  const auto number_of_stacks = 3;
  const auto stack_size = 1;
  auto stacks = MultiStack<int>(stack_size);

  for (auto i = 0; i < number_of_stacks; ++i) {
    for (auto j = 0; j < stack_size; ++j) {
      stacks.Push(i, j);
      EXPECT_EQ(stacks.Top(i), j);
    }
  }
}

TEST(three_in_one_test, PushPopIsEmptyAllStacks) {
  const auto number_of_stacks = 3;
  const auto stack_size = 1;
  auto stacks = MultiStack<int>(stack_size);

  for (auto i = 0; i < number_of_stacks; ++i) {
    stacks.Push(i, 1);
    stacks.Pop(i);
    EXPECT_TRUE(stacks.IsEmpty(i));
  }
}

TEST(three_in_one_test, IsEmptyAllStacks) {
  const auto number_of_stacks = 3;
  const auto stack_size = 1;
  auto stacks = MultiStack<int>(stack_size);

  for (auto i = 0; i < number_of_stacks; ++i) {
    EXPECT_TRUE(stacks.IsEmpty(i));
  }
}

TEST(three_in_one_test, IsFullAllStacks) {
  const auto number_of_stacks = 3;
  const auto stack_size = 1;
  auto stacks = MultiStack<int>(stack_size);

  for (auto i = 0; i < number_of_stacks; ++i) {
    for (auto j = 0; j < stack_size; ++j) {
      stacks.Push(i, j);
    }
  }

  for (auto i = 0; i < number_of_stacks; ++i) {
    EXPECT_TRUE(stacks.IsFull(i));
  }
}
