#pragma once

#include <iostream>

#include "../Model/interface.h"

namespace s21 {
class Facade {
 private:
  s21::Interface* inter;

 public:
  explicit Facade(s21::Interface* interInit);
  bool openFile(const std::string& fileName);
  bool generate(size_t rows, size_t cols);
  std::pair<std::vector<std::vector<bool>>, std::vector<std::vector<bool>>> getData();
  std::pair<size_t, size_t> getRowsAndCols();
  std::vector<std::pair<int, int>> findPath(int startx, int starty, int endx, int endy);
  void saveFile(const std::string& fileName);
  void cleanFileMaze();
  void cleanFileCave();

  bool openFileCave(const std::string& fileName);
  bool generateCave(size_t rows, size_t cols, int chance);
  std::vector<std::vector<bool>> getDataCave();
  std::pair<size_t, size_t> getRowsAndColsCave();
  bool caveStep(size_t birth, size_t death);
};

}  // namespace s21
