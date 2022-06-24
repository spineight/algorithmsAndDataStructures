#pragma once
namespace lec8 {
  bool equalDouble(double first, double second, double Epsilon) {
    return abs(first-second) <= Epsilon;
  }
  bool lessDouble(double first, double second, double Epsilon) {
    return first < (second - Epsilon);
  }
  bool lessEqualDouble(double first, double second, double Epsilon) {
    return first <= (second + Epsilon);
  }
  bool greaterDouble(double first, double second, double Epsilon) {
    return first > (second + Epsilon);
  }
  bool greaterEqualDouble(double first, double second, double Epsilon) {
    return first > (second - Epsilon);
  }
}