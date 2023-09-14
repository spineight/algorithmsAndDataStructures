//! https://habr.com/ru/articles/722292/
//! https://www.eolymp.com/ru/problems/3680
//! http://acm.math.spbu.ru/~sk1/mm/lections/kharkiv/lection-2013.pdf
//! https://ru.algorithmica.org/cs/hashing/isomorphism/


/*
 https://codeforces.com/blog/entry/113465

 Рекомендую также лекцию по изоморфизму деревьев от Сергея Копелиовича
 в сборнике с лекциями и разборами «Зимняя школа по программированию 2013», страница 264.
 Там есть крутые задачи, крутые хеш-функции и крутые идеи.

  https://codeforces.com/blog/entry/19068
  https://codeforces.com/blog/entry/19068?locale=ru#comment-239863
  https://codeforces.com/blog/entry/19068?locale=ru#comment-240121
  https://codeforces.com/blog/entry/19068?locale=ru#comment-240173
 */

// /home/oleg/github/algorithmsAndDataStructures/WinterSchool/lectures/WPS2013.pdf


// https://cses.fi/problemset/task/1700/

// ? https://codeforces.com/contest/1800/problem/G

// ? https://open.kattis.com/problems/twochartsbecomeone

#include <bits/stdc++.h>

using namespace std;

//! https://cses.fi/problemset/task/1700/
struct SolveTreeIsomorphismI {
  int classCnt{0};
  map<vector<int>, int/*class*/> _class;
  map<int,int> vertexClass;
  unordered_map<int, bool> visited;
  void DFS(unordered_map<int, vector<int>>& tree, int v) {
    visited[v] = true;
    vector<int> children;
    for(auto u : tree[v]) {
      if(!visited[u]) {
        DFS(tree, u);
        children.push_back(vertexClass[u]);
      }
    }
    sort(begin(children), end(children));
    auto it = _class.find(children);
    if(it == end(_class)) {
      _class[children] = classCnt++;
    }
    vertexClass[v] = _class[children];
  }
  void solve() {
    int t;
    cin >> t;
    while (t--) {
      //! reset state for each test case
      classCnt = 0;
      _class.clear();
      visited.clear();
      vertexClass.clear();

      int n;
      cin >> n;
      unordered_map<int, vector<int>> tree0, tree1;
      for (int i = 0; i < n-1; ++i) {
        int u, v;
        cin >> u >> v;
        tree0[u].push_back(v);
        tree0[v].push_back(u);
      }
      for (int i = 0; i < n-1; ++i) {
        int u, v;
        cin >> u >> v;
        tree1[u].push_back(v);
        tree1[v].push_back(u);
      }
      DFS(tree0,1);
      auto classTree0 = vertexClass[1];

      visited.clear();
      vertexClass.clear();
      DFS(tree1,1);
      auto classTree1 = vertexClass[1];
      if(classTree0 == classTree1) {
        cout << "YES\n";
      } else {
        cout << "NO\n";
      }
    }

  }
};


int main() {
  SolveTreeIsomorphismI sti;
  sti.solve();
  return 0;
}