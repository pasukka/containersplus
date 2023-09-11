#include <gtest/gtest.h>

#include "vector.h"

// TODO: std::vector<char> letters {'a', 'b', 'c', 'd', 'e', 'f'};

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

TEST(TestConstructorVector, ConstructorWithParamIntAndValue) {
  int n = 2;
  int m = 5;
  try {
    Vector<int> v(n, m);
    EXPECT_EQ(n, v.size());
    EXPECT_EQ(n, v.capacity());
    EXPECT_EQ(m, v[0]);
    SUCCEED();
  } catch (...) {
    FAIL();
  }
}

TEST(TestConstructorVector, Copy_1) {
  int n = 3;
  Vector<int> v;
  v.push_back(n);

  Vector<int> v2 = v;
  EXPECT_EQ(v2.capacity(), v.capacity());
  EXPECT_EQ(v2.size(), v.size());
}

TEST(TestConstructorVector, Move_1) {
  int n = 3;
  Vector<int> v;
  v.push_back(n);

  Vector<int> v2(std::move(v));
  EXPECT_EQ(0, v.capacity());
  EXPECT_EQ(0, v.size());

  EXPECT_EQ(1, v2.size());
  EXPECT_EQ(n, v2[0]);
}

TEST(TestConstructorVector, Move_2) {
  int n = 3;
  Vector<int> v;
  v.push_back(n);

  Vector<int> v2 = std::move(v);
  EXPECT_EQ(0, v.capacity());
  EXPECT_EQ(0, v.size());

  EXPECT_EQ(1, v2.size());
  EXPECT_EQ(n, v2[0]);
}

TEST(TestConstructorVector, Assign_1) {
  int n = 3;
  Vector<int> v;
  v.push_back(n);
  v.push_back(n + 2);

  int count = 1;
  v.assign(count, 10);
  EXPECT_EQ(count, v.size());
  EXPECT_EQ(10, v[0]);
}

TEST(TestConstructorVector, Assign_2) {
  int n = 3;
  Vector<int> v;
  v.push_back(n);
  v.push_back(n + 2);

  int count = 3;
  v.assign(count, 10);
  EXPECT_EQ(count, v.size());
  EXPECT_EQ(10, v[0]);
  EXPECT_EQ(10, v[2]);
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

TEST(TestFuncs, PopBackInt) {
  int n = 2;
  Vector<int> v;
  v.push_back(n);
  v.push_back(n);

  v.pop_back();
  EXPECT_EQ(1, v.size());
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

TEST(TestFuncs, ShrinkToFit) {
  int n = 2;
  Vector<int> v;
  v.push_back(n);

  int m = 5;
  v.reserve(m);
  EXPECT_EQ(m, v.capacity());

  v.shrink_to_fit();
  EXPECT_EQ(1, v.size());
  EXPECT_EQ(1, v.capacity());
  EXPECT_EQ(n, v[0]);
}

TEST(TestAccess, AtNoExInt) {
  int n = 2;
  Vector<int> v;
  v.push_back(n);
  EXPECT_EQ(n, v.at(0));
}

TEST(TestAccess, AtExInt_1) {
  Vector<int> v;
  try {
    v.at(-1);
    FAIL();
  } catch (std::out_of_range& ex) {
    SUCCEED();
  }
}

TEST(TestAccess, AtExInt_2) {
  Vector<int> v;
  try {
    v.at(0);
    FAIL();
  } catch (std::out_of_range& ex) {
    SUCCEED();
  }
}

TEST(TestAccess, Data) {
  Vector<int> v;
  EXPECT_EQ(v.data(), nullptr);

  int n = 2, m = 3;
  v.push_back(n);
  v.push_back(m);
  int* data = v.data();
  EXPECT_EQ(data[0], v[0]);
  EXPECT_EQ(data[1], v[1]);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
