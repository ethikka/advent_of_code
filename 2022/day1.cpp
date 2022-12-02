#include <sstream>
#include <set>
#include "../common/lib.h"

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  std::string line;
  std::set<int> calories;
  int total(0);

  while (std::getline(std::cin, line)) {
    if (line.length() == 0) {
      calories.emplace(total);
      total = 0;
    } else total += std::stoi(line);
  }

  int c(0);
  res.first = *calories.rbegin();
  for(auto i = calories.rbegin(); c < 3; c++) 
    res.second += *(i++);
  return res;
}