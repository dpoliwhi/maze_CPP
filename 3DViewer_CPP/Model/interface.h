#pragma once

#include "actions.h"
#include "matrix.h"
#include "object.h"

namespace s21 {

class Interface {
 private:
  s21::Action *move = nullptr;
  s21::Object *figure = nullptr;

 public:
  Interface() {}
  ~Interface();
  std::pair<std::vector<std::vector<double>>, std::vector<std::vector<int>>> openFile(std::string fileName);
  std::pair<int, int> getCountVandF();
  std::pair<int, int> getRowsVandF();
  std::pair<std::vector<std::vector<double>>, std::vector<std::vector<int>>> allActions(std::string fileName,
                                                                                        char choseAction,
                                                                                        char choseAxis,
                                                                                        double var);
  std::pair<double, double> getExtremum();
};
}  // namespace s21
