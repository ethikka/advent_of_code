#include <sstream>
#include <set>
#include <map>
#include <vector>
#include <algorithm>
#include "../common/lib.h"

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  std::string line;
  std::vector<std::string> badgedetector;

  const std::string priorities = ".abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

  while (std::cin >> line) {
    std::set<char> cc;
    badgedetector.push_back(line);
    for (int i = 0; i < line.length()/2; i++) cc.emplace(line[i]);
    for (int i = line.length()/2; i < line.length(); i++) {
      if (cc.find(line[i]) != cc.end()) {
        res.first += priorities.find(line[i]);  
        cc.erase(line[i]);
      }
    }

    if (badgedetector.size() == 3) {
      std::set<char> pp, po;
      for (int i = 0; i < badgedetector[0].length(); i++) pp.emplace(badgedetector[0][i]);
      for (int i = 0; i < badgedetector[1].length(); i++) if (pp.find(badgedetector[1][i]) != pp.end()) po.emplace(badgedetector[1][i]);
      for (int i = 0; i < badgedetector[2].length(); i++) if (po.find(badgedetector[2][i]) != po.end()) { res.second += priorities.find(badgedetector[2][i]); break; }
      badgedetector.clear();
    }
  }
  return res;
}
