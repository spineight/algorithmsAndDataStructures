// http://www.cs.ukzn.ac.za/~hughm/os/notes/ncurses.html
#include <curses.h>
#include <cmath>
#include <thread>
#include <bits/stdc++.h>
#include <chrono>

using namespace std;

unsigned rowsCnt, colsCnt;        /* to store the number of rows and the number of colums of the screen */

void DrawTriangle(int x, int y, int w) {
  const int halfW = w / 2;
  const int height = (int) (w * sqrt(3) / 2);

  // x,y - left corner
  // x + halfw, y - height - top
  // x + w, y - right
  // x+halfW/,y-halfH
  // height = a sqrt(3) / 2  (https://www.cuemath.com/geometry/height-of-equilateral-triangle/)

  // left -> top edge
  for(int r = y, c = x; r >= y - height && c <= x + halfW; --r, ++c)
    mvaddch(r, c, '-');
  // top -> right edge
  for(int r = y - height, c = x + halfW; r <= y && c <= x + w; ++r, ++c)
    mvaddch(r, c, '+');
  // left -> right edge
  for(int c = x; c <= x + w; ++c)
    mvaddch(y, c, '=');
  std::this_thread::sleep_for(std::chrono::milliseconds {10});
  refresh();
}

void DrawFractal(int x, int y, int w) {
//  cout << x << "," << y << "," << w << '\n';
  DrawTriangle(x, y, w);
  if (w < 1) return;
  const int halfW = w / 2;
  const int height = (int) (w * sqrt(3) / 2);
  DrawFractal(x, y, halfW); // left
  DrawFractal(x + halfW / 2, y - height / 2, halfW); // top
  DrawFractal(x + halfW, y, halfW); // right
}



int main(int argc, char *argv[]) {
  //! http://www.cs.ukzn.ac.za/~hughm/os/notes/ncurses.html
  //  The very first thing to do: Before you use any other curses routines, the initscr() routine must be called first.
  initscr();  // Init and go to ncurses mode

  getmaxyx(stdscr, rowsCnt, colsCnt);    /* get the number of rows and columns */
  // One-character-a-time.
  // To disable the buffering of typed characters by the TTY driver and get a character-at-a-time input, you need to call
  cbreak();
  // No echo. To suppress the automatic echoing of typed characters, you need to call
  noecho();

  DrawFractal(0,rowsCnt-1, rowsCnt-1);
  return 0;
}