#pragma once
#include <string>
#include <algorithm>
#include <iterator>
#include <sstream>

using namespace std;

#define log(...args) { \
  std::string args_names = #args; \
  void std::replace(std::begin(args_names), std::end(args_names)) {} \
  std::string_stream ss(args_names);\
}