#include <sstream>
#include <map>
#include <algorithm>
#include <cmath>
#include "../common/lib.h"

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  std::string line;
  std::getline(std::cin, line);
  std::replace(line.begin(), line.end(), ',', ' '); 
  std::istringstream ssl(line);
  int depth(0);
  std::map<int, int> depths;
  while (ssl >> depth) if (depths.count(depth) == 0) depths[depth] = 1; else depths[depth]++;

  int wm(0), t(0);
  for (auto d: depths) { wm += (d.first * d.second); t += d.second; }
  for (auto d: depths) for (int i = 0; i < std::abs((wm/t)-d.first); i++) res.second += ((i+1)* d.second);

  int maxd(depths.rbegin()->first);
  for (int cd = (depths.begin()->first); cd <= maxd; cd++) {
    uintmax_t fuel(0);
    for (auto d: depths) fuel += (std::abs(cd-d.first) * d.second);
    res.first = (res.first == 0) ? fuel : std::min(res.first, fuel);
  }
  return res;
}
