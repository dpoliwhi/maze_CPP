#pragma once

#include "matrix.h"
#include "object.h"

namespace s21 {

class Action : public s21::Object {
 public:
  s21::Matrix moveMatrix = s21::Matrix(4, 4);

  void actionsWithObject();
  void actionScalePlus(double var);
  void actionScaleMinus(double var);
  void actionMoveX(double var);
  void actionMoveY(double var);
  void actionMoveZ(double var);
  void actionRotateX(double var);
  void actionRotateY(double var);
  void actionRotateZ(double var);
};

}  // namespace s21
