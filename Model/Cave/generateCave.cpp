#include "generateCave.h"

namespace s21 {

void GenerateCave::createEmptyCave(size_t rows, size_t cols) {
  data.rows = rows;
  data.cols = cols;
  data.life.resize(data.rows);
  for (size_t i = 0; i < data.rows; i++) {
    data.life[i].resize(data.cols);
  }
}

bool GenerateCave::randomizer(int chance) {
  std::random_device random;
  std::default_random_engine engine(random());
  std::uniform_int_distribution<int> res(0, 100);
  return (res(engine)) <= chance;
}

bool GenerateCave::generate(size_t rows, size_t cols, int chance) {
  if (rows < 1 || cols < 1) {
    return false;
  } else {
    cleanData();
    createEmptyCave(rows, cols);
    for (size_t i = 0; i < data.rows; i++) {
      for (size_t j = 0; j < data.cols; j++) {
        data.life[i][j] = randomizer(chance);
      }
    }
    return true;
  }
}
}  // namespace s21
