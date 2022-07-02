#pragma once

#include <fstream>
#include <string>
#include <vector>

#include "caveData.h"

namespace s21 {

class OpenCave : public Cave {
 private:
  bool parsingSize(std::string line);
  std::pair<std::vector<bool>, bool> parsingLine(std::string line);
  bool checkSizeData();

 public:
  bool openFile(std::string fileName);
};

}  // namespace s21
