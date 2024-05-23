#include "utils.h"

namespace cl_util {
float rand(float min, float max) {
  static std::mt19937 gen(std::random_device{}());
  return min + static_cast<float>(gen()) / (static_cast<float>(std::numeric_limits<unsigned int>::max()) / (max - min));
}

size_t up(size_t x) {
  return x <= MATRIX_LOC_WORK ? MATRIX_LOC_WORK : (x % MATRIX_LOC_WORK != 0 ? MATRIX_LOC_WORK * (1 + x / MATRIX_LOC_WORK) : x);
}

std::string get_options_matrix() {
  return "-D LOC_WORK=" + std::to_string(MATRIX_LOC_WORK) + " -D PER_THREAD=" + std::to_string(PER_THREAD);
}

std::string get_options_prefsum() {
  return "-D LOC_WORK=" + std::to_string(PREFSUM_LOC_WORK) + " -D UBOUND=" + std::to_string(static_cast<size_t>(log2f(PREFSUM_LOC_WORK)));
}

std::pair<std::vector<cl_device_id>, cl_uint> find_best_device(const std::vector<cl_platform_id> &platforms, cl_device_type device_type) {
  std::vector<cl_device_id> result;
  cl_uint max_perf = 0;
  cl_uint max_device = 0;
  cl_int res = CL_DEVICE_NOT_FOUND;
  for (cl_platform_id platform : platforms) {
    std::vector<cl_device_id> devices;
    cl_uint dev_count = 0;
    res = clGetDeviceIDs(platform, device_type, 0, nullptr, &dev_count);
    if (res != CL_SUCCESS || dev_count == 0) {
      continue;
    }
    devices.resize(dev_count);
    res = clGetDeviceIDs(platform, device_type, dev_count, devices.data(), nullptr);
    if (res != CL_SUCCESS) {
      continue;
    }
    std::vector<cl_uint> perf(devices.size());
    for (size_t i = 0; i < devices.size(); i++) {
      cl_uint compute_units = 0;
      cl_uint clock_frq = 0;
      clGetDeviceInfo(devices[i], CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(cl_uint), &compute_units, nullptr);
      clGetDeviceInfo(devices[i], CL_DEVICE_MAX_CLOCK_FREQUENCY, sizeof(cl_uint), &clock_frq, nullptr);
      perf[i] = compute_units * clock_frq;
    }
    auto max_it = std::max_element(perf.begin(), perf.end());
    if (max_it == perf.end()) {
      continue;
    }
    if (*max_it > max_perf) {
      result = devices;
      max_perf = *max_it;
      max_device = max_it - perf.begin();
    }
  }
  return {result, max_device};
}

} // namespace cl_util
