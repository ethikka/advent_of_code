#include <sstream>
#include "../common/lib.h"
#include "../common/grid2d.h"

tbb::grid2d<char> grid;

bool co(vector2<int> pos, vector2<int> os) { 
  char cc[2];
  cc[0] = grid.get_element(pos+os).second;
  cc[1] = grid.get_element(pos+(os*-1)).second;
  return ((cc[0] == 'M' && cc[1] == 'S') || (cc[1] == 'M' && cc[0] == 'S'));
}

std::pair<std::uintmax_t,std::uintmax_t> solve() {
    std::pair<std::uintmax_t,std::uintmax_t> res;
    grid.read();
    for(auto e: grid.find_elements('X')) for(auto d: diagonals) if (grid.test_element(e+d, 'M') && grid.test_element(e+(d*2), 'A') && grid.test_element(e+(d*3), 'S')) res.first++;
    for(auto e: grid.find_elements('A')) if (co(e, diagonals[1]) && co(e, diagonals[3])) res.second++;
    return res;
}