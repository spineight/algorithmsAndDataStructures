#include <bits/stdc++.h>

using namespace std;

//! 0-idx array

template<typename ValT = int, typename Comparator = less<ValT>>
void siftDown(vector<ValT>& a, int n, int i) {
  Comparator cmp;
  while(2*i+1 < n) { // exist left child
    // min/max from 3
    int j = i;
    if(cmp(a[2*i+1], a[i])) j = 2*i+1;
    if(2*i+2 < n && cmp(a[2*i+2], a[j])) // exist right child
      j = 2*i+2;
    if(i == j) break;
    swap(a[i], a[j]);
    i = j;
  }
}

template<typename ValT = int, typename Comparator = less<ValT>>
void siftUp(vector<ValT>& a, int i) {
  Comparator cmp;
  while(i > 0) { // exists parent node
    if(cmp(a[i], a[i/2])) {
      swap(a[i], a[i/2]);
      i /= 2;
    }
  }
}



template<typename ValT = int, typename Comparator = less<ValT>>
void heapify(vector<ValT>& a) {
  const int n = a.size();
  //! Кол-во элементов на уровнях:
  // 1, 2, 4, 8, 16
  // Заметим, что на последнем уровне(16) на 1 элемент больше чем на всех предудущих (15)
  // на последнем уровне у нас листья, их нет смысла просеивать вниз (так как ниже уже некуда)
  // Поэтому мы идем от n/2 так как половину всех вершин составляют листья
  for(int i = n / 2; i >= 0; --i) {
    siftDown<ValT, Comparator>(a, n, i);
  }
}

void print(auto& a) {
  for(auto v : a) cout << v << " ";
  cout << '\n';
}

template<typename ValT>
void heapSort(vector<ValT>& a) {
  heapify<ValT, greater<ValT>>(a);
  const int n = a.size();
  for(int i = n-1; i >=0; --i) {
    ValT tmp = a[0];
    swap(a[0], a[i]);
    siftDown<ValT, greater<ValT>>(a,i,0);
    a[i] = tmp;
  }
}




int main() {
  vector<int> b = {6,5,4,3,2,1};
  heapify(b);
  heapSort(b);

  const int n = 10'000;
  vector<int> a0(n);
  iota(begin(a0), end(a0), 0);
  heapSort(a0);
  assert(is_sorted(begin(a0), end(a0)));

  vector<int> a1(n);
  iota(begin(a1), end(a1),0);
  reverse(begin(a1), end(a1));
  vector<int> a2(a1);
  sort(begin(a2), end(a2));
  heapSort(a1);
  assert(a1 == a2);

  //! Random test
  random_device rd;
  mt19937 engine(rd());
  uniform_int_distribution<int> dist(0,n);
  vector<int> a3(n);
  generate(begin(a3), end(a3), [&](){return dist(engine);});
  vector<int> a4(a3);
  sort(begin(a3), end(a3));
  heapSort(a4);
  assert(a4 == a3);


  //! all elements equal
  vector<int> a5 = {5,5,5,5,5,5};
  vector<int> a6(a5);
  heapSort(a5);
  sort(begin(a6), end(a6));
  assert(a5 == a6);
  return 0;
}