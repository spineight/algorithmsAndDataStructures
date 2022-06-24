#pragma once
#include <cmath>
namespace lec7 {
  struct Line {
    double a,b,c;
    /** ax+by=c
     * Зная a,b,c можно посчитать:
    *   1. Координаты направляющего вектора AB(x2-x1,y2-y1) - AB(-b,a)
     *      a = y2-y1, b = x1-x2
     *  2. координаты точки в основании перпендикуляра от прямой до начала координат
     *   P(ac/(a^2+b^2), bc/(a^2+b2))
     */
    Line(double a, double b, double c) : a(a), b(b), c(c){}

    /**
     *
     * @param dx,dy - координаты направляющего вектора
     * @param px,py - координаты точки на прямой
     */
    Line(double dx,double dy, double px,double py) {
      a = dy;
      b = -dx;
      c = a * px + b * py;
    }
    double distToOrigin() {
      return c / sqrt(a*a+b*b);
    }
    /**
     *
        Test if the point with (x,y) is on the line
     */
    bool has(double x, double y) {
      const double Epsilon = 1e-9;
      return abs(a*x+b*y-c) <= Epsilon;
    }

    /**
     *
     * @return точку в основании перпендикуляра из начала координат на прямую
     */
    std::pair<double,double> getSpecialPoint() {
      return {a*c/(a*a+b*b), b*c/(a*a+b*b)};
    }
    /**
     *
        (x-x1) * a + (y-y1) * b
        Направляющий вектор должен быть нормирован (a^2+b^2==1)
     */
    double distToPoint(double x, double y) {
      double vectorLength = std::hypot(-b,a);
      auto [x1,y1] = getSpecialPoint();
      double dist = (x-x1) * a / vectorLength + (y-y1) * b / vectorLength;
      return dist;
    }

    /**
     *
        Если точка пересечения существует и единственная, возвращает ее

        a1x + b1y = c1
        a2x + b2y = c2
     */
    std::optional<std::pair<double,double>> intersects(const Line& other) const {
      double a1 = a;
      double b1 = b;
      double c1 = c;
      double a2 = other.a;
      double b2 = other.b;
      double c2 = other.c;
      double determinant = a1 * b2 - a2 * b1;
      if(determinant == 0) return {};
      double x = (c1*b2 - b1*c2) / determinant;
      double y = (a1*c2 - a2*c1) / determinant;
      return {{x,y}};
    }
  };
}