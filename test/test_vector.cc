#include <gtest/gtest.h>

#include <vector>

#include "vector.h"

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
  char n = 2;
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
  char n = 2;
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

TEST(TestConstructorvector, Copy_2) {
  int n = 3;
  vector<int> v;
  v.push_back(n);

  vector<int> v2;
  v2 = v;
  EXPECT_EQ(v2.capacity(), v.capacity());
  EXPECT_EQ(v2.size(), v.size());
}

TEST(TestConstructorvector, Copy_3) {
  int n = 3;
  vector<int> v;
  v.push_back(n);
  size_t cap = v.capacity();
  size_t size = v.size();

  vector<int> v2;
  v2 = std::move(v);
  EXPECT_NE(v2.capacity(), v.capacity());
  EXPECT_NE(v2.size(), v.size());
  EXPECT_EQ(v2.capacity(), cap);
  EXPECT_EQ(v2.size(), size);
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

TEST(TestConstructorvectorConst, InitializerList) {
  const vector<char> letters{'a', 'b', 'c', 'd', 'e', 'f'};
}

TEST(TestConstructorvectorConst, InitializerListEqual) {
  const vector<char> letters = {'a', 'b', 'c', 'd', 'e', 'f'};
}

TEST(TestAccessConst, InitListFrontBack) {
  const vector<char> letters{'a', 'b', 'c', 'd', 'e', 'f'};
  EXPECT_EQ(letters.front(), 'a');
  EXPECT_EQ(letters.back(), 'f');
}

TEST(TestAccessConst, InitListEqualFrontBack) {
  const vector<char> letters = {'a', 'b', 'c', 'd', 'e', 'f'};
  EXPECT_EQ(letters.front(), 'a');
  EXPECT_EQ(letters.back(), 'f');
}

TEST(TestConstructorvector, InitializerList) {
  vector<char> letters{'a', 'b', 'c', 'd', 'e', 'f'};
}

TEST(TestConstructorvector, InitializerListEqual) {
  vector<char> letters = {'a', 'b', 'c', 'd', 'e', 'f'};
}

TEST(TestAccess, InitListFrontBack) {
  vector<char> letters{'a', 'b', 'c', 'd', 'e', 'f'};
  EXPECT_EQ(letters.front(), 'a');
  EXPECT_EQ(letters.back(), 'f');
}

TEST(TestAccess, InitListEqualFrontBack) {
  vector<char> letters = {'a', 'b', 'c', 'd', 'e', 'f'};
  EXPECT_EQ(letters.front(), 'a');
  EXPECT_EQ(letters.back(), 'f');
}

TEST(TestAccess, InitListEqualFrontBack_2) {
  vector<char> letters = {'a', 'b', 'c', 'd', 'e', 'f'};
  letters = {'g', 'h'};
  EXPECT_EQ(letters.front(), 'g');
  EXPECT_EQ(letters.back(), 'h');
}

TEST(TestIter, Begin) {
  vector<char> letters = {'g', 'h'};
  std::vector<char> letters_std = {'g', 'h'};
  auto it = letters.begin();
  auto std_it = letters_std.begin();
  for (size_t i = 0; i < letters_std.size(); ++i) {
    EXPECT_EQ(*it, *std_it);
    ++it;
    ++std_it;
  }
}

TEST(TestIterConst, Begin) {
  const vector<char> letters = {'g', 'h'};
  const std::vector<char> letters_std = {'g', 'h'};
  auto it = letters.begin();
  auto std_it = letters_std.begin();
  for (size_t i = 0; i < letters_std.size(); ++i) {
    EXPECT_EQ(*it, *std_it);
    ++it;
    ++std_it;
  }
}

TEST(TestIter, Cbegin) {
  vector<char> letters = {'g', 'h'};
  std::vector<char> letters_std = {'g', 'h'};
  auto it = letters.cbegin();
  auto std_it = letters_std.cbegin();
  for (size_t i = 0; i < letters_std.size(); ++i) {
    EXPECT_EQ(*it, *std_it);
    ++it;
    ++std_it;
  }
}

TEST(TestIterConst, Cbegin) {
  const vector<char> letters = {'g', 'h'};
  const std::vector<char> letters_std = {'g', 'h'};
  auto it = letters.cbegin();
  auto std_it = letters_std.cbegin();
  for (size_t i = 0; i < letters_std.size(); ++i) {
    EXPECT_EQ(*it, *std_it);
    ++it;
    ++std_it;
  }
}

TEST(TestIter, Rbegin) {
  vector<char> letters = {'g', 'h'};
  std::vector<char> letters_std = {'g', 'h'};
  auto it = letters.rbegin();
  auto std_it = letters_std.rbegin();
  for (size_t i = 0; i < letters_std.size(); ++i) {
    EXPECT_EQ(*it, *std_it);
    ++it;
    ++std_it;
  }
}

TEST(TestIterConst, Rbegin) {
  const vector<char> letters = {'g', 'h'};
  const std::vector<char> letters_std = {'g', 'h'};
  auto it = letters.rbegin();
  auto std_it = letters_std.rbegin();
  for (size_t i = 0; i < letters_std.size(); ++i) {
    EXPECT_EQ(*it, *std_it);
    ++it;
    ++std_it;
  }
}

TEST(TestIter, Crbegin) {
  vector<char> letters = {'g', 'h'};
  std::vector<char> letters_std = {'g', 'h'};
  auto it = letters.crbegin();
  auto std_it = letters_std.crbegin();
  for (size_t i = 0; i < letters_std.size(); ++i) {
    EXPECT_EQ(*it, *std_it);
    ++it;
    ++std_it;
  }
}

TEST(TestIterConst, Crbegin) {
  const vector<char> letters = {'g', 'h'};
  const std::vector<char> letters_std = {'g', 'h'};
  auto it = letters.crbegin();
  auto std_it = letters_std.crbegin();
  for (size_t i = 0; i < letters_std.size(); ++i) {
    EXPECT_EQ(*it, *std_it);
    ++it;
    ++std_it;
  }
}

// Tests for ends contain leaks because we reach element after vector.
// There will be 8 leaks for 4 tests: one for our implementation
// and another for real vector.

TEST(TestIter, Rend) {
  vector<char> letters = {'g', 'h'};
  std::vector<char> letters_std = {'g', 'h'};
  auto it = letters.rend();
  auto std_it = letters_std.rend();
  for (size_t i = letters_std.size() - 1; i > 0; --i) {
    EXPECT_EQ(*it, *std_it);
    --it;
    --std_it;
  }
}

TEST(TestIterConst, Rend) {
  const vector<char> letters = {'g', 'h'};
  const std::vector<char> letters_std = {'g', 'h'};
  auto it = letters.rend();
  auto std_it = letters_std.rend();
  for (size_t i = letters_std.size() - 1; i > 0; --i) {
    EXPECT_EQ(*it, *std_it);
    --it;
    --std_it;
  }
}

TEST(TestIter, Crend) {
  vector<char> letters = {'g', 'h'};
  std::vector<char> letters_std = {'g', 'h'};
  auto it = letters.crend();
  auto std_it = letters_std.crend();
  for (size_t i = letters_std.size() - 1; i > 0; --i) {
    EXPECT_EQ(*it, *std_it);
    --it;
    --std_it;
  }
}

TEST(TestIterConst, Crend) {
  const vector<char> letters = {'g', 'h'};
  const std::vector<char> letters_std = {'g', 'h'};
  auto it = letters.crend();
  auto std_it = letters_std.crend();
  for (size_t i = letters_std.size() - 1; i > 0; --i) {
    EXPECT_EQ(*it, *std_it);
    --it;
    --std_it;
  }
}

TEST(TestFunc, EmptyFalse) {
  const vector<char> letters = {'g', 'h'};
  EXPECT_FALSE(letters.empty());
}

TEST(TestFunc, EmptyTrue) {
  const vector<char> letters;
  EXPECT_TRUE(letters.empty());
}

TEST(TestIters, ConstructConst) {
  const vector<char> letters = {'g', 'h', 'l', 'k'};
  auto first = letters.begin();
  auto last = letters.end();

  const vector<char> new_letters(first, last);
  for (size_t i = 0; i < new_letters.size(); ++i) {
    EXPECT_EQ(letters[i], new_letters[i]);
  }
}

TEST(TestIters, Construct) {
  vector<char> letters = {'g', 'h', 'l', 'k'};
  auto first = letters.begin();
  auto last = letters.end();

  vector<char> new_letters(first, last);
  for (size_t i = 0; i < new_letters.size(); ++i) {
    EXPECT_EQ(letters[i], new_letters[i]);
  }
}

TEST(TestIters, Insert) {
  char to_insert_1 = 'o';
  char to_insert_2 = 'i';

  std::vector<char> letters = {'g', 'h', 'l', 'k'};
  auto first_std = letters.begin();
  letters.insert(first_std + 2, to_insert_1);

  vector<char> new_letters = {'g', 'h', 'l', 'k'};
  auto first = new_letters.begin();
  new_letters.insert(first + 2, to_insert_1);

  auto last_std = letters.end();
  auto res = letters.insert(last_std - 1, to_insert_2);

  auto last = new_letters.end();
  auto my_res = new_letters.insert(last - 1, to_insert_2);

  EXPECT_EQ(letters.size(), new_letters.size());
  EXPECT_EQ(*res, *my_res);

  for (size_t i = 0; i < new_letters.size(); ++i) {
    EXPECT_EQ(letters[i], new_letters[i]);
  }
}

TEST(TestIters, InsertMove) {
  char to_insert_1 = 'o';
  char to_insert_2 = 'i';

  std::vector<char> letters = {'g', 'h', 'l', 'k'};
  auto first_std = letters.begin();
  letters.insert(first_std + 2, std::move(to_insert_1));

  vector<char> new_letters = {'g', 'h', 'l', 'k'};
  auto first = new_letters.begin();
  new_letters.insert(first + 2, std::move(to_insert_1));

  auto last_std = letters.end();
  auto res = letters.insert(last_std - 1, std::move(to_insert_2));

  auto last = new_letters.end();
  auto my_res = new_letters.insert(last - 1, std::move(to_insert_2));

  EXPECT_EQ(letters.size(), new_letters.size());
  EXPECT_EQ(*res, *my_res);
  for (size_t i = 0; i < new_letters.size(); ++i) {
    EXPECT_EQ(letters[i], new_letters[i]);
  }
}

TEST(TestIters, InsertCount) {
  char to_insert_1 = 'o';
  char to_insert_2 = 'i';

  std::vector<char> letters = {'g', 'h', 'l', 'k'};
  auto first_std = letters.begin();
  letters.insert(first_std + 2, 2, to_insert_1);

  vector<char> new_letters = {'g', 'h', 'l', 'k'};
  auto first = new_letters.begin();
  new_letters.insert(first + 2, 2, to_insert_1);

  auto last_std = letters.end();
  letters.insert(last_std - 1, 6, to_insert_2);

  auto last = new_letters.end();
  new_letters.insert(last - 1, 6, to_insert_2);  // -1

  EXPECT_EQ(letters.size(), new_letters.size());
  for (size_t i = 0; i < new_letters.size(); ++i) {
    EXPECT_EQ(letters[i], new_letters[i]);
  }
}

TEST(TestIters, InsertCountNeg) {
  try {
    char to_insert = 'o';
    vector<char> new_letters = {'g', 'h', 'l', 'k'};
    auto first = new_letters.begin();
    new_letters.insert(first + 2, -2, to_insert);
    FAIL();
  } catch (std::length_error& ex) {
    SUCCEED();
  }
}

TEST(TestIters, InsertIter) {
  std::vector<char> list_1 = {'i', 'l', 'o', 'v', 'e', 'i', 't'};
  vector<char> list_2 = {'i', 'l', 'o', 'v', 'e', 'i', 't'};

  std::vector<char> letters = {'g', 'h', 'l', 'k'};
  auto pos_std = letters.begin() + 1;
  letters.insert(pos_std, list_1.begin() + 1, list_1.begin() + 5);

  vector<char> new_letters = {'g', 'h', 'l', 'k'};
  auto pos = new_letters.begin() + 1;
  new_letters.insert(pos, list_2.begin() + 1, list_2.begin() + 5);

  EXPECT_EQ(letters.size(), new_letters.size());
  for (size_t i = 0; i < new_letters.size(); ++i) {
    EXPECT_EQ(letters[i], new_letters[i]);
  }
}

TEST(TestIters, InsertList) {
  std::initializer_list<char> list = {'i', 'l', 'o', 'v', 'e', 'i', 't'};

  std::vector<char> letters = {'g', 'h', 'l', 'k'};
  auto pos_std = letters.begin() + 3;
  auto res = letters.insert(pos_std, list);

  vector<char> new_letters = {'g', 'h', 'l', 'k'};
  auto pos = new_letters.begin() + 3;
  auto my_res = new_letters.insert(pos, list);

  EXPECT_EQ(letters.size(), new_letters.size());
  EXPECT_EQ(*res, *my_res);
  for (size_t i = 0; i < new_letters.size(); ++i) {
    EXPECT_EQ(letters[i], new_letters[i]);
  }
}

TEST(TestIters, Erase) {
  std::vector<char> letters = {'g', 'h', 'l', 'k', 'f', 'u', 'i'};
  auto pos_std = letters.begin() + 1;
  auto res = letters.erase(pos_std);

  vector<char> new_letters = {'g', 'h', 'l', 'k', 'f', 'u', 'i'};
  auto pos = new_letters.begin() + 1;
  auto my_res = new_letters.erase(pos);

  EXPECT_EQ(letters.size(), new_letters.size());
  EXPECT_EQ(*res, *my_res);
  for (size_t i = 0; i < new_letters.size(); ++i) {
    EXPECT_EQ(letters[i], new_letters[i]);
  }
}

TEST(TestIters, EraseIter) {
  std::vector<char> letters = {'g', 'h', 'l', 'k', 'j', 'o', 'a', 's'};
  auto fisrt_std = letters.begin() + 2;
  auto last_std = letters.begin() + 4;
  auto res = letters.erase(fisrt_std, last_std);

  vector<char> new_letters = {'g', 'h', 'l', 'k', 'j', 'o', 'a', 's'};
  auto fisrt = new_letters.begin() + 2;
  auto last = new_letters.begin() + 4;
  auto my_res = new_letters.erase(fisrt, last);

  EXPECT_EQ(letters.size(), new_letters.size());
  EXPECT_EQ(*res, *my_res);
  for (size_t i = 0; i < new_letters.size(); ++i) {
    EXPECT_EQ(letters[i], new_letters[i]);
  }
}

TEST(TestCompare, Equal) {
  vector<char> v1 = {'g', 'h', 'l', 'k'};
  vector<char> v2 = {'g', 'h', 'l', 'k'};
  EXPECT_EQ(v1, v2);
}

TEST(TestCompare, NotEqual) {
  vector<char> v1 = {'g', 'h', 'l', 'k'};
  vector<char> v2 = {'g', 'h', 'l', 'l'};
  EXPECT_NE(v1, v2);
}

TEST(TestCompare, NotEqual2) {
  vector<char> v1 = {'g', 'h', 'l'};
  vector<char> v2 = {'g', 'h', 'l', 'l'};
  EXPECT_NE(v1, v2);
}

TEST(TestCompare, Smaller) {
  vector<char> v1 = {'g', 'h', 'l', 'k'};
  vector<char> v2 = {'g', 'h', 'l', 'l'};
  EXPECT_TRUE(v1 < v2);
}

TEST(TestCompare, Smaller2) {
  vector<char> v1 = {'g', 'h', 'l'};
  vector<char> v2 = {'g', 'h', 'l', 'l'};
  EXPECT_TRUE(v1 < v2);
}

TEST(TestCompare, Bigger) {
  vector<char> v1 = {'g', 'h', 'l', 'k'};
  vector<char> v2 = {'g', 'h', 'l', 'l'};
  EXPECT_TRUE(v2 > v1);
}

TEST(TestCompare, BiggerOrEqual) {
  vector<char> v1 = {'g', 'h', 'l', 'k'};
  vector<char> v2 = {'g', 'h', 'l', 'k'};
  EXPECT_TRUE(v2 >= v1);
}

TEST(TestCompare, SmallerOrEqual) {
  vector<char> v1 = {'g', 'h', 'l', 'k'};
  vector<char> v2 = {'g', 'h', 'l', 'k'};
  EXPECT_TRUE(v2 <= v1);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
