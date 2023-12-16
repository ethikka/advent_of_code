#include <sstream>
#include <queue>
#include <set>
#include <thread>
#include <cmath>
#include "../common/lib.h"
#include "../common/grid2d.h"
#include "../common/vector2.h"

struct work {
  vector2 pos;
  direction dir;
};

std::uintmax_t energized_tiles(tbb::grid2d<char> g, vector2 v, direction d) {
  std::map<vector2,std::set<direction>> visited;
  std::queue<work> q;

  q.emplace(work{v,d});
  while (!q.empty()) {
    auto w = q.front(); q.pop();
    bool do_it = (visited.find(w.pos) == visited.end());
    if (!do_it) do_it = (visited[w.pos].find(w.dir) == visited[w.pos].end());
    do_it &= g.in_bounds(w.pos);
    if (do_it) {
      visited[w.pos].emplace(w.dir);
      if (g.has_element(w.pos)) {
        char c = g.get_element(w.pos).second;
        switch(c) {
          case '|' : if (w.dir == east  || w.dir == west)  {q.emplace(work{w.pos+offsets[north],north}); q.emplace(work{w.pos+offsets[south],south}); } else q.emplace(work{w.pos+offsets[w.dir],w.dir}); break;
          case '-' : if (w.dir == north || w.dir == south) {q.emplace(work{w.pos+offsets[east],east});  q.emplace(work{w.pos+offsets[west],west});  } else q.emplace(work{w.pos+offsets[w.dir],w.dir}); break;
          default:
            q.emplace(work{w.pos+offsets[deflections[c][w.dir]],deflections[c][w.dir]});
        }
      } else
        q.emplace(work{w.pos+offsets[w.dir], w.dir});
    } 
  }
  return visited.size();
};

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  tbb::grid2d<char> g;
  g.read('.');
  res.first = energized_tiles(g, {0,0},east);
  for (int xx = 0; xx <= g._x; xx++) { res.second = std::max(res.second, energized_tiles(g, {xx,0},south)); 
                                       res.second = std::max(res.second, energized_tiles(g, {xx,g._y},north)); }
  for (int yy = 0; yy <= g._y; yy++) { res.second = std::max(res.second, energized_tiles(g, {0,yy},east));  
                                       res.second = std::max(res.second, energized_tiles(g, {g._x,yy},west)); }  
  return res;
}