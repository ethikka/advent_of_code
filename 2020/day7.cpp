#include <sstream>
#include <set>
#include <vector>
#include <iterator>
#include <map>
#include <queue>
#include "../common/lib.h"

struct workload {
  int multiplier;
  std::string key;
};

std::pair<int,int> solve() {
  std::pair<int,int> res; 
  std::string line;

  std::map<std::string, std::set<std::string>> bag_in;
  std::map<std::string, std::vector<std::pair<int,std::string>>> bag_contains;

  while (std::getline(std::cin, line)) {
    std::istringstream iss(line); 
    std::vector<std::string> result{ std::istream_iterator<std::string>(iss), {} };
    if (result.size() > 7) {
      for (int i = 4; i < result.size(); i += 4) {
        std::string bag(""), in("");
        in = std::string(result[i+1]+" "+result[i+2]);
        bag = std::string(result[0]+" "+result[1]);
        bag_in[in].insert(bag);
        bag_contains[bag].push_back(std::make_pair(std::stoi(result[i]), in));
      }
    }
  }

  std::queue<std::string> work;
  std::set<std::string> bags;
  work.push("shiny gold");
  while(!work.empty()) {
    std::string key = work.front();
    for (auto s: bag_in[key]) {
      bags.insert(s);
      work.push(s);
    }
    work.pop();
  }
  res.first = bags.size();

  std::queue<workload> work2;
  work2.push({1, "shiny gold"});
  while(!work2.empty()) {
    workload l = work2.front();
    for (auto s: bag_contains[l.key]) {
      res.second += (s.first * l.multiplier);
      work2.push({l.multiplier*s.first, s.second});
    }
    work2.pop();
  }  

  return res;
}

int main(void) {
  post_solve(solve());
}
