#include <gtest/gtest.h>

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "map.h"

TEST(MapTestConstructor, SimpleConstructorInt) {
  map<int, int> map1;
  std::map<int, int> map2;
  EXPECT_EQ(map2.size(), map1.size());
}

TEST(MapTestMaxSize, MaxSize) {
  map<int, int> map1;
  std::map<int, int> map2;
  EXPECT_NE(0, map1.max_size());
  EXPECT_NE(map2.max_size(), map1.max_size());
}

TEST(MapTestSwap, Swap) {
  int val = 60;
  int key = 2;

  map<int, int> map1;
  map<int, int> map2;
  map1.insert({key, val});

  std::map<int, int> std_map1;
  std::map<int, int> std_map2;
  std_map1.insert({key, val});

  EXPECT_EQ(std_map1[key], map1[key]);

  map2.insert({key + 1, val + 2});
  map2.swap(map1);

  std_map2.insert({key + 1, val + 2});
  std_map2.swap(std_map1);

  auto std_it = std_map1.begin();
  auto our_it = map1.begin();
  for (size_t i = 0; i < std_map1.size() - 1; ++i) {
    ++std_it;
    ++our_it;
    EXPECT_EQ(*std_it, *our_it);
  }

  std_it = std_map2.begin();
  our_it = map2.begin();
  for (size_t i = 0; i < std_map2.size() - 1; ++i) {
    ++std_it;
    ++our_it;
    EXPECT_EQ(*std_it, *our_it);
  }
}

TEST(MapTestCopy, Copy_1) {
  map<int, int> map1;
  map<int, int> map2;

  std::map<int, int> std_map1;
  std::map<int, int> std_map2;

  int val = 60;
  int key = 2;
  map1.insert({key, val});
  map1.insert({key + 1, val + 2});
  std_map1.insert({key, val});
  std_map1.insert({key + 1, val + 2});

  map2 = map1;
  std_map2 = std_map1;
  EXPECT_EQ(map1[key], map2[key]);
  EXPECT_EQ(map1[key + 1], map2[key + 1]);
  EXPECT_EQ(map1.size(), map2.size());

  auto std_it = std_map1.begin();
  auto our_it = map1.begin();
  for (size_t i = 0; i < std_map1.size() - 1; ++i) {
    ++std_it;
    ++our_it;
    EXPECT_EQ(*std_it, *our_it);
  }

  std_it = std_map2.begin();
  our_it = map2.begin();
  for (size_t i = 0; i < std_map2.size() - 1; ++i) {
    ++std_it;
    ++our_it;
    EXPECT_EQ(*std_it, *our_it);
  }
}

TEST(MapTestCopy, Copy_2) {
  map<int, int> map1;
  std::map<int, int> std_map1;

  int val = 60;
  int key = 2;
  map1.insert({key, val});
  map1.insert({key + 1, val + 2});
  std_map1.insert({key, val});
  std_map1.insert({key + 1, val + 2});

  std::map<int, int> std_map2(std_map1);
  map<int, int> map2(map1);

  EXPECT_EQ(map1[key], map2[key]);
  EXPECT_EQ(map1.size(), map2.size());

  auto std_it = std_map1.begin();
  auto our_it = map1.begin();
  for (size_t i = 0; i < std_map1.size() - 1; ++i) {
    ++std_it;
    ++our_it;
    EXPECT_EQ(*std_it, *our_it);
  }

  std_it = std_map2.begin();
  our_it = map2.begin();
  for (size_t i = 0; i < std_map2.size() - 1; ++i) {
    ++std_it;
    ++our_it;
    EXPECT_EQ(*std_it, *our_it);
  }
}

TEST(MapTestMove, Move_1) {
  map<int, int> map1;
  std::map<int, int> std_map1;
  int val = 60;
  int key = 2;
  map1.insert({key, val});
  std_map1.insert({key, val});

  map<int, int> map2;
  std::map<int, int> std_map2;
  map2 = std::move(map1);
  std_map2 = std::move(std_map1);
  EXPECT_EQ(map2[key], val);
  EXPECT_EQ(1, map2.size());
  EXPECT_EQ(0, map1.size());

  auto std_it = std_map1.begin();
  auto our_it = map1.begin();

  std_it = std_map2.begin();
  our_it = map2.begin();
  for (size_t i = 0; i < std_map2.size() - 1; ++i) {
    ++std_it;
    ++our_it;
    EXPECT_EQ(*std_it, *our_it);
  }
}

TEST(MapTestMove, Move_2) {
  map<int, int> map1;
  std::map<int, int> std_map1;

  int val = 60;
  int key = 2;
  map1.insert({key, val});
  std_map1.insert({key, val});

  map<int, int> map2(std::move(map1));
  std::map<int, int> std_map2(std::move(std_map1));

  EXPECT_EQ(map2[key], val);
  EXPECT_EQ(1, map2.size());
  EXPECT_EQ(0, map1.size());

  auto std_it = std_map1.begin();
  auto our_it = map1.begin();

  std_it = std_map2.begin();
  our_it = map2.begin();
  for (size_t i = 0; i < std_map2.size() - 1; ++i) {
    ++std_it;
    ++our_it;
    EXPECT_EQ(*std_it, *our_it);
  }
}

TEST(MapTestMerge, Merge) {
  int val = 60;
  int key = 20;
  map<int, int> map1;
  map<int, int> map2;
  map1.insert(key, val);
  map1.insert(key + 3, val);
  map1.insert(key + 34, val);
  map1.insert(key - 14, val);

  map2.insert(key, val);
  map2.insert(key + 78, val);
  map2.insert(key + 1, val);
  map2.insert(key - 6, val);

  map1.merge(map2);

  std::map<int, int> map11;
  std::map<int, int> map12;
  map11.insert({key, val});
  map11.insert({key + 3, val});
  map11.insert({key + 34, val});
  map11.insert({key - 14, val});

  map12.insert({key, val});
  map12.insert({key + 78, val});
  map12.insert({key + 1, val});
  map12.insert({key - 6, val});

  map11.merge(map12);

  for (auto it = map11.begin(); it != map11.end(); ++it) {
    EXPECT_FLOAT_EQ(it->second, map11[it->first]);
  }
  EXPECT_EQ(map11.size(), map1.size());
}

TEST(MapTestInsert, InsertKeyVal) {
  map<int, int> map1;
  std::map<int, int> std_map1;
  int val = 60;
  map1.insert({2, val});
  std_map1.insert({2, val});
  EXPECT_EQ(val, map1[2]);

  auto std_it = std_map1.begin();
  auto our_it = map1.begin();

  std_it = std_map1.begin();
  our_it = map1.begin();
  for (size_t i = 0; i < std_map1.size() - 1; ++i) {
    ++std_it;
    ++our_it;
    EXPECT_EQ(*std_it, *our_it);
  }
}

TEST(MapTestInsert, SimpleInsertInt) {
  map<int, int> map1;
  std::map<int, int> std_map1;
  int val = 60;
  map1.insert({2, val});
  map1.insert({1, val});
  map1.insert({3, val});
  map1.insert({4, val});
  std_map1.insert({2, val});
  std_map1.insert({1, val});
  std_map1.insert({3, val});
  std_map1.insert({4, val});
  EXPECT_EQ(val, map1[3]);

  auto std_it = std_map1.begin();
  auto our_it = map1.begin();

  std_it = std_map1.begin();
  our_it = map1.begin();
  for (size_t i = 0; i < std_map1.size() - 1; ++i) {
    ++std_it;
    ++our_it;
    EXPECT_EQ(*std_it, *our_it);
  }
}

TEST(MapTestInsert, SimpleInsertInt2) {
  map<int, int> map1;
  std::map<int, int> std_map1;
  int val = 60;
  int key = 2;
  map1.insert({key, val});
  std_map1.insert({key, val});
  EXPECT_EQ(val, map1[key]);

  auto std_it = std_map1.begin();
  auto our_it = map1.begin();

  std_it = std_map1.begin();
  our_it = map1.begin();
  for (size_t i = 0; i < std_map1.size() - 1; ++i) {
    ++std_it;
    ++our_it;
    EXPECT_EQ(*std_it, *our_it);
  }
}

TEST(MapTestInsert, InsertNoChange) {
  map<int, int> map1;
  std::map<int, int> std_map1;
  int val = 60;
  int key = 2;
  map1.insert({key, val});
  map1.insert({key, 3});
  std_map1.insert({key, val});
  std_map1.insert({key, 3});

  EXPECT_EQ(val, map1[key]);
  auto std_it = std_map1.begin();
  auto our_it = map1.begin();

  std_it = std_map1.begin();
  our_it = map1.begin();
  for (size_t i = 0; i < std_map1.size() - 1; ++i) {
    ++std_it;
    ++our_it;
    EXPECT_EQ(*std_it, *our_it);
  }
}

TEST(MapTestInsert, InsertChange) {
  map<int, int> map1;
  std::map<int, int> std_map1;

  int val = 60;
  int key = 2;
  map1.insert({key, val});
  map1[key] = val + 2;
  std_map1.insert({key, val});
  std_map1[key] = val + 2;

  EXPECT_EQ(val + 2, map1[key]);

  auto std_it = std_map1.begin();
  auto our_it = map1.begin();

  std_it = std_map1.begin();
  our_it = map1.begin();
  for (size_t i = 0; i < std_map1.size() - 1; ++i) {
    ++std_it;
    ++our_it;
    EXPECT_EQ(*std_it, *our_it);
  }
}

TEST(MapTestInsert, InsertInt) {
  map<int, int> map1;
  std::map<int, int> std_map1;

  int val = 60;
  int key = 2;
  map1[key] = val;
  std_map1[key] = val;
  EXPECT_EQ(val, map1[key]);
  EXPECT_EQ(1, map1.size());

  auto std_it = std_map1.begin();
  auto our_it = map1.begin();

  std_it = std_map1.begin();
  our_it = map1.begin();
  for (size_t i = 0; i < std_map1.size() - 1; ++i) {
    ++std_it;
    ++our_it;
    EXPECT_EQ(*std_it, *our_it);
  }
}

TEST(MapTestInsert, InsertList) {
  map<int, int> map1;
  std::map<int, int> std_map1;
  int val = 60;
  int key = 2;
  map1[key] = val;
  std_map1[key] = val;
  EXPECT_EQ(val, map1[key]);

  auto list = {std::pair<const int, int>{1, 2}, {3, 4}, {5, 6}};
  map1.insert(list);
  std_map1.insert(list);
  EXPECT_EQ(val, map1[key]);
  EXPECT_EQ(4, map1.size());

  auto std_it = std_map1.begin();
  auto our_it = map1.begin();

  std_it = std_map1.begin();
  our_it = map1.begin();
  for (size_t i = 0; i < std_map1.size() - 1; ++i) {
    ++std_it;
    ++our_it;
    EXPECT_EQ(*std_it, *our_it);
  }
}

TEST(MapTestInsertOrAssign, InsertInt) {
  map<int, int> map1;
  std::map<int, int> std_map1;
  int val = 60;
  int key = 2;
  map1[key] = val;
  map1.insert_or_assign(key, val + 1);
  std_map1[key] = val;
  std_map1.insert_or_assign(key, val + 1);
  EXPECT_EQ(val + 1, map1[key]);

  auto std_it = std_map1.begin();
  auto our_it = map1.begin();

  std_it = std_map1.begin();
  our_it = map1.begin();
  for (size_t i = 0; i < std_map1.size() - 1; ++i) {
    ++std_it;
    ++our_it;
    EXPECT_EQ(*std_it, *our_it);
  }
}

TEST(MapTestInsertOrAssign, InsertEndInt) {
  map<int, int> map1;
  std::map<int, int> std_map1;
  int val = 60;
  int key = 2;
  map1.insert_or_assign(key, val);
  std_map1.insert_or_assign(key, val);
  EXPECT_EQ(val, map1[key]);

  auto std_it = std_map1.begin();
  auto our_it = map1.begin();

  std_it = std_map1.begin();
  our_it = map1.begin();
  for (size_t i = 0; i < std_map1.size() - 1; ++i) {
    ++std_it;
    ++our_it;
    EXPECT_EQ(*std_it, *our_it);
  }
}

TEST(MapTestInsertOrAssign, InsertIntMove) {
  map<int, int> map1;
  std::map<int, int> std_map1;
  int val = 60;
  int key = 2;
  map1[key] = val;
  map1.insert_or_assign(std::move(key), val + 1);
  std_map1[key] = val;
  std_map1.insert_or_assign(std::move(key), val + 1);
  EXPECT_EQ(val + 1, map1[key]);

  auto std_it = std_map1.begin();
  auto our_it = map1.begin();

  std_it = std_map1.begin();
  our_it = map1.begin();
  for (size_t i = 0; i < std_map1.size() - 1; ++i) {
    ++std_it;
    ++our_it;
    EXPECT_EQ(*std_it, *our_it);
  }
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

TEST(MapTestErase, Erase_1) {
  map<int, int> map1;
  std::map<int, int> std_map1;
  int val = 60;
  int key = 2;
  map1[key] = val;
  map1[key + 1] = val + 90;
  map1[key + 6] = val + 74;
  std_map1[key] = val;
  std_map1[key + 1] = val + 90;
  std_map1[key + 6] = val + 74;

  auto begin = map1.begin();
  ++begin;
  map1.erase(begin);
  auto std_begin = std_map1.begin();
  ++std_begin;
  std_map1.erase(std_begin);

  EXPECT_EQ(map1[key], val);
  EXPECT_EQ(2, map1.size());

  auto std_it = std_map1.begin();
  auto our_it = map1.begin();

  std_it = std_map1.begin();
  our_it = map1.begin();
  for (size_t i = 0; i < std_map1.size() - 1; ++i) {
    ++std_it;
    ++our_it;
    EXPECT_EQ(*std_it, *our_it);
  }
}

TEST(MapTestErase, Erase_2) {
  map<int, int> map1;
  int val = 60;
  int key = 2;
  map1[key] = val;
  map1[key + 1] = val + 90;
  map1[key + 6] = val + 74;
  auto begin = map1.begin();
  map1.erase(begin);
  EXPECT_EQ(map1[key + 1], val + 90);
  EXPECT_EQ(2, map1.size());
}

TEST(MapTestErase, Erase_3) {
  map<int, int> map1;
  int val = 60;
  int key = 2;
  map1[key] = val;
  map1[key - 1] = val + 90;
  map1[key + 6] = val + 74;
  auto begin = map1.begin();
  map1.erase(begin);
  EXPECT_EQ(map1[key], val);
  EXPECT_EQ(2, map1.size());
}

TEST(MapTestErase, Erase_4) {
  map<int, int> map1;
  std::map<int, int> std_map1;
  int val = 60;
  int key = 2;
  map1[key] = val;
  map1[key - 1] = val + 90;
  map1[key - 6] = val + 74;
  auto begin = map1.begin();
  map1.erase(begin);

  std_map1[key] = val;
  std_map1[key - 1] = val + 90;
  std_map1[key - 6] = val + 74;
  auto std_begin = std_map1.begin();
  std_map1.erase(std_begin);

  EXPECT_EQ(map1[key - 1], val + 90);
  EXPECT_EQ(2, map1.size());

  auto std_it = std_map1.begin();
  auto our_it = map1.begin();

  std_it = std_map1.begin();
  our_it = map1.begin();
  for (size_t i = 0; i < std_map1.size() - 1; ++i) {
    ++std_it;
    ++our_it;
    EXPECT_EQ(*std_it, *our_it);
  }
}

TEST(MapTestErase, Erase_5) {
  map<int, int> map1;
  int val = 60;
  int key = 2;
  map1[key] = val;
  map1[key + 3] = val + 90;
  map1[key + 1] = val + 74;
  map1[key + 6] = val + 74;
  auto begin = map1.begin();
  ++begin;
  map1.erase(begin);
  EXPECT_EQ(map1[key + 3], val + 90);
  EXPECT_EQ(3, map1.size());
}

TEST(MapTestErase, Erase_6) {
  map<int, int> map1;
  int val = 60;
  int key = 2;
  map1[key] = val;
  map1[key + 3] = val + 90;
  map1[key + 1] = val + 74;
  map1[key + 6] = val + 74;
  auto begin = map1.begin();
  map1.erase(begin);
  EXPECT_EQ(map1[key + 1], val + 74);
  EXPECT_EQ(3, map1.size());
}

TEST(MapTestErase, Erase_7) {
  map<int, int> map1;
  std::map<int, int> std_map1;
  int val = 60;
  int key = 2;
  map1[key] = val;
  map1[key - 1] = val + 90;
  map1[key + 1] = val + 90;
  map1[key + 6] = val + 74;
  auto begin = map1.begin();
  ++begin;
  ++begin;
  map1.erase(begin);

  std_map1[key] = val;
  std_map1[key - 1] = val + 90;
  std_map1[key + 1] = val + 90;
  std_map1[key + 6] = val + 74;
  auto std_begin = std_map1.begin();
  ++std_begin;
  ++std_begin;
  std_map1.erase(std_begin);

  EXPECT_EQ(map1[key], val);
  EXPECT_EQ(3, map1.size());

  auto std_it = std_map1.begin();
  auto our_it = map1.begin();

  std_it = std_map1.begin();
  our_it = map1.begin();
  for (size_t i = 0; i < std_map1.size() - 1; ++i) {
    ++std_it;
    ++our_it;
    EXPECT_EQ(*std_it, *our_it);
  }
}

TEST(MapTestErase, Erase_8) {
  map<int, int> map1;
  int val = 60;
  int key = 3;
  map1[key] = val;
  map1[key - 1] = val + 90;
  map1[key - 2] = val + 74;
  auto begin = map1.begin();
  ++begin;
  map1.erase(begin);
  EXPECT_EQ(map1[key - 2], val + 74);
  EXPECT_EQ(2, map1.size());
}

TEST(MapTestErase, Erase_9) {
  map<int, int> map1;
  int val = 60;
  int key = 2;
  map1[key] = val;
  map1[key + 6] = val + 74;
  auto begin = map1.begin();
  map1.erase(begin);
  EXPECT_EQ(map1[key + 6], val + 74);
  EXPECT_EQ(1, map1.size());
  EXPECT_NE(map1[key], val);
}

TEST(MapTestErase, Erase_10) {
  map<int, int> map1;
  int val = 60;
  int key = 2;
  map1[key] = val;
  map1[key - 1] = val + 74;
  auto begin = map1.begin();
  map1.erase(begin);
  EXPECT_EQ(map1[key], val);
  EXPECT_EQ(1, map1.size());
}

TEST(MapTestErase, Erase_11) {
  map<int, int> map1;
  std::map<int, int> std_map1;
  int val = 60;
  int key = 3;
  map1[key] = val;
  map1[key - 1] = val + 74;
  map1[key - 2] = val + 80;
  auto begin = map1.begin();
  ++begin;
  ++begin;
  map1.erase(begin);
  EXPECT_EQ(map1[key - 1], val + 74);
  EXPECT_EQ(2, map1.size());

  std_map1[key] = val;
  std_map1[key - 1] = val + 74;
  std_map1[key - 2] = val + 80;
  auto std_begin = std_map1.begin();
  ++std_begin;
  ++std_begin;
  std_map1.erase(std_begin);
  auto std_it = std_map1.begin();
  auto our_it = map1.begin();

  std_it = std_map1.begin();
  our_it = map1.begin();
  for (size_t i = 0; i < std_map1.size() - 1; ++i) {
    ++std_it;
    ++our_it;
    EXPECT_EQ(*std_it, *our_it);
  }
}

TEST(MapTestErase, Erase_12) {
  map<int, int> map1;
  int val = 60;
  int key = 3;
  map1[key] = val;
  map1[key - 1] = val + 74;
  map1[key + 1] = val + 80;
  auto begin = map1.begin();
  ++begin;
  ++begin;
  map1.erase(begin);
  EXPECT_EQ(map1[key - 1], val + 74);
  EXPECT_EQ(2, map1.size());
}

TEST(MapTestErase, EraseRange) {
  map<int, int> map;
  std::map<int, int> std_map1;
  map.insert({1, 10});
  map.insert({2, 20});
  map.insert({3, 30});
  map.insert({4, 40});
  map.insert({5, 50});

  map.erase(map.find(2), map.find(4));

  std_map1.insert({1, 10});
  std_map1.insert({2, 20});
  std_map1.insert({3, 30});
  std_map1.insert({4, 40});
  std_map1.insert({5, 50});

  std_map1.erase(std_map1.find(2), std_map1.find(4));

  EXPECT_EQ(3, map.size());

  EXPECT_EQ(map[1], 10);
  EXPECT_EQ(map[4], 40);
  EXPECT_EQ(map[5], 50);

  auto std_it = std_map1.begin();
  auto our_it = map.begin();

  std_it = std_map1.begin();
  our_it = map.begin();
  for (size_t i = 0; i < std_map1.size() - 1; ++i) {
    ++std_it;
    ++our_it;
    EXPECT_EQ(*std_it, *our_it);
  }
}

TEST(MapTestExtract, ExtractByPosition) {
  map<int, int> map;
  map.insert({1, 10});
  map.insert({2, 20});
  map.insert({3, 30});
  map.insert({4, 40});
  map.insert({5, 50});

  auto it = map.find(2);
  auto extractedNode = map.extract(it);
  EXPECT_EQ(4, map.size());
  int a = extractedNode.getNode()->data.first;
  int b = extractedNode.getNode()->data.second;
  EXPECT_EQ(3, a);
  EXPECT_EQ(30, b);
}

TEST(MapTestExtract, ExtractByKey) {
  map<int, int> map;
  map.insert({1, 10});
  map.insert({2, 20});
  map.insert({3, 30});
  map.insert({4, 40});
  map.insert({5, 50});

  auto extractedNode = map.extract(3);

  int a = extractedNode.getNode()->data.first;
  int b = extractedNode.getNode()->data.second;

  EXPECT_EQ(4, map.size());
  EXPECT_EQ(4, a);
  EXPECT_EQ(40, b);
}

TEST(MapTestExtract, ExtractNonexistentKey) {
  map<int, int> map;
  map.insert({1, 10});
  map.insert({2, 20});
  map.insert({3, 30});
  map.insert({4, 40});
  map.insert({5, 50});

  auto extractedNode = map.extract(6);

  EXPECT_EQ(5, map.size());
  EXPECT_EQ(map.end(), extractedNode);
}

TEST(MapTestContains, Contains) {
  map<int, int> map1;
  int val = 60;
  int key = 2;
  map1[key] = val;
  EXPECT_TRUE(map1.contains(key));
  EXPECT_FALSE(map1.contains(key - 1));
}

TEST(MapTestIter, IteratorBeginEnd) {
  map<int, float> num_map;
  std::map<int, float> num_map2;

  num_map.insert({4, 4.13});
  num_map.insert({9, 9.24});
  num_map.insert({1, 1.09});

  num_map2.insert({4, 4.13});
  num_map2.insert({9, 9.24});
  num_map2.insert({1, 1.09});
  EXPECT_EQ(3, num_map.size());

  for (auto it = num_map.begin(); it != num_map.end(); ++it) {
    EXPECT_FLOAT_EQ(it->second, num_map2[it->first]);
  }
}

TEST(MapTestIter, IteratorConstBegin) {
  int key = 2;
  int val = 3;
  const map<int, float> num_map = {std::pair<const int, int>{key, val}};
  const auto it = num_map.begin();
  EXPECT_EQ(key, (*it).first);
  EXPECT_EQ(val, (*it).second);
}

TEST(MapTestIter, IteratorCBegin) {
  int key = 2;
  int val = 3;
  const map<int, float> num_map = {std::pair<const int, int>{key, val}};
  const auto it = num_map.cbegin();
  const auto it2 = num_map.cend();
  EXPECT_EQ(key, (*it).first);
  EXPECT_EQ(val, (*it).second);
  EXPECT_NE(it2, it);
}

TEST(MapTestIter, InsertEndLast) {
  auto list = {std::pair<const char, char>{'a', 'b'}, {'c', 'd'}, {'e', 'f'}};
  map<char, char> our_map = list;
  std::map<char, char> std_map = list;
  auto our_it = our_map.end();
  --our_it;
  auto std_it = std_map.end();
  --std_it;
  EXPECT_EQ(*our_it, *std_it);
}

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
  const int res = map1.at(key + 1);
  EXPECT_EQ(val + 1, res);
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

TEST(MapTestAt, AtNoKey_1) {
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

TEST(MapTestAt, AtKey_4) {
  int val = 60;
  const int key = 2;
  const map<int, int> map1 = {std::pair<const int, int>{key, val}};
  EXPECT_EQ(val, map1.at(key));
}

TEST(MapTestAt, AtNoKey_2) {
  int val = 60;
  const int key = 2;
  const map<int, int> map1 = {std::pair<const int, int>{key, val}};
  const int key2 = 1;
  try {
    map1.at(key2);
    FAIL();
  } catch (std::out_of_range &ex) {
    SUCCEED();
  }
}

TEST(MapTestConstructor, SimpleConstructorInitList) {
  map<const char, char> map1;
  std::map<const char, char> std_map1;
  auto list = {std::pair<const char, char>{'a', 'b'}, {'c', 'd'}, {'e', 'f'}};
  map1 = list;
  std_map1 = list;
  EXPECT_EQ('b', map1['a']);
  EXPECT_EQ('f', map1['e']);

  auto std_it = std_map1.begin();
  auto our_it = map1.begin();

  std_it = std_map1.begin();
  our_it = map1.begin();
  for (size_t i = 0; i < std_map1.size() - 1; ++i) {
    ++std_it;
    ++our_it;
    EXPECT_EQ(*std_it, *our_it);
  }
}

TEST(MapTestCompare, Key_Comp) {
  map<int, char> cont{{1, 'a'}, {2, 'b'}, {3, 'c'}, {4, 'd'}, {5, 'e'}};
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
  map<int, char, ModCmp> cont;
  cont = {{1, 'a'}, {2, 'b'}, {3, 'c'}, {4, 'd'}, {5, 'e'}};
  auto comp_func = cont.key_comp();
  bool res = comp_func(20, 100);
  EXPECT_FALSE(res);
}

TEST(MapTestAlloc, GetAlloc_1) {
  map<int, int> other = {{1, 2}};
  auto alloc = other.get_allocator();
  try {
    map<int, int> map1(other, alloc);
    SUCCEED();
  } catch (...) {
    FAIL();
  }
}

TEST(MapTestAlloc, GetAlloc_2) {
  map<int, int> other = {{1, 2}};
  auto alloc = other.get_allocator();
  try {
    map<int, int> map1(std::move(other), alloc);
    SUCCEED();
  } catch (...) {
    FAIL();
  }
}

TEST(MapTestAlloc, GetAlloc_3) {
  map<int, int> other = {{1, 2}};
  auto alloc = other.get_allocator();
  try {
    map<int, char> cont({{1, 'a'}, {2, 'b'}, {3, 'c'}, {4, 'd'}, {5, 'e'}},
                        alloc);
    SUCCEED();
  } catch (...) {
    FAIL();
  }
}
