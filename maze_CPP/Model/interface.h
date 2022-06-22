#pragma once

#include "Cave/generateCave.h"
#include "Cave/openCave.h"
#include "Maze/generateMaze.h"
#include "Maze/openMaze.h"

namespace s21 {

class Interface {
 private:
  s21::OpenMaze *openMaze = nullptr;
  s21::Generate *generateMaze = nullptr;
  s21::OpenCave *openCave = nullptr;
  s21::GenerateCave *generateCave = nullptr;

 public:
  Interface() {}
  ~Interface();
  bool openFile(const std::string &fileName);
  bool generate(size_t rows, size_t cols);
  std::pair<std::vector<std::vector<bool>>, std::vector<std::vector<bool>>> getData();
  std::pair<size_t, size_t> getRowsAndCols();
  std::vector<std::pair<int, int>> findPath(int startx, int starty, int endx, int endy);
  void saveFile(const std::string &fileName);
  void cleanFileMaze();
  void cleanFileCave();

  bool openFileCave(const std::string &fileName);
  std::vector<std::vector<bool>> getDataCave();
  std::pair<size_t, size_t> getRowsAndColsCave();
  bool step(size_t birth, size_t death);
  bool generateC(size_t rows, size_t cols, int chance);
};
}  // namespace s21
