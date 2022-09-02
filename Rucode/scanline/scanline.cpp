//! /run/media/oleg/TOSHIBA EXT/RUCODE/ScanLineNevstruev.mp4
//! 24:50 - Implementations

#include <bits/stdc++.h>
using namespace std;



/*
 * Find intervals where number of intersected segments is maximized
 * and return their cnt and length of these intervals
 */
pair<int,int> scanLineTask0(const vector<pair<int,int>>& segments) {
  enum EventType {open = 1, close = -1};

  struct Event {
    int x;
    EventType type;
    Event(int x, EventType type) : x(x), type(type) {}

    bool operator <(const Event& e) const {
      if(x != e.x) return x < e.x;
      return type > e.type;
    }
  };

  vector<Event> events;

  for(const auto& [l,r] : segments) {
    events.emplace_back(l,EventType::open);
    events.emplace_back(r,EventType::close);
  }

  sort(begin(events), end(events));

  int bestCnt{0};
  int balance{0};
  int len{0};

  for(int i = 0; i < size(events); ++i) {
    const auto event = events[i];
    if(event.type == EventType::close) {
      if(bestCnt < balance) {
        bestCnt = balance;
        len = 0;
      }
      if(balance == bestCnt) {
        len += event.x - events[i-1].x;
      }
    }
    balance += event.type;
  }

  return {bestCnt,len};
}

//! return total len of covered interval
int scanLineTask1(const vector<pair<int,int>>& segments) {
  enum EventType {open = 1, close = -1};

  struct Event {
    int x;
    EventType type;
    Event(int x, EventType type) : x(x), type(type) {}

    bool operator <(const Event& e) const {
      if(x != e.x) return x < e.x;
      return type > e.type;
    }
  };

  vector<Event> events;

  for(const auto& [l,r] : segments) {
    events.emplace_back(l,EventType::open);
    events.emplace_back(r,EventType::close);
  }

  sort(begin(events), end(events));

  int balance{0};
  int length{0};
  int left{0};
  for(int i = 0; i < size(events); ++i) {
    const auto event = events[i];
    if(balance == 0 && event.type == EventType::open)
      left = event.x;
    if(balance == 1 && event.type == EventType::close)
      length += (event.x - left);
    balance += event.type;
  }
  return length;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cout.setf(ios::fixed);
  cout.precision(10);

  auto [cnt, len] = scanLineTask0({{1,2}, {3,4}, {5,6}, {7,8}});
  cout << cnt << "," << len << '\n';

  tie(cnt, len) = scanLineTask0({{1,3}, {2,4}, {3,6}, {5,8}});
  cout << cnt << "," << len << '\n';

  std::cout << scanLineTask1({ {1,4},{2,7}, {3 ,8}, {4,9} }) << '\n';
  return 0;
}