#pragma once

#include <fstream>
#include <string>
#include <vector>

namespace s21 {

class Maze {
 protected:
  struct fileData {
    size_t rows = 0;
    size_t cols = 0;
    std::vector<std::vector<bool>> rightWalls;
    std::vector<std::vector<bool>> bottomWalls;
  };
  fileData data;
  bool checkWalls(int k, int y, int x);

 public:
  void cleanData();
  std::pair<std::vector<std::vector<bool>>, std::vector<std::vector<bool>>> getData();
  std::pair<size_t, size_t> getRowsAndCols();
  std::vector<std::pair<int, int>> findPath(int startx, int starty, int endx, int endy);
  void saveMaze(std::string fileName);
};

}  // namespace s21
