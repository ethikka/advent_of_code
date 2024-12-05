#include <sstream>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include "../common/lib.h"

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  std::string line;

  std::map<int,std::set<int>> rules;

  while (std::getline(std::cin,line) && line.size() > 0) {
    int spl = line.find('|');
    rules[std::stoi(line.substr(spl+1))].emplace(std::stoi(line.substr(0,spl)));
  }

  while (std::getline(std::cin,line) && line.size() > 0) {
    std::istringstream ssl(line);
    std::vector<int> upd;
    int num;
    char discard;
    while (!ssl.eof()) {
      ssl >> num >> discard;
      upd.push_back(num);
    }

    bool valid = true;
    for(int i = 0; i < upd.size()-1; i++) valid &= (rules[upd.at(i+1)].find(upd.at(i)) != rules[upd.at(i+1)].end());

    if (valid) res.first += upd[(upd.size()-1)/2];
    else {
      std::map<int,int> fc, cf;
      for(auto i: upd) { fc[i] = 0; for (auto e: rules[i]) if (std::find(upd.begin(), upd.end(), e) != upd.end()) fc[i]++; }
      for (auto e: fc) cf[e.second] = e.first;
      auto it = cf.begin();
      res.second += std::next(it, (cf.size()-1)/2)->second;
    }
  }

  return res;
}