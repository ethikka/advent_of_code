#include <sstream>
#include <vector>
#include <algorithm>
#include "../common/lib.h"

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  std::vector<int64_t> fish;
  for (int dd = 0; dd < 9; dd++) fish.push_back(0);
  std::string line;
  std::getline(std::cin, line);
  std::replace(line.begin(), line.end(), ',', ' '); 
  std::istringstream ssl(line);
  int age(0);
  while (ssl >> age) fish[age]++;

  int64_t nf[9];
  for (int days = 0; days < 256; days++) {
    for (int ii = 0; ii < 9; ii++) nf[ii] = 0;
    for (int ii = 0; ii < 9; ii++) {
      switch (ii) {
        case 0: nf[8] += fish[ii]; nf[6] = fish[ii]; break;
        default:
          nf[ii-1] += fish[ii];
      }
    }
    for (int ii = 0; ii < 9; ii++) fish[ii] = nf[ii];
    if (days == 79) for (int ii = 0; ii < 9; ii++) res.first += fish[ii];
  }
  for (int ii = 0; ii < 9; ii++) res.second += fish[ii];
  return res;
}