#include <fstream>
#include <iomanip>
#include <iostream>
#include <streambuf>

#include "common/matrix.h"
#include "common/utils.h"

// random section
static constexpr float RMIN = -100;
static constexpr float RMAX = 100;

static constexpr size_t DEBUG_DIV = 1;
static constexpr size_t A = 2048 / DEBUG_DIV;
static constexpr size_t B = 512 / DEBUG_DIV;
static constexpr size_t C = 1024 / DEBUG_DIV;

static constexpr size_t WORK_DIM = 2;

static constexpr const char *KERNEL_FILE_NAME = "mat_mp.cl";

using cl_buffer = cl_util::cl_raii<cl_mem, clReleaseMemObject>;

int main() {
  // generating matrices
  cl_util::matrix first(A, B);
  cl_util::matrix second(B, C);
  cl_util::matrix result(A, C);

  first.fill_rand(RMIN, RMAX);
  second.fill_rand(RMIN, RMAX);

  //    first.print();
  //    second.print();

  cl_util::matrix second_t = cl_util::transpose(second);

  // go-go openCL
  cl_int res = 0;
  cl_uint pl_amount = 0;

  res = clGetPlatformIDs(0, nullptr, &pl_amount);
  ERROR_CHECK("get platforms amount")
  std::cout << "Found " << pl_amount << " platforms" << std::endl;

  std::vector<cl_platform_id> platforms(pl_amount);
  res = clGetPlatformIDs(pl_amount, platforms.data(), nullptr);
  ERROR_CHECK("get platforms ids")

  // choose devices
  auto device = cl_util::find_best_device(platforms, CL_DEVICE_TYPE_GPU);
  if (device.first.empty()) {
    device = cl_util::find_best_device(platforms, CL_DEVICE_TYPE_CPU);
  }
  if (device.first.empty()) {
    res = CL_DEVICE_NOT_FOUND;
    ERROR_CHECK("get devices")
  }

  // choose concrete device
  size_t DEV = device.second;
  auto devices = device.first;

  size_t device_info_size;
  res = clGetDeviceInfo(devices[DEV], CL_DEVICE_NAME, 0, nullptr, &device_info_size);
  if (res == CL_SUCCESS) {
    std::string name;
    name.resize(device_info_size);
    res = clGetDeviceInfo(devices[DEV], CL_DEVICE_NAME, device_info_size, const_cast<char *>(name.data()), nullptr);
    if (res == CL_SUCCESS) {
      std::cout << "Device chosen, it's name: " << name << std::endl;
    }
  } else {
    std::cerr << "Can't get device name";
  }

  // context now
  cl_util::cl_raii<cl_context, clReleaseContext> ctx(clCreateContext(nullptr, devices.size(), devices.data(), nullptr, nullptr, &res));
  ERROR_CHECK("create context");
  if (ctx.obj == nullptr) {
    std::cerr << "Can't create context is null" << std::endl;
    return 1;
  }

  cl_util::cl_raii<cl_command_queue, clReleaseCommandQueue> cmd_q(clCreateCommandQueue(ctx.obj, devices[DEV], CL_QUEUE_PROFILING_ENABLE, &res));
  ERROR_CHECK("create command queue")
  if (cmd_q.obj == nullptr) {
    std::cerr << "Cmd queue is null" << std::endl;
    return 1;
  }

  // now kernel
  std::fstream kfile(KERNEL_FILE_NAME);
  std::string code((std::istreambuf_iterator<char>(kfile)), std::istreambuf_iterator<char>());
  size_t code_sz = code.size();
  const char *code_c = code.c_str();

  cl_util::cl_raii<cl_program, clReleaseProgram> program(clCreateProgramWithSource(ctx.obj, sizeof(char), &code_c, &code_sz, &res));
  ERROR_CHECK("create program")
  kfile.close();

  std::string ops = cl_util::get_options_matrix();
  res = clBuildProgram(program.obj, devices.size(), devices.data(), ops.c_str(), nullptr, nullptr);

  if (res != CL_SUCCESS) {
    std::cerr << "Can't build program. Error code: " << res << std::endl;
    size_t log_size = 0;
    clGetProgramBuildInfo(program.obj, devices[DEV], CL_PROGRAM_BUILD_LOG, 0, nullptr, &log_size);
    std::string log;
    log.resize(log_size);
    clGetProgramBuildInfo(program.obj, devices[DEV], CL_PROGRAM_BUILD_LOG, log_size, const_cast<char *>(log.data()), nullptr);
    std::cerr << log;
  }

  std::cout << "Program is built" << std::endl;

  cl_util::cl_raii<cl_kernel, clReleaseKernel> kernel(clCreateKernel(program.obj, "mat_mp", &res));
  ERROR_CHECK("create kernel")

  // std::cout << first.byte_size() << first.data;
  cl_buffer first_buf(clCreateBuffer(ctx.obj, CL_MEM_READ_ONLY, first.byte_size(), nullptr, &res));
  ERROR_CHECK("create first cl mem")
  cl_buffer second_buf(clCreateBuffer(ctx.obj, CL_MEM_READ_ONLY, second_t.byte_size(), nullptr, &res));
  ERROR_CHECK("create second cl mem")
  cl_buffer result_buf(clCreateBuffer(ctx.obj, CL_MEM_READ_WRITE, result.byte_size(), nullptr, &res));
  ERROR_CHECK("create result cl mem")

  res = clEnqueueWriteBuffer(cmd_q.obj, first_buf.obj, CL_TRUE, 0, first.byte_size(), first.data.data(), 0, nullptr, nullptr);
  ERROR_CHECK("enqueue first buffer")
  res = clEnqueueWriteBuffer(cmd_q.obj, second_buf.obj, CL_TRUE, 0, second_t.byte_size(), second_t.data.data(), 0, nullptr, nullptr);
  ERROR_CHECK("enqueue second buffer")

  auto casted_first_rows = static_cast<cl_uint>(first.rows);
  auto casted_first_cols = static_cast<cl_uint>(first.cols);
  auto casted_second_cols = static_cast<cl_uint>(second.cols);

  res = clSetKernelArg(kernel.obj, 0, sizeof(cl_mem), &first_buf);
  res |= clSetKernelArg(kernel.obj, 1, sizeof(cl_mem), &second_buf);
  res |= clSetKernelArg(kernel.obj, 2, sizeof(cl_mem), &result_buf);
  res |= clSetKernelArg(kernel.obj, 3, sizeof(cl_uint), &casted_first_rows);
  res |= clSetKernelArg(kernel.obj, 4, sizeof(cl_uint), &casted_first_cols);
  res |= clSetKernelArg(kernel.obj, 5, sizeof(cl_uint), &casted_second_cols);
  ERROR_CHECK("set kernel.obj args")

  size_t global_work[WORK_DIM] = {first.rows, second.cols / cl_util::PER_THREAD};
  size_t local_work[WORK_DIM] = {cl_util::MATRIX_LOC_WORK, cl_util::MATRIX_LOC_WORK / cl_util::PER_THREAD};

  cl_event event = nullptr;
  res = clEnqueueNDRangeKernel(cmd_q.obj, kernel.obj, WORK_DIM, nullptr, global_work, local_work, 0, nullptr, &event);
  ERROR_CHECK("enqueue kernel")

  std::cout << "Waiting for ending of computation" << std::endl;

  clWaitForEvents(1, &event);
  clFinish(cmd_q.obj);

  cl_ulong time_start = 0;
  cl_ulong time_end = 0;
  clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_START, sizeof(time_start), &time_start, nullptr);
  clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_END, sizeof(time_end), &time_end, nullptr);
  double time = time_end - time_start;
  std::cout << "Time spent in opencl computation: " << std::fixed << std::setprecision(6) << time / 1e6 << " ms" << std::endl;

  res = clEnqueueReadBuffer(cmd_q.obj, result_buf.obj, CL_TRUE, 0, result.byte_size(), result.data.data(), 0, nullptr, nullptr);
  ERROR_CHECK("read result")

  auto check_res = first * second;
  // 1e-3 is magic, lower the random range - lower is the error epsilon,
  // but the differ dramatically if range grows
  if (!cl_util::compare(check_res, result, (RMAX - RMIN) * 1e-3)) {
    std::cerr << "Checking result failed!" << std::endl;
    return 1;
  }
  std::cout << "Checking result passed" << std::endl;
  std::cout << "Resulting GFLOPS: " << 2.0 * first.rows * first.cols * second.cols / time << std::endl;
}
