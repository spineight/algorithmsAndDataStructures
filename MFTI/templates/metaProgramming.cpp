#include <iostream>


//! Meta programming - operations with types and code


//! tools
//! loops: recursion + specialization
//! result returned as static member of a struct or as a using directive from a struct
//!
//! for convenience template variables and template aliases are used

namespace show_result_values {
    template<typename T, typename U>
    struct is_same {
        static const bool val = false;
    };  

    template<typename T>
    struct is_same<T,T> {
        static const bool val = true;
    };  

    template<typename T, typename U>
    bool is_same_v = is_same<T,U>::val;
}

namespace show_result_types {
    template<typename T>
    struct remove_const {
        using val = T;
    };

    template<typename T>
    struct remove_const<const T> {
        using val = T;
    };

    template<typename T>
    using remove_const_v = typename remove_const<T>::val;

    template<typename T>
    class GetTypeName{
        GetTypeName() = delete;
    };
}

namespace show_compile_time_computations {
    template<int N>
    struct Fib {
        static const int res = Fib<N-1>::res + Fib<N-2>::res;
    };

    template<>
    struct Fib<0> {
        static const int res = 1;
    };
    template<>
    struct Fib<1> {
        static const int res = 1;
    };
}

int main() {
    using namespace show_result_values;
    using namespace show_result_types;
    std::cout << is_same_v<int,double> << '\n';
    std::cout << is_same_v<int,int> << '\n';

    // GetTypeName< remove_const_v<const int> > gtn;

    // 1 1 2 3 5 8
    std::cout << show_compile_time_computations::Fib<5>::res << '\n';
    return 0;
}