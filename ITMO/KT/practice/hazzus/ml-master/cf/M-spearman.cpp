#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

std::vector<int> count_rangs(std::vector<int> const& x) {
	std::vector<int> result(x.size());
	std::vector<std::pair<int, size_t>> xi;
	xi.reserve(x.size());
	for (size_t i = 0; i < x.size(); i++) {
		xi.emplace_back(x[i], i);
	}
	std::sort(xi.begin(), xi.end());
	
	//std::cout << xi.size() << std::endl;
	//for (auto a : xi) {
	//	std::cout << a.first << a.second << " ";
	//}
	// std::cout << std::endl;
	
	int current = 0;
	
	for (size_t i = 1; i < xi.size(); i++) {
		if (xi[i - 1].first != xi[i].first) {
			current++;
		}
		result[xi[i].second] = current;
	}
	return result;
}

double spearman_coefficient(std::vector<int> const& x, std::vector<int> const& y) {
	if (x.size() < 2) {
		return 0;
	}
	std::vector<int> rangs_x = count_rangs(x);
	std::vector<int> rangs_y = count_rangs(y);

	double sum = 0;
	for (size_t i = 0; i < x.size(); i++) {
		sum += pow(rangs_x[i] - rangs_y[i], 2);
	}
	return 1 - 6 * sum / (pow(x.size(), 3) - x.size()); 
}

int main() {
	size_t n;
	std::cin >> n;
	std::vector<int> x(n), y(n);
	for (size_t i = 0; i < n; i++) {
		std::cin >> x[i] >> y[i];
	}
	std::cout << spearman_coefficient(x, y);
}
