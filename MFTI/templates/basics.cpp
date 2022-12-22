#include <iostream>

namespace template_types {
    
    template<typename T>
    struct TemplateStruct {
        T v;
        TemplateStruct(T v) : v(v) {
            std::cout << v << '\n';
        }
    };

    struct StructWithTemplateMethod {
        template<typename T>
        void templateMethod(T val) {
            std::cout << val << '\n';
        }
    };

    template<typename T>
    void templateFn(T val) {
        std::cout << val << '\n';
    }

    //! https://stackoverflow.com/questions/21051141/c14-variable-templates-what-is-their-purpose-any-usage-example
    //! TODO:
    //! https://mariusbancila.ro/blog/2021/12/23/use-cases-of-variable-templates-in-cpp/
    //! https://www.youtube.com/watch?v=2kY-go52rNw
    template<int N>
    int square = N*N;
}

int main() {
    template_types::TemplateStruct ts(10);
    template_types::templateFn(11);
    template_types::StructWithTemplateMethod stm;
    stm.templateMethod(12);
    std::cout << template_types::square<10> << '\n';

    return 0;
}