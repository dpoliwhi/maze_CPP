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
