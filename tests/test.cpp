#include <gtest/gtest.h>
#include <list>
#include "s21_list.h"

TEST(Constructor, test1) {
    s21::list<int> d;
    std::list<int> c;
    //c.push_back(1);
    //d.push_back(1);
    ASSERT_EQ(d.empty() == c.empty(), true);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
