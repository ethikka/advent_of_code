#include <sstream>
#include <map>
#include <vector>
#include "../common/lib.h"

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  int turn(0), lastnum(0);  
  std::vector<std::pair<int,int>> turns;
  std::vector<int> spoken;

  turns.resize(30000000);
  spoken.resize(30000000);
  for (auto i: {5,1,9,18,13,8,0}) {
    turns[i].first = ++turn;
    turns[i].second = turn;
    spoken[i]++;
    lastnum = i; 
  }
  while (turn < 30000000) {
    turn++;
    if (spoken[lastnum] == 1) { // first time spoken
      turns[lastnum].first = turns[lastnum].second;
      spoken[lastnum]++;
      lastnum = 0;
    } else {
      lastnum = turns[lastnum].second - turns[lastnum].first;
    }
    turns[lastnum].first = turns[lastnum].second;
    turns[lastnum].second = turn;
    spoken[lastnum]++;
    if (turn == 2020)
      res.first = lastnum;
  }
 
  res.second = lastnum;
  return res;
}