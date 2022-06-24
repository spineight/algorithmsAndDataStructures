#include <grasshopper.hpp>
#include <turtle.hpp>
#include <zoo_store.hpp>
#include <knapsack.hpp>
#include <iostream>

int main() {
  std::cout << grasshopper(2, 2) << '\n'; // 2

  std::cout << grasshopper_and_money(5, 2, { 0, 2, -5, -1, 3, 0 }) << '\n'; // 4

  auto res = grasshopper_and_money_restoring_sequence_of_jumps(
      5, 2, { 0, 2, -5, -1, 3, 0 });
  for (auto v : res)
    std::cout << v << ",";
  std::cout << '\n';

  std::cout << "turtle\n";
  std::cout << turtle(3, 3) << '\n';

  //
  //   0 3 1 1
  //   1 1 1 1
  //   5 2 3 2
  //   5 5 5 5
  // expected: (3,3), (3,2), (3,1), (3,0), (2,0), (1,0), (0,0)
  auto seq = turtle_and_money(
      4, 4, { { 0, 3, 1, 1 }, { 1, 1, 1, 1 }, { 5, 2, 3, 1 }, { 5, 5, 5, 5 } });
  for (auto[ r, c ] : seq)
    std::cout << r << "," << c << '\n';

  // Идея: чтобы понять какие комбинации подходят, мы пронумеруем все комбинация
  // (начинаем с 0 и каждая
  // следующая комбинация на единицу больше предыдущей, далее вычеркиваем
  // неподходящие комбинации
  // Пример для 3-х: (000)X,(001)V,(010)V,(011)V, (100)V, (101)V, (110)V, (111)X
  std::cout << zoo_store(3) << '\n'; // (001), (010), (011), (100), (101), (110)
  std::cout
      << zoo_store(4)
      << '\n'; // (0010),(0011),(0100),(0101),(0110),(1001),(1010),(1011),(1100),(1101)

  std::cout << "knapsack\n";
  std::cout << knapsack({ 4, 3, 3 }, { 8, 5, 5 }, 6) << '\n'; // expected 10
  return 0;
}