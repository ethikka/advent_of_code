#include <sstream>
#include <queue>
#include <map>
#include "../common/lib.h"

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;

  std::priority_queue<int> left, right;
  std::map<int,int> freqmap;
  int l, r;

  while (!std::cin.eof()) {
    std::cin >> l >> r;
    left.emplace(l);
    right.emplace(r);
    freqmap[r]++;
  }

  while(!left.empty()) {
    res.first += abs(left.top()-right.top());
    res.second += left.top() * freqmap[left.top()];
    left.pop();
    right.pop();
  }
  return res;
}