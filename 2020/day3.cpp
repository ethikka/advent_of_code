#include <sstream>
#include <vector>
#include <map>
#include "../common/lib.h"

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  char inp;
  int x(0), y(0), width(0);
  std::map<std::pair<int,int>,char> map;
  while (std::cin >> std::noskipws >> inp) {
    switch(inp) {
      case '#': map[std::make_pair(y,x++)] = inp; break; /*tree*/
      case '\n': width = x; x = 0; y++; break; /*next line*/
      default: x++;
    }
  }

  int64_t tot(1);
  std::vector<std::tuple<int,int>> inputs({{1,1},{3,1},{5,1},{7,1},{1,2}});
  for(auto i: inputs) {
    int nx(0), hits(0);
    for (int ny = 0; ny <= y; ny += std::get<1>(i)) {
      if (map.find(std::make_pair(ny, nx % width)) != map.end()) hits++;
      nx += std::get<0>(i);
    }
    if (std::get<0>(i) == 3) res.first = hits;
    res.second *= hits;
  }
  return res;
}