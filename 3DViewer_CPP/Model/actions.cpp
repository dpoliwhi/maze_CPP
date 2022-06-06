#include "actions.h"

namespace s21 {

void Action::actionScalePlus(double var) {
  double scaling[] = {var, 0, 0, 0, 0, var, 0, 0, 0, 0, var, 0, 0, 0, 0, 1};
  moveMatrix.fill_matrix(scaling);
}

void Action::actionScaleMinus(double var) {
  double scaling[] = {1 / var, 0, 0, 0, 0, 1 / var, 0, 0, 0, 0, 1 / var, 0, 0, 0, 0, 1};
  moveMatrix.fill_matrix(scaling);
}

void Action::actionMoveX(double var) {
  double scaling[] = {1, 0, 0, var, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
  moveMatrix.fill_matrix(scaling);
}

void Action::actionMoveY(double var) {
  double scaling[] = {1, 0, 0, 0, 0, 1, 0, var, 0, 0, 1, 0, 0, 0, 0, 1};
  moveMatrix.fill_matrix(scaling);
}

void Action::actionMoveZ(double var) {
  double scaling[] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, var, 0, 0, 0, 1};
  moveMatrix.fill_matrix(scaling);
}

void Action::actionRotateX(double var) {
  double scaling[] = {1, 0, 0, 0, 0, cos(var), -sin(var), 0, 0, sin(var), cos(var), 0, 0, 0, 0, 1};
  moveMatrix.fill_matrix(scaling);
}

void Action::actionRotateY(double var) {
  double scaling[] = {cos(var), 0, sin(var), 0, 0, 1, 0, 0, -sin(var), 0, cos(var), 0, 0, 0, 0, 1};
  moveMatrix.fill_matrix(scaling);
}

void Action::actionRotateZ(double var) {
  double scaling[] = {cos(var), -sin(var), 0, 0, sin(var), cos(var), 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
  moveMatrix.fill_matrix(scaling);
}

void Action::actionsWithObject() {
  s21::Matrix dot(4, 1);
  s21::Matrix res(4, 1);
  for (int j = 0; j < V.rows; j++) {
    for (size_t i = 0; i < V.data[j].size(); i++) {
      dot(i, 0) = V.data[j][i];
    }
    dot(3, 0) = 1;
    res = moveMatrix;
    res.mul_matrix(dot);
    for (int t = 0; t < 3; t++) {
      V.data[j][t] = res(t, 0);
    }
  }
}

}  // namespace s21
