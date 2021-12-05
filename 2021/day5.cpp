#include <sstream>
#include <algorithm>
#include <cmath>
#include <map>
#include "../common/lib.h"

bool check_collinear(int x, int y, int x1, int y1, int x2, int y2){
  // https://en.wikipedia.org/wiki/Collinearity
  return (x * (y1 - y2) + x1 * (y2 - y) + x2 * (y - y1)) == 0;
}

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  std::map<int,int> ventlines_a, ventlines_b;

  std::string line;
  while (std::getline(std::cin, line)) {
    int x1(0),x2(0),y1(0),y2(0);
    std::string discard;
    std::replace(line.begin(), line.end(), ',', ' '); 
    std::istringstream ssl(line);
    ssl >> x1 >> y1 >> discard >> x2 >> y2;
    for (int xx = std::min(x1,x2); xx <= std::max(x1,x2); xx++) 
      for (int yy = std::min(y1,y2); yy <= std::max(y1,y2); yy++) {
        if (x1 == x2 || y1 == y2) ventlines_a[xx+(yy*1000)]++; 
        if (x1 == x2 || y1 == y2 || check_collinear(xx, yy, x1, y1, x2, y2)) ventlines_b[xx+(yy*1000)]++; 
      }
  }
  for (auto k: ventlines_a) if (k.second > 1) res.first++;
  for (auto k: ventlines_b) if (k.second > 1) res.second++;
  return res;
}