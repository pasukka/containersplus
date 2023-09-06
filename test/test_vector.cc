#include <gtest/gtest.h>

#include "vector.h"

TEST(TestConstructorVector, SimpleConstructorInt) {
  Vector<int> v;
  EXPECT_EQ(0, v.size());
  EXPECT_EQ(0, v.capacity());
}

TEST(TestConstructorVector, SimpleConstructorIntEx) {
  try {
    Vector<int> v(-2);
    FAIL();
  } catch (...) {
    SUCCEED();
  }
}

TEST(TestConstructorVector, ConstructorWithParamInt) {
  int n = 2;
  try {
    Vector<int> v(n);
    EXPECT_EQ(n, v.size());
    EXPECT_EQ(n, v.capacity());
    EXPECT_EQ(0, v[0]);
    SUCCEED();
  } catch (...) {
    FAIL();
  }
}

TEST(TestConstructorVector, ConstructFromAnotherInt_1) {
  int n = 3;
  Vector<int> v(2);
  v.push_back(n);
  Vector<int> v2(v);
  EXPECT_EQ(v.capacity(), v2.capacity());
  EXPECT_EQ(v.size(), v2.size());
  for (size_t i = 0; i < v.size(); ++i) {
    EXPECT_EQ(v[i], v2[i]);
  }
}

TEST(TestConstructorVector, ConstructFromAnotherInt_2) {
  int n = 3;
  Vector<int> v(2);
  v.push_back(n);
  Vector<int> v2 = v;
  EXPECT_EQ(v.capacity(), v2.capacity());
  EXPECT_EQ(v.size(), v2.size());
  for (size_t i = 0; i < v.size(); ++i) {
    EXPECT_EQ(v[i], v2[i]);
  }
}

TEST(TestFuncs, ReserveInt) {
  int n = 2;
  Vector<int> v;
  v.reserve(n);
  EXPECT_EQ(n, v.capacity());
}

TEST(TestFuncs, PushBackInt) {
  int n = 2;
  Vector<int> v;
  v.push_back(n);
  EXPECT_EQ(n, v[0]);
}

TEST(TestFuncs, SwapInt) {
  int n = 2;
  Vector<int> v;
  v.push_back(n);

  int m = 4;
  Vector<int> v2;
  v2.push_back(m);

  v.swap(v2);
  EXPECT_EQ(n, v2[0]);
  EXPECT_EQ(m, v[0]);
}

TEST(TestAccess, AtNoExInt) {
  int n = 2;
  Vector<int> v;
  v.push_back(n);
  EXPECT_EQ(n, v.at(0));
}

TEST(TestAccess, AtExInt) {
  Vector<int> v;
  try {
    v.at(0);
    FAIL();
  } catch (std::out_of_range& ex) {
    EXPECT_STREQ("Index out of range.", ex.what());
  }
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
