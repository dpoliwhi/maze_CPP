#pragma once

#include <cmath>
#include <iostream>

namespace s21 {

class Matrix {
  friend Matrix operator*(const Matrix& other, double number);
  friend Matrix operator*(double number, const Matrix& other);

 private:
  int _rows, _cols;
  double** _matrix;
  double** Create_matrix(int rows, int cols);
  void Destroy_matrix();
  void Copy_matrix(double** other);
  double determ(int m);
  Matrix get_smaller_matrix(int i, int j, int m);

 public:
  Matrix();  // Default constructor
  Matrix(int rows, int cols);
  ~Matrix();                    // Destructor
  Matrix(const Matrix& other);  // copy matrix
  Matrix(Matrix&& other);       // Move Matrix

  bool eq_matrix(const Matrix& other);
  void sum_matrix(const Matrix& other);
  void sub_matrix(const Matrix& other);
  void mul_number(const double num);
  void mul_matrix(const Matrix& other);
  Matrix transpose();
  Matrix calc_complements();
  double determinant();
  Matrix inverse_matrix();

  // overloading operators
  Matrix operator+(const Matrix& other);
  Matrix operator+=(const Matrix& other);
  Matrix operator-(const Matrix& other);
  Matrix operator-=(const Matrix& other);
  Matrix operator*(const Matrix& other);
  Matrix operator*=(const Matrix& other);
  Matrix operator*=(double number);
  Matrix& operator=(const Matrix& other);
  bool operator==(const Matrix& other);
  double& operator()(int i, int j) const;

  // Accessors and mutators
  void setRows(int rows);
  void setCols(int cols);
  int getRows();
  int getCols();

  // additional
  void fill_matrix(const double* a);
};

}  // namespace s21
