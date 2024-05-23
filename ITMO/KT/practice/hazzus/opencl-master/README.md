# opencl
OpenCL course homeworks

## Lab 1: Matrix Multiplication
Directory: matrix_mul_ocl
Device code: mat_mp.cl
Host code: main.cpp

Input for device code is 2 randomly generated matrices, result buffer and all sizes (N x M x K).  
Device code uses local group memory, splites matrix on tiles, transposes input matrix.  
Tiles have fixed size `LOC_WORK^2`, all of N, M, K must devide on `LOC_WORK` (LOC_WORK is compile defined in `common/utils.h`).  
Devision condition is automatically fixed in code.
GFLOPS is ~10 times lower than Intel UHD 620 specification. 

**For OpenMP version look at**: matrix_mul_omp

## Lab 2: Array Prefix Sums
Directory: prefsum_ocl
Device code: prefsum.cl
Host code: main.cpp

Counts prefix sum of float array. Uses tree-building algorithm. (splits array on power of 2 chunks and aggregate them)  
Whole array is splitted on local groups of fixed size.
Actually is straightforward, stupid implementation.
