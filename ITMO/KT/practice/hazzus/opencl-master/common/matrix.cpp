#include "matrix.h"

#include <cmath>
#include <iomanip>

namespace cl_util {

matrix::matrix(size_t rows, size_t cols)
  : rows(up(rows))
  , cols(up(cols))
  , data(this->rows * this->cols) {
  // data = static_cast<float *>(malloc(this->cols * this->rows * sizeof(float)));
  // data = new float[this->cols * this->rows];
}

void matrix::fill_rand(float rand_min, float rand_max) {
  for (std::size_t i = 0; i < rows * cols; i++) {
    data[i] = rand(rand_min, rand_max);
  }
}

size_t matrix::byte_size() const {
  return rows * cols * sizeof(float);
}

matrix::~matrix() {
  // if (data != nullptr) {
  // free(data);
  // delete data;
  //}
}

void matrix::print() const {
  std::cout << "=====================================================" << std::endl;
  for (size_t i = 0; i < rows; i++) {
    for (size_t j = 0; j < cols; j++) {
      std::cout << data[i * cols + j] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << "=====================================================" << std::endl;
}

void matrix::clear() {
  for (size_t i = 0; i < rows * cols; i++) {
    data[i] = 0.0;
  }
}

matrix operator*(const matrix &a, const matrix &b) {
  BENCH_START

  matrix result(a.rows, b.cols);
  for (size_t i = 0; i < a.rows; i++) {
    for (size_t j = 0; j < b.cols; j++) {
      float acc = 0;
      for (size_t k = 0; k < a.cols; k++) {
        acc += a.data[i * a.cols + k] * b.data[k * b.cols + j];
      }
      result.data[i * b.cols + j] = acc;
    }
  }

  BENCH_END("stupid cpu")
  return result;
}

matrix transpose(matrix const &orig) {
  matrix res(orig.cols, orig.rows);
  for (size_t i = 0; i < res.cols; i++) {
    for (size_t j = 0; j < res.rows; j++) {
      res.data[j * orig.rows + i] = orig.data[i * orig.cols + j];
    }
  }
  return res;
}

bool compare(const matrix &a, const matrix &b, float eps) {
  if (a.cols != b.cols || a.rows != b.rows) {
    std::cerr << "Rows or cols mismatch" << std::endl;
    return false;
  }
  for (size_t i = 0; i < a.rows; i++) {
    for (size_t j = 0; j < b.cols; j++) {
      float diff = std::fabs(a.data[i * b.cols + j] - b.data[i * b.cols + j]);
      if (diff > eps) {
        std::cerr << std::fixed << std::setprecision(10) << "Failed compare. Actual: " << b.data[i * b.cols + j] << " Expected: " << a.data[i * b.cols + j]
                  << " Difference: " << diff << std::endl;
        std::cerr << " Index: " << i << " " << j << std::endl;
        return false;
      }
    }
  }
  return true;
}

} // namespace cl_util
