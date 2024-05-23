//! https://app.codility.com/programmers/lessons/6-sorting/number_of_disc_intersections/

//! see codility/sorting/numberOfDiscIntersections.odt

#include <algorithm>
int solution(vector<int> &A) {
  enum Event{START, END};
  vector<pair<long long, Event>> events;
  for(size_t center = 0; center < A.size(); ++center) {
    events.emplace_back(center-A[center], START);
    events.emplace_back(center+A[center], END);
  }
  sort(begin(events), end(events));
  int balance{0};
  size_t cnt{0};
  for(const auto& e: events) {
    if(START == e.second) {
      cnt += balance;
      ++balance;
      if(cnt > 10'000'000) return -1;
    } else -- balance;
  }
  return cnt;
}

//! 14/11/2023
int solution(vector<int> &A) {
  vector<pair<int64_t,int/*open/closed*/>> events;
  enum EventType{closed = 1, opened = -1}    ;
  const int n = A.size();
  for(int i = 0; i < n; ++i) {
    events.emplace_back(i-(int64_t)A[i], opened);
    events.emplace_back(i+(int64_t)A[i], closed);
  }
  sort(begin(events), end(events));
  int balance{0};
  int res{0};
  for(const auto [x, e] : events) {
    balance += e;
    if(closed == e) {
      res += abs(balance);
      if( res > 10'000'000) return -1;
    }
  }
  return res;
}