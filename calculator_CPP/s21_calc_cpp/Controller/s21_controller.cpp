#include "s21_controller.h"

namespace s21 {
controller::controller(model *m) : c(m) {}

std::string controller::calc_expression(std::string in, std::string x) {
  std::string out;
  try {
    double res = c->s21_calc(in, x);
    std::ostringstream os_out;
    os_out << res;
    out = os_out.str();
    c->vec_s.clear();
    c->vec_polish.clear();
    return out;
  } catch (const char *msg) {
    return msg;
  }
}

std::vector<double> controller::create_graph(std::string in, std::vector<double> x) {
  std::vector<double> res;
  try {
    res = c->s21_calc_graph(in, x);
    c->vec_s.clear();
    c->vec_polish.clear();
    return res;
  } catch (const char *msg) {
    res.resize(x.size(), 0.0);
    return res;
  }
}

void controller::clear_containers() {
  c->vec_s.clear();
  c->vec_polish.clear();
  while (c->stack_d.size()) c->stack_d.pop();
}

}  // namespace s21
