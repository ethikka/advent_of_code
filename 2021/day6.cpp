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

  for (int days = 0; days < 256; days++) {
    int nf(fish[0]);
    for (int ii = 0; ii < 8; ii++) fish[ii] = fish[ii+1];
    fish[6] += fish[8] = nf;
    if (days == 79) for (auto f: fish) res.first += f;
  }
  for (auto f: fish) res.second += f;
  return res;
}