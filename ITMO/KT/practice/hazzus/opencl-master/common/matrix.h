#ifndef OPENCL_MATRIX_H
#define OPENCL_MATRIX_H

#include "utils.h"
#include <chrono>

// for benching stupid
#define STUPID_MUL_BENCH

namespace cl_util {

struct matrix {
  matrix(size_t rows, size_t cols);

  void fill_rand(float rand_min, float rand_max);

  size_t byte_size() const;

  void print() const;

  void clear();

  ~matrix();

  friend matrix operator*(matrix const &a, matrix const &b);

  size_t rows, cols;
  std::vector<float> data;
};

matrix operator*(matrix const &a, matrix const &b);

matrix transpose(matrix const &orig);

bool compare(matrix const &a, matrix const &b, float eps);

} // namespace cl_util

#endif // OPENCL_MATRIX_H
