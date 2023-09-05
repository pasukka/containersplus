#include <gtest/gtest.h>

#include "vector.h"

TEST(TestConstructorVector, SimpleConstructor) {
  Vector<int> v;
  EXPECT_EQ(0, v.size());
  EXPECT_EQ(0, v.capacity());
}

// TEST(TestConstructorVector, ConstructorWithParam) {
//   Vector<int> v(2);
//   EXPECT_EQ(2, v.size());
//   EXPECT_EQ(2, v.capacity());
// }

TEST(TestConstructorVector, Reserve) {
  int n = 2;
  Vector<int> v;
  v.reserve(n);
  EXPECT_EQ(n, v.capacity());
}

TEST(TestConstructorVector, PushBack) {
  int n = 2;
  Vector<int> v;
  v.push_back(n);
  EXPECT_EQ(2, v[0]);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
