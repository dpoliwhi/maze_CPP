#include "openMaze.h"

namespace s21 {

bool OpenMaze::openFile(std::string fileName) {
  cleanData();
  std::ifstream file(fileName);
  std::string line;
  int choseData = 0;
  bool isOpen = true;
  size_t countLines = 0;
  while (getline(file, line) && isOpen) {
    if (line.empty() || countLines == data.rows + 1) {
      choseData = 2;
      countLines++;
      continue;
    }
    if (countLines == 0) {
      isOpen = parsingSize(line);
      choseData = 1;
    } else if (choseData == 1) {
      std::pair<std::vector<bool>, bool> oneLine = parsingLine(line);
      isOpen = oneLine.second;
      data.rightWalls.push_back(oneLine.first);
    } else if (choseData == 2) {
      std::pair<std::vector<bool>, bool> oneLine = parsingLine(line);
      isOpen = oneLine.second;
      data.bottomWalls.push_back(oneLine.first);
    }
    countLines++;
  }
  file.close();
  isOpen = checkSizeData();
  return isOpen;
}

bool OpenMaze::checkSizeData() {
  bool isOk = true;
  if (data.rightWalls.size() != data.rows && data.bottomWalls.size() != data.rows) {
    isOk = false;
  } else {
    for (size_t i = 0; i < data.rightWalls.size(); i++) {
      if (data.rightWalls[i].size() != data.cols || data.bottomWalls[i].size() != data.cols) {
        isOk = false;
        break;
      }
    }
  }
  if (data.cols == 0 || data.rows == 0) isOk = false;
  return isOk;
}

bool OpenMaze::parsingSize(std::string line) {
  bool isCoorectSize = true;
  std::vector<int> pairOfSizes;
  std::string::iterator iter(line.begin());
  std::string buffer;
  while (iter != line.end()) {
    if (isdigit(*iter)) {
      buffer.push_back(*iter);
      if ((iter + 1) == line.end() || (*(iter + 1) == ' ')) {
        pairOfSizes.push_back(atoi(buffer.c_str()));
        buffer.clear();
      }
      ++iter;
    } else if (*iter == ' ') {
      ++iter;
    } else {
      isCoorectSize = false;
      break;
    }
  }
  if (pairOfSizes.size() == 2 && pairOfSizes[0] <= 50 && pairOfSizes[1] <= 50) {
    data.rows = pairOfSizes[0];
    data.cols = pairOfSizes[1];
  } else {
    isCoorectSize = false;
  }
  return isCoorectSize;
}

std::pair<std::vector<bool>, bool> OpenMaze::parsingLine(std::string line) {
  std::vector<bool> oneLine;
  bool isValid = true;
  std::string::iterator iter(line.begin());
  while (iter != line.end()) {
    if (*iter == '0' || *iter == '1') {
      oneLine.push_back(*iter - '0');
      ++iter;
    } else if (*iter == ' ') {
      ++iter;
    } else {
      isValid = false;
      break;
    }
  }
  return {oneLine, isValid};
}

}  // namespace s21
