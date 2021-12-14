#include <sstream>
#include <vector>
#include "../common/lib.h"

std::vector<std::string> input;

int binstr_to_int(std::string s) {
  int mult(1), res(0);
  for (int d = s.size()-1; d >= 0; d--) {
    if (s[d] == '1') res += mult;
    mult *= 2;
  }
  return res;
}

int f(bool oxy) {
  std::string str("");
  for (int d = 0; d < (int)input.front().size(); d++) {
    int cnt(0), tot(0);
    for(auto l: input) {
      if (l.rfind(str, 0) == 0) {
        if (l[d] == '1') cnt++;
        tot++;
      }
    }
    if (tot == 1) {
      for(auto l: input) 
        if (l.rfind(str, 0) == 0) 
          return binstr_to_int(l);
    } else if ((oxy && (cnt*2 < tot)) || (!oxy && (cnt*2 >= tot))) str += '0'; else str += '1';
  }
  return binstr_to_int(str);
}

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::string line;
  while (std::cin >> line) input.push_back(line);

  int64_t gam(0), eps(0), mult(1);
  for (int d = input.front().size()-1; d >= 0; d--) {
    int t_gam(0), t_eps(0);
    for(auto l: input) 
      if (l[d] == '0') t_eps++; else t_gam++;
    if (t_gam*2 > (int)input.size()) gam += mult;
    if (t_eps*2 > (int)input.size()) eps += mult;
    mult *= 2;
  }
  return {gam*eps, f(true)*f(false)};
}
