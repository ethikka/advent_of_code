#include <sstream>
#include <queue>
#include <vector>
#include <cmath>
#include "../common/lib.h"

std::uintmax_t p1_wins(0), p2_wins(0);

int path_mult[10] = { -1, -1, -1, 1, 3, 6, 7, 6, 3, 1 };

void quantum(int p1, int p2, int p1score, int p2score, bool turn_p1, std::uintmax_t multiplier) {
  if (turn_p1) {
    for (int i = 3; i <= 9; ++i) {
      int np1 = (p1 + i) % 10; if (np1 == 0) np1 = 10;
      int np1s = p1score + np1;
      if   (np1s >= 21) p1_wins += (multiplier * path_mult[i]);
      else quantum(np1, p2, np1s, p2score, !turn_p1, multiplier * path_mult[i]);
    }
  } else {
    for (int i = 3; i <= 9; ++i) {
      int np2 = (p2 + i) % 10; if (np2 == 0) np2 = 10;
      int np2s = p2score + np2;
      if   (np2s >= 21) p2_wins += (multiplier * path_mult[i]);
      else quantum(p1, np2, p1score, np2s, !turn_p1, multiplier * path_mult[i]);
    }
  }  
}

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;

  //int p1(4), p2(8); // test input
    int p1(4), p2(9); 
  int die(1), rolls(0);
  int64_t score_p1(0), score_p2(0);

  while (score_p1 < 1000 && score_p2 < 1000) {
    p1 = (p1 + (++die*3)) % 10; if (p1 == 0) p1 = 10;
    die = (die+2) % 100; if (die == 0) die = 100;
    score_p1 += p1;
    rolls += 3;
    if (score_p1 >= 1000)
      res.first = score_p2 * rolls;
    else {
      int m = (++die*3);
      p2 = (p2 + m) % 10; if (p2 == 0) p2 = 10;
      die = (die+2) % 100; if (die == 0) die = 100;
      score_p2 += p2;
      rolls += 3;
      if (score_p2 >= 1000)
        res.first = score_p1 * rolls;
    }
  }
  quantum(4, 9, 0, 0, true, 1);
  res.second = std::max(p1_wins, p2_wins);
  return res;
}
