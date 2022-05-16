#include <gtest/gtest.h>

#include "s21_calc_cpp/Controller/s21_controller.h"
#include "s21_calc_cpp/Model/s21_model.h"

// simple
TEST(test_s21_calc, simple) {
  s21::model model;
  s21::controller c(&model);
  std::string out;

  out = c.calc_expression("2+2*2^2", "nox");
  ASSERT_EQ(out, "10");

  out = c.calc_expression("1.23-45.98+73*2.9", "nox");
  ASSERT_EQ(out, "166.95");

  out = c.calc_expression("0.0000012-0.1234567^0.00003456/9.9999999", "nox");
  ASSERT_EQ(out, "-0.0999916");

  out = c.calc_expression("-2+9+(-4)", "nox");
  ASSERT_EQ(out, "3");
}

// hard
TEST(test_s21_calc, hard) {
  s21::model model;
  s21::controller c(&model);
  std::string out;
  out = c.calc_expression("2.19/sin(3-2)*cos(2/sqrt(8-5))*5.123", "nox");
  ASSERT_EQ(out, "5.38912");

  out = c.calc_expression("sin(20.1232*0.000017^2+5.4+cos(0.0099+3))", "nox");
  ASSERT_EQ(out, "-0.954228");

  out = c.calc_expression("sqrt(2.023*sin(2.91))", "nox");
  ASSERT_EQ(out, "0.681421");

  out = c.calc_expression("0.099*tan(1.11)+(9+0.88)*1.12", "nox");
  ASSERT_EQ(out, "11.265");

  out = c.calc_expression("8+ln(1.15)-56^0.1", "nox");
  ASSERT_EQ(out, "6.64415");

  out = c.calc_expression("sqrt(34.76)+log(1.15+(1.1-1.0856))", "nox");
  ASSERT_EQ(out, "5.96186");

  out = c.calc_expression("log(2.33*sin(0.99)+ln(cos(56)/tan(0.5667)))", "nox");
  ASSERT_EQ(out, "0.350491");
}

// substitution x
TEST(test_s21_calc, substitution) {
  s21::model model;
  s21::controller c(&model);
  std::string out;
  out = c.calc_expression("2.19/sin(x-2)", "5");
  ASSERT_EQ(out, "15.5187");

  out = c.calc_expression("sin(x*0.000017^2+x+cos(0.0099+x))", "5.43");
  ASSERT_EQ(out, "-0.187064");

  out = c.calc_expression("sqrt(2.023*sin(x))", "0.143");
  ASSERT_EQ(out, "0.53694");

  out = c.calc_expression("0.099*tan(x)+(9+x)*1.12", "-2.305");
  ASSERT_EQ(out, "7.60809");
}

// graph
TEST(test_s21_calc, graph) {
  s21::model model;
  s21::controller c(&model);
  std::vector<double> out;
  std::vector<double> out_cmp = {-11, -6, -1, 4, 9};
  std::vector<double> x = {-2, -1, 0, 1, 2};
  out = c.create_graph("x*5-1", x);
  ASSERT_EQ(out, out_cmp);
  c.clear_containers();
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
