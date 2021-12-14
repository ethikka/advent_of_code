#include <sstream>
#include <map>
#include <cmath>
#include <limits>
#include "../common/lib.h"

std::uintmax_t diff(std::map<std::string, std::uintmax_t> chains, char b) {
  std::uintmax_t min(std::numeric_limits<uintmax_t>::max()), max(0);
  std::map<char,std::uintmax_t> fm;
  for (auto c: chains) fm[c.first[0]]+=c.second;
  fm[b]++;

  for(auto m: fm) {
    min = std::min(min, m.second);    
    max = std::max(max, m.second);
  }
  return max-min;
}

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  std::string start;
  std::cin >> start;
  std::map<std::string, std::string> rules;

  std::string l, r;
  while (std::cin >> l >> r >> r) rules[l] = r;

  std::map<std::string, std::uintmax_t> subchains;
  for (int i = 0; i < (int)start.size()-1; i++) subchains[start.substr(i,2)]++;

  for (int cnt = 0; cnt < 40; cnt++) {
    std::map<std::string, std::uintmax_t> newsubchains;
    for (auto c: subchains) {
      newsubchains[c.first[0]+rules[c.first]] += c.second;
      newsubchains[rules[c.first]+c.first[1]] += c.second;
    }
    subchains = newsubchains;
    if (cnt == 9) res.first = diff(subchains, start[start.size()-1]);
    if (cnt == 39) res.second = diff(subchains, start[start.size()-1]);
  }
  return res;
}