#include <sstream>
#include "../common/lib.h"

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  char p1, p2;
  while (std::cin >> p1 >> p2) {
    if ((p1 == 'A' && p2 == 'Y') || (p1 == 'B' && p2 == 'Z') || (p1 == 'C' && p2 == 'X')) res.first += 6;
    if ((p1 == 'A' && p2 == 'X') || (p1 == 'B' && p2 == 'Y') || (p1 == 'C' && p2 == 'Z')) res.first += 3;
    res.first += (int)p2-'X'+1;

    int p1i = (int)p1-'A'+1;
    switch(p2) {
      case 'X': res.second += 0 + p1i-1; if (p1i == 1) res.second += 3; break;
      case 'Y': res.second += 3 + p1i; break;
      case 'Z': res.second += 6 + p1i+1; if (p1i == 3) res.second -= 3; break;
    }
  }
  return res;
}