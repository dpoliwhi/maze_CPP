#include "interface.h"

namespace s21 {

Interface::~Interface() {
  delete move;
  delete figure;
}

std::pair<std::vector<std::vector<double>>, std::vector<std::vector<int>>> Interface::openFile(
    std::string fileName) {
  if (figure == nullptr) {
    figure = new Object();
  }
  figure->openFile(fileName);
  return figure->getVandF();
}

std::pair<int, int> Interface::getCountVandF() {
  if (figure == nullptr) {
    return std::pair<int, int>{0, 0};
  } else {
    return figure->getCountVandF();
  }
}

std::pair<int, int> Interface::getRowsVandF() {
  if (figure == nullptr) {
    return std::pair<int, int>{0, 0};
  } else {
    return figure->getRowsVandF();
  }
}

std::pair<double, double> Interface::getExtremum() { return figure->getExtremum(); }

std::pair<std::vector<std::vector<double>>, std::vector<std::vector<int>>> Interface::allActions(
    std::string fileName, char choseAction, char choseAxis, double var) {
  if (move == nullptr) {
    move = new Action();
  }
  if (fileName != "notNew") {
    move->openFile(fileName);
  }
  if (choseAction == 'R') {
    if (choseAxis == 'X') {
      move->actionRotateX(var);
    } else if (choseAxis == 'Y') {
      move->actionRotateY(var);
    } else if (choseAxis == 'Z') {
      move->actionRotateZ(var);
    }
  } else if (choseAction == 'M') {
    if (choseAxis == 'X') {
      move->actionMoveX(var);
    } else if (choseAxis == 'Y') {
      move->actionMoveY(var);
    } else if (choseAxis == 'Z') {
      move->actionMoveZ(var);
    }
  } else if (choseAction == 'S') {
    if (choseAxis == 'X') {
      move->actionScalePlus(var);
    } else if (choseAxis == 'Y') {
      move->actionScaleMinus(var);
    }
  }
  move->actionsWithObject();
  return move->getVandF();
}

}  // namespace s21
