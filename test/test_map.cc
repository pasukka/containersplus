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
    m1.insert({ 1, 10 });

    
}