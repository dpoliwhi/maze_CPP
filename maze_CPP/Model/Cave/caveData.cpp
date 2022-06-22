#include "caveData.h"

namespace s21 {

std::vector<std::vector<bool>> Cave::getData() { return data.life; }

std::pair<size_t, size_t> Cave::getRowsAndCols() { return {data.rows, data.cols}; }

bool Cave::oneStep(size_t birth, size_t death) {
  bool result = true;
  std::vector<std::vector<bool>> lifeTemp = data.life;
  const int neighboursy[8] = {1, 1, 0, -1, -1, -1, 0, 1};
  const int neighboursx[8] = {0, 1, 1, 1, 0, -1, -1, -1};
  size_t count, checkChanges = 0;
  for (size_t i = 0; i < data.rows; i++) {
    for (size_t j = 0; j < data.cols; j++) {
      count = 0;
      for (size_t k = 0; k < 8; k++) {
        int newy = i + neighboursy[k], newx = j + neighboursx[k];
        if (newy < 0 || newx < 0 || newx == (int)data.cols || newy == (int)data.rows) {
          count++;
        } else if (lifeTemp[newy][newx]) {
          count++;
        }
      }
      if (lifeTemp[i][j] && count < death)
        data.life[i][j] = false;
      else if (!lifeTemp[i][j] && count > birth)
        data.life[i][j] = true;
      else
        checkChanges++;
    }
  }
  if (checkChanges == data.rows * data.cols) result = false;
  return result;
}

void Cave::cleanData() {
  for (size_t i = 0; i < data.life.size(); i++) {
    data.life[i].clear();
  }
  data.life.clear();
  data.rows = 0, data.cols = 0;
}

}  // namespace s21
