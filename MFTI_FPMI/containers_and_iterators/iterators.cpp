//! refs
//! https://en.cppreference.com/w/cpp/iterator/iterator
//! https://en.cppreference.com/w/cpp/iterator/iterator_tags
//! https://en.cppreference.com/w/cpp/iterator/iterator_traits

//! Iterators types

//! 1. Input iterator
//! only one time traversal of elements
//! ++; *

//! 2. Forward iterator

//! 3. Bidirectional iterator
//! --;

//! 4. Random access iterator
// []

#include <iterator>
#include <iostream>
#include <vector>

int main() {
    //! https://en.cppreference.com/w/cpp/iterator/istream_iterator
    // std::istream_iterator<int> it(std::cin);
    // int cnt{5};
    // while(cnt--) {
        // std::cout << *it++ << '\n';
    // }
    std::istream_iterator<int> it(std::cin);
    std::vector<int> a (it, std::istream_iterator<int>()); // press ctrl + D to finish input

    for(auto v : a) std::cout << v << " ";
    std::cout << '\n';

    return 0;
}