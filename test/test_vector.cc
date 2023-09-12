#include <gtest/gtest.h>

#include "vector.h"

// TODO: std::vector<char> letters {'a', 'b', 'c', 'd', 'e', 'f'};

TEST(TestConstructorvector, SimpleConstructorInt) {
  vector<int> v;
  EXPECT_EQ(0, v.size());
  EXPECT_EQ(0, v.capacity());
}

TEST(TestConstructorvectorConst, SimpleConstructorInt) {
  const vector<int> v;
  EXPECT_EQ(0, v.size());
  EXPECT_EQ(0, v.capacity());
}

TEST(TestConstructorvector, SimpleConstructorChar) {
  vector<char> v;
  EXPECT_EQ(0, v.size());
  EXPECT_EQ(0, v.capacity());
}

TEST(TestConstructorvectorConst, SimpleConstructorChar) {
  const vector<char> v;
  EXPECT_EQ(0, v.size());
  EXPECT_EQ(0, v.capacity());
}

TEST(TestConstructorvector, SimpleConstructorIntEx) {
  try {
    vector<int> v(-2);
    FAIL();
  } catch (...) {
    SUCCEED();
  }
}

TEST(TestConstructorvectorConst, SimpleConstructorIntEx) {
  try {
    const vector<int> v(-2);
    FAIL();
  } catch (...) {
    SUCCEED();
  }
}

TEST(TestConstructorvector, SimpleConstructorCharEx) {
  try {
    vector<char> v(-2);
    FAIL();
  } catch (...) {
    SUCCEED();
  }
}

TEST(TestConstructorvectorConst, SimpleConstructorCharEx) {
  try {
    const vector<char> v(-2);
    FAIL();
  } catch (...) {
    SUCCEED();
  }
}

TEST(TestConstructorvector, ConstructorWithParamInt) {
  int n = 2;
  try {
    vector<int> v(n);
    EXPECT_EQ(n, v.size());
    EXPECT_EQ(n, v.capacity());
    EXPECT_EQ(0, v[0]);
    SUCCEED();
  } catch (...) {
    FAIL();
  }
}

TEST(TestConstructorvectorConst, ConstructorWithParamInt) {
  int n = 2;
  try {
    const vector<int> v(n);
    EXPECT_EQ(n, v.size());
    EXPECT_EQ(n, v.capacity());
    EXPECT_EQ(0, v[0]);
    EXPECT_EQ(0, v.at(0));
    SUCCEED();
  } catch (...) {
    FAIL();
  }
}

TEST(TestConstructorvector, ConstructorWithParamChar) {
  int n = 2;
  try {
    vector<char> v(n);
    EXPECT_EQ(n, v.size());
    EXPECT_EQ(n, v.capacity());
    EXPECT_EQ(0, v[0]);
    SUCCEED();
  } catch (...) {
    FAIL();
  }
}

TEST(TestConstructorvectorConst, ConstructorWithParamChar) {
  int n = 2;
  try {
    const vector<char> v(n);
    EXPECT_EQ(n, v.size());
    EXPECT_EQ(n, v.capacity());
    EXPECT_EQ(0, v[0]);
    EXPECT_EQ(0, v.at(0));
    SUCCEED();
  } catch (...) {
    FAIL();
  }
}

TEST(TestConstructorvectorConst, At_1) {
  const vector<int> v(2);
  try {
    EXPECT_EQ(0, v.at(10));
    FAIL();
  } catch (...) {
    SUCCEED();
  }
}

TEST(TestConstructorvectorConst, At_2) {
  const vector<int> v(2);
  try {
    EXPECT_EQ(0, v.at(-1));
    FAIL();
  } catch (...) {
    SUCCEED();
  }
}

TEST(TestConstructorvectorConst, At_3) {
  const vector<char> v(2);
  try {
    EXPECT_EQ(0, v.at(10));
    FAIL();
  } catch (...) {
    SUCCEED();
  }
}

TEST(TestConstructorvectorConst, At_4) {
  const vector<char> v(2);
  try {
    EXPECT_EQ(0, v.at(-1));
    FAIL();
  } catch (...) {
    SUCCEED();
  }
}

TEST(TestConstructorvector, ConstructorWithParamIntAndValue) {
  int n = 2;
  int m = 5;
  try {
    vector<int> v(n, m);
    EXPECT_EQ(n, v.size());
    EXPECT_EQ(n, v.capacity());
    EXPECT_EQ(m, v[0]);
    SUCCEED();
  } catch (...) {
    FAIL();
  }
}

TEST(TestConstructorvectorConst, ConstructorWithParamIntAndValue) {
  int n = 2;
  int m = 5;
  try {
    const vector<int> v(n, m);
    EXPECT_EQ(n, v.size());
    EXPECT_EQ(n, v.capacity());
    EXPECT_EQ(m, v[0]);
    SUCCEED();
  } catch (...) {
    FAIL();
  }
}

TEST(TestConstructorvector, ConstructorWithParamValueAndValue) {
  char n = 'a';
  char m = 'b';
  try {
    vector<int> v(n, m);
    EXPECT_EQ(n, v.size());
    EXPECT_EQ(n, v.capacity());
    EXPECT_EQ(m, v[0]);
    SUCCEED();
  } catch (...) {
    FAIL();
  }
}

TEST(TestConstructorvectorConst, ConstructorWithParamValueAndValue) {
  char n = 'a';
  char m = 'b';
  try {
    const vector<int> v(n, m);
    EXPECT_EQ(n, v.size());
    EXPECT_EQ(n, v.capacity());
    EXPECT_EQ(m, v[0]);
    SUCCEED();
  } catch (...) {
    FAIL();
  }
}

TEST(TestConstructorvector, Copy_1) {
  int n = 3;
  vector<int> v;
  v.push_back(n);

  vector<int> v2 = v;
  EXPECT_EQ(v2.capacity(), v.capacity());
  EXPECT_EQ(v2.size(), v.size());
}

TEST(TestConstructorvector, Move_1) {
  int n = 3;
  vector<int> v;
  v.push_back(n);

  vector<int> v2(std::move(v));
  EXPECT_EQ(0, v.capacity());
  EXPECT_EQ(0, v.size());

  EXPECT_EQ(1, v2.size());
  EXPECT_EQ(n, v2[0]);
}

TEST(TestConstructorvector, Move_2) {
  int n = 3;
  vector<int> v;
  v.push_back(n);

  vector<int> v2 = std::move(v);
  EXPECT_EQ(0, v.capacity());
  EXPECT_EQ(0, v.size());

  EXPECT_EQ(1, v2.size());
  EXPECT_EQ(n, v2[0]);
}

TEST(TestConstructorvector, Assign_1) {
  int n = 3;
  vector<int> v;
  v.push_back(n);
  v.push_back(n + 2);

  int count = 1;
  v.assign(count, 10);
  EXPECT_EQ(count, v.size());
  EXPECT_EQ(10, v[0]);
}

TEST(TestConstructorvector, Assign_2) {
  int n = 3;
  vector<int> v;
  v.push_back(n);
  v.push_back(n + 2);

  int count = 3;
  v.assign(count, 10);
  EXPECT_EQ(count, v.size());
  EXPECT_EQ(10, v[0]);
  EXPECT_EQ(10, v[2]);
}

TEST(TestConstructorvector, ConstructFromAnotherInt_1) {
  int n = 3;
  vector<int> v(2);
  v.push_back(n);
  vector<int> v2(v);
  EXPECT_EQ(v.capacity(), v2.capacity());
  EXPECT_EQ(v.size(), v2.size());
  for (size_t i = 0; i < v.size(); ++i) {
    EXPECT_EQ(v[i], v2[i]);
  }
}

TEST(TestConstructorvector, ConstructFromAnotherInt_2) {
  int n = 3;
  vector<int> v(2);
  v.push_back(n);
  vector<int> v2 = v;
  EXPECT_EQ(v.capacity(), v2.capacity());
  EXPECT_EQ(v.size(), v2.size());
  for (size_t i = 0; i < v.size(); ++i) {
    EXPECT_EQ(v[i], v2[i]);
  }
}

TEST(TestConstructorvector, ConstructFromEqual_1) {
  int n = 3;
  vector<int> v(2);
  v.push_back(n);
  vector<int> v2 = v;
  EXPECT_EQ(v.capacity(), v2.capacity());
  EXPECT_EQ(v.size(), v2.size());
  for (size_t i = 0; i < v.size(); ++i) {
    EXPECT_EQ(v[i], v2[i]);
  }
}

TEST(TestFuncs, ResizeInt_1) {
  int n = 10;
  int m = 2;
  vector<int> v;
  v.push_back(n);
  v.resize(m);
  EXPECT_EQ(n, v[0]);
  EXPECT_EQ(m, v.size());
}

TEST(TestFuncs, ResizeInt_2) {
  int n = 10;
  int m = 5;
  int y = 60;
  vector<int> v;
  v.push_back(n);
  v.resize(m, y);

  EXPECT_EQ(n, v[0]);
  EXPECT_EQ(y, v[1]);
  EXPECT_EQ(y, v[4]);
  EXPECT_EQ(m, v.size());
}

TEST(TestFuncs, ResizeInt_3) {
  int n = 10;
  int m = 10;
  int y = 60;
  vector<int> v;
  v.push_back(n);
  v.resize(m, y);

  EXPECT_EQ(n, v[0]);
  EXPECT_EQ(y, v[1]);
  EXPECT_EQ(y, v[4]);
  EXPECT_EQ(m, v.size());
}

TEST(TestFuncs, ReserveInt) {
  int n = 2;
  vector<int> v;
  v.reserve(n);
  EXPECT_EQ(n, v.capacity());
}

TEST(TestFuncs, PushBackInt) {
  int n = 2;
  vector<int> v;
  v.push_back(n);
  EXPECT_EQ(n, v[0]);
}

TEST(TestFuncs, PushBackMoveInt) {
  int n = 2;
  vector<int> v;
  v.push_back(std::move(n));
  EXPECT_EQ(2, v[0]);
}

TEST(TestFuncs, PopBackInt) {
  int n = 2;
  vector<int> v;
  v.push_back(n);
  v.push_back(n);

  v.pop_back();
  EXPECT_EQ(1, v.size());
}

TEST(TestFuncs, SwapInt) {
  int n = 2;
  vector<int> v;
  v.push_back(n);

  int m = 4;
  vector<int> v2;
  v2.push_back(m);

  v.swap(v2);
  EXPECT_EQ(n, v2[0]);
  EXPECT_EQ(m, v[0]);
}

TEST(TestFuncs, ShrinkToFit) {
  int n = 2;
  vector<int> v;
  v.push_back(n);

  int m = 5;
  v.reserve(m);
  EXPECT_EQ(m, v.capacity());

  v.shrink_to_fit();
  EXPECT_EQ(1, v.size());
  EXPECT_EQ(1, v.capacity());
  EXPECT_EQ(n, v[0]);
}

TEST(TestFuncs, Clear) {
  int n = 2;
  vector<int> v;
  v.push_back(n);
  v.push_back(n);
  size_t cap = v.capacity();

  v.clear();
  EXPECT_EQ(0, v.size());
  EXPECT_EQ(cap, v.capacity());
}

TEST(TestAccess, AtNoExInt) {
  int n = 2;
  vector<int> v;
  v.push_back(n);
  EXPECT_EQ(n, v.at(0));
}

TEST(TestAccess, AtExInt_1) {
  vector<int> v;
  try {
    v.at(-1);
    FAIL();
  } catch (std::out_of_range& ex) {
    SUCCEED();
  }
}

TEST(TestAccess, AtExInt_2) {
  vector<int> v;
  try {
    v.at(0);
    FAIL();
  } catch (std::out_of_range& ex) {
    SUCCEED();
  }
}

TEST(TestAccess, Data) {
  vector<int> v;
  EXPECT_EQ(v.data(), nullptr);

  int n = 2, m = 3;
  v.push_back(n);
  v.push_back(m);
  int* data = v.data();
  EXPECT_EQ(data[0], v[0]);
  EXPECT_EQ(data[1], v[1]);
}

TEST(TestAccessConst, Data) {
  const vector<int> v(2);
  const int* data = v.data();
  EXPECT_EQ(data[0], 0);
  EXPECT_EQ(data[1], 0);
}

TEST(TestAccess, FrontBack) {
  vector<int> v;
  int n = 2, m = 3;
  v.push_back(n);
  v.push_back(m);

  EXPECT_EQ(v.front(), n);
  EXPECT_EQ(v.back(), m);
}

TEST(TestAccessConst, FrontBack) {
  const vector<int> v(2);
  EXPECT_EQ(v.front(), 0);
  EXPECT_EQ(v.back(), 0);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
