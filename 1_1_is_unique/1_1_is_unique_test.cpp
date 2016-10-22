#include "gtest/gtest.h"
#include "1_1_is_unique.cpp"

bool is_unique() {
  return true;
}

TEST(is_unique_test, Dummy) {
  EXPECT_EQ(is_unique(), true);
}
