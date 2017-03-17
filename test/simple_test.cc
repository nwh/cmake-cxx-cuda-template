#include <gtest/gtest.h>
#include <foobar/foobar.h>

TEST(SimpleTest,Test1) {
  EXPECT_TRUE(true);
}

TEST(SimpleTest,Test2) {
  EXPECT_EQ(foo(42),42);
}
