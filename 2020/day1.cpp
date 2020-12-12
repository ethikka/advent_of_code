#include <sstream>
#include <iostream>
#include <string>
#include <chrono>
#include <vector>
#include <cppitertools/combinations.hpp>
#include "../common/lib.h"

std::pair<int,int> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  int line(0);
  std::vector<int> e;
  while (std::cin >> line) 
    e.push_back(line);

  for (auto&& i: iter::combinations(e, 3)) {
    if (i[0] + i[1] == 2020 && res.first == 0)
      res.first = i[0] * i[1];
    if (i[0] + i[1] + i[2] == 2020 && res.second == 0)
      res.second = i[0] * i[1] * i[2];
  }
  return res;
}

int main(int argc, char *argv[]) {
  output_for_timing = (argc > 1);
  post_solve(solve());
}

