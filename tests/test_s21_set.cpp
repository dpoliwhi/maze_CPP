#include <gtest/gtest.h>
#include <set>
#include <string>
#include "../s21_set.h"

TEST(Set, test1) {
    s21::set<int> d;
    std::set<int> c;
    ASSERT_EQ(d.empty() == c.empty(), true);
}

TEST(Set, test2) {
    s21::set<int> d = {12, 112, 13, 113, 10, 100, 5, 55, 7, 77, 2, 22};
    std::set<int> c = {12, 112, 13, 113, 10, 100, 5, 55, 7, 77, 2, 22};
    ASSERT_EQ(d.size() == c.size(), true);
}

TEST(Set, test3) {
    s21::set<int> d = {12, 112, 13, 113, 10, 100, 5, 55, 7, 77, 2, 22};
    s21::set<int> c(d);
    ASSERT_EQ(d.size() == c.size(), true);
}

TEST(Set, test4) {
    s21::set<int> d = {12, 112, 13, 113, 10, 100, 5, 55, 7, 77, 2, 22};
    s21::set<int> c(std::move(d));
    ASSERT_EQ(d.size() == 0, true);
    ASSERT_EQ(c.size() == 12, true);
}

TEST(Set, test5) {
    s21::set<int> d = {12, 112, 13, 113, 10, 100, 5, 55, 7, 77, 2, 22};
    s21::set<int> c;
    c = std::move(d);
    ASSERT_EQ(d.size() == 0, true);
    ASSERT_EQ(c.size() == 12, true);
}

TEST(Set, test6) {
    s21::set<int> d = {12, 112, 13, 113, 10, 100, 5, 55, 7, 77, 2, 22};
    s21::set<int> c;
    c = d;
    ASSERT_EQ(d.size() == c.size(), true);
}

TEST(Set, test7) {
    s21::set<int> d = {12, 112, 13, 113, 10, 100, 5, 55, 7, 77, 2, 22};
    d.insert(1);
    ASSERT_EQ(d.find(1) == d.begin(), true);
}

TEST(Set, test8) {
    s21::set<std::string> d = {"a", "b", "c", "d"};
    s21::set<std::string>::iterator iter_begin = d.begin();
    ++iter_begin;
    ASSERT_EQ(d.find("b") == iter_begin, true);
    s21::set<std::string>::iterator iter_end = d.end();
    --iter_end;
    ASSERT_EQ(d.find("d") == iter_end, true);
}

TEST(Set, test9) {
    s21::set<int> d = {12, 112, 13, 113, 10, 100, 5, 55, 7, 77, 2, 22};
    d.erase(d.begin());
    ASSERT_EQ(d.begin() == d.find(5), true);
}

TEST(Set, test10) {
    s21::set<int> d = {12, 112, 13, 113, 10, 100, 5, 55, 7, 77, 2, 22};
    d.erase(++d.begin());
    ASSERT_EQ(++d.begin() == d.find(7), true);
}

TEST(Set, test11) {
    s21::set<int> d = {12, 112, 13, 113, 10, 100, 5, 55, 7, 77, 2, 22};
    s21::set<int> d1 = {1, 2, 3, 4, 5};
    d.swap(d1);
    std::set<int> c = {12, 112, 13, 113, 10, 100, 5, 55, 7, 77, 2, 22};
    std::set<int> c1 = {1, 2, 3, 4, 5};
    c.swap(c1);
    ASSERT_EQ(d.size() == c.size(), true);
    ASSERT_EQ(d1.size() == c1.size(), true);
}

TEST(Set, test12) {
    s21::set<int> d = {12, 112, 13, 113, 10};
    s21::set<int> d1 = {1, 2, 3, 4, 5};
    d.merge(d1);
    ASSERT_EQ(d.size() == 10, true);
    ASSERT_EQ(d.begin() == d.find(1), true);
}

TEST(Set, test13) {
    s21::set<int> d = {12, 112, 13, 113, 10, 100, 5, 55, 7, 77, 2, 22};
    ASSERT_EQ(d.contains(12) == true, true);
    ASSERT_EQ(d.contains(3) == false, true);
}

TEST(Set, test14) {
    s21::set<int> d = {1, 3, 5, 7, 9};
    auto myPair = d.emplace(2, 4, 6, 8);
    ASSERT_EQ(d.size() == 9, true);
    ASSERT_EQ(d.begin() == d.find(1), true);
    s21::set<int>::iterator iter_begin = d.begin();
    ++iter_begin;
    ASSERT_EQ(iter_begin == d.find(2), true);
    ++iter_begin;
    ASSERT_EQ(iter_begin == d.find(3), true);
}
