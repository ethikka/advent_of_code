#include <sstream>
#include <map>
#include <vector>
#include <numeric>
#include "../common/lib.h"
#include "../common/circularlist.h"

struct gs {
  std::string pos;
  int64_t count;
};

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  tbb::circularlist<char> instructions;
  std::vector<gs> ghostspots;
  std::map<std::string,std::pair<std::string,std::string>> mappings;
  std::string a, al, ar;
  std::cin >> a;

  for (int i = 0; i < a.size(); i++) instructions.enqueue(a[i]);
  while (std::cin >> a >> al >> al >> ar ) {
    mappings[a] = {al.substr(1, 3), ar.substr(0,3)};
    if (a[2] == 'A') ghostspots.push_back(gs{a,0});
  }

  int64_t count(0);
  a = "AAA";

  while ((res.first == 0 || res.second == 0) && ++count) {
    char dir = instructions.front_and_next();
    if (res.first == 0) if ((a = dir == 'L' ? mappings[a].first : mappings[a].second) == "ZZZ") res.first = count;

    if (res.second == 0) {
      int64_t r(1);
      for (auto &s: ghostspots) {
        if (s.count == 0) if ((s.pos = dir == 'L' ? mappings[s.pos].first : mappings[s.pos].second)[2] == 'Z') s.count = count;
        if (r != 0) r = std::lcm(r, s.count);
      }
      res.second = r;
    }
  }
  return res;
}