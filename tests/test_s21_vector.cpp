#include <gtest/gtest.h>
#include <stack>
#include <string>
#include "../s21_vector.h"

TEST(Vector, test1) {
    s21::vector<int> d;
    std::vector<int> c;
    ASSERT_EQ(d.empty() == c.empty(), true);
}

TEST(Vector, test2) {
    s21::vector<int> d(8);
    d.push_back(1);
    d.push_back(2);
    d.push_back(3);
    ASSERT_EQ(d.front() == 1, true);
    ASSERT_EQ(d.capacity() == 8, true);
    d.pop_back();
    ASSERT_EQ(d.size() == 2, true);
}

TEST(Vector, test3) {
    s21::vector<int> d{1, 2, 3, 4, 5};
    ASSERT_EQ(d[0] == 1, true);
    ASSERT_EQ(d[1] == 2, true);
}

TEST(Vector, test4) {
    s21::vector<int> d;
    std::vector<int> c;
    d.push_back(1);
    d.push_back(2);
    d.push_back(3);
    c.push_back(1);
    c.push_back(2);
    c.push_back(3);
    ASSERT_EQ(d.front() == c.front(), true);
    ASSERT_EQ(d.back() == c.back(), true);
    ASSERT_EQ(d.size() == c.size(), true);
    ASSERT_EQ(d.capacity() == c.capacity(), true);
}

TEST(Vector, test5) {
    s21::vector<int> d{1, 2, 3, 4, 5};
    s21::vector<int> c(d);
    ASSERT_EQ(d.front() == c.front(), true);
    ASSERT_EQ(d.size() == c.size(), true);
    d.clear();
    ASSERT_EQ(d.size() == 0, true);
}

TEST(Vector, test6) {
    s21::vector<int> d{1, 2, 3, 4, 5};
    s21::vector<int> c(std::move(d));
    ASSERT_EQ(c.front() == 1, true);
    ASSERT_EQ(d.size() == 0, true);
}

TEST(Vector, test7) {
    s21::vector<int> d{1, 2, 3, 4, 5};
    s21::vector<int> c;
    c = d;
    ASSERT_EQ(d.front() == c.front(), true);
    ASSERT_EQ(d.size() == c.size(), true);
    s21::vector<int> f;
    f = (std::move(d));
    ASSERT_EQ(f.front() == 1, true);
    ASSERT_EQ(d.size() == 0, true);
}

TEST(Vector, test8) {
    s21::vector<int> d{1, 2, 3, 4, 5};
    d[0] = 9;
    std::vector<int> c{1, 2, 3, 4, 5};
    c[0] = 9;
    ASSERT_EQ(d.front() == c.front(), true);
    ASSERT_EQ(d.size() == c.size(), true);
    ASSERT_EQ(d.capacity() == c.capacity(), true);
}

TEST(Vector, test9) {
    s21::vector<int> d{1, 2, 3, 4, 5};
    s21::vector<int>::iterator it_d = d.begin();
    d.insert(it_d, 9);
    s21::vector<int>::iterator it_d1 = d.begin();
    it_d1++;
    d.insert(it_d1, 8);
    std::vector<int> c{1, 2, 3, 4, 5};
    std::vector<int>::iterator it_c = c.begin();
    c.insert(it_c, 9);
    std::vector<int>::iterator it_c1 = c.begin();
    it_c1++;
    c.insert(it_c1, 8);
    ASSERT_EQ(d.front() == c.front(), true);
    ASSERT_EQ(d.size() == c.size(), true);
    ASSERT_EQ(d.capacity() == c.capacity(), true);
}

TEST(Vector, test10) {
    s21::vector<int> d{1, 2, 3, 4, 5};
    std::vector<int> c{1, 2, 3, 4, 5};
    ASSERT_EQ(d.back() == c.back(), true);
    ASSERT_EQ(d.size() == c.size(), true);
    ASSERT_EQ(d.capacity() == c.capacity(), true);
}

TEST(Vector, test11) {
    s21::vector<int> d{1, 2, 3, 4, 5};
    s21::vector<int>::iterator it_d = d.begin();
    d.erase(it_d);
    std::vector<int> c{1, 2, 3, 4, 5};
    std::vector<int>::iterator it_c = c.begin();
    c.erase(it_c);
    ASSERT_EQ(d.front() == c.front(), true);
    ASSERT_EQ(d.size() == c.size(), true);
    ASSERT_EQ(d.capacity() == c.capacity(), true);
}

TEST(Vector, test12) {
    s21::vector<int> d{1, 2, 3, 4, 5};
    s21::vector<int> d1{6, 7, 8};
    d.swap(d1);
    std::vector<int> c{1, 2, 3, 4, 5};
    std::vector<int> c1{6, 7, 8};
    c.swap(c1);
    ASSERT_EQ(d.front() == c.front(), true);
    ASSERT_EQ(d.back() == c.back(), true);
    ASSERT_EQ(d.size() == c.size(), true);
    ASSERT_EQ(d.capacity() == c.capacity(), true);
}

TEST(Vector, test13) {
    s21::vector<int> d{1, 2, 3, 4, 5};
    std::vector<int> c{1, 2, 3, 4, 5};
    ASSERT_EQ(d.at(3) == c.at(3), true);
}

TEST(Vector, test14) {
    s21::vector<int> d{1, 2, 3, 4, 5};
    std::vector<int> c{1, 2, 3, 4, 5};
    ASSERT_EQ(*(d.data()) == *(c.data()), true);
}

TEST(Vector, test15) {
    s21::vector<int> d;
    std::vector<int> c;
    d.push_back(1);
    d.push_back(2);
    d.push_back(3);
    c.push_back(1);
    c.push_back(2);
    c.push_back(3);
    ASSERT_EQ(*(d.end()) == *(c.end()), true);
}

TEST(Vector, test16) {
    s21::vector<int> d{1, 2, 3, 4, 5};
    std::vector<int> c{1, 2, 3, 4, 5};
    d.reserve(9);
    c.reserve(9);
    ASSERT_EQ(d.size() == c.size(), true);
    d.reserve(3);
    c.reserve(3);
    ASSERT_EQ(d.size() == c.size(), true);
    ASSERT_EQ(d.capacity() == c.capacity(), true);
}

TEST(Vector, test17) {
    s21::vector<int> d(8);
    std::vector<int> c(8);
    d.push_back(1);
    d.push_back(2);
    d.push_back(3);
    c.push_back(1);
    c.push_back(2);
    c.push_back(3);
    d.shrink_to_fit();
    c.shrink_to_fit();
    ASSERT_EQ(d.size() == d.capacity(), true);
    ASSERT_EQ(c.size() == c.capacity(), true);
}
