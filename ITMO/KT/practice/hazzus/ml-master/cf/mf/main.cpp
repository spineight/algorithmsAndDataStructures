//#include <iostream>
//#include <utility>
//#include <vector>
//#include <cmath>
//#include <numeric>
//#include <cassert>
//#include <functional>
//
//struct matrix {
//    matrix() = default;
//    matrix(size_t h, size_t w, double init = 0) : height(h), width(w), data(h, std::vector<double>(w, init)) {}
//
//    size_t height = 0, width = 0;
//    std::vector<std::vector<double>> data;
//};
//
//std::istream& operator>>(std::istream& in, matrix& m) {
//    for (size_t i = 0; i < m.height; i++) {
//        for (size_t j = 0; j < m.width; j++) {
//            in >> m.data[i][j];
//        }
//    }
//    return in;
//}
//
//std::ostream& operator<<(std::ostream& out, matrix const& m) {
//    for (size_t i = 0; i < m.height; i++) {
//        for (size_t j = 0; j < m.width; j++) {
//            out << m.data[i][j] << " ";
//        }
//        out << std::endl;
//    }
//    return out;
//}
//
//matrix operator*(matrix const& left, matrix const& right) {
//    assert(left.width == right.height);
//    matrix res(left.height, right.width);
//    for (size_t i = 0; i < res.height; i++)
//        for (size_t j = 0; j < res.width; j++)
//            for (size_t k = 0; k < left.width; k++)
//                res.data[i][j] += left.data[i][k] * right.data[k][j];
//    return res;
//}
//
//matrix operator+(matrix const& left, matrix const& right) {
//    matrix res(left.height, left.width);
//    for (size_t i = 0; i < res.height; i++) {
//        for (size_t j = 0; j < res.width; j++) {
//            res.data[i][j] = left.data[i][j] + right.data[i][j];
//        }
//    }
//    return res;
//}
//
//matrix& operator+=(matrix& left, matrix const& right) {
//    for (size_t i = 0; i < left.height; i++) {
//        for (size_t j = 0; j < left.width; j++) {
//            left.data[i][j] += right.data[i][j];
//        }
//    }
//    return left;
//}
//
//void impure_map(matrix& x, std::function<void(size_t, size_t)> const& func) {
//    for (size_t i = 0; i < x.height; i++) {
//        for (size_t j = 0; j < x.width; j++) {
//            func(i, j);
//        }
//    }
//}
//
//struct node {
//    matrix result, derivative;
//
//    node() = default;
//    node(size_t h, size_t w) : result(h, w) {}
//
//    virtual void compute() = 0;
//    virtual void back_propagation() = 0;
//
//    void create_derivative() {
//        derivative = matrix(result.height, result.width);
//    }
//};
//
//struct var : node {
//    size_t index;
//
//    explicit var(size_t h, size_t w, size_t i) : index(i), node(h, w) {}
//
//    void compute() override {}
//    void back_propagation() override {}
//};
//
//struct tnh : node {
//    node* prev;
//
//    explicit tnh(node* prev) : prev(prev) {}
//
//    void compute() override {
//        result = matrix(prev->result.height, prev->result.width);
//        impure_map(result, [&](size_t i, size_t j) {
//            result.data[i][j] = std::tanh(prev->result.data[i][j]);
//        });
//    }
//
//    void back_propagation() override {
//        impure_map(prev->derivative, [&](size_t i, size_t j) {
//            prev->derivative.data[i][j] += (1 - result.data[i][j] * result.data[i][j]) * derivative.data[i][j];
//        });
//    }
//};
//
//struct rlu : node {
//    node* prev;
//    double alpha;
//
//    rlu(node* x, double alpha) : prev(x), alpha(alpha) {}
//
//    void compute() override {
//        result = matrix(prev->result.height, prev->result.width);
//        impure_map(result, [&](size_t i, size_t j) {
//            if (prev->result.data[i][j] < 0) {
//                result.data[i][j] = prev->result.data[i][j] / alpha;
//            } else {
//                result.data[i][j] = prev->result.data[i][j];
//            }
//        });
//    }
//
//    void back_propagation() override {
//        impure_map(result, [&](size_t i, size_t j) {
//            if (prev->result.data[i][j] >= 0) {
//                prev->derivative.data[i][j] += derivative.data[i][j];
//            } else {
//                prev->derivative.data[i][j] += derivative.data[i][j] / alpha;
//            }
//        });
//    }
//};
//
//struct mul : node {
//    node *a, *b;
//
//    mul(node* a, node* b) : a(a), b(b) {}
//
//    void compute() override {
//        result = a->result * b->result;
//    }
//
//    void back_propagation() override {
//        for (std::size_t i = 0; i < a->result.height; i++)
//            for (std::size_t j = 0; j < a->result.width; j++)
//                for (std::size_t k = 0; k < b->result.width; k++)
//                    a->derivative.data[i][j] += derivative.data[i][k] * b->result.data[j][k];
//
//
//        for (std::size_t i = 0; i < a->result.width; i++)
//            for (std::size_t j = 0; j < b->result.width; j++)
//                for (std::size_t k = 0; k < a->result.height; k++)
//                    b->derivative.data[i][j] += a->result.data[k][i] * derivative.data[k][j];
//    }
//};
//
//struct sum : node {
//    std::vector<node*> v;
//
//    explicit sum(std::vector<node*> v) : v(std::move(v)) {}
//
//    void compute() override {
//        result = std::accumulate(v.begin(), v.end(),
//                                 matrix(v[0]->result.height, v[0]->result.width), [](matrix& a, node* b) {
//            return a + b->result;
//        });
//    }
//
//    void back_propagation() override {
//        for (auto x : v) {
//            x->derivative += derivative;
//        }
//    }
//};
//
//struct had : node {
//    std::vector<node*> v;
//
//    explicit had(std::vector<node*> v) : v(std::move(v)) {}
//
//    void compute() override {
//        result = matrix(v[0]->result.height, v[0]->result.width, 1);
//        for (auto& x : v) {
//            impure_map(result, [&](size_t i, size_t j) {
//                result.data[i][j] *= x->result.data[i][j];
//            });
//        }
//    }
//
//    void back_propagation() override {
//        for (size_t x1 = 0; x1 < v.size(); x1++) {
//            impure_map(result, [&](size_t i, size_t j) {
//                double m = 1;
//                for (size_t x2 = 0; x2 < v.size(); x2++) {
//                    if (x1 != x2) {
//                        m *= v[x2]->result.data[i][j];
//                    }
//                }
//                v[x1]->derivative.data[i][j] += m * derivative.data[i][j];
//            });
//        }
//    }
//};
//
//int main() {
//    size_t n, m, k;
//    std::cin >> n >> m >> k;
//    std::vector<node*> network;
//    std::string s;
//    for (size_t i = 0; i < n; i++) {
//        std::cin >> s;
//        if (s == "var") {
//            size_t h, w;
//            std::cin >> h >> w;
//            network.push_back(new var(h, w, i));
//        } else if (s == "tnh") {
//            size_t x;
//            std::cin >> x;
//            network.push_back(new tnh(network[x - 1]));
//        } else if (s == "rlu") {
//            size_t alpha, x;
//            std::cin >> alpha >> x;
//            network.push_back(new rlu(network[x - 1], alpha));
//        } else if (s == "mul") {
//            size_t a, b;
//            std::cin >> a >> b;
//            network.push_back(new mul(network[a - 1], network[b - 1]));
//        } else if (s == "sum" || s == "had") {
//            std::vector<node*> local;
//            size_t len;
//            std::cin >> len;
//            for (size_t j = 0; j < len; j++) {
//                size_t x;
//                std::cin >> x;
//                local.push_back(network[x - 1]);
//            }
//            if (s == "sum") {
//                network.push_back(new sum(local));
//            } else {
//                network.push_back(new had(local));
//            }
//        }
//    }
//
//    for (size_t i = 0; i < m; i++) {
//        std::cin >> network[i]->result;
//    }
//
//    for (size_t i = 0; i < n; i++) {
//        network[i]->compute();
//    }
//
//    for (size_t i = 0; i < n; i++) {
//        network[i]->create_derivative();
//        if (i >= n - k) {
//            std::cin >> network[i]->derivative;
//            std::cout << network[i]->result;
//        }
//    }
//
//    for (size_t i = n; i --> 0; ) {
//        network[i]->back_propagation();
//    }
//
//    for (size_t i = 0; i < m; i++) {
//        std::cout << network[i]->derivative;
//    }
//}
//
//
//
//


#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <numeric>

uint64_t in_dist(std::map<size_t, std::vector<int>> data) {
    uint64_t distance = 0;
    for (auto& p : data) {
        std::sort(p.second.begin(), p.second.end());
        auto& x = p.second;
        uint64_t suffix = std::accumulate(x.begin(), x.end(), static_cast<uint64_t>(0));
        uint64_t prefix = 0;
        for (size_t i = 0; i < x.size(); i++) {
            suffix -= x[i];

            distance += (x[i] * i - prefix) + (suffix - x[i] * (x.size() - i - 1));

            prefix += x[i];
        }
    }
    return distance;
}

uint64_t ex_dist(std::vector<std::pair<int, size_t>> data, size_t k) {
    uint64_t distance = 0;
    std::sort(data.begin(), data.end());

    std::vector<std::pair<uint64_t, uint64_t>> prefixes(k), suffixes(k);
    uint64_t prefix_total = 0, suffix_total = 0;

    for (auto const& p : data) {
        suffixes[p.second].first += p.first;
        suffixes[p.second].second++;
        suffix_total += p.first;
    }

    for (int i = 0; i < data.size(); i++) {
        auto const& p = data[i];

        suffixes[p.second].first -= p.first;
        suffixes[p.second].second--;
        suffix_total -= p.first;

        uint64_t p_delta = (i - prefixes[p.second].second) * p.first - (prefix_total - prefixes[p.second].first);
        uint64_t s_delta = (suffix_total - suffixes[p.second].first) - ((data.size() - 1 - i) - suffixes[p.second].second) * p.first;
        distance += p_delta + s_delta;

        prefixes[p.second].first += p.first;
        prefixes[p.second].second++;
        prefix_total += p.first;
    }

    return distance;
}

int main() {
    size_t k, n;
    std::cin >> k >> n;
    std::vector<std::pair<int, size_t>> data(n);
    std::map<size_t, std::vector<int>> data_map;
    for (size_t i = 0; i < n; i++) {
        std::cin >> data[i].first >> data[i].second;
        data[i].second--;
        data_map[data[i].second].push_back(data[i].first);
    }
    std::cout << in_dist(data_map) << '\n' << ex_dist(data, k);
}

