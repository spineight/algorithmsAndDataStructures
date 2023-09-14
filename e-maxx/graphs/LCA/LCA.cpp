//! https://informatics.msk.ru/mod/statements/view.php?id=26138#1
/*
 Задача №111796. LCA

Задано подвешенное дерево, содержащее n (1≤n≤100000) вершин, пронумерованных от 0 до n-1.
 Требуется ответить на m (1≤m≤100000) запросов о наименьшем общем предке для пары вершин.

Запросы генерируются следующим образом.
 Заданы числа a1, a2 и числа x, y и z. Числа a3, ..., a2m генерируются следующим образом:
 ai=(x·ai-2+y·ai-1+z)mod:n. Первый запрос имеет вид (a1,a2). Если ответ на (i-1)-й запрос равен v,
 то i-й запрос имеет вид ((a2i-1+v)mod:n,a2i).

Входные данные

Первая строка содержит два числа: n и m. Корень дерева имеет номер 0.
 Вторая строка содержит n-1 целых чисел, i-е из этих чисел равно номеру родителя вершины i.
 Третья строка содержит число содержит два целых числа в диапазоне от 0 до n-1: a1 и a2.
 Четвертая строка содержит три целых числа: x, y и z, эти числа неотрицательны и не превосходят 109.

Выходные данные

Выведите в выходной файл сумму номеров вершин — ответов на все запросы.

Примеры
Входные данные

3 2
0 1
2 1
1 1 0

Выходные данные

2

 */

//! https://www.eolymp.com/ru/problems/2318
/*
 Задано подвешенное дерево, содержащее n (1 ≤ n ≤ 100) вершин, пронумерованных от 0 до n - 1.
 Требуется ответить на m (1 ≤ m ≤ 100) запросов о наименьшем общем предке для пары вершин.

Запросы генерируются следующим образом. Заданы числа a[1], a[2] и числа x, y и z.
 Числа a[3], ..., a[2m] генерируются следующим образом: a[i] = (x · a[i-2] + y · a[i-1] + z) mod n.
 Первый запрос имеет вид <a[1], a[2]>.
 Если ответ на (i - 1)-ый запрос равен v, то i-ый запрос имеет вид <(a[2i-1] + v) mod n, a[2i]>.

 Входные данные

Первая строка содержит два числа n и m.
 Корень дерева имеет номер 0.
 Вторая строка содержит n - 1 целых чисел, i-ое из этих чисел равно номеру родителя вершины i.
 Третья строка содержит два целых числа в диапазоне от 0 до n - 1: a[1] и a[2].
 Четвертая строка содержит три целых числа: x, y и z, эти числа неотрицательны и не превосходят 10^9.

 Выходные данные

Выведите сумму номеров вершин - ответов на все запросы.

 Пример
Входные данные #1

3 2
0 1
2 1
1 1 0

Выходные данные #1

2

 */
#include <bits/stdc++.h>

using namespace std;
struct LCA {
  uint32_t timer{0};
  vector<uint32_t> timeIn, timeOut;
  vector<vector<uint32_t>> ancestor;
  unordered_map<uint32_t , vector<uint32_t>> tree;
  int maxK{1};
  void DFS(uint32_t u, uint32_t parent = 0) {
    timeIn[u] = timer++;
    ancestor[u][0] = parent;
    for(int k = 1; k <= maxK; ++k)
      ancestor[u][k] = ancestor[ancestor[u][k-1]][k-1];
    for(auto v : tree[u]) {
      if(!timeIn[v]) {
        DFS(v,u);
      }
    }
    timeOut[u] = timer++;
  }
  bool isAncestor(uint32_t u, uint32_t v) {
    return timeIn[u] <= timeIn[v] && timeOut[v] <= timeOut[u];
  }
  uint32_t lca(uint32_t u,uint32_t v) {
    if(isAncestor(u,v)) return u;
    if(isAncestor(v,u)) return v;

    for(auto k = maxK; k >= 0; --k) {
      if(!isAncestor(ancestor[u][k], v)) {
        u = ancestor[u][k];
      }
    }
    return ancestor[u][0];
  }
  void solve() {
    uint32_t n,m;
    cin >> n >> m;

    uint32_t i = 1;
    for(uint32_t j = 0; j < n - 1; ++j) {
      int v;
      cin >> v;
      tree[v].push_back(i);
      ++i;
    }
    size_t a1,a2;
    cin >> a1 >> a2;
    size_t x,y,z;
    cin >> x >> y >> z;

    size_t res{0};
    size_t v{0};

    while((1 << maxK) <= n) ++maxK; // NB!!! NOT while(maxK < n) maxK *= 2;
    ancestor.assign(n, vector<uint32_t>(maxK+1,0));
    timeIn.resize(n,0);
    timeOut.resize(n,0);

    DFS(0);

    while(m--) {
      v = lca((a1+v) % n,a2);
      res += v;
      a1 = (x*a1 + y*a2 +z) % n;
      a2 = (x*a2 + y*a1 +z) % n;
    }
    cout << res << '\n';
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cout.tie(0);

  LCA lca;
  lca.solve();
  return 0;
}