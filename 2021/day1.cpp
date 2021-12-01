#include <sstream>
#include "../common/lib.h"

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;

  int cur(0), cnt(0);
  int w[2001];
  for(int i=0; i < 2000; i++) w[i] = 0;
  
  while (std::cin >> cur) {
    if (w[cnt+1] < cur && cnt > 0) res.first++;
    w[cnt] += cur;
    w[cnt+1] += cur;
    w[2+cnt++] += cur;
  }

  for(int i=3; i < 2000; i++) 
    if (w[i-1] < w[i]) res.second++;

  return res;
}