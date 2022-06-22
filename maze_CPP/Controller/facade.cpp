#include "facade.h"

namespace s21 {

Facade::Facade(s21::Interface *interInit) : inter(interInit) {}

bool Facade::openFile(const std::string& fileName) { return inter->openFile(fileName); }

bool Facade::generate(size_t rows, size_t cols) { return inter->generate(rows, cols); }

std::pair<std::vector<std::vector<bool>>, std::vector<std::vector<bool>>> Facade::getData() {
  return inter->getData();
}

std::pair<size_t, size_t> Facade::getRowsAndCols() { return inter->getRowsAndCols(); }

std::pair<size_t, size_t> Facade::getRowsAndColsCave() { return inter->getRowsAndColsCave(); }

bool Facade::caveStep(size_t birth, size_t death) { return inter->step(birth, death); }

std::vector<std::pair<int, int>> Facade::findPath(int startx, int starty, int endx, int endy) {
  return inter->findPath(startx, starty, endx, endy);
}

void Facade::saveFile(const std::string& fileName) { inter->saveFile(fileName); }

void Facade::cleanFileMaze() { inter->cleanFileMaze(); }

void Facade::cleanFileCave() { inter->cleanFileCave(); }

bool Facade::openFileCave(const std::string& fileName) { return inter->openFileCave(fileName); }

bool Facade::generateCave(size_t rows, size_t cols, int chance) {
  return inter->generateC(rows, cols, chance);
}

std::vector<std::vector<bool>> Facade::getDataCave() { return inter->getDataCave(); }

}  // namespace s21
