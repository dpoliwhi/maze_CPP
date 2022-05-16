#include <gtest/gtest.h>
#include <array>
#include <string>

#include "../s21_array.h"

TEST(Array, test1) {
    s21::array<int, 0> d;
    std::array<int, 0> c;
    ASSERT_EQ(d.empty() == c.empty(), true);
}

TEST(Array, test2) {
    s21::array<int, 5> d;
    std::array<int, 5> c;
    ASSERT_EQ(d.empty() == c.empty(), true);
}

TEST(Array, test3) {
    s21::array<int, 5> d = {1, 2, 3, 4, 5};
    std::array<int, 5> c = {1, 2, 3, 4, 5};
    ASSERT_EQ(d.size() == c.size(), true);
}

TEST(Array, test4) {
    s21::array<int, 5> d = {1, 2, 3, 4, 5};
    s21::array<int, 5> c(d);
    ASSERT_EQ(d.size() == c.size(), true);
    ASSERT_EQ(d.front() == c.front(), true);
    ASSERT_EQ(d.back() == c.back(), true);
}

TEST(Array, test5) {
    s21::array<int, 5> d = {1, 2, 3, 4, 5};
    s21::array<int, 5> c(std::move(d));
    std::array<int, 5> d1 = {1, 2, 3, 4, 5};
    std::array<int, 5> c1(std::move(d1));
    ASSERT_EQ(d.size() == d1.size(), true);
    ASSERT_EQ(c.size() == c1.size(), true);
    ASSERT_EQ(c.front() == c1.front(), true);
    ASSERT_EQ(c.back() == c1.back(), true);
}

TEST(Array, test6) {
    s21::array<int, 5> d = {1, 2, 3, 4, 5};
    s21::array<int, 5> c;
    c = d;
    std::array<int, 5> d1 = {1, 2, 3, 4, 5};
    std::array<int, 5> c1;
    c1 = d1;
    ASSERT_EQ(d.size() == d1.size(), true);
    ASSERT_EQ(c.size() == c1.size(), true);
    ASSERT_EQ(d.front() == d1.front(), true);
    ASSERT_EQ(d.back() == d1.back(), true);
    ASSERT_EQ(c.front() == c1.front(), true);
    ASSERT_EQ(c.back() == c1.back(), true);
}

TEST(Array, test7) {
    s21::array<int, 5> d = {1, 2, 3, 4, 5};
    s21::array<int, 5> c;
    c = std::move(d);
    std::array<int, 5> d1 = {1, 2, 3, 4, 5};
    std::array<int, 5> c1;
    c1 = std::move(d1);
    ASSERT_EQ(d.size() == d1.size(), true);
    ASSERT_EQ(c.size() == c1.size(), true);
    ASSERT_EQ(c.front() == c1.front(), true);
    ASSERT_EQ(c.back() == c1.back(), true);
}

TEST(Array, test8) {
    s21::array<int, 5> d = {1, 2, 3, 4, 5};
    s21::array<int, 5> c = {1, 2, 3, 4, 5};
    ASSERT_EQ(d.at(0), c.at(0));
    ASSERT_EQ(d.at(2), c.at(2));
}

TEST(Array, test9) {
    s21::array<int, 8> d = {6, 7, 8, 9, 10};
    s21::array<int, 8> c = {6, 7, 8, 9, 10};
    ASSERT_EQ(d[0], c[0]);
    ASSERT_EQ(d[4], c[4]);
    ASSERT_EQ(d[7], c[7]);
}

TEST(Array, test10) {
    s21::array<int, 5> d = {1, 2, 3, 4, 5};
    s21::array<int, 5>::iterator it = d.data();
    s21::array<int, 5>::iterator it1 = d.begin();
    ASSERT_EQ(it, it1);
}

TEST(Array, test11) {
    s21::array<int, 5> d = {1, 2, 3, 4, 5};
    s21::array<int, 5>::iterator it = d.end();
    for (int i = 0; i < 5; ++i) --it;
    s21::array<int, 5>::iterator it1 = d.begin();
    ASSERT_EQ(it, it1);
}

TEST(Array, test12) {
    s21::array<int, 5> d = {1, 2, 3, 4, 5};
    std::array<int, 5> c = {1, 2, 3, 4, 5};
    d.fill(1);
    c.fill(1);
    for (int i = 0; i < 5; ++i)
        ASSERT_EQ(d[i], c[i]);
}

TEST(Array, test13) {
    s21::array<int, 8> d = {1, 2, 3, 4, 5};
    s21::array<int, 8> d1 = {6, 7, 8};
    std::array<int, 8> c = {1, 2, 3, 4, 5};
    std::array<int, 8> c1 = {6, 7, 8};
    d.swap(d1);
    c.swap(c1);
    for (int i = 0; i < 8; ++i) {
        ASSERT_EQ(d[i], c[i]);
        ASSERT_EQ(d1[i], c1[i]);
    }
}