#include <sstream>
#include <vector>
#include <iterator>
#include "../common/lib.h"

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res{0,0};
  std::vector<char> input { std::istream_iterator<char>{ std::cin }, {}};
  int steps = 0;
  for(auto& i: input) {
    if      (i == '(') res.first++;
    else if (i == ')') res.first--;
    steps++;
    if (res.first == -1 && res.second == 0)
      res.second = steps;
  }
  return res;
}
