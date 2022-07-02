#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace s21 {

class Cave {
 protected:
  struct fileData {
    size_t rows = 0;
    size_t cols = 0;
    std::vector<std::vector<bool>> life;
  };
  fileData data;

 public:
  void cleanData();
  std::vector<std::vector<bool>> getData();
  std::pair<size_t, size_t> getRowsAndCols();
  bool oneStep(size_t birth, size_t death);
};

}  // namespace s21
