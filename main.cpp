#include <bits/stdc++.h>
//using namespace std;


template<typename KeyT, typename ValT>
class LRU_cache {
  const size_t sz{0};
  std::list< std::pair<KeyT, ValT> > list;
  std::unordered_map<KeyT, typename decltype(list)::iterator> keyToListIterator;

public:
  LRU_cache(size_t sz) : sz(sz) {}


  void Add(KeyT key, ValT val) {
    list.emplace_back(key, val);;
    auto addedElemIt = std::prev(list.end());
    keyToListIterator[key] = addedElemIt;

    if(list.size() > sz) {
      const auto [evictElemKey, _] = list.front();
      Remove(evictElemKey);
    }
  }

  std::optional<ValT> Get(KeyT key) {
    if(list.back().first == key)
      return list.back().second;

    auto it = keyToListIterator.find(key);
    if(it!= end(keyToListIterator)) {
      auto [key_, val_] = *(*it).second;
      //! Make LRU
      Remove(key_);
      Add(key_,val_);
      return std::optional(val_);
    }
    return std::nullopt;
  }

private:
  void Remove(KeyT key) {
    auto it = keyToListIterator.find(key);
    keyToListIterator.erase(it);
    list.erase(it->second);
  }
};

int main() {
  LRU_cache<int,int> lru(4);

  for(size_t i = 0; i < 10; ++i)
    lru.Add(i,i);

  for(size_t i = 0; i < 10; ++i) {
    auto tmp = lru.Get(i);
    if (tmp) std::cout << *tmp << '\n';
  }

  return 0;
}