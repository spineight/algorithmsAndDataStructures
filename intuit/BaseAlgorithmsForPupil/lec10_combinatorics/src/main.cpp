#include <permutations.hpp>
#include <find_kth_permutation.hpp>
#include <find_permutation_number.hpp>
#include <vector>
#include <iostream>

int main() {
  std::vector<int> a = {1,2,3,4,5};
  do {
    for(auto e: a) std::cout << e << " ";
    std::cout << '\n';
  } while(lec10_combinatorics::next_permutation(&a[0], &a[a.size()-1]+1));

  std::cout << '\n';
  auto permutation = lec10_combinatorics::find_kth_permutation(7, 5);
  for(auto e : permutation) std::cout << e << " ";
  std::cout << '\n';

  std::cout << '\n';
  permutation = lec10_combinatorics::find_kth_permutation(120, 5);
  for(auto e : permutation) std::cout << e << " ";
  std::cout << '\n';

  auto idx = lec10_combinatorics::find_permutation_number({1,2,3,4,5});
  std::cout << idx << '\n';
  idx = lec10_combinatorics::find_permutation_number({1,3,2,4,5});
  std::cout << idx << '\n';
  idx = lec10_combinatorics::find_permutation_number({5,4,3,2,1});
  std::cout << idx << '\n';
  return 0;
}