#include <sstream>
#include <unordered_map>
#include <vector>
#include "../common/lib.h"

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  uint32_t turn(0), lastnum(0);  
  std::vector<long> turns;

  turns.resize(30000000);
  for (auto i: {5,1,9,18,13,8,0}) {
    turns[i] = ++turn;
    turns[i] = (turns[i] << 32) + turn;
    lastnum = i; 
  }
  
  while (turn++ < 30000000) {
    int first, second, tst;
    second = (turns[lastnum]);
    first = (turns[lastnum] >> 32);

    if (first == 0) { // first time spoken
      turns[lastnum] = (turns[lastnum] << 32) + second;
      lastnum = 0;
    } else 
      lastnum = second - first;
    turns[lastnum] = (turns[lastnum] << 32) + turn;
    if (turn == 2020)
      res.first = lastnum;
  }
  res.second = lastnum;
  return res;
}