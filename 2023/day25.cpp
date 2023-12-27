#include <sstream>
#include <map>
#include <vector>
#include <limits.h>
#include <algorithm>
#include "../common/lib.h"

int64_t s(std::map<std::string, std::vector<std::string>> lines, std::map<std::string,int> lookup) {
  int64_t res;
  int N = lookup.size();
  std::vector<std::vector<int>> wiring(N, std::vector<int>(N, 0));
  for(auto l: lines) for (auto ll: l.second) wiring[lookup[l.first]][lookup[ll]] = wiring[lookup[ll]][lookup[l.first]] = 1; 

  std::pair<int, std::vector<int>> best = {INT_MAX, {}};
  int n = (int)(wiring).size();
    
  std::vector<std::vector<int>> co(n);
  for(int64_t i = 0; i < n; ++i) co[i] = {(int)i};
  for(int64_t ph = 1; ph < n; ++ph) {
    std::vector<int> w = wiring[0];
    size_t s = 0, t = 0;

    for(int64_t it = 0; it < n-ph; ++it) { // O(V^2) -> O(E log V) with prio. queue
      w[t] = INT_MIN;
      s = t, t = std::max_element(begin(w), end(w)) - w.begin();
      for(int64_t i = 0; i < n; ++i) w[i] += wiring[t][i];
    }
    best = std::min(best, {w[t] - wiring[t][t], co[t]});
    co[s].insert(co[s].end(), begin(co[t]), end(co[t]));
    for(int64_t i = 0; i < n; ++i) wiring[s][i] += wiring[t][i];
    for(int64_t i = 0; i < n; ++i) wiring[i][s] = wiring[s][i];
    wiring[0][t] = INT_MIN;
  }
  return best.second.size() * (wiring.size()-best.second.size());
}

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::map<std::string,int> lookup;
  std::map<std::string, std::vector<std::string>> lines;
  std::string line, w, ct;
  while (std::getline(std::cin, line)) { 
    std::istringstream ssl(line); 
    ssl >> w; 
    w.pop_back(); 
    if (lookup.find(w) == lookup.end()) lookup[w] = lookup.size();
    while (ssl >> ct) { 
      if (lookup.find(ct) == lookup.end()) lookup[ct] = lookup.size();
      lines[w].push_back(ct);
    }
  }
 
  return {s(lines, lookup), 0};
}