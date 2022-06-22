#include <gtest/gtest.h>

#include "Controller/facade.h"

// open maze
TEST(test_s21_Maze, openCheck) {
  s21::Interface inter;
  s21::Facade maze(&inter);
  bool check = maze.openFile("Labyrinth/4x5.txt");
  ASSERT_EQ(check, true);
  check = maze.openFile("Labyrinth/10x10.txt");
  ASSERT_EQ(check, true);
  check = maze.openFile("Labyrinth/10x10(incorrect).txt");
  ASSERT_EQ(check, false);
  check = maze.openFile("Labyrinth/20x20.txt");
  ASSERT_EQ(check, true);
  check = maze.openFile("Labyrinth/empty.txt");
  ASSERT_EQ(check, false);
}

// check size
TEST(test_s21_Maze, sizeCheck) {
  s21::Interface inter;
  s21::Facade maze(&inter);
  maze.openFile("Labyrinth/4x5.txt");
  ASSERT_EQ(maze.getRowsAndCols().first, 4);
  maze.openFile("Labyrinth/10x10.txt");
  ASSERT_EQ(maze.getRowsAndCols().second, 10);
  maze.openFile("Labyrinth/20x20.txt");
  ASSERT_EQ(maze.getRowsAndCols().first, 20);
}

// check side walls maze
TEST(test_s21_Maze, sideWallsCheck) {
  s21::Interface inter;
  s21::Facade maze(&inter);
  maze.openFile("Labyrinth/4x5.txt");
  std::vector<std::vector<bool>> rightWalls = maze.getData().first;
  std::vector<std::vector<bool>> bottomWalls = maze.getData().second;
  size_t rows = maze.getRowsAndCols().first;
  size_t cols = maze.getRowsAndCols().second;
  for (size_t i = 0; i < rows; i++) {
    ASSERT_EQ(rightWalls[i][cols - 1], true);
  }
  for (size_t i = 0; i < cols; i++) {
    ASSERT_EQ(bottomWalls[rows - 1][i], true);
  }
  maze.openFile("Labyrinth/20x20.txt");
  rightWalls = maze.getData().first;
  bottomWalls = maze.getData().second;
  rows = maze.getRowsAndCols().first;
  cols = maze.getRowsAndCols().second;
  for (size_t i = 0; i < rows; i++) {
    ASSERT_EQ(rightWalls[i][cols - 1], true);
  }
  for (size_t i = 0; i < cols; i++) {
    ASSERT_EQ(bottomWalls[rows - 1][i], true);
  }
}

// check maze data
TEST(test_s21_Maze, mazeDataCheck) {
  s21::Interface inter;
  s21::Facade maze(&inter);
  maze.openFile("Labyrinth/10x10.txt");
  std::vector<std::vector<bool>> rightWalls = maze.getData().first;
  std::vector<std::vector<bool>> bottomWalls = maze.getData().second;
  size_t rows = maze.getRowsAndCols().first;
  size_t cols = maze.getRowsAndCols().second;
  bool check_1[10] = {1, 0, 0, 1, 0, 0, 1, 0, 1, 1};
  for (size_t i = 0, k = 0; i < cols; i++) {
    ASSERT_EQ(rightWalls[3][i], check_1[k++]);
  }
  bool check_2[10] = {1, 0, 0, 0, 1, 0, 0, 0, 1, 1};
  for (size_t i = 0, k = 0; i < rows; i++) {
    ASSERT_EQ(bottomWalls[i][7], check_2[k++]);
  }
  maze.openFile("Labyrinth/20x20.txt");
  rightWalls = maze.getData().first;
  bottomWalls = maze.getData().second;
  rows = maze.getRowsAndCols().first;
  cols = maze.getRowsAndCols().second;
  bool check_3[20] = {0, 1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0};
  for (size_t i = 0, k = 0; i < rows; i++) {
    ASSERT_EQ(rightWalls[i][14], check_3[k++]);
  }
  bool check_4[20] = {0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0};
  for (size_t i = 0, k = 0; i < cols; i++) {
    ASSERT_EQ(bottomWalls[18][i], check_4[k++]);
  }
}

// generate maze
TEST(test_s21_Maze, generateCheck) {
  s21::Interface inter;
  s21::Facade maze(&inter);
  bool check = maze.generate(10, 10);
  ASSERT_EQ(check, true);
  check = maze.generate(15, 24);
  ASSERT_EQ(check, true);
  check = maze.generate(8, 0);
  ASSERT_EQ(check, false);
  check = maze.generate(0, 45);
  ASSERT_EQ(check, false);
  check = maze.generate(0, 0);
  ASSERT_EQ(check, false);
}

// check generate size
TEST(test_s21_Maze, sizeGenerateCheck) {
  s21::Interface inter;
  s21::Facade maze(&inter);
  maze.generate(10, 10);
  ASSERT_EQ(maze.getRowsAndCols().first, 10);
  maze.generate(2, 17);
  ASSERT_EQ(maze.getRowsAndCols().first, 2);
  ASSERT_EQ(maze.getRowsAndCols().second, 17);
}

// check side walls generate
TEST(test_s21_Maze, sideWallsGenerateCheck) {
  s21::Interface inter;
  s21::Facade maze(&inter);
  maze.generate(34, 34);
  std::vector<std::vector<bool>> rightWalls = maze.getData().first;
  std::vector<std::vector<bool>> bottomWalls = maze.getData().second;
  size_t rows = maze.getRowsAndCols().first;
  size_t cols = maze.getRowsAndCols().second;
  for (size_t i = 0; i < rows; i++) {
    ASSERT_EQ(rightWalls[i][cols - 1], true);
  }
  for (size_t i = 0; i < cols; i++) {
    ASSERT_EQ(bottomWalls[rows - 1][i], true);
  }
  maze.generate(4, 8);
  rightWalls = maze.getData().first;
  bottomWalls = maze.getData().second;
  rows = maze.getRowsAndCols().first;
  cols = maze.getRowsAndCols().second;
  for (size_t i = 0; i < rows; i++) {
    ASSERT_EQ(rightWalls[i][cols - 1], true);
  }
  for (size_t i = 0; i < cols; i++) {
    ASSERT_EQ(bottomWalls[rows - 1][i], true);
  }
}

// save maze
TEST(test_s21_Maze, saveCheck) {
  s21::Interface inter;
  s21::Facade maze(&inter);
  maze.generate(15, 15);
  maze.saveFile("Labyrinth/15x15.txt");
  bool check = maze.openFile("Labyrinth/15x15.txt");
  ASSERT_EQ(check, true);
  std::vector<std::vector<bool>> rightWalls = maze.getData().first;
  std::vector<std::vector<bool>> bottomWalls = maze.getData().second;
  size_t rows = maze.getRowsAndCols().first;
  size_t cols = maze.getRowsAndCols().second;
  for (size_t i = 0; i < rows; i++) {
    ASSERT_EQ(rightWalls[i][cols - 1], true);
  }
  for (size_t i = 0; i < cols; i++) {
    ASSERT_EQ(bottomWalls[rows - 1][i], true);
  }
  ASSERT_EQ(rows, 15);
  ASSERT_EQ(cols, 15);
}

// check find path
TEST(test_s21_Maze, mazePathCheck) {
  s21::Interface inter;
  s21::Facade maze(&inter);
  maze.openFile("Labyrinth/4x5.txt");
  std::vector<std::pair<int, int>> path = maze.findPath(2, 1, 3, 3);
  int path_check_1[] = {3, 3, 3, 2, 3, 1, 2, 1};
  for (size_t i = 0, k = 0; i < path.size(); i++) {
    ASSERT_EQ(path[i].first, path_check_1[k++]);
    ASSERT_EQ(path[i].second, path_check_1[k++]);
  }
  maze.openFile("Labyrinth/10x10.txt");
  path = maze.findPath(2, 3, 9, 8);
  int path_check_2[] = {9, 8, 8, 8, 7, 8, 7, 7, 7, 6, 7, 5, 8, 5, 8, 6, 9, 6, 9, 5, 9, 4, 9, 3, 9,
                        2, 9, 1, 9, 0, 8, 0, 8, 1, 8, 2, 8, 3, 7, 3, 7, 2, 7, 1, 6, 1, 5, 1, 4, 1,
                        4, 0, 3, 0, 3, 1, 3, 2, 4, 2, 5, 2, 5, 3, 4, 3, 4, 4, 3, 4, 3, 3, 2, 3};
  for (size_t i = 0, k = 0; i < path.size(); i++) {
    ASSERT_EQ(path[i].first, path_check_2[k++]);
    ASSERT_EQ(path[i].second, path_check_2[k++]);
  }
}

// open cave
TEST(test_s21_Cave, openCheck) {
  s21::Interface inter;
  s21::Facade cave(&inter);
  bool check = cave.openFileCave("Caves/3x3.txt");
  ASSERT_EQ(check, true);
  check = cave.openFileCave("Caves/50X50.txt");
  ASSERT_EQ(check, true);
  check = cave.openFileCave("Caves/20x20(incorrect).txt");
  ASSERT_EQ(check, false);
  check = cave.openFileCave("Caves/503450.txt");
  ASSERT_EQ(check, false);
}

// check size cave
TEST(test_s21_Cave, sizeCheck) {
  s21::Interface inter;
  s21::Facade cave(&inter);
  cave.openFileCave("Caves/3x3.txt");
  ASSERT_EQ(cave.getRowsAndColsCave().first, 3);
  cave.openFileCave("Caves/20x20.txt");
  ASSERT_EQ(cave.getRowsAndColsCave().second, 20);
  cave.openFileCave("Caves/50X50.txt");
  ASSERT_EQ(cave.getRowsAndColsCave().first, 50);
  cave.openFileCave("Caves/abcd.txt");
  ASSERT_EQ(cave.getRowsAndColsCave().first, 0);
}

// check cave data
TEST(test_s21_Cave, caveDataCheck) {
  s21::Interface inter;
  s21::Facade cave(&inter);
  cave.openFileCave("Caves/10x10.txt");
  std::vector<std::vector<bool>> dataCave = cave.getDataCave();
  size_t rows = cave.getRowsAndColsCave().first;
  size_t cols = cave.getRowsAndColsCave().second;
  bool check_1[10] = {1, 1, 0, 0, 0, 0, 0, 1, 0, 0};
  for (size_t i = 0, k = 0; i < cols; i++) {
    ASSERT_EQ(dataCave[6][i], check_1[k++]);
  }
  bool check_2[10] = {0, 1, 0, 1, 1, 1, 0, 0, 0, 0};
  for (size_t i = 0, k = 0; i < rows; i++) {
    ASSERT_EQ(dataCave[i][3], check_2[k++]);
  }
  cave.openFileCave("Caves/20x20.txt");
  dataCave = cave.getDataCave();
  rows = cave.getRowsAndColsCave().first;
  cols = cave.getRowsAndColsCave().second;
  bool check_3[20] = {0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0, 1};
  for (size_t i = 0, k = 0; i < rows; i++) {
    ASSERT_EQ(dataCave[i][15], check_3[k++]);
  }
  bool check_4[20] = {0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0};
  for (size_t i = 0, k = 0; i < cols; i++) {
    ASSERT_EQ(dataCave[7][i], check_4[k++]);
  }
}

// check cave step
TEST(test_s21_Cave, caveStepCheck) {
  s21::Interface inter;
  s21::Facade cave(&inter);
  cave.openFileCave("Caves/10x10.txt");
  cave.caveStep(2, 3);
  std::vector<std::vector<bool>> dataCave = cave.getDataCave();
  size_t cols = cave.getRowsAndColsCave().second;
  bool check_1[10] = {1, 1, 1, 1, 1, 1, 1, 0, 0, 1};
  for (size_t i = 0, k = 0; i < cols; i++) {
    ASSERT_EQ(dataCave[4][i], check_1[k++]);
  }
  cave.caveStep(2, 3);
  dataCave = cave.getDataCave();
  bool check_2[10] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
  for (size_t i = 0, k = 0; i < cols; i++) {
    ASSERT_EQ(dataCave[4][i], check_2[k++]);
  }
  cave.openFileCave("Caves/20x20.txt");
  cave.caveStep(1, 4);
  dataCave = cave.getDataCave();
  size_t rows = cave.getRowsAndColsCave().first;
  bool check_3[20] = {1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 1};
  for (size_t i = 0, k = 0; i < rows; i++) {
    ASSERT_EQ(dataCave[i][12], check_3[k++]);
  }
  cave.caveStep(1, 4);
  dataCave = cave.getDataCave();
  bool check_4[20] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
  for (size_t i = 0, k = 0; i < rows; i++) {
    ASSERT_EQ(dataCave[i][12], check_4[k++]);
  }
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
