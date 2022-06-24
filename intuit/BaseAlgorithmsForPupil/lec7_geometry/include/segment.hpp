#pragma once
#include <include/ray.hpp>
namespace lec7 {
  struct Segment {
    double x0,y0,x1,y1;
    /**
     *
        Задаем двумя точками
     */
    Segment(double x0,double y0, double x1, double y1) : x0(x0), y0(y0), x1(x1), y1(y1) {

    }
    bool hasPointMethod1(double x, double y) {
      Ray r0(x1-x0, y1-y0, x0,y0);
      Ray r1(x0-x1, y0-y1, x1,y1);
      return r0.has(x,y) && r1.has(x,y);
    }

    /**
     *
         Точка лежит на отрезке тогда и только тогда:
         когда она лежит на прямой + лежит внутри ограничивающего прямоугольника этого отрезка
     */
    bool hasPointMethod2(double x, double y) {
      // (x1-x0,y1-y0) x (x-x0,y-y0)
      const double Epsilon = 1e-9;
      bool isOnLine = (x1-x0)*(y-y0) - (x-x0)*(y1-y0) <= Epsilon;
      bool isWithinBoundingRect =
              std::min(x1,x0) <= x && x <= std::max(x1,x0)
              && std::min(y1,y0) <= y && y <= std::max(y1,y0);
      return isOnLine && isWithinBoundingRect;
    }
  };
}