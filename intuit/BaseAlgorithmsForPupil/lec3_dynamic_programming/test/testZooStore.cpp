#include <gtest/gtest.h>

#ifdef PRACTICE
#include <practice/zoo_store.hpp>
using namespace lec3::practice;
#else
#include <include/zoo_store.hpp>
using namespace lec3;
#endif

TEST(zoo_store, simple) {
  // Для удобства, чтобы не допустить ошибку и учесть все комбинации
  // Рассмотрим массив, как двоичную запись числа, и пройдем все числа от 0 до 2^n - 1
  // После чего уберем не подходящие варианты
  // n = 3
  // 0: 0 0 0
  // 1: 0 0 1  OK
  // 2: 0 1 0  OK
  // 3: 0 1 1  OK
  // 4: 1 0 0  OK
  // 5: 1 0 1  OK
  // 6: 1 1 0  OK
  // 7: 1 1 1
  // Sum(if OK) = 6
  EXPECT_EQ(zoo_store(3),6);
  // n = 2
  // 0: 0 0
  // 1: 0 1
  // 2: 1 0
  // 3: 1 1
  EXPECT_EQ(zoo_store(2),4);
  EXPECT_EQ(zoo_store(1),2);
  EXPECT_EQ(zoo_store(0),0);

  // n = 4
  // 0: 0 0 0 0
  // 1: 0 0 0 1
  // 2: 0 0 1 0  OK
  // 3: 0 0 1 1  OK
  // 4: 0 1 0 0  OK
  // 5: 0 1 0 1  OK
  // 6: 0 1 1 0  OK
  // 7: 0 1 1 1
  // 8: 1 0 0 0
  // 9: 1 0 0 1  OK
  //10: 1 0 1 0  OK
  //11: 1 0 1 1  OK
  //12: 1 1 0 0  OK
  //13: 1 1 0 1  OK
  //14: 1 1 1 0
  //15: 1 1 1 1
  // SUM(if=OK) = 10
  EXPECT_EQ(zoo_store(4),10);
}