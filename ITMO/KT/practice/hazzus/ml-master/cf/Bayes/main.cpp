#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <iomanip>

constexpr long double Q_POWER = 2.0L;

int main() {
    uint32_t k;
    std::cin >> k;

    // some class related containers
    std::vector<long double> lambda(k);
    std::vector<std::map<std::string, uint32_t>> word_count(k);
    std::vector<uint32_t> class_count(k);

    for (uint32_t i = 0; i < k; i++) {
        std::cin >> lambda[i];
    }
    long double alpha;
    std::cin >> alpha;

    auto get_word_probability = [&](std::string const& word, uint32_t class_num) {
        auto it = word_count[class_num].find(word);
        long double divisor = Q_POWER * alpha + class_count[class_num];
        long double count = (it == word_count[class_num].end()) ? 0 : it->second;
        return (count + alpha) / divisor;
    };

    uint32_t n;
    std::cin >> n;
    std::set<std::string> all_words;
    for (uint32_t i = 0; i < n; i++) {
        uint32_t class_num, word_amount;
        std::cin >> class_num;
        std::cin >> word_amount;
        std::set<std::string> words;
        for (uint32_t j = 0; j < word_amount; j++) {
            std::string word;
            std::cin >> word;
            all_words.insert(word);
            words.insert(std::move(word));
        }
        for (auto&& word : words) {
            word_count[class_num - 1][word] += 1;
        }
        class_count[class_num - 1] += 1;
    }

    for (uint32_t c = 0; c < k; c++) {
        for (auto&& word : all_words) {
            std::cout << word << " : " << get_word_probability(word, c) << ", ";
        }
        std::cout << "\n";
    }

    uint32_t m;
    std::cin >> m;
    for (uint32_t i = 0; i < m; i++) {
        uint32_t word_amount;
        std::cin >> word_amount;
        std::set<std::string> words;
        for (uint32_t j = 0; j < word_amount; j++) {
            std::string s;
            std::cin >> s;
            words.insert(std::move(s));
        }

        std::vector<long double> score(k);
        long double sum_score = 0.0L;
        for (uint32_t class_num = 0; class_num < k; class_num++) {
            long double& score_current = score[class_num];
            score_current = lambda[class_num] * class_count[class_num] / n;
            std::cout << "Init " << class_num << " " << score_current << '\n';

            for (auto const& word : words) {
                if (all_words.count(word)) {
                    score_current *= get_word_probability(word, class_num);
                }
            }
            std::cout << "Mid " << class_num << " " << score_current << '\n';

            for (auto const& word : all_words) {
                if (!words.count(word)) {
                    score_current *= 1.0L - get_word_probability(word, class_num);
                }
            }
            std::cout << "Finish " << class_num << " " << score_current << '\n';

            sum_score += score_current;
        }
        std::cout << std::fixed << std::setprecision(11);
        for (auto s : score) {
            std::cout << s / sum_score << ' ';
        }
        std::cout << '\n';
    }

}
