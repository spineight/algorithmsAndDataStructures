#include <iostream>
#include <string>

namespace show_overloading {
    template<typename T>
    void fn(T val) {
        std::cout << val << ": generic version\n";
    }
    //! This is overload, since it doesn't have template arguments
    void fn(int val) {
        std::cout << val << ": overloaded version \n";
    }
}

//! https://www.modernescpp.com/index.php/template-specialization
namespace show_specialization {
    //! specialization idea: we fix some of a template parameters, specifying them as arguments
    //! specialized version is a subset of a generic version
    
    //! (0) - generic version
    template<typename T, typename U> //! <- template parameters list
    struct TemplateStruct {
        TemplateStruct(T t,U u) {
            std::cout << "generic version\n";
        }
    };

    //! ### partial specializations:
    //! specialization version can have absolutely different content & members
    //! specialization is this is more specific(specialize case) of the generic version - (0)
    template<typename T>
    struct TemplateStruct<T,T> { //! <T,T> <- template arguments list
        TemplateStruct(T val) {
            std::cout << "<T,T> version\n";
        }
    };

    template<typename T>
    struct TemplateStruct<double,T> { //! <T,T> <- template arguments list
        TemplateStruct(T val) {
            std::cout << "<double,T> version" << '\n';
        }
    };

    template<typename T, typename U> //! <- template parameters list
    struct TemplateStruct<T, U&> {
        TemplateStruct(T t) {
            std::cout << "<T, U&> version" << '\n';
        }
        int val;
        void doSmth() {}
    };

    //! full specialization
    template<>
    struct TemplateStruct<std::string,std::string> {
        TemplateStruct() {
            std::cout << "full specialization" << '\n';
        }
        std::string s;
    };
}



int main() {
    show_overloading::fn(1.);
    show_overloading::fn(1);


    show_specialization::TemplateStruct ts0(1,2.);
    show_specialization::TemplateStruct<int,int> ts1(3);
    show_specialization::TemplateStruct<double,int> ts2(4);
    show_specialization::TemplateStruct<int,int&> ts3(5);
    show_specialization::TemplateStruct<std::string, std::string> ts4;
    return 0;
}