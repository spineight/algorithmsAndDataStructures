#include <gtest/gtest.h>

#ifdef PRACTICE
#include <practice/euler_cycle.hpp>
using namespace lec6::practice;
#else
#include <include/vector2D.hpp>
using namespace lec7;
#endif

#include <bits/stdc++.h>
using namespace std;


//! https://www.wolframalpha.com

TEST(vector, testLength) {
  for(double alpha = 0; alpha <= 2 * M_PI; alpha += M_PI / 10.) {
    for(double length = 0; length <= 20; ++length) {
      EXPECT_DOUBLE_EQ(length, Vector2D(alpha,length).length());
    }
  }
}

TEST(vector, testConstructors) {
  for(double alpha = 0; alpha <= 2 * M_PI; alpha += M_PI / 10.) {
    for(double length = 0; length <= 20; ++length) {
      Vector2D v0(make_pair(cos(alpha)*length, sin(alpha)*length));
      Vector2D v1(alpha,length);
      EXPECT_EQ(v0, v1);
    }
  }
}

TEST(vector, testNotmalize) {
  for(double alpha = 0; alpha <= 2 * M_PI; alpha += M_PI / 10.) {
    for(double length = 0; length <= 20; ++length) {
      Vector2D v(std::make_pair(cos(alpha)*length, sin(alpha)*length));
      if(v.length() >0 ) {
        v.normalize();
        auto len = v.length();
        if(len == 100000) cout << ";";
        EXPECT_DOUBLE_EQ(v.length(), 1);
      }
    }
  }

}

double normalizeAngle(double phi) {
  while(phi < 0) phi += M_PI * 2;
  return phi;
}

TEST(vector, testAngle) {
  for(double alpha = 0; alpha <= 2 * M_PI; alpha += M_PI / 10.) {
    for(double length = 1; length <= 20; ++length) {
      cout << alpha << "," << length << '\n';
      EXPECT_FLOAT_EQ((float)normalizeAngle(alpha), (float)normalizeAngle(Vector2D(alpha,length).angle()));
    }
  }
}


TEST(vector, testAngleBetweenVectors) {
  for(double alpha0 = 0; alpha0 <= 2 * M_PI; alpha0 += M_PI / 10.) {
    for (double alpha1 = 0; alpha1 <= 2 * M_PI; alpha1 += M_PI / 10.) {
      for (double length = 1; length <= 20; ++length) {
        Vector2D v0(alpha0,length), v1(alpha1,length);
        double EPSILON = 1e-15;
        EXPECT_TRUE(normalizeAngle(v0.angle(v1)) - normalizeAngle(alpha1-alpha0) < EPSILON);
      }
    }
  }
}

//! @attention При действии с floating points numbers - возможны погрешности, поэтому мы вводим EPSILON
TEST(DISABLED_vector, testDirection) {
  for(double alpha0 = 0; alpha0 <= 2 * M_PI; alpha0 += M_PI / 10.) {
    for (double alpha1 = 0; alpha1 <= 2 * M_PI; alpha1 += M_PI / 10.) {
      for (double length = 0; length <= 20; ++length) {
        Vector2D v0(alpha0,length), v1(alpha1,length);
      }
    }
  }
}

TEST(vector, testCrossProduct) {
  for(double alpha0 = 0; alpha0 <= 2 * M_PI; alpha0 += M_PI / 10.) {
    for (double alpha1 = 0; alpha1 <= 2 * M_PI; alpha1 += M_PI / 10.) {
      for (double length = 0; length <= 20; ++length) {
        Vector2D v0(alpha0,length), v1(alpha1,length);
        auto [x1,y1] = v0.coords;
        auto [x2,y2] = v1.coords;
        EXPECT_DOUBLE_EQ(v0.cross(v1), x1*y2 - x2*y1);
      }
    }
  }
}

TEST(vector, testDotProduct) {
  for(double alpha0 = 0; alpha0 <= 2 * M_PI; alpha0 += M_PI / 10.) {
    for (double alpha1 = 0; alpha1 <= 2 * M_PI; alpha1 += M_PI / 10.) {
      for (double length = 0; length <= 20; ++length) {
        Vector2D v0(alpha0,length), v1(alpha1,length);
        auto [x1,y1] = v0.coords;
        auto [x2,y2] = v1.coords;
        EXPECT_DOUBLE_EQ(v0.dot(v1), x1*x2 + y1*y2);
      }
    }
  }
}

TEST(DISABLED_vector, testCCW) {
  for(double alpha0 = 0; alpha0 <= 2 * M_PI; alpha0 += M_PI / 10.) {
    for (double alpha1 = 0; alpha1 <= 2 * M_PI; alpha1 += M_PI / 10.) {
      for (double length = 0; length <= 20; ++length) {
        Vector2D v0(alpha0,length), v1(alpha1,length);
        auto [x1,y1] = v0.coords;
        auto [x2,y2] = v1.coords;
        EXPECT_DOUBLE_EQ(v0.cross(v1), x1*x2 - y1*y2);
      }
    }
  }
}