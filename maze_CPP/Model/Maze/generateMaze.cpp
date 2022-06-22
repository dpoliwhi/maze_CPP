#include "generateMaze.h"

namespace s21 {

void Generate::createEmptyMaze(size_t rows, size_t cols) {
  data.rows = rows;
  data.cols = cols;
  data.rightWalls.resize(data.rows);
  for (size_t i = 0; i < data.rows; i++) {
    data.rightWalls[i].resize(data.cols);
  }
  data.bottomWalls.resize(data.rows);
  for (size_t j = 0; j < data.rows; j++) {
    data.bottomWalls[j].resize(data.cols);
  }
  setLine.resize(data.cols);
}

bool Generate::generate(size_t rows, size_t cols) {
  if (rows < 1 || cols < 1) {
    return false;
  } else {
    cleanData();
    createEmptyMaze(rows, cols);
    for (size_t i = 0; i < data.rows - 1; i++) {
      createUniqSetLine();
      createRightWalsInLine(i);
      createBottomWalsInLine(i);
      setForNewLine(i);
    }
    createLastWalls();
    setLine.clear();
    uniqSet = 1;
    return true;
  }
}

bool Generate::randomizer() {
  std::random_device random;
  std::default_random_engine engine(random());
  std::uniform_int_distribution<int> res(0, 1);
  return static_cast<bool>(res(engine));
}

void Generate::createUniqSetLine() {
  for (size_t i = 0; i < data.cols; i++) {
    if (setLine[i] == 0) {
      setLine[i] = uniqSet++;
    }
  }
}

void Generate::createRightWalsInLine(size_t row) {
  for (size_t i = 0; i < data.cols - 1; i++) {
    bool wall = randomizer();
    if (wall == true || setLine[i] == setLine[i + 1]) {
      data.rightWalls[row][i] = true;
    } else {
      mergeSetInLine(i);
    }
  }
  data.rightWalls[row][data.cols - 1] = true;
}

void Generate::mergeSetInLine(size_t index) {
  int firstElement = setLine[index];
  int secondElement = setLine[index + 1];
  for (size_t i = 0; i < data.cols; i++) {
    if (setLine[i] == secondElement) {
      setLine[i] = firstElement;
    }
  }
}

void Generate::createBottomWalsInLine(size_t row) {
  for (size_t i = 0; i < data.cols; i++) {
    bool wall = randomizer();
    if (wall == true && calcUniqSets(setLine[i]) != 1) {
      data.bottomWalls[row][i] = true;
    }
  }
  checkBottomWalls(row);
}

int Generate::calcUniqSets(int uniqSet) {
  int result = 0;
  for (size_t i = 0; i < data.cols; i++) {
    if (setLine[i] == uniqSet) result++;
  }
  return result;
}

void Generate::checkBottomWalls(size_t row) {
  for (size_t i = 0; i < data.cols; i++) {
    if (calcBottomWalls(setLine[i], row) == 0) {
      data.bottomWalls[row][i] = false;
    }
  }
}

int Generate::calcBottomWalls(int uniqSet, size_t row) {
  int result = 0;
  for (size_t i = 0; i < data.cols; i++) {
    if (data.bottomWalls[row][i] == false && setLine[i] == uniqSet) {
      result++;
    }
  }
  return result;
}

void Generate::setForNewLine(size_t row) {
  for (size_t i = 0; i < data.cols; i++) {
    if (data.bottomWalls[row][i] == true) {
      setLine[i] = 0;
    }
  }
}

void Generate::createLastWalls() {
  createUniqSetLine();
  createRightWalsInLine(data.rows - 1);
  for (size_t i = 0; i < data.cols - 1; i++) {
    data.bottomWalls[data.rows - 1][i] = true;
    if (setLine[i] != setLine[i + 1]) {
      data.rightWalls[data.rows - 1][i] = false;
      mergeSetInLine(i);
    }
  }
  data.bottomWalls[data.rows - 1][data.cols - 1] = true;
}

}  // namespace s21
