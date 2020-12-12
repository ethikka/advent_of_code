#include <sstream>
#include <list>
#include <vector>
#include <cmath>
#include <cppitertools/combinations.hpp>
#include "../common/lib.h"

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  int PREAMBLE = 25;
  std::pair<std::uintmax_t,std::uintmax_t> res; 
  std::list<int> numbers;
  std::vector<int> hist_num;
  int inp;
  for (int i = 0; i < PREAMBLE; i++) {
    std::cin >> inp;
    numbers.push_back(inp);
    hist_num.push_back(inp);
  }

  while (std::cin >> inp) {
    bool makeable = false;
    for (auto&& i: iter::combinations(numbers, 2)) makeable |= (i[0] + i[1] == inp);
    if (!makeable) res.first = inp;

    numbers.push_back(inp);
    hist_num.push_back(inp);
    numbers.pop_front();
  }
    
  for(int i = 0, j = i, subtotal; i < hist_num.size() && res.second == 0; i++, j = i, subtotal = 0) {
    while (subtotal < res.first && j < hist_num.size()) 
      subtotal += hist_num[j++];

    if (subtotal == res.first) {
      int min(999999), max(0);
      for (int k = i; k < j; k++) {
        max = std::max(max, hist_num[k]);
        min = std::min(min, hist_num[k]);
      }
      res.second = (min + max);
    }
  }
  return res;
}