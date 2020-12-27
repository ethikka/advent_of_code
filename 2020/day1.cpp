#include <sstream>
#include <set>
#include "../common/lib.h"

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  int line(0);
  std::set<int64_t> e;
  while (std::cin >> line)
    e.insert(line);

  for (int i: e) {
    if (e.count(2020-i)) res.first = i * (2020-i);
    for (int ii: e) {
      if (res.first && res.second) return res;
      if (i != ii && e.count(2020-i-ii)) res.second = i*ii*(2020-i-ii);
    }
  }
  return res;
}