#include <fstream>
#include <iomanip>
#include <iostream>

#include "common/utils.h"

static constexpr size_t ARRAY_SIZE_APPROX = 10000000;
static constexpr size_t ARRAY_SIZE = cl_util::PREFSUM_LOC_WORK * (1 + ARRAY_SIZE_APPROX / cl_util::PREFSUM_LOC_WORK);

static constexpr const char *KERNEL_FILE_NAME = "prefsum.cl";

bool check(std::vector<float> const &a, std::vector<float> const &b) {
  float sum = 0;
  for (size_t i = 0; i < a.size(); i++) {
    sum += a[i];
    float diff = std::fabs(b[i] - sum);
    float error_percent = diff / b[i];
    if (diff > 1e-4 && error_percent > 0.03) { // three percents error on difference big enough - works good
      std::cerr << "Expected: " << sum << " Actual: " << b[i] << " Difference: " << diff << " Error percent: " << error_percent << std::endl;
      return false;
    }
    sum = b[i]; // for not
  }
  return true;
}

int main() {
  std::vector<float> array(ARRAY_SIZE);
  std::vector<float> result(ARRAY_SIZE);
  for (float &f : array) {
    f = cl_util::rand(-1e5, 1e5);
  }

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

  std::string ops = cl_util::get_options_prefsum();
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

  cl_int res1 = 0;
  cl_util::cl_raii<cl_kernel, clReleaseKernel> kernel(clCreateKernel(program.obj, "prefix_sum", &res));

  ERROR_CHECK("create kernel tiles_sum")
  res = res1;
  ERROR_CHECK("create kernel calc_sum")

  auto casted_size = static_cast<cl_uint>(ARRAY_SIZE * sizeof(float));

  cl_util::cl_raii<cl_mem, clReleaseMemObject> array_buf(clCreateBuffer(ctx.obj, CL_MEM_READ_ONLY, casted_size, nullptr, &res));
  ERROR_CHECK("create array buffer")
  cl_util::cl_raii<cl_mem, clReleaseMemObject> sums_buf(clCreateBuffer(ctx.obj, CL_MEM_READ_WRITE, casted_size, nullptr, &res));
  ERROR_CHECK("create sum array buffer")

  res = clEnqueueWriteBuffer(cmd_q.obj, array_buf.obj, CL_TRUE, 0, casted_size, array.data(), 0, nullptr, nullptr);
  ERROR_CHECK("enqueue write buffer")

  res = clSetKernelArg(kernel.obj, 0, sizeof(cl_mem), &array_buf);
  res |= clSetKernelArg(kernel.obj, 1, sizeof(cl_mem), &sums_buf);
  res |= clSetKernelArg(kernel.obj, 2, sizeof(cl_uint), &casted_size);
  ERROR_CHECK("set 1st kernel args")

  size_t global_work[1] = {cl_util::PREFSUM_LOC_WORK};
  size_t local_work[1] = {cl_util::PREFSUM_LOC_WORK};

  cl_ulong time = 0;
  cl_event event = nullptr;
  res = clEnqueueNDRangeKernel(cmd_q.obj, kernel.obj, 1, nullptr, global_work, local_work, 0, nullptr, &event);

  clWaitForEvents(1, &event);
  clFinish(cmd_q.obj);

  cl_ulong time_start = 0;
  cl_ulong time_end = 0;
  clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_START, sizeof(time_start), &time_start, nullptr);
  clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_END, sizeof(time_end), &time_end, nullptr);
  time += time_end - time_start;
  std::cout << "Time spent in opencl computation: " << std::fixed << std::setprecision(6) << time / 1e6 << " ms" << std::endl;

  res = clEnqueueReadBuffer(cmd_q.obj, sums_buf.obj, CL_TRUE, 0, casted_size, result.data(), 0, nullptr, nullptr);

  if (!check(array, result)) {
    std::cerr << "Checking result failed!" << std::endl;
    return 1;
  }
  std::cout << "Checking result succeed!" << std::endl;
  std::cout << "GFLOPS: " << std::fixed << std::setprecision(10) << log2f(ARRAY_SIZE) * ARRAY_SIZE / time << std::endl;
}
