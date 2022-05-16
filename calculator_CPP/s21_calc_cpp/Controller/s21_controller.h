#pragma once

#include <sstream>

#include "../Model/s21_model.h"

namespace s21 {
class controller {
 private:
  model *c;

 public:
  explicit controller(model *m);
  std::string calc_expression(std::string in, std::string x);
  std::vector<double> create_graph(std::string in, std::vector<double> x);
  void clear_containers();
};

}  // namespace s21
