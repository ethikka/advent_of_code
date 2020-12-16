#include <sstream>
#include <vector>
#include <algorithm>
#include "../common/lib.h"

struct rule {
  std::string name;
  int range1l, range1h;
  int range2l, range2h;
};

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;

  std::vector<rule> rules;
  std::vector<std::vector<int>> tickets;
  std::string line;
  std::stringstream sl;
  std::vector<int> props;
  std::string nums;
  
  while (std::getline(std::cin, line)) {
    if (line.length() == 0) break;
    sl.clear();
    sl << line;
    std::string rulename, range1, range2;
    sl >> rulename >> range1 >> range2 >> range2;
    int pos1(range1.find('-')), pos2(range2.find('-'));
    rulename.pop_back();
    rule r {.name = rulename, .range1l = std::stoi(range1.substr(0,pos1)), .range1h = std::stoi(range1.substr(pos1+1)), .range2l = std::stoi(range2.substr(0,pos2)), .range2h = std::stoi(range2.substr(pos2+1))};
    rules.push_back(r);    
  }

  std::getline(std::cin, line);
  std::getline(std::cin, line);
  sl.clear();
  sl << line;
  while (std::getline(sl, nums, ',')) 
    props.push_back(std::stoi(nums));
  if (props.size() > 0)
    tickets.push_back(props);

  std::getline(std::cin, line);
  std::getline(std::cin, line);
  while (std::getline(std::cin, line)) {
    sl.clear();
    sl << line;
    props.clear();
    bool add(true);
    while (std::getline(sl, nums, ',')) {
      props.push_back(std::stoi(nums));
      int num = props.back();
      bool good(false);
      for(auto r: rules) 
        good |= (num >= r.range1l && num <= r.range1h) || (num >= r.range2l && num <= r.range2h);
      if (!good) res.first += num;
      add &= good;
    }
    if (add)
      tickets.push_back(props);
  }
  
  std::vector<std::string> rulemappings;
  rulemappings.resize(rules.size());
  int d(0);
  while (d < rules.size()) 
    for (auto r: rules) 
      if (std::find(rulemappings.begin(), rulemappings.end(), r.name) == rulemappings.end()) {
        int cnt(0), id(0);
        std::string name;
        for (int i = 0; i < tickets[0].size(); i++) {
          bool maybe(true);
          if (rulemappings[i] == "") 
            for (auto v: tickets) 
              maybe &= (v[i] >= r.range1l && v[i] <= r.range1h) || (v[i] >= r.range2l && v[i] <= r.range2h);
            if (maybe) {
              cnt++;
              id = i;
              name = r.name;
            }
        }
        if (cnt == 1) {
          rulemappings[id] =  name;
          d++;
        }
      }

  res.second = 1;
  for (int i = 0; i < rulemappings.size(); i++)
    if (rulemappings[i].substr(0, 9) == "departure")
      res.second *= tickets[0][i];

  return res;
}