#pragma once

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace s21 {

class Object {
 protected:
  template <class T>
  class StructOfObject {
   public:
    std::vector<std::vector<T>> data;
    int rows;
    int count;
  };

  struct ExtremumStruct {
    double min = 0;
    double max = 0;
  };

  ExtremumStruct extremum = {0, 0};
  StructOfObject<double> V;
  StructOfObject<int> F;

  std::vector<double> parsingLineVertexes(std::string line);
  std::vector<int> parsingLineFaces(std::string line);

 public:
  Object();
  void openFile(std::string fileName);
  void cleanData();
  std::pair<std::vector<std::vector<double>>, std::vector<std::vector<int>>> getVandF();
  std::pair<int, int> getCountVandF();
  std::pair<int, int> getRowsVandF();
  std::pair<double, double> getExtremum();
};

}  // namespace s21
