#include <iostream>
#include <memory>
#include <vector>
#include <functional>


struct decision_tree {
    using sample_t = std::vector<std::vector<int>>;
    using answer_t = std::vector<int>;
    using scorer_t = std::function<double()>;

    decision_tree(size_t max_depth, scorer_t scorer) : max_depth(max_depth), scorer(std::move(scorer)) {}

    void fit(sample_t const& X, answer_t const& y) {
        root = std::make_unique<node>();
        train_node(*root, 0, X, y);
    }

    [[nodiscard]] std::string to_string() const {
        return std::to_string(max_depth);
    }

private:
    struct node {
        size_t id;
    };
    struct leaf : node {
        int class_;
    };
    struct split : node {
        double threshold;
        std::unique_ptr<node> left;
        std::unique_ptr<node> right;
    };

    void train_node(node& current, size_t depth, ) {
        current.id = last_id++;
        
    }


    size_t max_depth;
    scorer_t scorer;
    size_t last_id = 0;
    std::unique_ptr<node> root;
};

int main() {
    uint32_t m, k, h, n;
    std::cin >> m >> k >> h >> n;
    std::vector<std::vector<int>> X(n, std::vector<int>(m));
    std::vector<int> y(n);
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < m; j++) {
            std::cin >> X[i][j];
        }
        std::cin >> y[j];
    }
    decision_tree clf(h, gini_index);
    clf.fit(X, y);
    std::cout << clf.to_string();
    return 0;
}
