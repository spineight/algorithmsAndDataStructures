#include <bits/stdc++.h>
using namespace std;

struct SudokuSolver {
  vector<vector<int>>& _mat;
  set<pair<int,int>> _unassignedCells;
  explicit SudokuSolver(vector<vector<int>>& mat) : _mat(mat) {
    for(int r = 0; r < 9; ++r)
      for(int c = 0; c < 9; ++c) _unassignedCells.emplace(r,c);
  }

  void showMatrix() {
    for(int r = 0; r < 9; ++r) {
      for (int c = 0; c < 9; ++c) {
        cout << setw(3) << _mat[r][c];
      }
      cout << '\n';
    }
    cout << '\n';
    this_thread::sleep_for(chrono::microseconds (10));
  }
  optional<pair<int,int>> getUnassignedCells() {
    if(!_unassignedCells.empty())
      return *begin(_unassignedCells);
    return {};
  }
  void assignCell(int r, int c, int val) {
    _mat[r][c] = val;
    _unassignedCells.erase({r,c});
  }
  void unassignCell(int r, int c) {
    _mat[r][c] = 0;
    _unassignedCells.emplace(r,c);
  }
  bool isSafeAssignment(int r, int c, int val) {
    // horizontal
    for(int cr = 0; cr < r; ++cr)
      if(_mat[cr][c] == val) return false;
    for(int cr = r + 1; cr < 9; ++cr)
      if(_mat[cr][c] == val) return false;
    // vertical
    for(int cc = 0; cc < c; ++cc)
      if(_mat[r][cc] == val) return false;
    for(int cc = c + 1; cc < 9; ++cc)
      if(_mat[r][cc] == val) return false;

    // 3 x 3 matrix
    // 0,0 0,1 0,2 | 0,3 0,4 0,5 | 0,6 0,7 0,8
    // 1,0
    // 2,0
    //--------------
    // 3,0 3,1 3,2 | 3,3 3,4 3,5 | 3,6 3,7 3,8
    // r0 = r / 3 * 3
    // c0 = c / 3 * 3
    // r1 = r0 + 3
    // c1 = c0 + 3
    for(int cr = r / 3 * 3; cr < r / 3 * 3 + 3; ++cr) {
      for(int cc = c /3 * 3; cc < c /3*3 + 3; ++cc) {
        if(cr != r && cc != c && _mat[cr][cc] == val) return false;
      }
    }
    return true;
  }
  bool solve() {
    auto p = getUnassignedCells();
    if(!p) return true;
    auto [r,c] = p.value();
    for(int val = 1; val <=9; ++val) {
      if(isSafeAssignment(r,c, val)) {
        assignCell(r,c,val);
        showMatrix();
        if (solve()) return true;
        unassignCell(r,c);
        showMatrix();
      }
    }
    return false;
  }
};

int main() {
  vector<vector<int>> mat = {{3,0,6, 5,0,8, 4,0,0},
                             {5,2,0, 0,0,0, 0,0,0},
                             {0,8,7, 0,0,0, 0,3,1},

                             {0,0,3, 0,1,0, 0,8,0},
                             {9,0,0, 8,6,3, 0,0,5},
                             {0,5,0, 0,9,0, 6,0,0},

                             {1,3,0, 0,0,0, 2,5,0},
                             {0,0,0, 0,0,0, 0,7,4},
                             {0,0,5, 2,0,6, 3,0,0}};
  SudokuSolver solver(mat);
  solver.solve();
  return 0;
}