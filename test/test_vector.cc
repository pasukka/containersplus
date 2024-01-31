#include <gtest/gtest.h>

#include <iostream>
#include <string>
#include <vector>

#include "vector.h"

TEST(VectorTestConstructor, SimpleConstructorInt) {
  vector<int> v;
  EXPECT_EQ(0, v.size());
  EXPECT_EQ(0, v.capacity());
}

TEST(VectorTestConstructorConst, SimpleConstructorInt) {
  const vector<int> v;
  EXPECT_EQ(0, v.size());
  EXPECT_EQ(0, v.capacity());
}

TEST(VectorTestConstructor, SimpleConstructorChar) {
  vector<char> v;
  EXPECT_EQ(0, v.size());
  EXPECT_EQ(0, v.capacity());
}

TEST(VectorTestConstructorConst, SimpleConstructorChar) {
  const vector<char> v;
  EXPECT_EQ(0, v.size());
  EXPECT_EQ(0, v.capacity());
}

TEST(VectorTestConstructor, SimpleConstructorIntEx) {
  try {
    vector<int> v(-2);
    FAIL();
  } catch (...) {
    SUCCEED();
  }
}

TEST(VectorTestConstructorConst, SimpleConstructorIntEx) {
  try {
    const vector<int> v(-2);
    FAIL();
  } catch (...) {
    SUCCEED();
  }
}

TEST(VectorTestConstructor, SimpleConstructorCharEx) {
  try {
    vector<char> v(-2);
    FAIL();
  } catch (...) {
    SUCCEED();
  }
}

TEST(VectorTestConstructorConst, SimpleConstructorCharEx) {
  try {
    const vector<char> v(-2);
    FAIL();
  } catch (...) {
    SUCCEED();
  }
}

TEST(VectorTestConstructor, ConstructorWithParamInt) {
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

TEST(VectorTestConstructor, ConstructorAllocCopy) {
  vector<int> other = {1, 2, 3};
  std::allocator<int> alloc;
  try {
    vector<int> v(other, alloc);
    EXPECT_EQ(other.size(), v.size());
    EXPECT_EQ(other.capacity(), v.capacity());
    SUCCEED();
  } catch (...) {
    FAIL();
  }
}

TEST(VectorTestConstructor, ConstructorWithAllocMove) {
  vector<int> other = {1, 2, 3};
  size_t size = other.size();
  size_t capacity = other.capacity();
  std::allocator<int> alloc;
  try {
    vector<int> v(std::move(other), alloc);
    EXPECT_EQ(size, v.size());
    EXPECT_EQ(capacity, v.capacity());
    SUCCEED();
  } catch (...) {
    FAIL();
  }
}

TEST(VectorTestConstructorConst, ConstructorWithParamInt) {
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

TEST(VectorTestConstructor, ConstructorWithParamChar) {
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

TEST(VectorTestConstructorConst, ConstructorWithParamChar) {
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

TEST(VectorTestConstructorConst, At_1) {
  const vector<int> v(2);
  try {
    EXPECT_EQ(0, v.at(10));
    FAIL();
  } catch (...) {
    SUCCEED();
  }
}

TEST(VectorTestConstructorConst, At_2) {
  const vector<int> v(2);
  try {
    EXPECT_EQ(0, v.at(-1));
    FAIL();
  } catch (...) {
    SUCCEED();
  }
}

TEST(VectorTestConstructorConst, At_3) {
  const vector<char> v(2);
  try {
    EXPECT_EQ(0, v.at(10));
    FAIL();
  } catch (...) {
    SUCCEED();
  }
}

TEST(VectorTestConstructorConst, At_4) {
  const vector<char> v(2);
  try {
    EXPECT_EQ(0, v.at(-1));
    FAIL();
  } catch (...) {
    SUCCEED();
  }
}

// Test contain error in Valgrind because we try to take more memmory than can
// get but Valgrind cannot throw exceptions and so is aborting instead

TEST(VectorTestMemory, ReserveError) {
  vector<char> v = {1, 2, 3};
  try {
    v.reserve(100000000000);
    FAIL();
  } catch (...) {
    SUCCEED();
  }
}

TEST(VectorTestConstructor, ConstructorWithParamIntAndValue) {
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

TEST(VectorTestConstructorConst, ConstructorWithParamIntAndValue) {
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

TEST(VectorTestConstructor, ConstructorWithParamValueAndValue) {
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

TEST(VectorTestConstructorConst, ConstructorWithParamValueAndValue) {
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

TEST(VectorTestConstructor, Copy_1) {
  int n = 3;
  vector<int> v;
  v.push_back(n);

  vector<int> v2 = v;
  EXPECT_EQ(v2.capacity(), v.capacity());
  EXPECT_EQ(v2.size(), v.size());
}

TEST(VectorTestConstructor, Copy_2) {
  int n = 3;
  vector<int> v;
  v.push_back(n);

  vector<int> v2;
  v2 = v;
  EXPECT_EQ(v2.capacity(), v.capacity());
  EXPECT_EQ(v2.size(), v.size());
}

TEST(VectorTestConstructor, Copy_3) {
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
TEST(VectorTestConstructor, Move_1) {
  int n = 3;
  vector<int> v;
  v.push_back(n);

  vector<int> v2(std::move(v));
  EXPECT_EQ(0, v.capacity());
  EXPECT_EQ(0, v.size());

  EXPECT_EQ(1, v2.size());
  EXPECT_EQ(n, v2[0]);
}

TEST(VectorTestConstructor, Move_2) {
  int n = 3;
  vector<int> v;
  v.push_back(n);

  vector<int> v2 = std::move(v);
  EXPECT_EQ(0, v.capacity());
  EXPECT_EQ(0, v.size());

  EXPECT_EQ(1, v2.size());
  EXPECT_EQ(n, v2[0]);
}

TEST(VectorTestConstructor, Assign_1) {
  int n = 3;
  vector<int> v;
  v.push_back(n);
  v.push_back(n + 2);

  int count = 1;
  v.assign(count, 10);
  EXPECT_EQ(count, v.size());
  EXPECT_EQ(10, v[0]);
}

TEST(VectorTestConstructor, Assign_2) {
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

TEST(VectorTestConstructor, ConstructFromAnotherInt_1) {
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

TEST(VectorTestConstructor, ConstructFromAnotherInt_2) {
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

TEST(VectorTestConstructor, ConstructFromEqual_1) {
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

TEST(VectorVectorTestFuncs, ResizeInt_1) {
  int n = 10;
  int m = 2;
  vector<int> v;
  v.push_back(n);
  v.resize(m);
  EXPECT_EQ(n, v[0]);
  EXPECT_EQ(m, v.size());
}

TEST(VectorVectorTestFuncs, ResizeInt_2) {
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

TEST(VectorVectorTestFuncs, ResizeInt_3) {
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

TEST(VectorVectorTestFuncs, ReserveInt) {
  int n = 2;
  vector<int> v;
  v.reserve(n);
  EXPECT_EQ(n, v.capacity());
}

TEST(VectorVectorTestFuncs, PushBackInt) {
  int n = 2;
  vector<int> v;
  v.push_back(n);
  EXPECT_EQ(n, v[0]);
}

TEST(VectorVectorTestFuncs, PushBackMoveInt) {
  int n = 2;
  vector<int> v;
  v.push_back(std::move(n));
  EXPECT_EQ(2, v[0]);
}

TEST(VectorVectorTestFuncs, PopBackInt) {
  int n = 2;
  vector<int> v;
  v.push_back(n);
  v.push_back(n);

  v.pop_back();
  EXPECT_EQ(1, v.size());
}

TEST(VectorVectorTestFuncs, SwapInt) {
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

TEST(VectorVectorTestFuncs, ShrinkToFit) {
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

TEST(VectorVectorTestFuncs, Clear) {
  int n = 2;
  vector<int> v;
  v.push_back(n);
  v.push_back(n);
  size_t cap = v.capacity();

  v.clear();
  EXPECT_EQ(0, v.size());
  EXPECT_EQ(cap, v.capacity());
}

TEST(VectorTestAccess, AtNoExInt) {
  int n = 2;
  vector<int> v;
  v.push_back(n);
  EXPECT_EQ(n, v.at(0));
}

TEST(VectorTestAccess, AtExInt_1) {
  vector<int> v;
  try {
    v.at(-1);
    FAIL();
  } catch (std::out_of_range& ex) {
    SUCCEED();
  }
}

TEST(VectorTestAccess, AtExInt_2) {
  vector<int> v;
  try {
    v.at(0);
    FAIL();
  } catch (std::out_of_range& ex) {
    SUCCEED();
  }
}

TEST(VectorTestAccess, Data) {
  vector<int> v;
  EXPECT_EQ(v.data(), nullptr);

  int n = 2, m = 3;
  v.push_back(n);
  v.push_back(m);
  int* data = v.data();
  EXPECT_EQ(data[0], v[0]);
  EXPECT_EQ(data[1], v[1]);
}

TEST(VectorTestAccessConst, Data) {
  const vector<int> v(2);
  const int* data = v.data();
  EXPECT_EQ(data[0], 0);
  EXPECT_EQ(data[1], 0);
}

TEST(VectorTestAccess, FrontBack) {
  vector<int> v;
  int n = 2, m = 3;
  v.push_back(n);
  v.push_back(m);

  EXPECT_EQ(v.front(), n);
  EXPECT_EQ(v.back(), m);
}

TEST(VectorTestAccessConst, FrontBack) {
  const vector<int> v(2);
  EXPECT_EQ(v.front(), 0);
  EXPECT_EQ(v.back(), 0);
}

TEST(VectorTestConstructorConst, InitializerList) {
  const vector<char> letters{'a', 'b', 'c', 'd', 'e', 'f'};
}

TEST(VectorTestConstructorConst, InitializerListEqual) {
  const vector<char> letters = {'a', 'b', 'c', 'd', 'e', 'f'};
}

TEST(VectorTestAccessConst, InitListFrontBack) {
  const vector<char> letters{'a', 'b', 'c', 'd', 'e', 'f'};
  EXPECT_EQ(letters.front(), 'a');
  EXPECT_EQ(letters.back(), 'f');
}

TEST(VectorTestAccessConst, InitListEqualFrontBack) {
  const vector<char> letters = {'a', 'b', 'c', 'd', 'e', 'f'};
  EXPECT_EQ(letters.front(), 'a');
  EXPECT_EQ(letters.back(), 'f');
}

TEST(VectorTestConstructor, InitializerList) {
  vector<char> letters{'a', 'b', 'c', 'd', 'e', 'f'};
}

TEST(VectorTestConstructor, InitializerListEqual) {
  vector<char> letters = {'a', 'b', 'c', 'd', 'e', 'f'};
}

TEST(VectorTestAccess, InitListFrontBack) {
  vector<char> letters{'a', 'b', 'c', 'd', 'e', 'f'};
  EXPECT_EQ(letters.front(), 'a');
  EXPECT_EQ(letters.back(), 'f');
}

TEST(VectorTestAccess, InitListEqualFrontBack) {
  vector<char> letters = {'a', 'b', 'c', 'd', 'e', 'f'};
  EXPECT_EQ(letters.front(), 'a');
  EXPECT_EQ(letters.back(), 'f');
}

TEST(VectorTestAccess, InitListEqualFrontBack_2) {
  vector<char> letters = {'a', 'b', 'c', 'd', 'e', 'f'};
  letters = {'g', 'h'};
  EXPECT_EQ(letters.front(), 'g');
  EXPECT_EQ(letters.back(), 'h');
}

TEST(VectorTestIter, Begin) {
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

TEST(VectorTestIterConst, Begin) {
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

TEST(VectorTestIter, Cbegin) {
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

TEST(VectorTestIterConst, Cbegin) {
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

TEST(VectorTestIter, Rbegin) {
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

TEST(VectorTestIterConst, Rbegin) {
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

TEST(VectorTestIter, Crbegin) {
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

TEST(VectorTestIterConst, Crbegin) {
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

TEST(VectorTestIter, Rend) {
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

TEST(VectorTestIterConst, Rend) {
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

TEST(VectorTestIter, Crend) {
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

TEST(VectorTestIterConst, Crend) {
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

TEST(VectorVectorTestFunc, EmptyFalse) {
  const vector<char> letters = {'g', 'h'};
  EXPECT_FALSE(letters.empty());
}

TEST(VectorVectorTestFunc, EmptyTrue) {
  const vector<char> letters;
  EXPECT_TRUE(letters.empty());
}

TEST(VectorTestIters, ConstructConst) {
  const vector<char> letters = {'g', 'h', 'l', 'k'};
  auto first = letters.begin();
  auto last = letters.end();

  const vector<char> new_letters(first, last);
  for (size_t i = 0; i < new_letters.size(); ++i) {
    EXPECT_EQ(letters[i], new_letters[i]);
  }
}

TEST(VectorTestIters, Construct) {
  vector<char> letters = {'g', 'h', 'l', 'k'};
  auto first = letters.begin();
  auto last = letters.end();

  vector<char> new_letters(first, last);
  for (size_t i = 0; i < new_letters.size(); ++i) {
    EXPECT_EQ(letters[i], new_letters[i]);
  }
}

TEST(VectorTestIters, Insert) {
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
  EXPECT_EQ(to_insert_2, 'i');

  for (size_t i = 0; i < new_letters.size(); ++i) {
    EXPECT_EQ(letters[i], new_letters[i]);
  }
}

TEST(VectorTestIters, InsertMove) {
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

TEST(VectorTestIters, InsertCount) {
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

TEST(VectorTestIters, InsertCountNeg) {
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

TEST(VectorTestIters, InsertIter) {
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

TEST(VectorTestIters, InsertList) {
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

TEST(VectorTestIters, Erase) {
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

TEST(VectorTestIters, EraseIter) {
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

TEST(VectorTestCompare, Equal) {
  vector<char> v1 = {'g', 'h', 'l', 'k'};
  vector<char> v2 = {'g', 'h', 'l', 'k'};
  EXPECT_EQ(v1, v2);
}

TEST(VectorTestCompare, NotEqual) {
  vector<char> v1 = {'g', 'h', 'l', 'k'};
  vector<char> v2 = {'g', 'h', 'l', 'l'};
  EXPECT_NE(v1, v2);
}

TEST(VectorTestCompare, NotEqual2) {
  vector<char> v1 = {'g', 'h', 'l'};
  vector<char> v2 = {'g', 'h', 'l', 'l'};
  EXPECT_NE(v1, v2);
}

TEST(VectorTestCompare, Smaller) {
  vector<char> v1 = {'g', 'h', 'l', 'k'};
  vector<char> v2 = {'g', 'h', 'l', 'l'};
  EXPECT_TRUE(v1 < v2);
}

TEST(VectorTestCompare, Smaller2) {
  vector<char> v1 = {'g', 'h', 'l'};
  vector<char> v2 = {'g', 'h', 'l', 'l'};
  EXPECT_TRUE(v1 < v2);
}

TEST(VectorTestCompare, Bigger) {
  vector<char> v1 = {'g', 'h', 'l', 'k'};
  vector<char> v2 = {'g', 'h', 'l', 'l'};
  EXPECT_TRUE(v2 > v1);
}

TEST(VectorTestCompare, BiggerOrEqual) {
  vector<char> v1 = {'g', 'h', 'l', 'k'};
  vector<char> v2 = {'g', 'h', 'l', 'k'};
  EXPECT_TRUE(v2 >= v1);
}

TEST(VectorTestCompare, SmallerOrEqual) {
  vector<char> v1 = {'g', 'h', 'l', 'k'};
  vector<char> v2 = {'g', 'h', 'l', 'k'};
  EXPECT_TRUE(v2 <= v1);
}

TEST(VectorTestFunc, EmplaceValue) {
  std::vector<char> letters = {'g', 'h', 'l', 'k', 'j', 'o', 'a', 's'};
  auto pos_std = letters.begin() + 2;
  char value = 'u';
  auto res = letters.emplace(pos_std, value);

  vector<char> new_letters = {'g', 'h', 'l', 'k', 'j', 'o', 'a', 's'};
  auto pos = new_letters.begin() + 2;
  auto my_res = new_letters.emplace(pos, value);

  EXPECT_EQ(letters.size(), new_letters.size());
  EXPECT_EQ(*res, *my_res);
  for (size_t i = 0; i < new_letters.size(); ++i) {
    EXPECT_EQ(letters[i], new_letters[i]);
  }
}

TEST(VectorTestFunc, EmplaceBack) {
  std::vector<char> letters = {'g', 'h', 'l', 'k', 'j', 'o', 'a', 's'};
  char value = 'u';
  auto res = letters.emplace_back(value);

  vector<char> new_letters = {'g', 'h', 'l', 'k', 'j', 'o', 'a', 's'};
  auto my_res = new_letters.emplace_back(value);

  EXPECT_EQ(letters.size(), new_letters.size());
  EXPECT_EQ(res, my_res);
  for (size_t i = 0; i < new_letters.size(); ++i) {
    EXPECT_EQ(letters[i], new_letters[i]);
  }
}

TEST(VectorTestFunc, EmplaceString) {
  std::vector<std::string> vtr = {"donkey",        "goat",   "cat",   "pig",
                                  "dog",           "Cow",    "Sheep", "horse",
                                  "water buffalo", "red fox"};
  auto value = "panda";
  auto res = vtr.emplace_back(value);

  vector<std::string> new_vtr = {"donkey",        "goat",   "cat",   "pig",
                                 "dog",           "Cow",    "Sheep", "horse",
                                 "water buffalo", "red fox"};
  auto my_res = new_vtr.emplace_back(value);

  EXPECT_EQ(vtr.size(), new_vtr.size());
  EXPECT_EQ(res, my_res);
  for (size_t i = 0; i < vtr.size(); ++i) {
    EXPECT_EQ(vtr[i], new_vtr[i]);
  }
}

TEST(VectorTestAlloc, GetAlloc) {
  vector<int> other = {1, 2, 3};
  auto alloc = other.get_allocator();
  try {
    vector<int> v(2, alloc);
    SUCCEED();
  } catch (...) {
    FAIL();
  }
}
