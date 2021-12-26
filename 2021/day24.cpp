#include <sstream>
#include <vector>
#include <stack>
#include "../common/lib.h"

struct mapping {
  int l;
  int r;
  int ldiff;
};

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  int ln(0), tmp(0);
  std::vector<int> a,b,c;
  while (std::cin.peek() != EOF) {
    std::string s,discard;
    std::getline(std::cin, s);
    if ((ln % 18) ==  4) { std::stringstream(s) >> discard >> discard >> tmp; a.push_back(tmp); }
    if ((ln % 18) ==  5) { std::stringstream(s) >> discard >> discard >> tmp; b.push_back(tmp); }
    if ((ln % 18) == 15) { std::stringstream(s) >> discard >> discard >> tmp; c.push_back(tmp); }
    ln++;
  }

  std::vector<mapping> mappings;
  std::stack<int> st;
  for (int i = 0; i < 14; i++) 
    if (a[i] == 1) st.push(i);
    else {         int p = st.top(); st.pop(); mappings.push_back({i, p, c[p]+b[i]}); }

  int n_a[14], n_b[14];

  for(auto a: mappings) {
    if (a.ldiff < 0) { n_a[a.r] = 9; n_a[a.l] = 9+a.ldiff; n_b[a.l] = 1; n_b[a.r] = 1-a.ldiff;}
    else             { n_a[a.l] = 9; n_a[a.r] = 9-a.ldiff; n_b[a.r] = 1; n_b[a.l] = 1+a.ldiff;}
  }

  for(int i = 0; i < 14; i++) {
    res.first += n_a[i]; res.second += n_b[i];
    if (i != 13) { res.first *= 10; res.second *= 10; }
  }
  return res;
}