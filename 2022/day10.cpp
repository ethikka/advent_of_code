#include <sstream>
#include <map>
#include "../common/lib.h"

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  std::string instr;
  int val, timeptr(2), tval(1);
  std::map<int,int> timeline;
  timeline[1] = 1;
  while (std::cin >> instr) {
    if (instr[0] == 'n') timeline[timeptr++] = tval;
    else { 
      std::cin >> val;
      timeline[timeptr++] = tval;
      tval += val;
      timeline[timeptr++] = tval;
    };
  }
  for (auto i: {20, 60, 100, 140, 180, 220}) res.first += ( i*timeline[i]);

  if (!output_for_timing) {
    int pxl(0);
    for (auto spr: timeline) {
      std::cout << ((abs(spr.second-(pxl++)) < 2) ? "|": " ");
      pxl %= 40;
      if (pxl == 0) std::cout << std::endl;
    }
  }              
  std::cout << std::endl;
  return res;
}