#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <numeric>

constexpr double EPS = 1e-6;

double pirson_coefficient(std::vector<int> const& x, std::vector<int> const& y) {
	double avg_x = std::accumulate(x.begin(), x.end(), 0.0) / x.size();
	double avg_y = std::accumulate(y.begin(), y.end(), 0.0) / y.size();
//	std::cout << avg_x << '\n';
	std::vector<double> dx, dy;
	std::transform(x.begin(), x.end(), std::back_inserter(dx), [=](int ex){
		return pow(static_cast<double>(ex) - avg_x, 2);
	});
	std::transform(y.begin(), y.end(), std::back_inserter(dy), [=](int ey){
		return pow(static_cast<double>(ey) - avg_y, 2);
	});
	

	double disp_x = std::accumulate(dx.begin(), dx.end(), 0.0);
	double disp_y = std::accumulate(dy.begin(), dy.end(), 0.0);

	if (fabs(disp_x) < EPS || fabs(disp_y) < EPS) {
		return 0;
	}
	std::vector<double> covariance(x.size());
	for (size_t i = 0; i < x.size(); i++) {
		covariance[i] = (static_cast<double>(x[i]) - avg_x) * (static_cast<double>(y[i]) - avg_y);
	}

	return std::accumulate(covariance.begin(), covariance.end(), 0.0) / sqrt(disp_x * disp_y);

}


int main() {
	size_t n;
	std::cin >> n;
	std::vector<int> x(n);
	std::vector<int> y(n);
	for (size_t i = 0; i < n; i++) {
		std::cin >> x[i] >> y[i];
	}
	std::cout << pirson_coefficient(x, y);
}
