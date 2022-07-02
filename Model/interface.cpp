#include "interface.h"

namespace s21 {

Interface::~Interface() {
  delete openMaze;
  delete generateMaze;
  delete openCave;
  delete generateCave;
}

bool Interface::openFile(const std::string& fileName) {
  if (openMaze == nullptr) {
    openMaze = new OpenMaze();
  }
  return openMaze->openFile(fileName);
}

bool Interface::generate(size_t rows, size_t cols) {
  if (generateMaze == nullptr) {
    generateMaze = new Generate();
  }
  return generateMaze->generate(rows, cols);
}

std::pair<std::vector<std::vector<bool>>, std::vector<std::vector<bool>>> Interface::getData() {
  if (openMaze == nullptr) {
    return generateMaze->getData();
  } else {
    return openMaze->getData();
  }
}

std::pair<size_t, size_t> Interface::getRowsAndCols() {
  if (openMaze == nullptr) {
    return generateMaze->getRowsAndCols();
  } else {
    return openMaze->getRowsAndCols();
  }
}

std::vector<std::pair<int, int>> Interface::findPath(int startx, int starty, int endx, int endy) {
  if (openMaze == nullptr) {
    return generateMaze->findPath(startx, starty, endx, endy);
  } else {
    return openMaze->findPath(startx, starty, endx, endy);
  }
}

void Interface::saveFile(const std::string& fileName) {
  if (openMaze == nullptr) {
    return generateMaze->saveMaze(fileName);
  } else {
    return openMaze->saveMaze(fileName);
  }
}

void Interface::cleanFileMaze() { openMaze = nullptr; }

void Interface::cleanFileCave() { openCave = nullptr; }

bool Interface::openFileCave(const std::string& fileName) {
  if (openCave == nullptr) {
    openCave = new OpenCave();
  }
  return openCave->openFile(fileName);
}

std::vector<std::vector<bool>> Interface::getDataCave() {
  if (openCave == nullptr) {
    return generateCave->getData();
  } else {
    return openCave->getData();
  }
}

std::pair<size_t, size_t> Interface::getRowsAndColsCave() {
  if (openCave == nullptr) {
    return generateCave->getRowsAndCols();
  } else {
    return openCave->getRowsAndCols();
  }
}

bool Interface::generateC(size_t rows, size_t cols, int chance) {
  if (generateCave == nullptr) {
    generateCave = new GenerateCave();
  }
  return generateCave->generate(rows, cols, chance);
}

bool Interface::step(size_t birth, size_t death) {
  if (openCave == nullptr) {
    return generateCave->oneStep(birth, death);
  } else {
    return openCave->oneStep(birth, death);
  }
}

}  // namespace s21
