#include <gtest/gtest.h>
#include <queue>
#include <string>
#include "../s21_queue.h"

TEST(Queue, test1) {
    s21::queue<int> d;
    std::queue<int> c;
    ASSERT_EQ(d.empty() == c.empty(), true);
}

TEST(Queue, test2) {
    s21::queue<int> d(8);
    d.push(1);
    ASSERT_EQ(d.back() == 1, true);
}

TEST(Queue, test3) {
    s21::queue<int> d{1, 2, 3, 4, 5};
    ASSERT_EQ(d.back() == 5, true);
    ASSERT_EQ(d.size() == 5, true);
    s21::queue<int> c(d);
    ASSERT_EQ(c.back() == 5, true);
    ASSERT_EQ(c.size() == 5, true);
    s21::queue<int> f(std::move(d));
    ASSERT_EQ(f.back() == 5, true);
    ASSERT_EQ(f.size() == 5, true);
    ASSERT_EQ(d.size() == 0, true);
}

TEST(Queue, test4) {
    s21::queue<int> d;
    std::queue<int> c;
    d.push(1);
    c.push(1);
    d.push(2);
    c.push(2);
    d.push(3);
    c.push(3);
    ASSERT_EQ(d.size() == c.size(), true);
    d.pop();
    c.pop();
    ASSERT_EQ(d.front() == c.front(), true);
    ASSERT_EQ(d.back() == c.back(), true);
}

TEST(Queue, test5) {
    s21::queue<std::string> d;
    d.push("hi");
    d.push("bye");
    s21::queue<std::string> c;
    c = d;
    ASSERT_EQ(d.front() == c.front(), true);
    s21::queue<std::string> f;
    f = (std::move(d));
    ASSERT_EQ(f.back() == c.back(), true);
    ASSERT_EQ(d.size() == 0, true);
}

TEST(Queue, test6) {
    s21::queue<std::string> d;
    d.push("hi");
    d.push("bye");
    s21::queue<std::string> c;
    c.push("abc");
    c.push("defg");
    c.swap(d);
    ASSERT_EQ(d.front() == "abc", true);
    ASSERT_EQ(c.front() == "hi", true);
}

TEST(Queue, test7) {
  s21::queue<int> a{55, 44, 33};
  a.emplace_back(3, 42, 5);
  ASSERT_EQ(a.size(), 6);
  ASSERT_EQ(a.back(), 5);
  ASSERT_EQ(a.front(), 55);
  a.pop();
  ASSERT_EQ(a.back(), 5);
  ASSERT_EQ(a.front(), 44);
}
