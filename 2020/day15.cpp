#include <sstream>
#include <vector>
#include "../common/lib.h"

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  uint32_t turn(0), lastnum(0);  
  std::vector<long> turns;
  std::vector<int> spoken;

  turns.resize(30000000);
  spoken.resize(30000000);
  for (auto i: {5,1,9,18,13,8,0}) {
    turns[i] = ++turn;
    turns[i] = (turns[i] << 32) + turn;
    spoken[i]++;
    lastnum = i; 
  }
  while (turn++ < 30000000) {
    int first, second;
    second = (turns[lastnum]);
    first = (turns[lastnum] >> 32);

    if (spoken[lastnum] == 1) { // first time spoken
      turns[lastnum] = (turns[lastnum] << 32) + turns[lastnum];
      spoken[lastnum]++;
      lastnum = 0;
    } else 
      lastnum = second - first;
    turns[lastnum] = (turns[lastnum] << 32) + turn;
    spoken[lastnum]++;
    if (turn == 2020)
      res.first = lastnum;
  }
  res.second = lastnum;
  return res;
}