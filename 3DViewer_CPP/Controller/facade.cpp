#include "facade.h"

namespace s21 {

Facade::Facade(s21::Interface *interInit) : inter(interInit) {}

std::pair<std::vector<std::vector<double>>, std::vector<std::vector<int>>> Facade::openFile(
    std::string fileName) {
  return inter->openFile(fileName);
}

std::pair<int, int> Facade::getCountVertexesAndFaces() { return inter->getCountVandF(); }

std::pair<int, int> Facade::getRowsVertexesAndFaces() { return inter->getRowsVandF(); }

std::pair<std::vector<std::vector<double>>, std::vector<std::vector<int>>> Facade::actionsWithObject(
    std::string fileName, char choseAction, char choseAxis, double var) {
  return inter->allActions(fileName, choseAction, choseAxis, var);
}

std::pair<double, double> Facade::getExtremum() { return inter->getExtremum(); }

}  // namespace s21
