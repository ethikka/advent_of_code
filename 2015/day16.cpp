#include <sstream>
#include <iostream>
#include <vector>
#include <unordered_map>
#include "../common/lib.h"

struct aunt {
  int num;
  std::unordered_map<std::string,int> props;
  bool filtered;
  bool filtered_b;
};

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  std::string line, prop, val, d;
  aunt aunts[501];

  while (std::getline(std::cin, line)) {
    aunt tmp;
    std::stringstream sl(line);
    sl >> d >> d;
    d.pop_back();
    tmp.num = std::stoi(d);
    while (!sl.eof()) {
      sl >> prop >> val;
      prop.pop_back();
      if (val.back() == ',') val.pop_back();
      tmp.props[prop] = std::stoi(val);
    }
    tmp.filtered = false;
    tmp.filtered_b = false;
    aunts[tmp.num] = tmp;
  }

  for(auto t: std::vector<std::pair<std::string,int>>{{"children",3},{"cats",7},{"samoyeds",2},{"pomeranians",3},{"akitas",0},{"vizslas",0},{"goldfish",5},{"trees",3},{"cars",2},{"perfumes",1}}) {
    for (int i = 1; i < 501; i++) {
      if (aunts[i].props.contains(t.first)) {
        aunts[i].filtered |= (aunts[i].props[t.first] != t.second);
        if (t.first == "cats" || t.first == "trees") aunts[i].filtered_b |= (aunts[i].props[t.first] <= t.second);
        else if (t.first == "pomeranians" || t.first == "goldfish") aunts[i].filtered_b |= (aunts[i].props[t.first] >= t.second);
        else aunts[i].filtered_b |= (aunts[i].props[t.first] != t.second);
      }
    }
  }

  for (int i = 1; i < 501; i++) {
    if (!aunts[i].filtered) res.first = i;
    if (!aunts[i].filtered_b) res.second = i;
  }

  return res;
}



