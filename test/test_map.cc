#include <gtest/gtest.h>

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "map.h"

TEST(MapTestConstructor, SimpleConstructorInt) {
  map<int, int> map1;
  EXPECT_EQ(0, map1.size());
}

TEST(MapTestCopy, Copy_1) {
  map<int, int> map1;
  int val = 60;
  int key = 2;
  map1.insert({key, val});
  map<int, int> map2;
  map2 = map1;
  EXPECT_EQ(map1[key], map2[key]);
  EXPECT_EQ(map1.size(), map2.size());
}

TEST(MapTestCopy, Copy_2) {
  map<int, int> map1;
  int val = 60;
  int key = 2;
  map1.insert({key, val});
  map<int, int> map2(map1);
  EXPECT_EQ(map1[key], map2[key]);
  EXPECT_EQ(map1.size(), map2.size());
}

TEST(MapTestMove, Move_1) {
  map<int, int> map1;
  int val = 60;
  int key = 2;
  map1.insert({key, val});
  map<int, int> map2;
  map2 = std::move(map1);
  EXPECT_EQ(map2[key], val);
  EXPECT_EQ(1, map2.size());
  EXPECT_EQ(0, map1.size());
}

TEST(MapTestMove, Move_2) {
  map<int, int> map1;
  int val = 60;
  int key = 2;
  map1.insert({key, val});
  map<int, int> map2(std::move(map1));
  EXPECT_EQ(map2[key], val);
  EXPECT_EQ(1, map2.size());
  EXPECT_EQ(0, map1.size());
}

TEST(MapTestInsert, SimpleInsertInt) {
  map<int, int> map1;
  int val = 60;
  map1.insert({2, val});
  map1.insert({1, val});
  map1.insert({3, val});
  map1.insert({4, val});
  EXPECT_EQ(val, map1[3]);
}

TEST(MapTestInsert, SimpleInsertInt2) {
  map<int, int> map1;
  int val = 60;
  int key = 2;
  map1.insert({key, val});
  EXPECT_EQ(val, map1[key]);
}

TEST(MapTestInsert, InsertNoChange) {
  map<int, int> map1;
  int val = 60;
  int key = 2;
  map1.insert({key, val});
  map1.insert({key, 3});
  EXPECT_EQ(val, map1[key]);
}

TEST(MapTestInsert, InsertChange) {
  map<int, int> map1;
  int val = 60;
  int key = 2;
  map1.insert({key, val});
  map1[key] = val + 2;
  EXPECT_EQ(val + 2, map1[key]);
}

TEST(MapTestInsert, InsertInt) {
  map<int, int> map1;
  int val = 60;
  int key = 2;
  map1[key] = val;
  // EXPECT_EQ(val, map1[key]);
}

TEST(MapTestInsert, InsertList) {
  map<int, int> map1;
  int val = 60;
  int key = 2;
  map1[key] = val;
  EXPECT_EQ(val, map1[key]);
  auto list = {std::pair<const int, int>{1, 2}, {3, 4}, {5, 6}};
  map1.insert(list);
  EXPECT_EQ(4, map1.size());
}

TEST(MapTestInsertOrAssign, InsertInt) {
  map<int, int> map1;
  int val = 60;
  int key = 2;
  map1[key] = val;
  map1.insert_or_assign(key, val + 1);
  EXPECT_EQ(val + 1, map1[key]);
}

TEST(MapTestInsertOrAssign, InsertIntMove) {
  map<int, int> map1;
  int val = 60;
  int key = 2;
  map1[key] = val;
  map1.insert_or_assign(std::move(key), val + 1);
  EXPECT_EQ(val + 1, map1[key]);
}

TEST(MapTestEmpty, Empty) {
  map<int, int> map1;
  EXPECT_TRUE(map1.empty());
  int val = 60;
  int key = 2;
  map1[key] = val;
  EXPECT_FALSE(map1.empty());
}

TEST(MapTestClear, Clear) {
  map<int, int> map1;
  int val = 60;
  int key = 2;
  map1[key] = val;
  map1.clear();
  EXPECT_EQ(0, map1.size());
  EXPECT_NE(map1[key], val);
}

// TEST(MapTestIter, IteratorBeginEnd) {
//   map<int, float> num_map;
//   std::vector v1 = {4, 9, 1};
//   std::vector v2 = {4.13, 9.24, 1.09};

//   num_map.insert({4, 4.13});
//   num_map.insert({9, 9.24});
//   num_map.insert({1, 1.09});
//   EXPECT_EQ(3, num_map.size());

//   size_t i = 0;
//   for (auto it = num_map.begin(); it != num_map.end(); ++it, ++i) {
//     printf("\n %d %f\n", it->first, it->second);
//     EXPECT_EQ(it->first, v1[i]);
//     EXPECT_EQ(it->second, v2[i]);
//   }
// }

TEST(MapTestAccess, AccessNoKey_1) {
  map<int, int> map1;
  int val = 60;
  int key = 2;
  map1.insert({key, val});
  EXPECT_EQ(0, map1[1]);
  EXPECT_EQ(val, map1[key]);
}

TEST(MapTestAccess, AccessNoKey_2) {
  map<int, int> map1;
  int val = 60;
  int key = 2;
  int k = 1;
  map1.insert({key, val});
  EXPECT_EQ(0, map1[k]);
}

TEST(MapTestAt, AtKey_1) {
  map<int, int> map1;
  int val = 60;
  int key = 2;
  map1.insert({key, val});
  EXPECT_EQ(val, map1.at(key));
}

TEST(MapTestAt, AtKey_2) {
  map<int, int> map1;
  int val = 60;
  int key = 2;
  map1.insert({key, val});
  map1.insert({key + 1, val + 1});
  EXPECT_EQ(val + 1, map1.at(key + 1));
}

TEST(MapTestAt, AtKey_3) {
  map<int, int> map1;
  int val = 60;
  int key = 2;
  map1.insert({key, val});
  map1.insert({key + 1, val + 1});
  map1.insert({key + 2, val + 2});
  map1.insert({key + 23, val + 23});
  const auto val1 = map1.at(key + 23);
  EXPECT_EQ(val + 23, val1);
}

TEST(MapTestAt, AtNoKey) {
  map<int, int> map1;
  int val = 60;
  int key = 2;
  map1.insert({key, val});
  try {
    map1.at(1);
    FAIL();
  } catch (std::out_of_range &ex) {
    SUCCEED();
  }
}

TEST(MapTestConstructor, SimpleConstructorInitList) {
  map<const char, char> map1;
  auto list = {std::pair<const char, char>{'a', 'b'}, {'c', 'd'}, {'e', 'f'}};
  map1 = list;
  EXPECT_EQ('b', map1['a']);
  EXPECT_EQ('f', map1['e']);
}

TEST(MapTestCompare, Key_Comp) {
  std::map<int, char> cont{{1, 'a'}, {2, 'b'}, {3, 'c'}, {4, 'd'}, {5, 'e'}};
  auto comp_func = cont.key_comp();
  bool res = comp_func(20, 100);
  EXPECT_TRUE(res);
}

TEST(MapTestCompare, Key_Comp_2) {
  struct ModCmp {
    bool operator()(const int lhs, const int rhs) const {
      return (lhs % 97) < (rhs % 97);
    }
  };
  std::map<int, char, ModCmp> cont;
  cont = {{1, 'a'}, {2, 'b'}, {3, 'c'}, {4, 'd'}, {5, 'e'}};
  auto comp_func = cont.key_comp();
  bool res = comp_func(20, 100);
  EXPECT_FALSE(res);
}
