#include <sstream>
#include <vector>
#include "../common/lib.h"

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  
  int64_t start(0);
  std::cin >> start;
  std::string line;
  std::vector<std::pair<int,int>> busses;
  int cnt(0);
  while (std::getline(std::cin, line, ',')) {
    if (line != "x")
      busses.push_back(std::make_pair(std::stoi(line),cnt));
    cnt++;
  }  

  int least(start);
  for (auto i: busses) {
    if ((i.first - (start % i.first)) < least) {
      least = (i.first - (start % i.first));
      res.first = i.first * least;
    }
  }

  int64_t lb(busses[0].first), timestamp(1 - (1 % busses[0].first));
  for (int i = 1; i < busses.size(); i++) {
    while ((timestamp+busses[i].second) % busses[i].first != 0)
      timestamp += lb;
    lb *= busses[i].first;
  }
  res.second = timestamp;
  return res;
}