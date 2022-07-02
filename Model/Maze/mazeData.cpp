#include "mazeData.h"

namespace s21 {

std::pair<std::vector<std::vector<bool>>, std::vector<std::vector<bool>>> Maze::getData() {
  return {data.rightWalls, data.bottomWalls};
}

std::pair<size_t, size_t> Maze::getRowsAndCols() { return {data.rows, data.cols}; }

void Maze::cleanData() {
  for (size_t i = 0; i < data.rightWalls.size(); i++) {
    data.rightWalls[i].clear();
  }
  data.rightWalls.clear();
  for (size_t i = 0; i < data.bottomWalls.size(); i++) {
    data.bottomWalls[i].clear();
  }
  data.bottomWalls.clear();
  data.rows = 0, data.cols = 0;
}

std::vector<std::pair<int, int>> Maze::findPath(int startx, int starty, int endx, int endy) {
  std::vector<std::pair<int, int>> result;
  // create path matrix for waves and fill it with -1
  int path[data.cols][data.rows];
  for (size_t i = 0; i < data.rows; i++) {
    for (size_t j = 0; j < data.cols; j++) {
      path[j][i] = -1;
    }
  }
  // create bool for tagget/not tagged cells
  bool stop = false;
  int wave = 0;
  path[startx][starty] = 0;
  // arrays to traverse all four directions around one cell
  const int movey[4] = {1, 0, -1, 0};
  const int movex[4] = {0, 1, 0, -1};
  while (!stop && path[endx][endy] == -1) {
    stop = true;  // suppose, that all free cells are tagged
    for (size_t i = 0; i < data.rows; i++)
      for (size_t j = 0; j < data.cols; j++)
        if (path[j][i] == wave) {
          for (size_t k = 0; k < 4; k++) {      // go through all unmarked neighbors
            bool choise = checkWalls(k, i, j);  // check walls around cell
            size_t newy = i + movey[k], newx = j + movex[k];
            if (newy < data.rows && newx < data.cols && path[newx][newy] == -1 && !choise) {
              stop = false;                   // find not tagged cell
              path[newx][newy] = (wave + 1);  // spread the wave
            }
          }
        }
    wave++;
  }
  // save the path
  wave = path[endx][endy];  // start from end point
  int x = endx;
  int y = endy;
  while (wave >= 0) {
    result.push_back({x, y});
    wave--;
    for (int k = 0; k < 4; ++k) {
      bool choise = checkWalls(k, y, x);  // check walls around cell
      size_t iy = y + movey[k], ix = x + movex[k];
      if (iy < data.rows && ix < data.cols && path[ix][iy] == wave && !choise) {
        x += movex[k];
        y += movey[k];  // go to the cell that is 1 closer to the start
        break;
      }
    }
  }
  return result;
}

bool Maze::checkWalls(int k, int y, int x) {
  bool result = false;
  if (k == 0) {
    result = data.bottomWalls[y][x];
  } else if (k == 1) {
    result = data.rightWalls[y][x];
  } else if (k == 2 && y > 0) {
    result = data.bottomWalls[y - 1][x];
  } else if (k == 3 && x > 0) {
    result = data.rightWalls[y][x - 1];
  }
  return result;
}

void Maze::saveMaze(std::string fileName) {
  std::ofstream file;
  file.open(fileName);
  if (file.is_open()) {
    file << getRowsAndCols().first << " " << getRowsAndCols().second << "\n";
    std::vector<std::vector<bool>> rightWalls = getData().first;
    std::vector<std::vector<bool>> bottomWalls = getData().second;
    for (size_t i = 0; i < rightWalls.size(); i++) {
      for (size_t j = 0; j < rightWalls[i].size(); j++) {
        file << rightWalls[i][j];
        if (j != rightWalls[i].size() - 1) {
          file << " ";
        }
      }
      file << "\n";
    }
    file << "\n";
    for (size_t i = 0; i < bottomWalls.size(); i++) {
      for (size_t j = 0; j < bottomWalls[i].size(); j++) {
        file << bottomWalls[i][j];
        if (j != bottomWalls[i].size() - 1) {
          file << " ";
        }
      }
      file << "\n";
    }
  }
}

}  // namespace s21
