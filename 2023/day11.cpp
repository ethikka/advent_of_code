#include <sstream>
#include <set>
#include <vector>
#include <algorithm>
#include <iterator>
#include "../common/lib.h"
#include "../common/grid2d.h"
#include "../common/vector2.h"

vector2 move_vector(vector2 origin, std::set<int> cols, std::set<int> rows, int64_t offset = 1) {
    vector2 res(origin);
    for (auto c: cols) if (origin.x > c) res.x += offset;
    for (auto r: rows) if (origin.y > r) res.y += offset;
    return res;
};

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  tbb::grid2d<char> grid;
  std::map<vector2,vector2> offsets;
  grid.read('.');

  std::set<int> cols, rows;
  int i(0), j(0);
  std::generate_n(std::inserter(cols, cols.begin()), grid._x, [&i](){ return i++; });
  std::generate_n(std::inserter(rows, rows.begin()), grid._y, [&j](){ return j++; });
  
  for(auto g: grid.get_raw()) { cols.erase(g.first.x); rows.erase(g.first.y); }

  std::vector<vector2> g;
  for(auto e: grid.get_raw()) g.push_back(e.first);
  for (int i = 0; i < g.size(); i++) 
    for (int j = i+1; j < g.size(); j++) {
      res.first  += (move_vector(g.at(i), cols, rows,      1) - move_vector(g.at(j), cols, rows,      1)).manhattanlength();
      res.second += (move_vector(g.at(i), cols, rows, 999999) - move_vector(g.at(j), cols, rows, 999999)).manhattanlength();
    }
  return res;
}