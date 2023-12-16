#include <sstream>
#include <vector>
#include <queue>
#include <algorithm>
#include "../common/lib.h"
#include "../common/grid2d.h"
#include "../common/vector2.h"

std::vector<vector2> loops(tbb::grid2d<char> grid, vector2 pos, direction d) {
  std::vector<vector2> loop;
  do {
    loop.push_back(pos);
    auto r = grid.get_element((pos + offsets[d]));
    switch (r.second) {
      case '|': if (d == north || d == south)                                  pos = r.first;   else return {};   break;
      case '-': if (d ==  east || d ==  west)                                  pos = r.first;   else return {};   break;
      case 'L': if (d == south || d ==  west) { d = d == south ? east : north; pos = r.first; } else return {};   break;
      case 'J': if (d == south || d ==  east) { d = d == south ? west : north; pos = r.first; } else return {};   break;
      case '7': if (d == north || d ==  east) { d = d == north ? west : south; pos = r.first; } else return {};   break;
      case 'F': if (d == north || d ==  west) { d = d == north ? east : south; pos = r.first; } else return {};   break;
      case '.':                                                                                      return {};   break;
      case 'S':                                                                                      return loop; break;
    }
  }
  while (true);
}

int64_t calc_area(tbb::grid2d<char> grid) {
  int64_t res(0);
  for (int y = 0; y <= grid._y; y++) {
    int parity(0);
    char enterPipe;
    for (int x = 0; x <= grid._x; x++) {
      if (grid.has_element({x, y})) {
        char c = grid.get_element({x, y}).second;
        switch (c) {
          case '|': ++parity; break;
          case 'F': 
          case 'L': enterPipe = c; break;
          case '7': parity += (enterPipe == 'L'); break;
          case 'J': parity += (enterPipe == 'F'); break;
        }
      } else if (parity % 2) ++res;
    }
  }
  return res;
};

char hotfix_start(tbb::grid2d<char> grid, vector2 pos) {
  std::string s[4] = {"|F7" , "-7J", "|JL", "-FL"};
  bool n[4];
  for(auto d: {north,east,south,west}) n[d] = (s[d].find(grid.get_element(pos+offsets[d]).second) != std::string::npos);
  std::string rr = "   L |F  J- 7";
  return rr.substr(n[0]+n[1]*2+n[2]*4+n[3]*8, 1)[0];
};

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  tbb::grid2d<char> grid, loopgrid;
  grid.read();
  auto m = grid.find_elements('S');
  vector2 tl(m.front()), br(m.front());
  if (m.size() == 1) {
    for(auto d: {north,east,south,west}) {
      auto r = loops(grid, m.front(), d);
      if (r.size() > 0) {
        vector2 tl = r.front();
        for(auto rr: r) {
          loopgrid.place_element({rr.x, rr.y}, grid.get_element(rr).second);
          if (tl > rr) tl = rr;
        }
        loopgrid.place_element(m.front(), hotfix_start(loopgrid, m.front()));
        return {loopgrid.count()/2, calc_area(loopgrid)};
      }
    }
  }
  return {0,0};
}