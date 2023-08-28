#include <bits/stdc++.h>
using namespace std;


template<size_t SZ>
struct MinHeap {
  int a[SZ+1]; // 1-indexed array
  int n{0};
  void push(int val) {
    ++n;
    a[n] = val;
    swim(n);
  }
  void pop() {
    a[1] = a[n];
    --n;
    sink(1);
  }
  int minElement() {
    return a[1];
  }
  bool empty() {
    return 0==n;
  }
  void sink(int idx) {
    const int leftChild = idx * 2;
    const int rightChild = idx*2 + 1;
    if(leftChild <= n && a[idx] > a[leftChild]) {
      swap(a[idx], a[leftChild]);
      sink(leftChild);
    }
    if(rightChild <= n && a[idx] > a[rightChild]) {
      swap(a[idx], a[rightChild]);
      sink(rightChild);
    }
  }
  void swim(int idx) {
    if(idx > 1) {
      int parent = idx / 2;
      if(a[parent] > a[idx]) {
        swap(a[parent], a[idx]);
        swim(parent);
      }
    }
  }
  void heapify(const vector<int>& source) {
    assert(SZ >= source.size());
    std::copy(begin(source), end(source), &a[1]);
    n = source.size();
    for(size_t i = 1; i <= source.size(); ++i)
      swim(i);
  }
};

int main() {
  MinHeap<10> minHeap;
  vector<int> a = {3,2,1,4,6,5,7,7,8,9};
  for(auto v : a) minHeap.push(v);

  while(!minHeap.empty()) {
    std::cout << minHeap.minElement() << '\n';
    minHeap.pop();
  }

  MinHeap<10> minHeap1;
  minHeap1.heapify(a);

  while(!minHeap1.empty()) {
    std::cout << minHeap1.minElement() << '\n';
    minHeap1.pop();
  }
  return 0;
}