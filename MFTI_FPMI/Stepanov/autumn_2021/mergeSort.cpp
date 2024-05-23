#include <bits/stdc++.h>
using namespace std;


void combine(vector<int>&a, vector<int>& aux, int l, int m , int r) {
  int i = l;
  int j = m;
  int outPos = l;
  while(i < m && j < r) {
    if(a[i] < a[j]) aux[outPos++] = a[i++];
    else aux[outPos++] = a[j++];
  }
  while(i < m) aux[outPos++] = a[i++];
  while(j < r) aux[outPos++] = a[j++];
  copy(begin(aux)+l, begin(aux)+r, begin(a)+l);
}

//! [l,r)
//! My Idea: pass aux vector to use it in combine for temporary result storage,
//! instead of creating it everytime in combine method
void mergeSortImpl(vector<int>&a, vector<int>& aux, int l , int r) {
  if(r-l >1) {
    const int m = l + (r-l) / 2;
    mergeSortImpl(a,aux,l,m);
    mergeSortImpl(a,aux,m,r);
    combine(a,aux,l,m,r);
  }
}

void mergeSort(vector<int>& a) {
  vector<int> aux(a);
  mergeSortImpl(a, aux, 0, a.size());
}

span<int> merge(span<int> first, span<int> second, vector<int>&aux) {
  auto it0 = first.begin();
  auto it1 = second.begin();
  int outPos{0};
  while(it0 != end(first) && it1 != end(second)) {
    if(*it0 < *it1) aux[outPos++ ] = *it0++;
    else aux[outPos++] = *it1++;
  }
  while(it0 != end(first)) aux[outPos++ ] = *it0++;
  while(it1 != end(second)) aux[outPos++] = *it1++;

  copy(begin(aux), begin(aux)+outPos, begin(first));
  return span(begin(first), first.size() + second.size());
}

//! Stepanov describes solution using queue of vectors
//! I have adjusted it to make more efficient using std::span
void mergeSortIterative(vector<int>& a) {
  //! make vector power of 2
  int prevSize = a.size();
  int n{1};
  while(n < a.size()) n <<= 1;
  constexpr int INF = numeric_limits<int>::max();
  a.resize(n, INF);

  vector<int> aux(a);
  queue<span<int>> q;
  for(auto it = begin(a); it != end(a); ++it) q.emplace(it,1);
  while(q.size() > 1) { // have at least 2 spans to merge
    auto first = q.front(); q.pop();
    auto second = q.front(); q.pop();
    auto res = merge(first, second, aux);
    q.push(res);
  }
  a.resize(prevSize); //! NB!!! remove artificial elements we added to make the array power of 2
}

int combineCountInversions(vector<int>& a, vector<int>& aux, int l, int m, int r) {
  int i = l;
  int j = m;
  int outPos = l;
  int inversions{0};
  while(i < m && j < r) {
    if(a[i] <= a[j]) aux[outPos++] = a[i++];
    else {
      aux[outPos++] = a[j++];
      const int remainingElemsCntFirst = m - i;
      //! idea once the smallest element from the remaining in the second array
      //! it forms inversions with all remaining elements in the first array
      inversions += remainingElemsCntFirst;
    }
  }
  return inversions;
}

//! [l,r)
int mergeSortCountInversionsImpl(vector<int>& a, vector<int>& aux, int l, int r) {
  int res{0};
  if(r-l > 1) {
    const int m = l + (r-l) / 2;
    //! as mentioned in the Stepanov lecture we deal with 3 types of inversions:
    //! inversions in the left array  |_x___x__|_______|
    res += mergeSortCountInversionsImpl(a,aux,l,m);
    //! inversions in the right array |_______|X_XXX_X|
    res += mergeSortCountInversionsImpl(a,aux,m,r);
    //! and inversions between left & right |_x____xx|xx___x_|
    res += combineCountInversions(a,aux,l,m,r);
  }
  return res;
}

size_t mergeSortCountInversions(vector<int>& a) {
  vector<int> aux(a);
  return mergeSortCountInversionsImpl(a,aux,0, a.size());
}


int main() {
  const int n = 10'000;
  {
    vector<int> a0(n);
    iota(begin(a0), end(a0), 0);
    mergeSort(a0);
    assert(is_sorted(begin(a0), end(a0)));

    vector<int> a1(n);
    iota(begin(a1), end(a1), 0);
    reverse(begin(a1), end(a1));
    vector<int> a2(a1);
    sort(begin(a2), end(a2));
    mergeSort(a1);
    assert(a1 == a2);

    //! Random test
    random_device rd;
    mt19937 engine(rd());
    uniform_int_distribution<int> dist(0, n);
    vector<int> a3(n);
    generate(begin(a3), end(a3), [&]() { return dist(engine); });
    vector<int> a4(a3);
    sort(begin(a3), end(a3));
    mergeSort(a4);
    assert(a4 == a3);

    //! all elements equal
    vector<int> a5 = {5, 5, 5, 5, 5, 5};
    vector<int> a6(a5);
    mergeSort(a5);
    sort(begin(a6), end(a6));
    assert(a5 == a6);
  }


  {
    vector<int> a0(n);
    iota(begin(a0), end(a0), 0);
    mergeSortIterative(a0);
    assert(is_sorted(begin(a0), end(a0)));

    vector<int> a1(n);
    iota(begin(a1), end(a1), 0);
    reverse(begin(a1), end(a1));
    vector<int> a2(a1);
    sort(begin(a2), end(a2));
    mergeSortIterative(a1);
    assert(a1 == a2);

    //! Random test
    random_device rd;
    mt19937 engine(rd());
    uniform_int_distribution<int> dist(0, n);
    vector<int> a3(n);
    generate(begin(a3), end(a3), [&]() { return dist(engine); });
    vector<int> a4(a3);
    sort(begin(a3), end(a3));
    mergeSortIterative(a4);
    assert(a4 == a3);

    //! all elements equal
    vector<int> a5 = {5, 5, 5, 5, 5, 5};
    vector<int> a6(a5);
    mergeSortIterative(a5);
    sort(begin(a6), end(a6));
    assert(a5 == a6);
  }

  {
    vector<int> a = {1,2,6,3,4,5};
    assert(3 == mergeSortCountInversions(a));
    vector<int> a0 = {1,2,3,4,5,6};
    assert(0 == mergeSortCountInversions(a0));
    vector<int> a1 = {6,5,4,3,2,1};
    assert(15 == mergeSortCountInversions(a1));
  }
  return 0;
}