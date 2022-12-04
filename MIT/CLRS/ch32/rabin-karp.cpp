#include<bits/stdc++.h>

using namespace std;

long long powModulo(long long base, long long power, long long modulo) {
    if(0 == power) return 1;
    if(1 == power) return base;

    const auto half = powModulo(base, power / 2, modulo);
    if(power & 1) return ( (base * half % modulo) * half ) % modulo;
    return half * half % modulo;
}

//! I used it to check powModulo, which initially worked incorrectly (I checked it using Python)
size_t powModulo2(size_t base, size_t power, size_t modulo) {
    size_t res{1};
    while(power--) res = (res * base) % modulo;
    return res;
}

vector<size_t> rabinKarp(const string& t, const string& p) {
    constexpr long long Radix = 256; // for ASCII

    const size_t n = t.size();
    const size_t m = p.size();

    constexpr long long prime = 982'451'653; // 50'000'000-th prime  https://primes.utm.edu/lists/small/millions/

    const auto RadixPower = powModulo(Radix, m-1, prime);

    

    long long rollingHash{0};
    long long hashP{0};

    for(size_t i = 0; i < m; ++i) {
        // use Gorners rule
        rollingHash =  ( (rollingHash*Radix % prime) + (t[i] % prime) ) % prime;
        hashP = ( (hashP*Radix % prime) + (p[i] % prime) ) % prime;
    }

    vector<size_t> matchedPositions;

    for(size_t i = 0; i + m <= n; ++i) {
        cout << "Rolling hash:" << rollingHash << ", hashP:" << hashP << '\n';
        cout << "offset:" << i << '\n';
        if(rollingHash == hashP) { // potential match
            cout << "possible match at:" << i << '\n';
            // cout << "Rolling hash:" << rollingHash << ", hashP:" << hashP << '\n';
            int k = 0;
            while(k < m && t[i+k] == p[k]) ++k;
            if(k == m) matchedPositions.push_back(i);
        }
        // move window one elem to the right if possible
        if(i+m < n) {
            const auto leftDigit = (RadixPower * t[i]) % prime;
            const auto leftDigitExcluded = (rollingHash - leftDigit + prime) % prime; 
            rollingHash = ( (leftDigitExcluded * Radix % prime) + t[i+m] ) % prime;
        }
    }
    return matchedPositions;
}

int main(int argc, char* argv[]) {
    cout << numeric_limits<long long>::digits10 << '\n';
    const string t  {"abcabcabd"};//= argv[1];
    const string p {"abcabd"};//= argv[2];
    // const string t  {"bcdeaaaaaaaaaaaaaaa"};//= argv[1];
    // const string p {"aaaaaaaaaaaaaaa"};//= argv[2];
    // const string t  {"abcabdabd"};//= argv[1];
    // const string p {"abcabd"};//= argv[2];
    auto res = rabinKarp(t,p);
    for(auto pos : res) cout << pos << " ";
    cout << '\n';
    return 0;
}