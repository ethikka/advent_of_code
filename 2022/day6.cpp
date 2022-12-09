#include <sstream>
#include <vector>
#include <set>
#include "../common/lib.h"

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  char c;
  std::vector<char> chars;
  while (std::cin >> c) chars.push_back(c);
  for (int i = 0; i < chars.size()-3 && (res.first == 0 || res.second == 0); i++) {
    std::set<char> test;
    for (int x = 0; x < 14; x++) {
      if (test.count(chars.at(i+x)) > 0) break;
      test.emplace(chars.at(i+x));
      if (x == 3 && test.size() == 4 && res.first == 0) res.first = i+4;
    }
    if (test.size() == 14 && res.second == 0) res.second = i+14;
  }
  return res;
}