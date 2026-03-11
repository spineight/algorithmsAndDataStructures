// #include <bits/stdc++.h>
// using namespace std;

#include <random>
#include <vector>
#include <algorithm>
#include <cassert>
#include <iostream>


// Combine two sorted subarrays [l, m) and [m, r) into a single sorted array
size_t combine(std::vector<int>& src, std::vector<int>& dest, int l, int m, int r) {
    int i = l;
    int j = m;
    int pos = l;
    size_t inversions = 0;

    // Merge elements from two sorted subarrays until one is exhausted.
    while(i < m && j < r) {
        if(src[i] <= src[j]) {
            dest[pos++] = src[i++];
        } else { // we take from the second part - means we have inversions (number = n of unfinished elements in the first part)
            dest[pos++] = src[j++];
            inversions += m - i; // Count all remaining elements in the left subarray as inversions
        }
    }
    // Copy remaining elements from the left subarray
    while(i < m) {
        dest[pos++] = src[i++];
    }
    // Copy remaining elements from the right subarray
    while(j < r) {
        dest[pos++] = src[j++];
    }

    return inversions;
}

// Recursively divide the array  [l,r) into 2 parts
// combine_to_aux=true: read from 'a', write merged result to 'aux'
// combine_to_aux=false: read from 'aux', write merged result to 'a'
// Alternating avoids an extra copy-back after each merge.
size_t merge_sort_impl(std::vector<int>& a, std::vector<int>& aux, int l, int r, bool combine_to_aux){
    size_t inversions = 0;
    if(l+1 < r) { // Recurse only if subarray has more than one element
        int m = l + (r-l) / 2;
        // recursively sort left half
        inversions += merge_sort_impl(a, aux, l, m, !combine_to_aux);
        // recursively sort right half
        inversions += merge_sort_impl(a, aux, m, r, !combine_to_aux);
        // Merge the two sorted halves
        if( combine_to_aux)
            inversions += combine(a, aux, l, m, r);
        else
            inversions += combine(aux, a, l, m, r);
    }
    return inversions;
}

size_t merge_sort(std::vector<int>& a) {
    std::vector<int>aux(std::begin(a), std::end(a));
    return merge_sort_impl(a, aux, 0, std::size(a), false);
}

// using modified Merge sort to count number of inversions
// inversion in an array: given idxs i,j, such that i< j and a[i] > a[j]
// number of inversions for index i, is number of elements with idxs > i such that 
// a[i] > a[idxs...]
// How merge sort can help here, seems like combine routine can be helpfull
// On example:
//  a = [1 6 3 4 2 5]
// Number of inversions 6 (counted manually)
// when we combine 2 arrays we can calculate number of inversions:
// if we take from the second array -> all elements in the first one are bigger, so they
// are inversions

int main() {
    // Seed the random number generator
    std::random_device rd;
    std::mt19937 engine(rd());
    std::uniform_int_distribution<int> dist(0, 1000);

    // Generate a random vector
    std::vector<int> v(20);
    std::generate(v.begin(), v.end(), [&]() { return dist(engine); });

    // Print the original vector
    std::cout << "Original vector: ";
    for (int x : v) std::cout << x << " ";
    std::cout << "\n";

    // Sort the vector
    std::vector<int> tmp = {1,6,3,4,2,5};
    auto inversions_cnt = merge_sort(tmp);
    std::cout << "Inversions cnt:" << inversions_cnt << '\n';

    // // Print the sorted vector
    // std::cout << "Sorted vector: ";
    // for (int x : v) std::cout << x << " ";
    // std::cout << "\n";

    // // Verify the result
    // assert(std::is_sorted(v.begin(), v.end()));
}
