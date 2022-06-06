#include "matrix.h"

namespace s21 {

// Accessors and mutators
int Matrix::getCols() { return this->_cols; }

int Matrix::getRows() { return this->_rows; }

void Matrix::setCols(int cols) { this->_cols = cols; }

void Matrix::setRows(int rows) { this->_rows = rows; }

// Constructors and destructrors
Matrix::Matrix() : _rows(1), _cols(1) { this->_matrix = Create_matrix(1, 1); }

Matrix::Matrix(int rows, int cols) : _rows(rows), _cols(cols) {
  if (_rows > 0 && _cols > 0) {
    this->_matrix = Create_matrix(rows, cols);
  } else {
    _rows = 0;
    _cols = 0;
    throw std::invalid_argument("Incorrect size of matrix");
  }
}

double** Matrix::Create_matrix(int rows, int cols) {
  double** _matrix = new double*[rows];
  for (int i = 0; i < rows; i++) {
    _matrix[i] = new double[cols]();
  }
  return _matrix;
}

Matrix::~Matrix() {
  if (_rows > 0 && _cols > 0) Destroy_matrix();
}

void Matrix::Destroy_matrix() {
  for (int i = 0; i < _rows; i++) delete[] _matrix[i];
  delete[] _matrix;
}

Matrix::Matrix(const Matrix& other) : _rows(other._rows), _cols(other._rows), _matrix(NULL) {
  Copy_matrix(other._matrix);
}

void Matrix::Copy_matrix(double** other) {
  this->_matrix = Create_matrix(this->_rows, this->_cols);
  for (int i = 0; i < this->_rows; i++)
    for (int j = 0; j < this->_cols; j++) this->_matrix[i][j] = other[i][j];
}

Matrix::Matrix(Matrix&& other) : _rows(other._rows), _cols(other._rows) {
  Copy_matrix(other._matrix);
  other._cols = 0;
  other._rows = 0;
  other.Destroy_matrix();
}

bool Matrix::eq_matrix(const Matrix& other) {
  bool res = true;
  if (this->_rows == other._rows && this->_cols == other._cols) {
    for (int i = 0; i < this->_rows; i++) {
      for (int j = 0; j < this->_cols; j++) {
        if (fabs(this->_matrix[i][j] - other._matrix[i][j]) >= 1e-7) {
          res = false;
          break;
        }
      }
    }
  } else {
    res = false;
  }
  return res;
}

void Matrix::sum_matrix(const Matrix& other) {
  if ((_matrix && other._matrix) && _rows == other._rows && _cols == other._cols) {
    for (int i = 0; i < _rows; i++)
      for (int j = 0; j < _cols; j++) _matrix[i][j] += other._matrix[i][j];
  } else {
    throw std::invalid_argument("Incorrect size of matrix");
  }
}

void Matrix::sub_matrix(const Matrix& other) {
  if ((_matrix && other._matrix) && _rows == other._rows && _cols == other._cols) {
    for (int i = 0; i < _rows; i++)
      for (int j = 0; j < _cols; j++) _matrix[i][j] -= other._matrix[i][j];
  } else {
    throw std::invalid_argument("Incorrect size of matrix");
  }
}

void Matrix::mul_number(const double num) {
  if (_matrix) {
    for (int i = 0; i < _rows; i++)
      for (int j = 0; j < _cols; j++) _matrix[i][j] *= num;
  } else {
    throw std::invalid_argument("Incorrect size of matrix");
  }
}

void Matrix::mul_matrix(const Matrix& other) {
  if (this->_cols == other._rows) {
    Matrix result(this->_rows, other._cols);
    for (int i = 0; i < this->_rows; i++) {
      for (int j = 0; j < other._cols; j++) {
        for (int k = 0; k < other._rows; k++) {
          result(i, j) += (*this)(i, k) * other(k, j);
        }
      }
    }
    this->Destroy_matrix();
    this->_rows = result._rows;
    this->_cols = result._cols;
    this->Copy_matrix(result._matrix);
  } else {
    throw std::invalid_argument("Matrix size error");
  }
}

Matrix Matrix::transpose() {
  Matrix res(this->_cols, this->_rows);
  for (int i = 0; i < res._rows; i++)
    for (int j = 0; j < res._cols; j++) res._matrix[j][i] = this->_matrix[i][j];
  return res;
}

Matrix Matrix::calc_complements() {
  Matrix minor(this->_cols, this->_cols);
  double det = determinant();
  if (this->_cols == this->_rows && this->_cols >= 0 && det != 0) {
    double sign = 1;
    for (int i = 0; i < this->_cols; i++) {
      for (int j = 0; j < this->_cols; j++) {
        Matrix buf = get_smaller_matrix(i, j, this->_cols);
        minor._matrix[i][j] = sign * buf.determinant();
        if (fabs(minor._matrix[i][j] == 0)) minor._matrix[i][j] = 0;
        sign = -sign;
        if ((j == this->_cols - 1) && (this->_cols % 2 == 0)) sign = -sign;
      }
    }
  } else {
    throw std::invalid_argument("Incorrect size of matrix");
  }
  return minor;
}

Matrix Matrix::get_smaller_matrix(int i, int j, int m) {
  Matrix res(m - 1, m - 1);
  int ki = 0;
  for (int ri = 0; ri < m - 1; ri++) {
    if (ri == i) ki = 1;
    int kj = 0;
    for (int rj = 0; rj < m - 1; rj++) {
      if (rj == j) kj = 1;
      res._matrix[ri][rj] = this->_matrix[ri + ki][rj + kj];
    }
  }
  return res;
}

double Matrix::determ(int m) {
  double d = 0;
  if (m == 1) d = this->_matrix[0][0];
  if (m == 2) d = this->_matrix[0][0] * this->_matrix[1][1] - (this->_matrix[1][0] * this->_matrix[0][1]);
  if (m == 3)
    d = this->_matrix[0][0] * this->_matrix[1][1] * this->_matrix[2][2] +
        this->_matrix[0][1] * this->_matrix[1][2] * this->_matrix[2][0] +
        this->_matrix[0][2] * this->_matrix[1][0] * this->_matrix[2][1] -
        this->_matrix[0][2] * this->_matrix[1][1] * this->_matrix[2][0] -
        this->_matrix[0][0] * this->_matrix[1][2] * this->_matrix[2][1] -
        this->_matrix[0][1] * this->_matrix[1][0] * this->_matrix[2][2];
  if (m > 3) {
    int sign = 1, n = m - 1;
    for (int i = 0; i < m; i++) {
      Matrix buf = get_smaller_matrix(i, 0, m);
      d += sign * this->_matrix[i][0] * buf.determ(n);
      sign = -sign;
    }
  }
  return d;
}

double Matrix::determinant() {
  double det;
  if (this->_matrix && this->_cols == this->_rows && this->_cols >= 0)
    det = determ(this->_cols);
  else
    det = NAN;
  return det;
}

Matrix Matrix::inverse_matrix() {
  Matrix res;
  double det = determinant();
  if (this->_rows != this->_cols || det == 0) {
    throw std::invalid_argument("Incorrect size of matrix");
  } else if (this->_rows == 1) {
    Matrix buf;
    buf._matrix[0][0] = 1;
    buf.mul_number(1.0 / det);
    res = buf;
  } else {
    Matrix buf_comp;
    buf_comp = calc_complements();
    Matrix buf_transp;
    buf_transp = buf_comp.transpose();
    buf_transp.mul_number(1.0 / det);
    res = buf_transp;
  }
  for (int i = 0; i < res._cols; i++)
    for (int j = 0; j < res._cols; j++)
      if (fabs(res._matrix[i][j] == 0)) res._matrix[i][j] = 0;
  return res;
}

// overloading operators

Matrix Matrix::operator+(const Matrix& other) {
  Matrix res(*this);
  res.sum_matrix(other);
  return res;
}

Matrix Matrix::operator+=(const Matrix& other) {
  this->sum_matrix(other);
  return *this;
}

Matrix Matrix::operator-(const Matrix& other) {
  Matrix res(*this);
  res.sub_matrix(other);
  return res;
}

Matrix Matrix::operator-=(const Matrix& other) {
  this->sub_matrix(other);
  return *this;
}

Matrix Matrix::operator*(const Matrix& A) {
  Matrix result(*this);
  result.mul_matrix(A);
  return result;
}

Matrix operator*(const Matrix& other, double number) {
  Matrix res(other);
  res.mul_number(number);
  return res;
}

Matrix operator*(double number, const Matrix& other) {
  Matrix res(other);
  res.mul_number(number);
  return res;
}

Matrix Matrix::operator*=(const Matrix& other) {
  this->mul_matrix(other);
  return *this;
}

Matrix Matrix::operator*=(double number) {
  this->mul_number(number);
  return *this;
}

bool Matrix::operator==(const Matrix& other) { return this->eq_matrix(other); }

Matrix& Matrix::operator=(const Matrix& other) {
  if (this != &other) {
    this->Destroy_matrix();
    this->_rows = other._rows;
    this->_cols = other._cols;
    this->Copy_matrix(other._matrix);
  }
  return *this;
}

double& Matrix::operator()(int i, int j) const {
  if (i < _rows && j < _cols && i >= 0 && j >= 0) {
    return (_matrix[i][j]);
  } else {
    throw std::out_of_range("Incorrect indexes");
  }
}

// additionals

void Matrix::fill_matrix(const double* a) {
  int t = 0;
  for (int i = 0; i < _rows; i++)
    for (int j = 0; j < _cols; j++) _matrix[i][j] = a[t++];
}

}  // namespace s21
