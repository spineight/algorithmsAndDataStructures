#pragma once
namespace lec7 {
  struct Ray {
    /**
     *
        Луч задается направляющим вектором, с координатами (dx,dy)
        И начальной точкой
     */
     double dx,dy,px,py;
    Ray(double dx, double dy, double px, double py) :dx(dx), dy(dy), px(px), py(py) {

    }
    /**
     *
        Проверяем пренадлежность точку лучу
     */
    bool has(double x, double y) {
      // (dx,dy) x (x-px,y-py) == 0
      const double Epsilon = 1e-9;
      bool isOnLine =  (dx * (y-py) -(x-px) * dy) <= Epsilon;
      bool isInOneDirection = dx*(x-px) + dy*(y-py) >= -Epsilon;
      return isOnLine && isInOneDirection;
    }
  };
}