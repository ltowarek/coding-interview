#include "gtest/gtest.h"

bool is_unique() {
  return true;
}

TEST(is_unique_test, Dummy) {
  EXPECT_EQ(is_unique(), true);
}
