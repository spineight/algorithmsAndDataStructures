#include "prefix.hh"
#include <x86intrin.h>

typedef __m256i v8i;
typedef __m128i v4i;

v4i broadcast(int *p) {
    return (v4i) _mm_broadcast_ss((float*) p);
}

void prefix(int *a, int n) {
    for (int i = 0; i < n; i += 8) {
        v8i x = _mm256_load_si256((v8i*) &a[i]);
        x = _mm256_add_epi32(x, _mm256_slli_si256(x, 4));
        x = _mm256_add_epi32(x, _mm256_slli_si256(x, 8));
        _mm256_store_si256((v8i*) &a[i], x);
    }
    
    v4i s = broadcast(&a[3]);
    
    for (int i = 4; i < n; i += 4) {
        v4i d = broadcast(&a[i + 3]);
        v4i x = _mm_load_si128((v4i*) &a[i]);
        x = _mm_add_epi32(s, x);
        _mm_store_si128((v4i*) &a[i], x);
        s = _mm_add_epi32(s, d);
    }   
}
