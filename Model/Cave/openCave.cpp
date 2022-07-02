#include "openCave.h"

namespace s21 {

bool OpenCave::openFile(std::string fileName) {
  cleanData();
  std::ifstream file(fileName);
  std::string line;
  bool isOpen = true;
  size_t countLines = 0;
  while (getline(file, line) && isOpen) {
    if (countLines == 0) {
      isOpen = parsingSize(line);
    } else {
      std::pair<std::vector<bool>, bool> oneLine = parsingLine(line);
      isOpen = oneLine.second;
      data.life.push_back(oneLine.first);
    }
    countLines++;
  }
  file.close();
  isOpen = checkSizeData();
  return isOpen;
}

bool OpenCave::checkSizeData() {
  bool isOk = true;
  if (data.life.size() != data.rows) {
    isOk = false;
  } else {
    for (size_t i = 0; i < data.life.size(); i++) {
      if (data.life[i].size() != data.cols) {
        isOk = false;
        break;
      }
    }
  }
  if (data.cols == 0 || data.rows == 0) isOk = false;
  return isOk;
}

bool OpenCave::parsingSize(std::string line) {
  bool isCoorectSize = true;
  std::vector<int> pairOfSizes;
  std::string::iterator iter(line.begin());
  std::string buffer;
  while (iter != line.end()) {
    if (isdigit(*iter)) {
      buffer.push_back(*iter);
      if ((iter + 1) == line.end() || ((*(iter + 1) == ' '))) {
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

std::pair<std::vector<bool>, bool> OpenCave::parsingLine(std::string line) {
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
