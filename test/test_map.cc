#include <gtest/gtest.h>

#include <iostream>
#include <map>
#include <vector>
#include <string>

#include "map.h"

TEST(MapTestConstructor, SimpleConstructorInt) {
  map<int, int> map1;
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

TEST(MapTestIter, IteratorBeginEnd) {
  map<int, float> num_map;
  std::vector v1 = {4, 9, 1};
  std::vector v2 = {4.13, 9.24, 1.09};

  num_map.insert({4, 4.13});
  num_map.insert({9, 9.24});
  num_map.insert({1, 1.09});
  EXPECT_EQ(3, num_map.size());

  size_t i = 0;
  // for (auto it = num_map.begin(); it != num_map.end(); ++it, ++i) {
  //   EXPECT_EQ(it->first, v1[i]);
  //   EXPECT_EQ(it->second, v2[i]);
  // }
}

// TEST(MapTestConstructor, SimpleConstructorString) {
//   map<std::string, int> map1;
//   int val = 69;
//   map1["something"] = val;
//   EXPECT_EQ(1, map1.size());
//   EXPECT_EQ(val, map1["something"]);
// }
