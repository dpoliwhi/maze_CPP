#pragma once

#include <string.h>

#include <cmath>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

#define SIZE 256
#define S21_NAN 0.0 / 0.0
#define FUNC \
  { "sin", "cos", "tan", "acos", "asin", "atan", "sqrt", "ln", "log" }

namespace s21 {
class model {
 public:
  model(){};
  ~model(){};

  std::vector<std::string> vec_s;
  std::vector<std::string> vec_polish;
  std::stack<double> stack_d;

  int check_parentheses(std::string str);
  std::string unary_sign(std::string s);
  void parsing_string(std::string strin, std::vector<std::string> *res);
  void polish_natation();
  void polish_helper_case_1(std::string data, std::stack<std::string> *buf);
  void polish_helper_case_2(std::stack<std::string> *buf);
  double calculate();
  double calc_operations(char tok);
  double calc_functions(std::string func);
  double s21_calc(std::string strin, std::string x);
  std::vector<double> s21_calc_graph(std::string strin, std::vector<double> x);
};
}  // namespace s21
