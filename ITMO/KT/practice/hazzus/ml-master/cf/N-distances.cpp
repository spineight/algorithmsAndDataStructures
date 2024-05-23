#include<iostream>

long long in_dist(std::vector<int> const& x, std::vector<int> const& c, size_t k) {
	std::vector<std::vector<int>> mapping(k);
	for (size_t i = 0; i < x.size(); i++) {
		mapping[c[i]].push_back(x[i]); 
	}
	for (size_t i = 0; i < k; i++) {
		sort(mapping[i].begin(), mapping[i].end());
	}
	long long res = 0;
	for (size_t i = 0; i < k; i++) {
		long long suff = std::accumulate(mapping[i].begin(), mapping[i].end(), 0LL);
		
	}
}

int main() {
	size_t k, n;
	std::cin >> k >> n;
    std::vector<int> x(n), c(n);
	for (size_t i = 0; i < n; i++) {
		std::cin >> x[i] >> c[i];
	}
	std::cout << in_dist(x, c, k) << '\n' << ex_dist(x, c, k);
}

