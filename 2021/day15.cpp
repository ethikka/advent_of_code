#include <sstream>
#include <vector>
#include <map>
#include <queue>
#include <cmath>
#include <algorithm>
#include "../common/lib.h"

typedef std::pair<int,int> point;
std::map<point, int> dm, cdm;

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  char c;
  int x(1), y(1);
  while (std::cin >> std::noskipws >> c) 
    switch(c) {
      case '\n': x = 1; y++; break; 
      default: dm[{x++, y}] = (int)c-48;
    }
  x--;
  for (int xm = 0; xm < 5; xm++) 
    for (int ym = 0; ym < 5; ym++) 
      for (int xi = 1; xi <= x; xi++) 
        for (int yi = 1; yi <= y; yi++) {
          int nr = ((dm[{xi,yi}])+xm+ym);
          if (nr > 9) nr -=9;
          dm[{(xm*x)+xi, (ym*y)+yi}] = nr;
        }

  int x2(x*5), y2(y*5);
  auto Compare = [](point &a, point &b) { return (cdm[a] >= cdm[b]); };
  std::priority_queue<point, std::vector<point>, decltype(Compare)> q(Compare);
  q.push({1,1});
  while (!q.empty()) {
    auto w = q.top();
    q.pop();
    for (point p: std::vector<point> {{-1,0},{0,-1},{0,1},{1,0}}) {
      point np = {w.first+p.first, w.second+p.second};
      if (!(np.first < 1 || np.first > x2 || np.second < 1 || np.second > y2) && (cdm[np] > (cdm[w]+dm[np]) || cdm[np] == 0)) {
        cdm[np] = cdm[w]+dm[np];
        q.push(np);
      }
    }
  }
  res.first = cdm[{x,y}];
  res.second = cdm[{x2,y2}];
  return res;
}