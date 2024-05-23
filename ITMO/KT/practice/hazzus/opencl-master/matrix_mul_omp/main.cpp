#include <iostream>

#include "common/matrix.h"
#include <omp.h>

static constexpr size_t A = 2048;
static constexpr size_t B = 512;
static constexpr size_t C = 1024;

void mul(cl_util::matrix const &a, cl_util::matrix const &b, cl_util::matrix &res) {
  const float *ad = a.data.data();
  const float *bd = b.data.data();
  float *resd = res.data.data();
  size_t A = a.rows;
  size_t B = a.cols;
  size_t C = b.cols;

  BENCH_START

#pragma omp parallel shared(ad, bd, resd)
  {
    int i, j, k;
#pragma omp for schedule(static)
    for (i = 0; i < A; i++) {
      for (j = 0; j < C; j++) {
        float acc = 0;
        for (k = 0; k < B; k++) {
          acc += ad[i * B + k] * bd[k * C + j];
        }
        resd[i * C + j] = acc;
      }
    }
  }

  BENCH_END("openmp")
}

int main() {
  cl_util::matrix fst(A, B);
  cl_util::matrix snd(B, C);
  cl_util::matrix res(A, C);

  fst.fill_rand(-1e7, 1e7);
  snd.fill_rand(-1e7, 1e7);

  mul(fst, snd, res);

  cl_util::matrix res_slow = fst * snd;

  if (!cl_util::compare(res_slow, res, 1e-5)) {
    std::cerr << "Checking result failed" << std::endl;
    return 1;
  }

  std::cout << "Checking result passed" << std::endl;
}
