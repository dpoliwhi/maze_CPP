#pragma once

#include <iostream>

#include "../Model/interface.h"

namespace s21 {
class Facade {
 private:
  s21::Interface *inter;

 public:
  explicit Facade(s21::Interface *interInit);
  std::pair<std::vector<std::vector<double>>, std::vector<std::vector<int>>> openFile(std::string fileName);
  std::pair<int, int> getCountVertexesAndFaces();
  std::pair<int, int> getRowsVertexesAndFaces();
  std::pair<std::vector<std::vector<double>>, std::vector<std::vector<int>>> actionsWithObject(
      std::string fileName, char choseAction, char choseAxis, double var);
  std::pair<double, double> getExtremum();
};

}  // namespace s21
