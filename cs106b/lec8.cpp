#include <iostream>
#include <lec8.hpp>
using namespace std;


int main() {
  cout << lec7::raise(2,10) << '\n';
  cout << lec7::raiseRecur(2,10) << '\n';
  cout << lec7::raiseRecurEfficient(2,10) << '\n';

  cout <<lec7::isPalindrome("abccba") << '\n';
  cout <<lec7::isPalindrome("abcdcba") << '\n';

  cout << lec7::BSearch({0,1,2,3,4,5,6,7}, 0, 7, 3) << '\n';
  cout << lec7::BSearch({0,1,2,3,4,5,6,7}, 0, 7, 0) << '\n';
  cout << lec7::BSearch({0,1,2,3,4,5,6,7}, 0, 7, 7) << '\n';
  cout << lec7::BSearch({0,1,2,3,4,5,6,7}, 0, 7, -1) << '\n';

  //! C(n,k) = n! / ( (n-k)! * k! )
  //! C(5,3) = 5! / (2! * 3!) =  5 * 4 * 3! / (2 * 3!) = 10
  cout << lec7::C(5,3) << '\n';
  return 0;
}
