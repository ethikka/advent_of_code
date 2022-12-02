#include <sstream>
#include "../common/lib.h"

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  char p1, p2;
  int p1i, p2i;
  while (std::cin >> p1 >> p2) {
    int p1i = (int)p1-'A'+1;
    int p2i = (int)p2-'X'+1;

    if (((p2i-p1i) == 1) || ((p2i-p1i) == -2)) res.first += 6;
    if (p1i == p2i) res.first += 3;
    res.first += p2i;

    switch(p2i) {
      case 1: res.second += p1i-1; if (p1i == 1) res.second += 3; break;
      case 2: res.second += p1i+3; break;
      case 3: res.second += p1i+7; if (p1i == 3) res.second -= 3; break;
    }
  }
  return res;
}