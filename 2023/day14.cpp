#include <sstream>
#include <set>
#include <map>
#include "../common/lib.h"
#include "../common/grid2d.h"
#include "../common/vector2.h"

enum direction { north, west, south, east };
vector2 offsets[4] = {{0,-1},{-1,0},{0,1},{1,0}};

class table {
  private:
    tbb::grid2d<char> grid;
    std::pair<std::uintmax_t,std::uintmax_t> res;
  public:
    table() { grid.read('.'); };

    int64_t value() { int64_t res(0); for(auto e: grid.get_raw()) if (e.second == 'O') res += ((grid._y+1)-e.first.y); return res; }

    bool in_bounds(vector2 v) { return ((v.x >= 0 && v.y >= 0 && v.x <= grid._x && v.y <= grid._y)); };

    void tilt(direction d) {
      vector2 from{0,0}, to{0,0};
      switch (d) {
        case north: from = {0,0};              to = {grid._x, grid._y}; break;
        case east:  from = {grid._x, 0};       to = {0, grid._y};       break;
        case south: from = {grid._x, grid._y}; to = {0, 0};             break;
        case west:  from = {0, grid._y};       to = {grid._x, 0};       break;
      };
      for(auto e: lerp(from, to)) {
        vector2 tmpv = e;
        if (grid.get_element(e).second == 'O') {
          while (in_bounds(tmpv+offsets[d]) && grid.get_element(tmpv+offsets[d]).second == '.') tmpv = tmpv + offsets[d];
          if (in_bounds(tmpv)) grid.move_element(e, tmpv);
        }
      }
    };

    void cycle(int n) {
      tilt(north);
      res.first = value();
      for(auto d: {west,south,east}) tilt(d);

      std::map<std::tuple<int64_t,int64_t,int64_t>,int64_t> history;
      int64_t c(0),cmo(0),cmt(0);
      bool ff(false);
      for (int i = 1; i < n; i++) {
        cmt = cmo; cmo = c;
        for(auto d: {north, west, south, east}) tilt(d);
        if (c && cmo && cmt && !ff) {
          std::tuple<int64_t,int64_t,int64_t> key{c,cmo,cmt};
          if (ff = history.find(key) != history.end()) i = i+(((n-i)/(i-history[{key}]))*(i-history[{key}]));
          history[{c,cmo,cmt}] = i;
        }
        c = value();
      }
      res.second = value();
    };

    std::pair<std::uintmax_t,std::uintmax_t> result() { return res; }
};

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  table t;
  t.cycle(1000000000);
  return t.result();
}