#include <bits/stdc++.h>

using namespace std;

struct QueensSolver {
  QueensSolver(int n) : board(n, vector<char>(n, '*')) {}

  vector<vector<char>> board;

  void showBoard() {
    const int n = board.size();
    for (int r = 0; r < n; ++r) {
      for (int c = 0; c < n; ++c) {
        cout << setw(3) << board[r][c];
      }
      cout << '\n';
    }
    cout << '\n';
  }

  bool isSafe(int r, int c) {
    const int n = board.size();
    //! we are checking only cells to the left & bottom from the current cell,
    //! because all others we have not visited and hence we know that there are no 'Q' at all
    // horizontal
    for (int cc = 0; cc < c; ++cc) if (board[r][cc] == 'Q') return false;

    // vertical
    for (int cr = 0; cr < r; ++cr) if (board[cr][c] == 'Q') return false;

    // diagonal left top -> right bottom
    for (int cr = r - 1, cc = c - 1; cr >= 0 && cc >= 0; --cr, --cc)
      if (board[cr][cc] == 'Q')
        return false;
    for(int cr = r + 1, cc = c - 1; cr < n && cc >= 0; ++cr, --cc)
      if (board[cr][cc] == 'Q')
        return false;

    return true;
  }

  void placeQueen(int r, int c) {
    board[r][c] = 'Q';
  }

  void removeQueen(int r, int c) {
    board[r][c] = '*';
  }

  bool solve(int c) {
    showBoard();
    this_thread::sleep_for(chrono::milliseconds(1000));
    if (c >= board.size()) return true; // base case

    for (int r = 0; r < board.size(); ++r) {
      if (isSafe(r, c)) {
        placeQueen(r, c);
        if (solve(c + 1)) return true; // try an option and delegate the simpler tasks to check

        removeQueen(r, c); // if this option no simpler tasks succeeded, undo it and try another one
        showBoard();
      }
    }
    return false; // if non of options worked we get here, we backing up to the column behind us
  }

  void solve() {
    solve(0);
  }
};

int main() {
  QueensSolver solver(4);
  solver.solve();
  return 0;
}