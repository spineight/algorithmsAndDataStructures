//! https://informatics.msk.ru/mod/statements/view3.php?id=46540&chapterid=114108#1

//! https://codeforces.com/blog/entry/17974

/*
Диаметром дерева называется максимальное из всех расстояний между парой его вершин.

Дано дерево, содержащее N вершин. Требуется вычислить его диаметр.

Входные данные

Первая строка содержит натуральное число N
( 1≤N≤2⋅10^5 ).

В следующих N−1 строках записаны рёбра дерева.
В каждой строке записана пара чисел a и b, разделённых пробелом (1≤a,b≤N) — ребро между вершинами a и b.

Выходные данные

Программа должна вывести одно число — диаметр дерева.

Примеры
Входные данные

5
1 2
1 3
3 4
3 5

Выходные данные

3
 */

#include <bits/stdc++.h>

using namespace std;

namespace ver0 {
  //! 09/11/2023
  //! Based on my idea how to find distance between 2 nodes and ideas from the lecture how to find diameter
  struct TreeDiameter {
    unordered_map<int, vector<int>> tree;
    unordered_map<int, int> distTo;
    int maxDist{-1};
    int farestNodeIdx{-1};

    void DFS_farestNodeImpl(int u, int dist) {
      if (!distTo.contains(u)) {
        distTo[u] = dist;
        if (maxDist < dist) {
          maxDist = dist;
          farestNodeIdx = u;
        }
        for (auto v: tree[u]) {
          if (!distTo.contains(v)) DFS_farestNodeImpl(v, dist + 1);
        }
      }
    }

    int DFS_farestNode(int u) {
      farestNodeIdx = -1;
      maxDist = -1;
      distTo.clear();
      DFS_farestNodeImpl(u, 0);
      return farestNodeIdx;
    }

    int dist(int u, int v) {
      queue<int> uBFS, vBFS;
      unordered_map<int, int> uDistTo, vDistTo;
      uBFS.push(u);
      vBFS.push(v);
      uDistTo[u] = 0;
      vDistTo[v] = 0;

      while (!uBFS.empty() && !vBFS.empty()) {
        //! z
        auto z0 = uBFS.front();
        uBFS.pop();

        for (auto z: tree[z0]) {
          if (!uDistTo.contains(z)) {
            uDistTo[z] = uDistTo[z0] + 1;
            uBFS.push(z);
          }
        }

        //! x
        auto x0 = vBFS.front();
        vBFS.pop();

        for (auto x: tree[x0]) {
          if (!vDistTo.contains(x)) {
            vDistTo[x] = vDistTo[x0] + 1;
            vBFS.push(x);
          }
        }

        if (vDistTo.contains(z0)) {
          return uDistTo[z0] + vDistTo[z0];
        }
      }
      return -1;
    }

    int solve() {
      int n;
      cin >> n;
      --n;

      while (n--) {
        int u, v;
        cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
      }

      int x = DFS_farestNode(1);
      int z = DFS_farestNode(x);

      return dist(x, z);
    }
  };
}

int main() {
  ver0::TreeDiameter td;
  cout << td.solve() << '\n';
  return 0;
}