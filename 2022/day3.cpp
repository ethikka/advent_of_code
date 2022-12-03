#include <sstream>
#include <set>
#include <map>
#include <vector>
#include <algorithm>
#include "../common/lib.h"

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  std::string line;
  std::vector<std::set<char>> badgedetector;

  const std::string priorities = ".abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

  while (std::cin >> line) {
    std::set<char> left, right, v;
    std::set<char> uch;
    for(auto c: line) uch.emplace(c);
    badgedetector.push_back(uch);

    for (int i = 0; i < (line.length()/2); i++) {
      left.emplace(line[i]);
      right.emplace(line[line.length()-i-1]);
    }

    std::set_intersection(left.begin(), left.end(), right.begin(), right.end(), std::inserter(v, v.end()));
    for(auto a: v) res.first += priorities.find(a);

    if (badgedetector.size() == 3) {
      std::map<char,int> pp;
      for(int i = 0; i < 3; i++) for(auto c: badgedetector.at(i)) pp[c]++;
      for (auto p: pp) if (p.second == 3) res.second += priorities.find(p.first);
      pp.clear();
      badgedetector.clear();
    }
  }
  return res;
}