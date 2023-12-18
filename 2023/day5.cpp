#include <sstream>
#include <vector>
#include <cmath>
#include <queue>
#include "../common/lib.h"

struct remap {
  int64_t src_start;
  int64_t src_end;
  int64_t offset;
};

class range {
public:
  int64_t start;
  int64_t end;
  range(int64_t s, int64_t e) { start = s; end = e; };
  std::vector<range> remap(std::vector<remap> rules) {
    std::vector<range> newranges;
    std::queue<range> q;
    q.emplace(range{start,end});
    while (!q.empty()) {
      range rr = q.front(); q.pop();
      bool d(false);
      for(auto r: rules) {
        if (!(r.src_end < rr.start || r.src_start > rr.end))
        {
          d |= true;
          if (rr.end > r.src_end) q.emplace(range{r.src_end+1, rr.end});
          if (rr.start < r.src_start) q.emplace(range{rr.start, r.src_start-1});
          newranges.push_back(range{std::max(rr.start, r.src_start)+r.offset, (std::min(rr.end, r.src_end)+r.offset)});
          //newranges.push_back(range{rr.start+r.offset, rr.end+r.offset});
        }
      }
      if (!d) newranges.push_back(rr);
    }
    return newranges;
  };
};

uintmax_t s(std::vector<range> seeds, std::vector<remap> rules[8]) {
  uintmax_t res(999999999999);
  for (int i = 0; i < 8; i++) {
    std::vector<range> tmp;
    for (auto s: seeds) {
      auto n = s.remap(rules[i]);
      for(auto nn: n) {
        tmp.push_back(nn);
        if (i == 7 && res > nn.start) res = nn.start;
      }
    }
    seeds = tmp;
  }
  return res;
};

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::vector<range> seeds_a, seeds_b;
  std::vector<remap> remap_rules[8];
  std::string line, d;
  int64_t n1, n2, n3, idx(-1);

  std::getline(std::cin, line);
  std::istringstream ssl(line);
  ssl >> d;
  while (ssl >> n1 >> n2) { seeds_a.push_back(range{n1, n1}); seeds_a.push_back(range{n2, n2}); seeds_b.push_back(range{n1, n1+n2}); }

  while (std::getline(std::cin, line)) {
    if (line.size() == 0) { idx++; std::getline(std::cin, line); }
    else { std::istringstream ssl(line); ssl >> n2 >> n1 >> n3; remap_rules[idx].push_back({n1, n1+n3-1, n2-n1}); }
  }

  return { s(seeds_a, remap_rules), s(seeds_b, remap_rules)};
}