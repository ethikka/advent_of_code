#include <sstream>
#include <vector>
#include "../common/lib.h"

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  std::vector<std::string> grid;
  std::string line;
  while (std::cin >> line) grid.push_back(line);

  for (int x = 0; x < grid[0].size(); x++)
    for (int y = 0; y < grid.size(); y++) {
      bool visible(true);
      char h(grid[y][x]);
      if (x == 0 || y == 0) res.first++; else {
        for (int xl = x-1; xl >= 0             && visible; xl--) visible &= (grid[ y][xl] < h); if (visible) res.first++; else { visible = true;
        for (int xr = x+1; xr < grid[0].size() && visible; xr++) visible &= (grid[ y][xr] < h); if (visible) res.first++; else { visible = true;
        for (int yu = y-1; yu >= 0             && visible; yu--) visible &= (grid[yu][ x] < h); if (visible) res.first++; else { visible = true;
        for (int yd = y+1; yd < grid.size()    && visible; yd++) visible &= (grid[yd][ x] < h); if (visible) res.first++; }}}
      }

      int xl(x-1), tl(0); do { tl++; if (grid[ y][xl--] >= h) break; } while (xl >= 0);
      int xr(x+1), tr(0); do { tr++; if (grid[ y][xr++] >= h) break; } while (xr < grid[0].size());
      int yu(y-1), tu(0); do { tu++; if (grid[yu--][ x] >= h) break; } while (yu >= 0);
      int yd(y+1), td(0); do { td++; if (grid[yd++][ x] >= h) break; } while (yd < grid.size());
      std::uintmax_t tmp(tl*tr*tu*td);
      if (res.second < tmp) res.second = tmp;

    }
  return res;
}