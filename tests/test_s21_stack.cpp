#include <gtest/gtest.h>
#include <stack>
#include <string>
#include "../s21_stack.h"

TEST(Stack, test1) {
    s21::stack<int> d;
    std::stack<int> c;
    ASSERT_EQ(d.empty() == c.empty(), true);
}

TEST(Stack, test2) {
    s21::stack<int> d(8);
    d.push(1);
    ASSERT_EQ(d.top() == 1, true);
}

TEST(Stack, test3) {
    s21::stack<int> d{1, 2, 3, 4, 5};
    ASSERT_EQ(d.top() == 5, true);
    ASSERT_EQ(d.size() == 5, true);
    s21::stack<int> c(d);
    ASSERT_EQ(c.top() == 5, true);
    ASSERT_EQ(c.size() == 5, true);
    s21::stack<int> f(std::move(d));
    ASSERT_EQ(f.top() == 5, true);
    ASSERT_EQ(f.size() == 5, true);
    ASSERT_EQ(d.size() == 0, true);
}

TEST(Stack, test4) {
    s21::stack<int> d;
    std::stack<int> c;
    d.push(1);
    c.push(1);
    d.push(2);
    c.push(2);
    d.push(3);
    c.push(3);
    ASSERT_EQ(d.size() == c.size(), true);
    d.pop();
    c.pop();
    ASSERT_EQ(d.top() == c.top(), true);
}

TEST(Stack, test5) {
    s21::stack<std::string> d;
    d.push("hi");
    d.push("bye");
    s21::stack<std::string> c;
    c = d;
    ASSERT_EQ(d.top() == c.top(), true);
    s21::stack<std::string> f;
    f = (std::move(d));
    ASSERT_EQ(f.top() == c.top(), true);
    ASSERT_EQ(d.size() == 0, true);
}

TEST(Stack, test6) {
    s21::stack<std::string> d;
    d.push("hi");
    d.push("bye");
    s21::stack<std::string> c;
    c.push("abc");
    c.push("defg");
    c.swap(d);
    ASSERT_EQ(d.top() == "defg", true);
    ASSERT_EQ(c.top() == "bye", true);
}
