#include <sstream>
#include <algorithm>
#include <cmath>
#include <map>
#include "../common/lib.h"

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
    if      (x1 == x2) for (int yy = std::min(y1,y2); yy <= std::max(y1,y2); yy++) ventlines_a[x1+(yy*10000)]++;
    else if (y1 == y2) for (int xx = std::min(x1,x2); xx <= std::max(x1,x2); xx++) ventlines_a[xx+(y1*10000)]++;
    else if (abs(x1-x2) == abs(y1-y2)) {
      for (int x = 0; x <= abs(x1-x2); x++) 
        ventlines_b[x1+(x*copysign(1, x2-x1))+((y1+(x*copysign(1, y2-y1)))*10000)]++;
    };
  }
  
  for (auto k: ventlines_a) {
    ventlines_b[k.first] += k.second;
    if (k.second > 1) res.first++;
  }
  for (auto k: ventlines_b) if (k.second > 1) res.second++;
  return res;
}
