#include <iterator>
#include <vector>
#include "../common/lib.h"

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res{0,0};
  std::vector<std::string> input { std::istream_iterator<std::string> { std::cin }, {}};
  for(auto& i: input) {
    std::string line(i);
    std::replace(line.begin(), line.end(), 'x', ' ');
    std::istringstream ssl(line);
    int w, h, l, x, y, z;
    ssl >> w >> h >> l;
    x = w < h ? ( w < l ? w : l) : ( h < l ? h : l);
    y = w <= h ? (l <= w ? w : l <= h ? l : h ) : l <= h ? h : l <= w ? l : w;
    z = w > h ? ( w > l ? w : l) : ( h > l ? h : l);
    if ((x+y+z) != (w+h+l))
      std::cout << w << ":" << h << ":" << l << ":" << x << ":" << y << ":" << z << std::endl; 
    res.first += ((2 * x * y) + (2 * y * z) + (2 * z * x)) + (x * y);
    res.second += ((2 * x) + (2 * y) + (x * y * z));
  }
  return res;
}