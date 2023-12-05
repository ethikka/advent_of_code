#include <sstream>
#include <vector>
#include <cmath>
#include <algorithm>
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
        }
      }
      if (!d) newranges.push_back(rr);
    }
    return newranges;
  };
};

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  std::vector<range> seeds_a;
  std::vector<range> seeds_b;
  std::vector<remap> remap_rules[8];
  
  std::string line, d;
  int64_t n1, n2, n3;
  int idx(-1);
  std::getline(std::cin, line);
  std::istringstream ssl(line);
  ssl >> d;
  while (ssl >> n1 >> n2) {
    seeds_a.push_back(range{n1, n1});
    seeds_a.push_back(range{n2, n2});
    seeds_b.push_back(range{n1, n1+n2});
  }

  while (std::getline(std::cin, line)) {
    if (line.size() == 0) { idx++; std::getline(std::cin, line); } 
    else {
      std::istringstream ssl(line);
      ssl >> n2 >> n1 >> n3;
      remap_rules[idx].push_back({n1, n1+n3-1, n2-n1});
    }
  }

  for (int i = 0; i < 8; i++) {
    std::vector<range> tmp_a, tmp_b;
    for (auto &s: seeds_a) {
      auto n = s.remap(remap_rules[i]);
      tmp_a.insert(tmp_a.end(), n.begin(), n.end());
    }
    seeds_a = tmp_a;

    for (auto &s: seeds_b) {
      auto n = s.remap(remap_rules[i]);
      tmp_b.insert(tmp_b.end(), n.begin(), n.end());
    }
    seeds_b = tmp_b;
  }

  for(auto s: seeds_a) if (res.first == 0 || res.first > s.start) res.first = s.start;
  for(auto s: seeds_b) if (res.second == 0 || res.second > s.start) res.second = s.start;
  return res;
}