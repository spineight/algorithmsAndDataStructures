#ifndef OPENCL_UTILS_H
#define OPENCL_UTILS_H

#include <algorithm>
#include <functional>
#include <iostream>
#include <random>
#include <sstream>

#include <CL/cl.h>

namespace cl_util {
static constexpr size_t PER_THREAD = 16;
static constexpr size_t MATRIX_LOC_WORK = 32;
static constexpr size_t PREFSUM_LOC_WORK = 256;

float rand(float min, float max);
size_t up(size_t x);

std::string get_options_matrix();

std::string get_options_prefsum();

std::pair<std::vector<cl_device_id>, cl_uint> find_best_device(const std::vector<cl_platform_id> &platforms, cl_device_type device_type);

template<typename T>
using releaser = cl_int (*)(T);

template<typename T, releaser<T> Release>
struct cl_raii {
  T obj;

  explicit cl_raii(T other) {
    *this = other;
  }

  cl_raii(cl_raii const &) = delete;
  cl_raii &operator=(cl_raii const &) = delete;

  cl_raii &operator=(T other) {
    obj = other;
    return *this;
  }

  ~cl_raii() {
    Release(obj);
  }
};
} // namespace cl_util

// needs res to be defined and set to an error
#define ERROR_CHECK(message)                                                                                                                                   \
  if (res != CL_SUCCESS) {                                                                                                                                     \
    std::cerr << "Error happened: Can't " << message << ". Error code: " << res << std::endl;                                                                  \
    return 1;                                                                                                                                                  \
  }

// easy benchmarks
#define BENCH_START                                                                                                                                            \
  std::chrono::time_point<std::chrono::high_resolution_clock> start;                                                                                           \
  std::chrono::time_point<std::chrono::high_resolution_clock> end;                                                                                             \
  start = std::chrono::high_resolution_clock::now();

#define BENCH_END(mes)                                                                                                                                         \
  end = std::chrono::high_resolution_clock::now();                                                                                                             \
  size_t time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();                                                                    \
  std::cout << "Time spent in " << mes << " computation: " << time << " ms" << std::endl;

#endif
