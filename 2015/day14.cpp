#include <sstream>
#include <vector>
#include "../common/lib.h"

struct reindeer {
  int spd;
  int dur;
  int rest;
  int score;
  int dist;
};

int distance(reindeer r, int cycle) {
  int cycles = (cycle/(r.dur+r.rest));
  int dist = r.spd*r.dur*cycles;
  int remainder = cycle-((r.dur+r.rest)*cycles);
  dist += (remainder < r.dur) ? r.spd*remainder : r.spd*r.dur;
  return dist;
};

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res {0, 0};
  std::string d;
  int spd, dur, rest;
  std::vector<reindeer> rl;

  while (std::cin >> d >> d >> d >> spd >> d >> d >> dur >> d >> d >> d >> d >> d >> d >> rest >> d) rl.push_back({spd, dur, rest, 0, 0});

  for (int i = 1; i <= 2503; i++) {
    for(auto& r: rl) {
      r.dist = distance(r, i);
      if (res.first < r.dist) res.first = r.dist;
    }
    for(auto& r: rl) {
      if (r.dist == res.first) r.score = r.score+1;
      if (res.second < r.score) res.second = r.score;
    }
  }
  return res;
}