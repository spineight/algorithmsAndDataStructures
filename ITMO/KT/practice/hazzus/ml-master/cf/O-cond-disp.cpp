#include <iostream>
#include <vector>

int main() {
	size_t k, n;
	std::cin >> k >> n;
	std::vector<int> x(n), y(n);
	for (size_t i = 0; i < n; i++) {
		std::cin >> x[i] >> y[i];
	}
	long double moment_square = 0;
	std::vector<long double> p(k), Ey(k);
	for (size_t i = 0; i < n; i++) {
		moment_square += y[i] * y[i] / static_cast<long double>(n);
		p[x[i] - 1] += 1.0L / n;
		Ey[x[i] - 1] += y[i] / static_cast<long double>(n);
	}
	long double expect_square = 0;
	for (size_t i = 0; i < k; i++) {
		if (p[i] != 0) {
			expect_square += Ey[i] * Ey[i] / p[i];
		}
	}
	std::cout << std::fixed << moment_square - expect_square;
}
