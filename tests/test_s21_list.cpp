#include <gtest/gtest.h>
#include <list>
#include <string>
#include "../s21_list.h"

TEST(List, test1) {
    s21::list<int> d;
    std::list<int> c;
    ASSERT_EQ(d.empty() == c.empty(), true);
}

TEST(List, test2) {
    s21::list<int> d{1, 2, 3, 4, 5};
    std::list<int> c{1, 2, 3, 4, 5};
    ASSERT_EQ(d.front() == c.front(), true);
    ASSERT_EQ(d.back() == c.back(), true);
}

TEST(List, test3) {
    s21::list<int> d(8);
    std::list<int> c(8);
    ASSERT_EQ(d.size() == c.size(), true);
}

TEST(List, test4) {
    s21::list<std::string> d{"a", "ab", "cd"};
    s21::list<std::string> c(d);
    ASSERT_EQ(d.front() == c.front(), true);
}

TEST(List, test5) {
    s21::list<std::string> d{"a", "ab", "cd"};
    s21::list<std::string> c(std::move(d));
    ASSERT_EQ(d.size() == 0, true);
    ASSERT_EQ(c.front() == "a", true);
}

TEST(List, test6) {
    s21::list<int> d{1, 2, 3, 4, 5};
    s21::list<int> c;
    c = d;
    ASSERT_EQ(d.front() == c.front(), true);
    ASSERT_EQ(d.back() == c.back(), true);
}

TEST(List, test7) {
    s21::list<int> d{7, 9, 3, 6, 1, 15, 4, 5, 0};
    std::list<int> c{7, 9, 3, 6, 1, 15, 4, 5, 0};
    s21::list<int>::iterator iter_d = d.end();
    std::list<int>::iterator iter_c = c.end();
    s21::list<int>::const_iterator const_iterator_d = d.cend();
    std::list<int>::const_iterator const_iterator_c = c.cend();
    while (iter_d._iter != iter_d._head) {
        --iter_d;
        --iter_c;
        --const_iterator_d;
        --const_iterator_c;
        ASSERT_EQ(*iter_d == *iter_c, true);
        ASSERT_EQ(*const_iterator_d == *const_iterator_c, true);
    }
}

TEST(List, test8) {
    s21::list<int> d;
    d.push_front(1);
    d.push_front(11);
    d.push_back(2);
    d.push_back(3);
    d.pop_front();
    d.pop_back();
    std::list<int> c;
    c.push_front(1);
    c.push_front(11);
    c.push_back(2);
    c.push_back(3);
    c.pop_front();
    c.pop_back();
    ASSERT_EQ(d.back() == c.back(), true);
}

TEST(List, test9) {
    s21::list<int> d;
    d.push_back(1);
    d.pop_back();
    std::list<int> c;
    c.push_back(1);
    c.pop_back();
    ASSERT_EQ(d.size() == c.size(), true);
    d.push_front(1);
    d.pop_front();
    c.push_front(1);
    c.pop_front();
    ASSERT_EQ(d.size() == c.size(), true);
}

TEST(List, test10) {
    s21::list<int> d{3, 1, 1, 3, 2, 2, 4, 5, 5};
    s21::list<int> c{1, 3, 2, 4, 5, 5};
    d.swap(c);
    std::list<int> d1{3, 1, 1, 3, 2, 2, 4, 5, 5};
    std::list<int> c1{1, 3, 2, 4, 5, 5};
    d1.swap(c1);
    ASSERT_EQ(d.front() == d1.front(), true);
    ASSERT_EQ(d.size() == d1.size(), true);
}

TEST(List, test11) {
    s21::list<int> d{1, 2, 3, 4, 5};
    s21::list<int> c{8, 9, 19, 55};
    d.merge(c);
    std::list<int> d1{1, 2, 3, 4, 5};
    std::list<int> c1{8, 9, 19, 55};
    d1.merge(c1);
    s21::list<int>::iterator iter_d = d.end();
    std::list<int>::iterator iter_d1 = d1.end();
    while (iter_d._iter != iter_d._head) {
        --iter_d;
        --iter_d1;
        ASSERT_EQ(*iter_d == *iter_d1, true);
    }
    ASSERT_EQ(c.size() == c1.size(), true);
}

TEST(List, test12) {
    s21::list<int> d{1, 2, 3, 4, 5};
    d.reverse();
    std::list<int> d1{1, 2, 3, 4, 5};
    d1.reverse();
    ASSERT_EQ(d.front() == d1.front(), true);
    ASSERT_EQ(d.back() == d1.back(), true);
    ASSERT_EQ(d.size() == d1.size(), true);
}

TEST(List, test13) {
    s21::list<int> d{7, 9, 3, 6, 1, 15, 4, 5, 0};
    std::list<int> c{7, 9, 3, 6, 1, 15, 4, 5, 0};
    s21::list<int>::iterator iter_d;
    iter_d = d.begin();
    std::list<int>::iterator iter_c;
    iter_c = c.begin();
    s21::list<int>::const_iterator const_iterator_d;
    const_iterator_d = d.cbegin();
    std::list<int>::const_iterator const_iterator_c;
    const_iterator_c = c.cbegin();
    ASSERT_EQ(*iter_d == *iter_c, true);
    ASSERT_EQ(*const_iterator_d == *const_iterator_c, true);
    ++iter_d;
    ++iter_c;
    ++const_iterator_d;
    ++const_iterator_c;
    ASSERT_EQ(*iter_d == *iter_c, true);
    ASSERT_EQ(*const_iterator_d == *const_iterator_c, true);
}

TEST(List, test14) {
    s21::list<int> d{7, 9, 3, 6, 1, 15, 4, 5, 0};
    s21::list<int>::const_iterator const_iterator = d.cbegin();
    s21::list<int>::const_iterator const_iterator1 = d.cbegin();
    if (const_iterator == const_iterator1) ++const_iterator;
    ASSERT_EQ(*const_iterator == 9, true);
    if (const_iterator != const_iterator1) --const_iterator;
    ASSERT_EQ(*const_iterator == 7, true);
}

TEST(List, test15) {
    s21::list<int> d{1, 1, 1, 3, 2, 2, 4, 5, 5};
    std::list<int> c{1, 1, 1, 3, 2, 2, 4, 5, 5};
    d.unique();
    c.unique();
    ASSERT_EQ(d.front() == c.front(), true);
    ASSERT_EQ(d.size() == c.size(), true);
}

TEST(List, test16) {
    s21::list<int> d{7, 9, 3, 6, 1, 15, 4, 5, 0};
    std::list<int> c{7, 9, 3, 6, 1, 15, 4, 5, 0};
    d.sort();
    c.sort();
    ASSERT_EQ(d.front() == c.front(), true);
    ASSERT_EQ(d.size() == c.size(), true);
}

TEST(List, test17) {
    s21::list<int> d{7, 9, 3, 6, 1, 15, 4, 5, 0};
    std::list<int> c{7, 9, 3, 6, 1, 15, 4, 5, 0};
    s21::list<int>::iterator iter_d = d.begin();
    std::list<int>::iterator iter_c = c.begin();
    d.insert(iter_d, 1);
    c.insert(iter_c, 1);
    ASSERT_EQ(d.front() == c.front(), true);
    ++iter_d;
    ++iter_c;
    d.insert(iter_d, 21);
    c.insert(iter_c, 21);
    ASSERT_EQ(d.size() == c.size(), true);
}

TEST(List, test18) {
    s21::list<int> d{7, 9, 3, 6, 1, 15, 4, 5, 0};
    std::list<int> c{7, 9, 3, 6, 1, 15, 4, 5, 0};
    s21::list<int>::iterator iter_d = d.end();
    --iter_d;
    d.erase(iter_d);
    std::list<int>::iterator iter_c = c.end();
    --iter_c;
    c.erase(iter_c);
    ASSERT_EQ(d.back() == c.back(), true);
}

TEST(List, test19) {
    s21::list<int> d{7, 9, 3, 6, 1, 15, 4, 5, 0};
    s21::list<int> d1{1, 2, 3};
    std::list<int> c{7, 9, 3, 6, 1, 15, 4, 5, 0};
    std::list<int> c1{1, 2, 3};
    s21::list<int>::const_iterator const_iterator_d = d1.cbegin();
    std::list<int>::const_iterator const_iterator_c = c1.cbegin();
    d1.splice(const_iterator_d, d);
    c1.splice(const_iterator_c, c);
    ASSERT_EQ(d1.front() == c1.front(), true);
}
