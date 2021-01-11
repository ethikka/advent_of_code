#include <bitset>
#include <algorithm>
#include <sstream>
#include <vector>
#include "../common/lib.h"

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  int b[20];
  int t[20]{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  int inp, idx(0);
  while (std::cin >> inp) b[idx++] = inp;
  idx = 0;
  for (int i = 0; i < 1048576; i++) { // 1048575 = 20 bits set to false
    std::bitset<20> bs(i);
    int total(0), c(0);
    for (int j = 0; j < 20; j++) if (bs[j]) { total += b[j]; c++; };
    if (total == 150) { t[c]++; idx++; }
  }
  for(int i = 0; i < 20; i++) if (t[i] > 0) return {idx, t[i]};
  return {0, 0};
}