#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <fstream>
#include <algorithm>

int main() {
  std::vector<std::string> input { std::istream_iterator<std::string> { std::cin }, {}};
  int footage = 0;
  int ribbon = 0;
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
    footage += ((2 * x * y) + (2 * y * z) + (2 * z * x)) + (x * y);
    ribbon += ((2 * x) + (2 * y) + (x * y * z));
    std::cout << "##" << footage << ":" << ribbon << std::endl;
  }
  std::cout << "Elves need " << footage << " square feet of wrapping paper" << std::endl;
  std::cout << "They'll also need " << ribbon << " feet of ribbon" << std::endl;
}
