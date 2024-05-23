#include <iostream>
#include <vector>
#include <concepts>
#include <functional>

//! https://stackoverflow.com/questions/60449592/how-do-you-define-a-c-concept-for-the-standard-library-containers
template <class ContainerType>
concept Container = requires(ContainerType a, const ContainerType b)
{
  requires std::regular<ContainerType>;
  requires std::swappable<ContainerType>;
  requires std::destructible<typename ContainerType::value_type>;
  requires std::same_as<typename ContainerType::reference, typename ContainerType::value_type &>;
  requires std::same_as<typename ContainerType::const_reference, const typename ContainerType::value_type &>;
  requires std::forward_iterator<typename ContainerType::iterator>;
  requires std::forward_iterator<typename ContainerType::const_iterator>;
  requires std::signed_integral<typename ContainerType::difference_type>;
  requires std::same_as<typename ContainerType::difference_type, typename std::iterator_traits<typename
  ContainerType::iterator>::difference_type>;
  requires std::same_as<typename ContainerType::difference_type, typename std::iterator_traits<typename
  ContainerType::const_iterator>::difference_type>;
  { a.begin() } -> std::same_as<typename ContainerType::iterator>;
  { a.end() } -> std::same_as<typename ContainerType::iterator>;
  { b.begin() } -> std::same_as<typename ContainerType::const_iterator>;
  { b.end() } -> std::same_as<typename ContainerType::const_iterator>;
  { a.cbegin() } -> std::same_as<typename ContainerType::const_iterator>;
  { a.cend() } -> std::same_as<typename ContainerType::const_iterator>;
  { a.size() } -> std::same_as<typename ContainerType::size_type>;
  { a.max_size() } -> std::same_as<typename ContainerType::size_type>;
  { a.empty() } -> std::same_as<bool>;
};

//! Priority queue is adapter!!!
// https://stackoverflow.com/questions/9958180/advantages-of-setting-priority-queue-container

namespace BinaryHeapDetails{
  //! O(logn)
  //! We need comparator for heap sort (as we use extractMax for it, instead of extractMin)
  template<class ContainerT, class Comparator = std::less<>>
          requires Container<ContainerT> && std::random_access_iterator<typename ContainerT::iterator>
  void siftUp(ContainerT& container, int i) {
    Comparator cmp;
    while(i > 1) {
      if(cmp(container[i], container[i/2])) {
        std::swap(container[i] , container[i/2] );
        i /= 2;
      } else {
        break;
      }
    }
  }
  //! O(logn)
  //! Works with 1-idx container
  template<class ContainerT, class Comparator = std::less<>>
  requires Container<ContainerT> && std::random_access_iterator<typename ContainerT::iterator>
  void siftDown(ContainerT& container, int i) {
    Comparator cmp;
    const size_t n = container.size();
    // Stankevich idea: min of 3
    int minIdx = i;
    while(2*i < n) {
      if (cmp(container[2 * i] , container[i])) minIdx = 2 * i;
      if (2 * i + 1 <= n && cmp(container[2 * i + 1] , container[minIdx]))
        minIdx = 2 * i + 1;
      if(i == minIdx) break;
      std::swap(container[i], container[minIdx]);
      i = minIdx;
    }
  }

  template<class ContainerT>
  requires Container<ContainerT> && std::random_access_iterator<typename ContainerT::iterator>
  void extractMax(ContainerT& container, int n) {
    std::swap(container.front(), container[n]);
    siftDown<ContainerT, std::greater<typename ContainerT::value_type>>(container, 1);
  }
}



//! https://en.cppreference.com/w/cpp/algorithm/make_heap
//! creates heap from the vector
//! O(n)
template<class ContainerT, class Comparator = std::less<>>
requires Container<ContainerT> && std::random_access_iterator<typename ContainerT::iterator>
void make_heap( ContainerT& container ) {
  const int n = container.size();
  for(int i = n / 2; i >= 1; --i) {
    BinaryHeapDetails::siftDown<ContainerT, Comparator>(container, i);
  }
}

template<class ContainerT, class Comparator = std::greater<>>
requires Container<ContainerT> && std::random_access_iterator<typename ContainerT::iterator>
void heap_sort(ContainerT& container) {
  make_heap<ContainerT, Comparator>(container);
  int n = container.size(); // 1-idx array
  while(n > 0) {
      BinaryHeapDetails::extractMax(container,--n);
  }
}

//! Binary heap build on 1-idx array
//! Interface Based on https://en.cppreference.com/w/cpp/container/priority_queue
template<typename ValT, typename ContainerT = std::vector<ValT>, typename CompareFunctor = std::less<ValT>>
struct BinaryHeap {
  ContainerT container{1};
  int n{0};

  void push(int val) {
    container.push_back(val);
    container[++n] = val;
    BinaryHeapDetails::siftUp(container, n);
  }

  //! O(logn) getMin
  int top() {
    return container[1];
  }
  //! O(logn) extractMin
  void pop() {
    std::swap(container[1], container[n--]);
    BinaryHeapDetails::siftDown(container, 1);
  }
  //! idx - index of the element in 1-idx array
  //! O(logn)
  void decreaseKey(int idx, int delta) {
    container[idx] -= delta;
    BinaryHeapDetails::siftUp(container, idx);
  }
  void inreaseKey(int idx, int delta) {
    container[idx] += delta;
    BinaryHeapDetails::siftDown(container, idx);
  }
  bool empty() const {
    return 0 == n;
  }
};

using namespace std;

int main() {
  BinaryHeap<int> bh;
  for(int i = 10; i >= 0; --i)
    bh.push(i);
  while(!bh.empty()) {
    cout << bh.top() << " ";
    bh.pop();
  }
  cout << '\n' << '\n';

  std::vector<int> a0 = {6,5,4,3,2,1};
  make_heap(a0);
  for(auto v : a0) cout << v << " ";
  cout << '\n';


  cout << "bh1.sort()\n";
  vector<int> a1 = {6,5,4,3,2,1};
  heap_sort(a1);
  for(auto v : a1) cout << v << " ";
  cout << '\n';
  return 0;
}