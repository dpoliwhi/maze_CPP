#include <gtest/gtest.h>
#include "test_s21_stack.cpp"
#include "test_s21_queue.cpp"
#include "test_s21_list.cpp"
#include "test_s21_vector.cpp"
#include "test_s21_map.cpp"

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
