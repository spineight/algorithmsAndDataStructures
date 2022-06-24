#pragma once
#include <cmath>
#include <cfenv>
#include <cstring>


namespace lec7 {

  /**
   * Вектор на плоскости
   * Заданный на прямоугольной Декартовой системе координат
   * выходящий из начала (0,0) -> (coords.first, coords.second)
   */
  struct Vector2D {
    Vector2D(const std::pair<double,double>& coords) : coords(coords) {}

    /**
     * cos(alpha) = x / len -> x = cos(alpha) * len
       sin(alpha) = y / len -> y = sin(alpha) * len
     * @param alpha
     * @param len
     */
    Vector2D(double alpha, double len) : coords(cos(alpha)*len, sin(alpha)*len) {}

    /**
     * @attention Мы можем получить feclearexcept (оно не преостанавливает выполнение программы)
     * но мы можем сами протестировать получили ли мы его
     * Оно может возникнуть при работе с double, например так как sqrt(2) - не представим в действительных числах:
     * мы получим FE_INEXACT
     *
     * Пример такой ситуации:
     *   Vector2D v(std::make_pair(1,1));
         cout << v.length() << '\n';
     */
    std::pair<double,double> coords;
    double length() const {

      std::feclearexcept(FE_ALL_EXCEPT);
      double res = std::hypot(coords.first,coords.second);
      if (errno == ERANGE)
        std::cout << "    errno = ERANGE " << std::strerror(errno) << '\n';
      if(std::fetestexcept(FE_INEXACT)) {
        std::cout << "inexact result reported\n";
      }
      else if(std::fetestexcept(FE_DIVBYZERO)){
        std::cout << "division by zero reported\n";
      }
      else if(std::fetestexcept(FE_INVALID)){
        std::cout << "invalid result reported\n";
      }
      else if(std::fetestexcept(FE_OVERFLOW)){
        std::cout << "FE_OVERFLOW reported\n";
      }
      else if(std::fetestexcept(FE_UNDERFLOW)){
        std::cout << "FE_UNDERFLOW reported\n";
      }
      return res;
    }

    /**
     * Пусть есть два вектора, тогда их можно сложить:
       один из них отложить от конца другого и после этого из начала первого провести вектор в конец второго.

       Это можно так понять: вектор - можно считать, что мы совершаем перемещение,
       тогда мы совершаем сначала такое перемещение (r1), после этого перемещение (r2),
       в сумме мы совершили перемещение как раз равное сумме этих векторов
     */
    Vector2D operator+(const Vector2D& other) {
      return Vector2D(std::make_pair(coords.first+other.coords.first, coords.second+other.coords.second));
    }
    Vector2D operator*(double k) const {
      return Vector2D(std::make_pair(coords.first*k,coords.second*k));
    }
    Vector2D operator/(double k) const {
      return *this * (1/k);
    }
    /**
     *  A (x/sqrt(x^2+y^2),y/sqrt(x^2+y^2)
     *  len(A) = sqrt(x^2/(x^2+y^2) + y^2/(x^2+y^2)) = sqrt((x^2+y^2)/(x^2+y^2)) == 1
     */
    void normalize() {
      auto& [x,y] = coords;
      const double len = length();
      if(len != 0) {
        x /= len;
        y /= len;
      }
    }
    bool isNormalized() const {
      return length() == 1;
    }
    /**
     *  cos (alpha) = x / |r|
        sin (alpha) = y / |r|

        когда |r| - длина вектора == 1:
        cos(alpha) = x
        sin(alpha) = y
     *
     * @return значение угла в радианах между осью OX и вектором
     * @attention Одного arccos недостаточно чтобы найти угол, нужно еще знать x и y, чтобы определить квадрант
     * arcos область определения -1 <= x <= 1, область значений 0 ≤ y ≤ π
     */
    double angle() const {
      auto [x,y] = coords;
      //! This assertion doesn't hold : !!!
      auto result = atan2(y,x);
      return result;
    }
    /**
     *  A.angle(B)
     *  Угол в радианах на который нужно повернуть вектор A, чтобы получить вектор B
     *  Положительное направление - против часовой стрелки (CCW)
     * @param other
     * @return
     */
    double angle(const Vector2D& other) const {
//      return other.angle() - angle(); - TODO вопрос можно ли так вычислять
      auto [x1,y1] = coords;
      auto [x2,y2] = other.coords;
      // Отложим вектор v длиной |r1|*|r2|
      // под углом alpha, где alpha - угол между векторами r1,r2
      // тогда v имеет следующие координаты:
      const double v_x = x1*x2+y1*y2;
      const double v_y = x1*y2 - y1*x2;
      return atan2(v_y,v_x);
    }

    /**
     * Скалярное произведение
     * r1*r2 = |r1| |r2| cos(alpha)
     * alpha - угол между векторами
     * Формула в координатах
        r1(x1,y1), r2(x2,y2)
        r1*r2 = x1x2 + y1y2
     * @param other
     * @return
     * Чем интересно скалярное произведение:
        Можем узнать угол alpha между векторами больше/меньше/равен по модулю чем Pi/2
        Те вектора которые находятся в одной полуплоскости - скалярное произведение > 0
     */
    double dot(const Vector2D& other) const {
      auto [x1,y1] = coords;
      auto [x2,y2] = other.coords;
      return x1*x2 + y1*y2;
    }

    /**
     *
     * @param other
     * @return -1 opposite direction, 0 - orthogonal, 1 - same direction
     */
    int direction(const Vector2D& other) const {
      const auto dot_product = dot(other);
      double EPSILON = 1e-15;
      if(dot_product < -EPSILON) return -1;
      if(dot_product > EPSILON) return 1;
      return 0;
    }
    /**
     * Векторное произведение
     * r1 X r2 = |r1| |r2| sin(alpha)
     * alpha - угол между векторами
     * Формула в координатах
     * r1 x r2 = x1y2 - x2y1
     * @param other
     * @return
     */
    double cross(const Vector2D& other) const {
      auto [x1,y1] = coords;
      auto [x2,y2] = other.coords;
      return x1*y2 - x2*y1;
    }
    /**
     * С помошью вектороного произведения Мы можем для векторов узнавать
     * слева(CCW)/ справа(CW) от прямой на которой лежит первый вектор лежит конец второго
        (так как знак этого произведения определяется знаком sin от угла между векторов)
     * @param other
     * @return -1 -CW, 1 - CCW, 0 - on the same line
     */
    int isCCW(const Vector2D& other) const{
      return cross(other) > 0 ? 1 : cross(other) < 0 ? -1 : 0;
    }
    bool operator==(const Vector2D& other) const {
      double epsilon = 0.000000001;
      return abs(coords.first - other.coords.first) < epsilon
      && abs(coords.second - other.coords.second) < epsilon;
    }
  };
}