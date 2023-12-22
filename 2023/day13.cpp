#include <sstream>
#include <map>
#include <cmath>
#include "../common/lib.h"
#include "../common/grid2d.h"
#include "../common/vector2.h"

class notes {
  private:
    bool _empty;
    std::map<int,int64_t> x, y;
  public:
    notes() {
      tbb::grid2d<char> g;
      g.read('.');
      for(auto e: g.get_raw()) { x[e.first.x] += pow(2,e.first.y); y[e.first.y] += pow(2,e.first.x); }
      _empty = (g._x == 0);
    };

    int64_t find_reflection(std::map<int,int64_t> m) {
      for (int xt = 1; xt < m.size(); xt++)
        if (bool mirror = (m[xt] == m[xt-1])) {
          for (int xmt = 0; xmt < xt; xmt++) if (xt+xmt < m.size()) mirror &= (m[xt+xmt] == m[xt-xmt-1]);
          if (mirror) return xt;
        }
      return 0;
    };

    int64_t find_smudge_reflection(std::map<int,int64_t> m) {
      for (int xt = 1; xt < m.size(); xt++) {
        auto r = m[xt] xor m[xt-1];
        if (r && !(r & (r-1))) {
          bool mirror(true);
          for (int xmt = 1; xmt < xt; xmt++) if (xt+xmt < m.size()) mirror &= (m[xt+xmt] == m[xt-xmt-1]);
          if (mirror) return xt;
        } else if (m[xt] == m[xt-1]) {
          bool mirror(true), smudge(false);
          for (int xmt = 1; xmt < xt && mirror; xmt++) {
            if (xt+xmt < m.size() && xt-xmt-1 >= 0) {
              auto r = m[xt+xmt] xor m[xt-xmt-1];
              if (r && !(r & (r-1))) {
                if (smudge) mirror = false;
                smudge = true;
              } else if (m[xt+xmt] != m[xt-xmt-1]) mirror = false;
            }
          }
          if (mirror && smudge) return xt;
        }
      }
      return 0;
    };

    int64_t mirrornumber() { return find_reflection(x)+(find_reflection(y)*100); };
    int64_t unsmudge() { return find_smudge_reflection(x)+(find_smudge_reflection(y)*100); };
    bool empty() { return _empty; }
};

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  while (true) {
    notes n;
    res.first += n.mirrornumber();
    res.second += n.unsmudge();
    if (n.empty()) return res;
  };
}