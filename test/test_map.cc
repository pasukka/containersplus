#include <gtest/gtest.h>

#include <iostream>
#include <map>
#include <string>

#include "map.h"

TEST(MapTestConstructor, SimpleConstructorInt) {
  map<int, int> map1;
  EXPECT_EQ(0, map1.size());

  std::map<int, int> m;
}

// TEST(MapTestConstructor, SimpleConstructorString) {
//   map<std::string, int> map1;
//   int val = 69;
//   map1["something"] = val;
//   EXPECT_EQ(1, map1.size());
//   EXPECT_EQ(val, map1["something"]);
// }

TEST(MapTestInsert, SimpleInsert) {
  map<int, int> m1;
  int num = 10;
  auto aa = m1.insert({1, num});
  EXPECT_EQ(aa.second, true);
  EXPECT_EQ(m1[1], num);
  for (size_t i = 0; i < m1.size(); ++i) {
    printf("\n %d \n", *(aa.first));
    // EXPECT_EQ(*it, *std_it);
  }

}