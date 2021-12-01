#include <sstream>
#include <vector>
#include "../common/lib.h"

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  std::vector<int> w;
  int cur;
  while (std::cin >> cur) w.push_back(cur);
  for (int i = 1; i < w.size(); i++) {
    if (w[i-1] < w[i]) res.first++;
    if (w[i-3] < w[i] && i > 2) res.second++;
  }
  return res;
}