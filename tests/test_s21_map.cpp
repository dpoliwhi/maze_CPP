#include <gtest/gtest.h>

#include <map>
#include <string>

#include "../s21_map.h"

TEST(Map, test1) {
  s21::map<int, int> d;
  std::map<int, int> c;
  ASSERT_EQ(d.empty() == c.empty(), true);
}

TEST(Map, test2) {
  s21::map<int, int> d = {{12, 112}, {13, 113}, {10, 100}, {5, 55}, {7, 77}, {2, 22}};
  std::map<int, int> c = {{12, 112}, {13, 113}, {10, 100}, {5, 55}, {7, 77}, {2, 22}};
  ASSERT_EQ(d.size() == c.size(), true);
}

TEST(Map, test3) {
  s21::map<int, int> d = {{12, 112}, {13, 113}, {10, 100}, {5, 55}, {7, 77}, {2, 22}};
  s21::map<int, int> c(d);
  ASSERT_EQ(d.size() == c.size(), true);
}

TEST(Map, test4) {
  s21::map<int, int> d = {{12, 112}, {13, 113}, {10, 100}, {5, 55}, {7, 77}, {2, 22}};
  s21::map<int, int> c(std::move(d));
  ASSERT_EQ(d.size() == 0, true);
  ASSERT_EQ(c.size() == 6, true);
}

TEST(Map, test5) {
  s21::map<int, int> d = {{12, 112}, {13, 113}, {10, 100}, {5, 55}, {7, 77}, {2, 22}};
  s21::map<int, int> c;
  c = std::move(d);
  ASSERT_EQ(d.size() == 0, true);
  ASSERT_EQ(c.size() == 6, true);
}

TEST(Map, test6) {
  s21::map<int, int> d = {{12, 112}, {13, 113}, {10, 100}, {5, 55}, {7, 77}, {2, 22}};
  s21::map<int, int> c;
  c = d;
  ASSERT_EQ(d.size() == c.size(), true);
}

TEST(Map, test7) {
  s21::map<int, int> d = {{12, 112}, {13, 113}, {10, 100}, {5, 55}, {7, 77}, {2, 22}};
  typename s21::map<int, int>::iterator iter_d(d.begin());
  std::pair<int, int> d_pair = *iter_d;
  typename s21::map<int, int>::iterator iter_d1(d.end());
  std::pair<int, int> d_pair1 = *iter_d1;
  std::map<int, int> c = {{12, 112}, {13, 113}, {10, 100}, {5, 55}, {7, 77}, {2, 22}};
  std::map<int, int>::iterator iter_c(c.begin());
  std::pair<int, int> c_pair = *iter_c;
  std::map<int, int>::iterator iter_c1(c.end());
  std::pair<int, int> c_pair1 = *iter_c1;
  ASSERT_EQ(d_pair.second == c_pair.second, true);
  ASSERT_EQ(d_pair.first == c_pair.first, true);
  ASSERT_EQ(d_pair1.second == c_pair1.second, true);
}

TEST(Map, test9) {
  s21::map<int, int> d = {{12, 112}, {13, 113}, {10, 100}, {5, 55}, {7, 77}, {2, 22}};
  typename s21::map<int, int>::iterator iter_d(d.begin());
  ++iter_d;
  std::pair<int, int> d_pair = *iter_d;
  typename s21::map<int, int>::iterator iter_d1(d.end());
  --iter_d1;
  std::pair<int, int> d_pair1 = *iter_d1;
  std::map<int, int> c = {{12, 112}, {13, 113}, {10, 100}, {5, 55}, {7, 77}, {2, 22}};
  std::map<int, int>::iterator iter_c(c.begin());
  ++iter_c;
  std::pair<int, int> c_pair = *iter_c;
  std::map<int, int>::iterator iter_c1(c.end());
  --iter_c1;
  std::pair<int, int> c_pair1 = *iter_c1;
  ASSERT_EQ(d_pair.second == c_pair.second, true);
  ASSERT_EQ(d_pair.first == c_pair.first, true);
  ASSERT_EQ(d_pair1.second == c_pair1.second, true);
}

TEST(Map, test10) {
  s21::map<int, int> d = {{12, 112}, {13, 113}, {10, 100}, {5, 55}, {7, 77}, {2, 22}};
  typename s21::map<int, int>::iterator iter_d1(d.end());
  ++iter_d1;
  std::pair<int, int> d_pair1 = *iter_d1;
  std::map<int, int> c = {{12, 112}, {13, 113}, {10, 100}, {5, 55}, {7, 77}, {2, 22}};
  std::map<int, int>::iterator iter_c1(c.end());
  ++iter_c1;
  std::pair<int, int> c_pair1 = *iter_c1;
  ASSERT_EQ(d_pair1.second == c_pair1.second, true);
  ++iter_c1;
  c_pair1 = *iter_c1;
  ++iter_d1;
  d_pair1 = *iter_d1;
  ASSERT_EQ(d_pair1.second == c_pair1.second, true);
}

TEST(Map, test11) {
  s21::map<int, int> d = {{12, 112}, {13, 113}, {10, 100}, {5, 55}, {7, 77}, {2, 22}};
  typename s21::map<int, int>::iterator iter_d1(d.begin());
  std::map<int, int> c = {{12, 112}, {13, 113}, {10, 100}, {5, 55}, {7, 77}, {2, 22}};
  std::map<int, int>::iterator iter_c1(c.begin());
  for (int i = 0; i < 6; i++) {
    ++iter_d1;
    ++iter_c1;
  }
  std::pair<int, int> d_pair1 = *iter_d1;
  std::pair<int, int> c_pair1 = *iter_c1;
  ASSERT_EQ(d_pair1.second == c_pair1.second, true);
}

TEST(Map, test12) {
  s21::map<int, int> d = {{12, 112}, {13, 113}, {10, 100}, {5, 55}, {7, 77}, {2, 22}};
  typename s21::map<int, int>::iterator iter_d1(d.end());

  std::map<int, int> c = {{12, 112}, {13, 113}, {10, 100}, {5, 55}, {7, 77}, {2, 22}};
  std::map<int, int>::iterator iter_c1(c.end());
  for (int i = 0; i < 6; i++) {
    --iter_d1;
    --iter_c1;
  }
  std::pair<int, int> d_pair1 = *iter_d1;
  std::pair<int, int> c_pair1 = *iter_c1;
  ASSERT_EQ(d_pair1.second == c_pair1.second, true);
}

TEST(Map, test13) {
  s21::map<int, int> d = {{12, 112}, {13, 113}, {10, 100}, {5, 55}, {7, 77}, {2, 22}};
  typename s21::map<int, int>::iterator iter_d1(d.begin());
  d.erase(iter_d1);
  std::map<int, int> c = {{12, 112}, {13, 113}, {10, 100}, {5, 55}, {7, 77}, {2, 22}};
  std::map<int, int>::iterator iter_c1(c.begin());
  c.erase(iter_c1);
  ASSERT_EQ(d.size() == c.size(), true);
  auto iter_check1(d.begin());
  auto iter_check2(c.begin());
  std::pair<int, int> d_pair = *iter_check1;
  std::pair<int, int> c_pair = *iter_check2;
  ASSERT_EQ(d_pair.second == c_pair.second, true);
}

TEST(Map, test14) {
  s21::map<int, int> d = {{12, 112}, {13, 113}, {10, 100}, {5, 55}, {7, 77}, {2, 22}};
  ASSERT_EQ(d.contains(5) == true, true);
  ASSERT_EQ(d.contains(3) == false, true);
}

TEST(Map, test15) {
  s21::map<int, int> d = {{12, 112}, {13, 113}, {10, 100}, {5, 55}, {7, 77},
                          {2, 22},   {1, 33},   {14, 98},  {6, 57}};
  s21::map<int, int> d1 = {{12, 112}, {13, 113}, {10, 100}};
  d.swap(d1);
  std::map<int, int> c = {{12, 112}, {13, 113}, {10, 100}, {5, 55}, {7, 77},
                          {2, 22},   {1, 33},   {14, 98},  {6, 57}};
  std::map<int, int> c1 = {{12, 112}, {13, 113}, {10, 100}};
  c.swap(c1);
  ASSERT_EQ(d.size() == c.size(), true);
  ASSERT_EQ(d1.size() == c1.size(), true);
}

TEST(Map, test16) {
  s21::map<int, int> d = {{12, 112}, {13, 113}, {10, 100}, {5, 55}, {7, 77},
                          {2, 22},   {1, 33},   {14, 98},  {6, 57}};
  d.clear();
  std::map<int, int> c = {{12, 112}, {13, 113}, {10, 100}, {5, 55}, {7, 77},
                          {2, 22},   {1, 33},   {14, 98},  {6, 57}};
  c.clear();
  ASSERT_EQ(d.size() == c.size(), true);
}

TEST(Map, test17) {
  s21::map<int, int> d = {{12, 112}, {13, 113}, {10, 100}, {5, 55}, {7, 77}, {2, 22}};
  d.insert({1, 11});
  typename s21::map<int, int>::iterator iter_d1(d.begin());
  std::pair<int, int> d_pair1 = *iter_d1;
  std::map<int, int> c = {{12, 112}, {13, 113}, {10, 100}, {5, 55}, {7, 77}, {2, 22}};
  c.insert({1, 11});
  std::map<int, int>::iterator iter_c1(c.begin());
  std::pair<int, int> c_pair1 = *iter_c1;
  ASSERT_EQ(d.size() == c.size(), true);
  ASSERT_EQ(d_pair1.second == c_pair1.second, true);
}

TEST(Map, test18) {
  s21::map<int, int> d = {{12, 112}, {13, 113}, {10, 100}, {5, 55}, {7, 77}, {2, 22}};
  d.insert(2, 11);
  typename s21::map<int, int>::iterator iter_d1(d.begin());
  std::pair<int, int> d_pair1 = *iter_d1;
  std::map<int, int> c = {{12, 112}, {13, 113}, {10, 100}, {5, 55}, {7, 77}, {2, 22}};
  c.insert({2, 11});
  std::map<int, int>::iterator iter_c1(c.begin());
  std::pair<int, int> c_pair1 = *iter_c1;
  ASSERT_EQ(d.size() == c.size(), true);
  ASSERT_EQ(d_pair1.second == c_pair1.second, true);
}

TEST(Map, test19) {
  s21::map<int, int> d = {{12, 112}, {13, 113}, {10, 100}, {5, 55}, {7, 77}, {2, 22}};
  typename s21::map<int, int>::iterator iter_d1(d.begin());
  std::pair<int, int> d_pair1 = *iter_d1;
  ASSERT_EQ(d_pair1.second == 22, true);
  d.insert_or_assign(2, 11);
  d_pair1 = *iter_d1;
  ASSERT_EQ(d_pair1.second == 11, true);
  d.insert_or_assign(1, 12);
  --iter_d1;
  d_pair1 = *iter_d1;
  ASSERT_EQ(d_pair1.second == 12, true);
}

TEST(Map, test20) {
  s21::map<int, int> d = {{12, 112}, {13, 113}, {10, 100}, {5, 55}, {7, 77}, {2, 22}};
  std::map<int, int> c = {{12, 112}, {13, 113}, {10, 100}, {5, 55}, {7, 77}, {2, 22}};
  ASSERT_EQ(d.at(7) == c.at(7), true);
  ASSERT_EQ(d.at(10) == c.at(10), true);
}

TEST(Map, test21) {
  s21::map<int, std::string> d = {{12, "one"}, {13, "two"}, {10, "three"},
                                  {5, "four"}, {7, "five"}, {2, "six"}};
  std::map<int, std::string> c = {{12, "one"}, {13, "two"}, {10, "three"},
                                  {5, "four"}, {7, "five"}, {2, "six"}};
  d[12] = 100;
  c[12] = 100;
  ASSERT_EQ(d.at(12) == c.at(12), true);
}

TEST(Map, test22) {
  s21::map<int, int> d = {{12, 112}, {13, 113}, {10, 100}, {5, 55}, {7, 77}, {2, 22}};
  typename s21::map<int, int>::iterator iter_d1(d.begin());
  for (int i = 0; i < 4; i++) ++iter_d1;
  d.erase(iter_d1);
  std::map<int, int> c = {{12, 112}, {13, 113}, {10, 100}, {5, 55}, {7, 77}, {2, 22}};
  std::map<int, int>::iterator iter_c1(c.begin());
  for (int i = 0; i < 4; i++) ++iter_c1;
  c.erase(iter_c1);
  ASSERT_EQ(d.size() == c.size(), true);

  typename s21::map<int, int>::iterator iterator_check_1(d.end());
  typename std::map<int, int>::iterator iterator_check_2(c.end());
  for (int i = 0; i < 4; i++) --iterator_check_1;
  for (int i = 0; i < 4; i++) --iterator_check_2;
  std::pair<int, int> d_pair1 = *iterator_check_1;
  std::pair<int, int> c_pair1 = *iterator_check_1;
  ASSERT_EQ(d_pair1.second == c_pair1.second, true);
}

TEST(Map, test23) {
  s21::map<int, int> d = {{12, 112}, {13, 113}, {10, 100}, {5, 55}, {7, 77}, {2, 22}};
  typename s21::map<int, int>::iterator iter_d1(d.end());
  for (int i = 0; i < 5; i++) --iter_d1;
  d.erase(iter_d1);
  std::map<int, int> c = {{12, 112}, {13, 113}, {10, 100}, {5, 55}, {7, 77}, {2, 22}};
  std::map<int, int>::iterator iter_c1(c.end());
  for (int i = 0; i < 5; i++) --iter_c1;
  c.erase(iter_c1);
  ASSERT_EQ(d.size() == c.size(), true);

  typename s21::map<int, int>::iterator iterator_check_1(d.begin());
  typename std::map<int, int>::iterator iterator_check_2(c.begin());
  for (int i = 0; i < 4; i++) ++iterator_check_1;
  for (int i = 0; i < 4; i++) ++iterator_check_2;
  std::pair<int, int> d_pair1 = *iterator_check_1;
  std::pair<int, int> c_pair1 = *iterator_check_1;
  ASSERT_EQ(d_pair1.second == c_pair1.second, true);
}

TEST(Map, test25) {
  s21::map<int, double> d = {{12, 1.12}, {13, 1.13}, {10, 1.00},  {5, 5.5}, {7, 7.7},
                             {2, 2.2},   {77, 8.5},  {58, 87.65}, {6, 8.76}};
  std::map<int, double> c = {{12, 1.12}, {13, 1.13}, {10, 1.00},  {5, 5.5}, {7, 7.7},
                             {2, 2.2},   {77, 8.5},  {58, 87.65}, {6, 8.76}};
  for (int i = 0; i < 8; i++) {
    typename s21::map<int, double>::iterator iter_d1(d.begin());
    ++iter_d1;
    d.erase(iter_d1);
    std::map<int, double>::iterator iter_c1(c.begin());
    ++iter_c1;
    c.erase(iter_c1);
    ASSERT_EQ(d.size() == c.size(), true);
  }
}

TEST(Map, test26) {
  s21::map<int, int> d = {{3, 33}, {4, 44}, {5, 55},   {6, 66},  {7, 77},
                          {8, 88}, {9, 99}, {10, 100}, {11, 111}};
  std::map<int, int> c = {{3, 33}, {4, 44}, {5, 55},   {6, 66},  {7, 77},
                          {8, 88}, {9, 99}, {10, 100}, {11, 111}};
  for (int i = 0; i < 8; i++) {
    typename s21::map<int, int>::iterator iter_d1(d.begin());
    ++iter_d1;
    d.erase(iter_d1);
    std::map<int, int>::iterator iter_c1(c.begin());
    ++iter_c1;
    c.erase(iter_c1);
    ASSERT_EQ(d.size() == c.size(), true);
  }
}

TEST(Map, test27) {
  s21::map<int, double> d = {{3, 33.3}, {4, 44.4}, {5, 55.5},   {6, 66.6},  {7, 77.7},
                             {8, 88.8}, {9, 99.9}, {10, 100.1}, {11, 111.1}};
  auto myPair = d.emplace(std::pair<int, double>(123, 21.2), std::pair<int, double>(32, 221.2));
  EXPECT_EQ(d[123], 21.2);
  EXPECT_EQ(d[32], 221.2);
  s21::map<int, double>::iterator iter(d.end());
  std::pair<int, int> d_pair1;
  --iter;
  EXPECT_EQ((*iter).second, 21.2);
  --iter;
  EXPECT_EQ((*iter).second, 221.2);
  --iter;
  EXPECT_EQ((*iter).second, 111.1);
}
