//! https://app.codility.com/programmers/lessons/10-prime_and_composite_numbers/min_perimeter_rectangle/

/*


An integer N is given, representing the area of some rectangle.

The area of a rectangle whose sides are of length A and B is A * B, and the perimeter is 2 * (A + B).

The goal is to find the minimal perimeter of any rectangle whose area equals N. The sides of this rectangle should be only integers.

For example, given integer N = 30, rectangles of area 30 are:

        (1, 30), with a perimeter of 62,
        (2, 15), with a perimeter of 34,
        (3, 10), with a perimeter of 26,
        (5, 6), with a perimeter of 22.

Write a function:

    int solution(int N);

that, given an integer N, returns the minimal perimeter of any rectangle whose area is exactly equal to N.

For example, given an integer N = 30, the function should return 22, as explained above.

Write an efficient algorithm for the following assumptions:

        N is an integer within the range [1..1,000,000,000].
 */

int solution(int N) {
  size_t n = N;
  size_t a = 1;
  size_t minPerimiter{ (a + n) * 2 };
  while(a * a <= n) {
    if( (n % a) == 0 ) {
      size_t b = n / a;
      minPerimiter = min(minPerimiter, (a + b) * 2);
    }
    ++a;
  }
  return minPerimiter;
}
