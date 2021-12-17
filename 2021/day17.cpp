#include <sstream>
#include <cmath>
#include "../common/lib.h"

int min_x(209), max_x(238), min_y(-86), max_y(-59);

std::uintmax_t sim(int dx, int dy) {
  int x(0), y(0), res(0);
  while(x <= max_x && y >= min_y){
    x += dx;
    y += dy--;
    res = std::max(res, y);
    if(dx)  dx--;
    if(min_x <= x && x <= max_x && min_y <= y && y <= max_y) return res;
    }
  return -1;
};

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  for(int y = min_y; y <= -min_y; y++)
    for(int x = 0; x <= max_x; x++){
      std::uintmax_t r = sim(x, y);
      if (r != -1) {
        res.second++;
        res.first = std::max(res.first, r);
      }
    }
  return res;
}