#include <sstream>
#include <vector>
#include <map>
#include <queue>
#include "../common/lib.h"

typedef std::pair<int,int> point;

struct work {
  point pos;
  int bn;
};

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  std::map<point,point> hm;
  std::map<int,int> bs;
  std::vector<point> offsets = { {-1,0}, {0,-1}, {1,0}, {0,1}};

  std::string line;
  int x(0), y(0);
  while (std::cin >> line) {
    for(char c: line) hm[{x++, y}] = {(int)c-48, 0};
    y++; x = 0;
  }

  for(auto &m: hm) {
    bool lowpoint(true);
    for (auto o: offsets) {
      point nk = {m.first.first+o.first, m.first.second+o.second};
      if (hm.find(nk) != hm.end()) lowpoint &= (m.second.first < hm[nk].first);
    }
    if (lowpoint) res.first += (m.second.first + 1);
  }

  for(auto &m: hm) 
    if (m.second.first != 9 && m.second.second == 0) {
      std::queue<work> q;
      q.push({m.first,  static_cast<int>(bs.size())});
      bs[bs.size()] = 0;
      while (!q.empty()) {
        auto wk = q.front();
        q.pop();
        if (hm[wk.pos].second != wk.bn) bs[wk.bn] = bs[wk.bn]+1;
        hm[wk.pos].second = wk.bn;
        for(point o : offsets) {
          point nk = {wk.pos.first+o.first, wk.pos.second+o.second};
          if (hm.find(nk) != hm.end()) if (hm[nk].first < 9 && hm[nk].second != wk.bn) q.push({nk, wk.bn});
        }
      }
    }

  int l0(0), l1(0), l2(0);
  for(auto l: bs) {
    if      (l0 <= l.second) { l2 = l1; l1 = l0; l0 = l.second; }
    else if (l1 <= l.second) { l2 = l1; l1 = l.second; }
    else if (l2 <= l.second) { l2 = l.second; }
  }

  res.second = l0*l1*l2;
  return res;
}