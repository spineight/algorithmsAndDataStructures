#include <iostream>
#include <cstring>
#include <sstream>
#include <vector>


template<typename T>
struct Struct0 {

};

namespace show_non_type_parameters {

    template<typename T, int rowsN, int colsN>
    struct Matrix {
        Matrix() {
            memset(mat, 0, sizeof(mat));
        }
        T mat[rowsN][colsN];
    };

    template<typename T, int rowsN, int colsN>
    std::ostream& operator<<(std::ostream& out, const Matrix<T,rowsN,colsN>& m) {
        for(int r = 0; r < rowsN; ++r) {
            for(int c = 0; c < colsN; ++c) {
                out << m.mat[r][c] << " ";
            }
            out << '\n';
        }
        return out;
    }

    template<typename T, int rowsN, int colsN>
    std::istream& operator>>(std::istream& in, Matrix<T,rowsN,colsN>& m) {
            for(int r = 0; r < rowsN; ++r) {
                for(int c = 0; c < colsN; ++c) {
                    in >> m.mat[r][c];
                }
            }
        return in;
    }

    template<typename T, int rowsN, int K, int colsN>
    Matrix<T, rowsN, colsN> operator*(const Matrix<T, rowsN, K>& a, const Matrix<T, K, colsN>& b) {
        Matrix<T, rowsN, colsN> res;
        for(int r = 0; r < rowsN; ++r) {
            for(int c = 0; c < colsN; ++c) {
                for(int i = 0; i < K; ++i) {
                    res.mat[r][c] += a.mat[r][i] * b.mat[i][c];
                }
            }
        }
        return res;
    }

}

namespace show_template_template_parameters {
    //! Before C++17 typename not allowed for template template parameters - class should be used
    template <template<typename> typename ContT>
    struct Stack{
        ContT<int> s;
    };

    template < typename T, template<typename> class ContT>
    T do_sum(const ContT<T>& cont) {
        T res{0};
        for(auto v : cont) res += v;
        return res;
    }
}

int main() {
    using namespace show_non_type_parameters;

    std::stringstream ss0 {"1 2 3  4 5 6"};
    Matrix<int,2,3> m0;
    ss0 >> m0;
    std::cout << m0 << '\n';

    std::stringstream ss1 {"1 4  2 5  3 6"};
    Matrix<int,3,2> m1;
    ss1 >> m1;
    std::cout << m1 << '\n';

    auto res = m0 * m1;
    std::cout << res << '\n';


    show_template_template_parameters::Stack<std::vector> s;

    std::vector<int> v = {1,2,3,4,5,6,7,8,9};
    std::cout << show_template_template_parameters::do_sum(v) << '\n';
    return 0;
}
