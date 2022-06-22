#pragma once

#include <cstdlib>
#include <ctime>
#include <random>

#include "mazeData.h"

namespace s21 {
class Generate : public Maze {
 private:
  std::vector<int> setLine;
  int uniqSet = 1;

  bool randomizer();
  void createEmptyMaze(size_t rows, size_t cols);
  void createUniqSetLine();
  void createRightWalsInLine(size_t row);
  void mergeSetInLine(size_t index);
  void createBottomWalsInLine(size_t row);
  int calcUniqSets(int uniqSet);
  void checkBottomWalls(size_t row);
  int calcBottomWalls(int uniqSet, size_t row);
  void setForNewLine(size_t row);
  void createLastWalls();

 public:
  bool generate(size_t rows, size_t cols);
};

}  // namespace s21
