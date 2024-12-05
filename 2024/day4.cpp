#include <sstream>
#include "../common/lib.h"
#include "../common/grid2d.h"

tbb::grid2d<char> grid, ng;

bool c(vector2<int> pos, char c) { return (grid.get_element(pos).second == c); }
bool co(vector2<int> pos, vector2<int> os) { 
  char cc[2];
  cc[0] = grid.get_element(pos+os).second;
  cc[1] = grid.get_element(pos+(os*-1)).second;
  return ((cc[0] == 'M' && cc[1] == 'S') || (cc[1] == 'M' && cc[0] == 'S'));
}

int find_xmas(vector2<int> pos) {
  int r = 0;
  for(auto d: diagonals) if (c(pos+d,'M') && c(pos+(d*2),'A') && c(pos+(d*3),'S')) r++;
  return r;
};

int find_mas(vector2<int> pos) {
    int r = 0;
    if (co(pos, diagonals[1]) && co(pos, diagonals[3])) r++;
    return r;
};

std::pair<std::uintmax_t,std::uintmax_t> solve() {
    std::pair<std::uintmax_t,std::uintmax_t> res;
    grid.read();
    for(auto e: grid.find_elements('X')) res.first += find_xmas(e);
    for(auto e: grid.find_elements('A')) res.second += find_mas(e);
    return res;
}